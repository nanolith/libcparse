/**
 * \file tools/import_enum/src/scan_input_and_write_output.c
 *
 * \brief Scan the input file and write the output file.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/event.h>
#include <libcparse/event/identifier.h>
#include <libcparse/event/raw_integer.h>
#include <libcparse/event_handler.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "import_enum_internal.h"

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_identifier;
CPARSE_IMPORT_event_raw_integer;

static int scanner_event_callback(import_enum_config* config, const event* ev);
static int process_eof_event(import_enum_config* config, const event* ev);
static int process_preprocessor_begin_event(
    import_enum_config* config, const event* ev);
static int process_preprocessor_end_event(
    import_enum_config* config, const event* ev);
static int process_left_brace_event(
    import_enum_config* config, const event* ev);
static int process_right_brace_event(
    import_enum_config* config, const event* ev);
static int process_comma_event(import_enum_config* config, const event* ev);
static int process_equal_assign_event(
    import_enum_config* config, const event* ev);
static int process_enum_keyword_event(
    import_enum_config* config, const event* ev);
static int process_identifier_event(
    import_enum_config* config, const event* ev);
static int process_raw_integer_event(
    import_enum_config* config, const event* ev);
static int process_unknown_event(import_enum_config* config, const event* ev);
static int insert_enum(import_enum_config* config);
static int save_identifier(import_enum_config* config, const event* ev);
static int save_integer(import_enum_config* config, const event* ev);

/**
 * \brief Scan the input file, writing enumeration details to the output file.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int scan_input_and_write_output(import_enum_config* config)
{
    int retval, release_retval;
    event_handler eh;

    /* create an event handler for preprocessor scanner events. */
    retval =
        event_handler_init(
            &eh, (event_callback_fn)&scanner_event_callback, config);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* subscribe to preprocessor scanner events. */
    retval = abstract_parser_preprocessor_scanner_subscribe(config->ap, &eh);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_eh;
    }

    /* run the scanner. */
    retval = abstract_parser_run(config->ap);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_eh;
    }

    /* reverse the list for use. */
    retval = enum_item_list_reverse(config);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_eh;
    }
 
    /* display all of the enums. */
    enum_item* tmp = config->head;
    while (NULL != tmp)
    {
        fprintf(
            stderr, "Found enum %s : %ld.\n", tmp->enum_name, tmp->enum_value);
        tmp = tmp->next;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_eh;

cleanup_eh:
    release_retval = event_handler_dispose(&eh);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Callback to receive events from the preprocessor scanner.
 *
 * \param config        The config for this instance.
 * \param ev            The event for this callback.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int scanner_event_callback(import_enum_config* config, const event* ev)
{
    int retval;

    /* get and decode the event type. */
    int event_type = event_get_type(ev);
    switch (event_type)
    {
        case CPARSE_EVENT_TYPE_EOF:
            return process_eof_event(config, ev);

        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_IF:
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_IFDEF:
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_IFNDEF:
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_ELIF:
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_ELSE:
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_ENDIF:
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_INCLUDE:
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_DEFINE:
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_UNDEF:
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_LINE:
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_ERROR:
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_PRAGMA:
            return process_preprocessor_begin_event(config, ev);

        case CPARSE_EVENT_TYPE_PP_END:
            return process_preprocessor_end_event(config, ev);

        case CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACE:
            return process_left_brace_event(config, ev);

        case CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACE:
            return process_right_brace_event(config, ev);

        case CPARSE_EVENT_TYPE_TOKEN_COMMA:
            return process_comma_event(config, ev);

        case CPARSE_EVENT_TYPE_TOKEN_EQUAL_ASSIGN:
            return process_equal_assign_event(config, ev);

        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ENUM:
            return process_enum_keyword_event(config, ev);

        case CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER:
            return process_identifier_event(config, ev);

        case CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER:
            return process_raw_integer_event(config, ev);

        default:
            return process_unknown_event(config, ev);
    }
}

/**
 * \brief Handle an EOF event in different scanner states.
 *
 * \param config        The config for this instance.
 * \param ev            The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_eof_event(import_enum_config* config, const event* ev)
{
    const cursor* pos = event_get_cursor(ev);

    switch (config->state)
    {
        /* we can ignore an EOF in these states. */
        case ENUM_PARSE_STATE_INIT:
        case ENUM_PARSE_STATE_IGNORE:
            return STATUS_SUCCESS;

        /* we are expecting a preprocessor end state here. */
        case ENUM_PARSE_STATE_IN_PREPROCESSOR_DIRECTIVE:
            fprintf(
                stderr,
                "error %s:%u Expecting end of preprocessor directive.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_PREPROCESSOR_END;

        case ENUM_PARSE_STATE_IN_ENUM:
            fprintf(
                stderr, "error %s:%u Expecting '{'.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_LEFT_BRACE;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK:
            fprintf(
                stderr, "error %s:%u Expecting '}'.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_RIGHT_BRACE;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM:
            fprintf(
                stderr, "error %s:%u Expecting '=', '}', or ','.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_EQUAL_RIGHT_BRACE_OR_COMMA;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_ASSIGN:
            fprintf(
                stderr, "error %s:%u Expecting integer constant.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_INTEGER;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_END:
            fprintf(
                stderr, "error %s:%u Expecting '}', or ','.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_RIGHT_BRACE_OR_COMMA;

        default:
            fprintf(
                stderr, "error %s:%u In unknown state.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_UNKNOWN_STATE;
    }
}

/**
 * \brief Handle a preprocessor begin event.
 *
 * \param config        The config for this instance.
 * \param ev            The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_preprocessor_begin_event(
    import_enum_config* config, const event* ev)
{
    const cursor* pos = event_get_cursor(ev);

    switch (config->state)
    {
        case ENUM_PARSE_STATE_IGNORE:
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_INIT:
            config->state = ENUM_PARSE_STATE_IN_PREPROCESSOR_DIRECTIVE;
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_IN_PREPROCESSOR_DIRECTIVE:
            fprintf(
                stderr, "error %s:%u Nested preprocessor directives.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_NESTED_PREPROCESSOR_DIRECTIVES;

        case ENUM_PARSE_STATE_IN_ENUM:
        case ENUM_PARSE_STATE_IN_ENUM_BLOCK:
        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM:
        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_ASSIGN:
        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_END:
            fprintf(
                stderr, "error %s:%u Unsupported directive location.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_UNSUPPORTED_DIRECTIVE_LOCATION;

        default:
            fprintf(
                stderr, "error %s:%u In unknown state.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_UNKNOWN_STATE;
    }
}

/**
 * \brief Handle a preprocessor end event.
 *
 * \param config        The config for this instance.
 * \param ev            The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_preprocessor_end_event(
    import_enum_config* config, const event* ev)
{
    const cursor* pos = event_get_cursor(ev);

    switch (config->state)
    {
        case ENUM_PARSE_STATE_IGNORE:
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_INIT:
        case ENUM_PARSE_STATE_IN_ENUM:
        case ENUM_PARSE_STATE_IN_ENUM_BLOCK:
        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM:
        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_ASSIGN:
        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_END:
            fprintf(
                stderr, "error %s:%u Unexpected preprocessor end events.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_UNEXPECTED_PREPROCESSOR_END;

        case ENUM_PARSE_STATE_IN_PREPROCESSOR_DIRECTIVE:
            config->state = ENUM_PARSE_STATE_INIT;
            return STATUS_SUCCESS;

        default:
            fprintf(
                stderr, "error %s:%u In unknown state.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_UNKNOWN_STATE;
    }
}

/**
 * \brief Handle a left brace event.
 *
 * \param config        The config for this instance.
 * \param ev            The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_left_brace_event(
    import_enum_config* config, const event* ev)
{
    const cursor* pos = event_get_cursor(ev);

    switch (config->state)
    {
        /* we can ignore a left brace in these states. */
        case ENUM_PARSE_STATE_INIT:
        case ENUM_PARSE_STATE_IN_PREPROCESSOR_DIRECTIVE:
        case ENUM_PARSE_STATE_IGNORE:
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_IN_ENUM:
            config->state = ENUM_PARSE_STATE_IN_ENUM_BLOCK;
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK:
            fprintf(
                stderr, "error %s:%u Expecting identifier or '}'.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_IDENTIFIER_OR_RIGHT_BRACE;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM:
            fprintf(
                stderr, "error %s:%u Expecting '}', or ','.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_RIGHT_BRACE_OR_COMMA;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_ASSIGN:
            fprintf(
                stderr, "error %s:%u Expecting integer constant.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_INTEGER;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_END:
            fprintf(
                stderr, "error %s:%u Expecting '}'.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_RIGHT_BRACE;

        default:
            fprintf(
                stderr, "error %s:%u In unknown state.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_UNKNOWN_STATE;
    }
}

/**
 * \brief Handle a right brace event.
 *
 * \param config        The config for this instance.
 * \param ev            The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_right_brace_event(
    import_enum_config* config, const event* ev)
{
    int retval;
    const cursor* pos = event_get_cursor(ev);

    switch (config->state)
    {
        /* we can ignore a left brace in these states. */
        case ENUM_PARSE_STATE_INIT:
        case ENUM_PARSE_STATE_IN_PREPROCESSOR_DIRECTIVE:
        case ENUM_PARSE_STATE_IGNORE:
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_IN_ENUM:
            fprintf(
                stderr, "error %s:%u Expecting '{'.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_LEFT_BRACE;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK:
            config->state = ENUM_PARSE_STATE_IGNORE;
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM:
        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_END:
            retval = insert_enum(config);
            if (STATUS_SUCCESS != retval)
            {
                return retval;
            }
            config->state = ENUM_PARSE_STATE_IGNORE;
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_ASSIGN:
            fprintf(
                stderr, "error %s:%u Expecting integer constant.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_INTEGER;

        default:
            fprintf(
                stderr, "error %s:%u In unknown state.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_UNKNOWN_STATE;
    }
}

/**
 * \brief Handle a comma event.
 *
 * \param config        The config for this instance.
 * \param ev            The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_comma_event(import_enum_config* config, const event* ev)
{
    int retval;
    const cursor* pos = event_get_cursor(ev);

    switch (config->state)
    {
        /* we can ignore a comma in these states. */
        case ENUM_PARSE_STATE_INIT:
        case ENUM_PARSE_STATE_IN_PREPROCESSOR_DIRECTIVE:
        case ENUM_PARSE_STATE_IGNORE:
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK:
            fprintf(
                stderr, "error %s:%u Expecting identifier.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_IDENTIFIER;

        case ENUM_PARSE_STATE_IN_ENUM:
            fprintf(
                stderr, "error %s:%u Expecting '{'.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_LEFT_BRACE;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM:
        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_END:
            retval = insert_enum(config);
            if (STATUS_SUCCESS != retval)
            {
                return retval;
            }
            config->state = ENUM_PARSE_STATE_IN_ENUM_BLOCK;
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_ASSIGN:
            fprintf(
                stderr, "error %s:%u Expecting integer constant.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_INTEGER;

        default:
            fprintf(
                stderr, "error %s:%u In unknown state.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_UNKNOWN_STATE;
    }
}

/**
 * \brief Handle a comma event.
 *
 * \param config        The config for this instance.
 * \param ev            The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_equal_assign_event(
    import_enum_config* config, const event* ev)
{
    int retval;
    const cursor* pos = event_get_cursor(ev);

    switch (config->state)
    {
        /* we can ignore an assignment in these states. */
        case ENUM_PARSE_STATE_INIT:
        case ENUM_PARSE_STATE_IN_PREPROCESSOR_DIRECTIVE:
        case ENUM_PARSE_STATE_IGNORE:
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_IN_ENUM:
            fprintf(
                stderr, "error %s:%u Expecting '{'.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_LEFT_BRACE;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK:
            fprintf(
                stderr, "error %s:%u Expecting '}'.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_RIGHT_BRACE;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM:
            config->state = ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_ASSIGN;
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_ASSIGN:
            fprintf(
                stderr, "error %s:%u Expecting integer constant.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_INTEGER;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_END:
            fprintf(
                stderr, "error %s:%u Expecting '}', or ','.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_RIGHT_BRACE_OR_COMMA;

        default:
            fprintf(
                stderr, "error %s:%u In unknown state.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_UNKNOWN_STATE;
    }
}

/**
 * \brief Handle a comma event.
 *
 * \param config        The config for this instance.
 * \param ev            The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_enum_keyword_event(
    import_enum_config* config, const event* ev)
{
    int retval;
    const cursor* pos = event_get_cursor(ev);

    switch (config->state)
    {
        /* we can ignore the enum keyword in these states. */
        case ENUM_PARSE_STATE_IN_PREPROCESSOR_DIRECTIVE:
        case ENUM_PARSE_STATE_IGNORE:
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_INIT:
            config->state = ENUM_PARSE_STATE_IN_ENUM;
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK:
            fprintf(
                stderr, "error %s:%u Expecting identifier.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_IDENTIFIER;

        case ENUM_PARSE_STATE_IN_ENUM:
            fprintf(
                stderr, "error %s:%u Expecting '{'.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_LEFT_BRACE;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM:
            fprintf(
                stderr, "error %s:%u Expecting '=', '}', or ','.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_EQUAL_RIGHT_BRACE_OR_COMMA;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_ASSIGN:
            fprintf(
                stderr, "error %s:%u Expecting integer constant.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_INTEGER;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_END:
            fprintf(
                stderr, "error %s:%u Expecting '}', or ','.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_RIGHT_BRACE_OR_COMMA;

        default:
            fprintf(
                stderr, "error %s:%u In unknown state.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_UNKNOWN_STATE;
    }
}

/**
 * \brief Handle a comma event.
 *
 * \param config        The config for this instance.
 * \param ev            The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_identifier_event(
    import_enum_config* config, const event* ev)
{
    int retval;
    const cursor* pos = event_get_cursor(ev);

    switch (config->state)
    {
        /* we can ignore an identifier in these states. */
        case ENUM_PARSE_STATE_INIT:
        case ENUM_PARSE_STATE_IN_PREPROCESSOR_DIRECTIVE:
        case ENUM_PARSE_STATE_IGNORE:
        case ENUM_PARSE_STATE_IN_ENUM:
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK:
            retval = save_identifier(config, ev);
            if (STATUS_SUCCESS != retval)
            {
                return retval;
            }
            config->state = ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM;
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM:
            fprintf(
                stderr, "error %s:%u Expecting '=', '}', or ','.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_EQUAL_RIGHT_BRACE_OR_COMMA;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_ASSIGN:
            fprintf(
                stderr, "error %s:%u Expecting integer constant.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_INTEGER;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_END:
            fprintf(
                stderr, "error %s:%u Expecting '}', or ','.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_RIGHT_BRACE_OR_COMMA;

        default:
            fprintf(
                stderr, "error %s:%u In unknown state.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_UNKNOWN_STATE;
    }
}

/**
 * \brief Handle a raw integer event.
 *
 * \param config        The config for this instance.
 * \param ev            The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_raw_integer_event(
    import_enum_config* config, const event* ev)
{
    int retval;
    const cursor* pos = event_get_cursor(ev);

    switch (config->state)
    {
        /* we can ignore an integer in these states. */
        case ENUM_PARSE_STATE_INIT:
        case ENUM_PARSE_STATE_IGNORE:
        case ENUM_PARSE_STATE_IN_PREPROCESSOR_DIRECTIVE:
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_IN_ENUM:
            fprintf(
                stderr, "error %s:%u Expecting '{'.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_LEFT_BRACE;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK:
            fprintf(
                stderr, "error %s:%u Expecting identifier.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_IDENTIFIER;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM:
            fprintf(
                stderr, "error %s:%u Expecting '=', '}', or ','.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_EQUAL_RIGHT_BRACE_OR_COMMA;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_ASSIGN:
            retval = save_integer(config, ev);
            if (STATUS_SUCCESS != retval)
            {
                return retval;
            }
            config->state = ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_END;
            return STATUS_SUCCESS;

        case ENUM_PARSE_STATE_IN_ENUM_BLOCK_ENUM_END:
            fprintf(
                stderr, "error %s:%u Expecting '}', or ','.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_EXPECTING_RIGHT_BRACE_OR_COMMA;

        default:
            fprintf(
                stderr, "error %s:%u In unknown state.\n",
                pos->file, pos->begin_line);
            return ERROR_IMPORT_ENUM_UNKNOWN_STATE;

    }
}

/**
 * \brief Handle an unknown event.
 *
 * \param config        The config for this instance.
 * \param ev            The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_unknown_event(import_enum_config* config, const event* ev)
{
    /* ignore all other events for now. */
    return STATUS_SUCCESS;
}

/**
 * \brief Insert an enumeration into the enumeration list.
 *
 * \param config        The config for this instance.
 * \param ev            The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int insert_enum(import_enum_config* config)
{
    int retval;

    /* insert the enumeration. */
    retval =
        enum_item_list_insert(config, config->enum_name, config->enum_value);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* increment the enum value. */
    config->enum_value += 1;

    /* we can clear the enum name, as it will no longer be needed. */
    free(config->enum_name);
    config->enum_name = NULL;

    return STATUS_SUCCESS;
}

/**
 * \brief Save an identifier for insertion later.
 *
 * \param config        The config for this instance.
 * \param ev            The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int save_identifier(import_enum_config* config, const event* ev)
{
    int retval;
    event_identifier* iev;

    /* free the name if set. */
    if (NULL != config->enum_name)
    {
        free(config->enum_name);
        config->enum_name = NULL;
    }

    /* attempt to downcast this event to an identifier event. */
    retval = event_downcast_to_event_identifier(&iev, (event*)ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* save the identifier name. */
    config->enum_name = strdup(event_identifier_get(iev));
    if (NULL == config->enum_name)
    {
        return ERROR_LIBCPARSE_OUT_OF_MEMORY;
    }

    /* success. */
    return STATUS_SUCCESS;
}

/**
 * \brief Save an integer for insertion later.
 *
 * \param config        The config for this instance.
 * \param ev            The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int save_integer(import_enum_config* config, const event* ev)
{
    int retval;
    event_raw_integer_token* rev;
    char* endval = NULL;
    const cursor* pos = event_get_cursor(ev);

    /* attempt to downcast this event to a raw integer token event. */
    retval = event_downcast_to_event_raw_integer_token(&rev, (event*)ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* get the string representation of this integer token. */
    const char* val = event_raw_integer_token_string_get(rev);

    /* attempt to convert this token to a long value. */
    long tmp = strtol(val, &endval, 0);

    /* was this successful? */
    if (val == endval || 0 != *endval)
    {
        fprintf(
            stderr, "error %s:%u Invalid integer: %s.\n",
            pos->file, pos->begin_line, val);
        return ERROR_IMPORT_ENUM_INVALID_INTEGER;
    }

    /* save this value. */
    config->enum_value = tmp;

    /* success. */
    return STATUS_SUCCESS;
}
