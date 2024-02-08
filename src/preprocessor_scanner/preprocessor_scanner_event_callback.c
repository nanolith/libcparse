/**
 * \file src/preprocessor_scanner/preprocessor_scanner_event_callback.c
 *
 * \brief The \ref preprocessor_scanner event handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>
#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/event/identifier.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/event_reactor.h>
#include <libcparse/file_position_cache.h>
#include <libcparse/preprocessor_scanner.h>
#include <libcparse/status_codes.h>
#include <libcparse/string_builder.h>
#include <libcparse/string_utils.h>

#include "preprocessor_scanner_internal.h"

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_identifier;
CPARSE_IMPORT_event_raw_character;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_file_position_cache;
CPARSE_IMPORT_preprocessor_scanner;
CPARSE_IMPORT_preprocessor_scanner_internal;
CPARSE_IMPORT_string_builder;
CPARSE_IMPORT_string_utils;

typedef int (*simple_event_ctor)(event*, const cursor*);

static int process_eof_event(
    preprocessor_scanner* scanner, const event* ev);
static int process_whitespace_event(
    preprocessor_scanner* scanner, const event* ev);
static int process_newline_event(
    preprocessor_scanner* scanner, const event* ev);
static int process_raw_character(
    preprocessor_scanner* scanner, const event* ev);
static bool char_is_alpha_underscore(const int ch);
static bool char_is_identifier(const int ch);
static int start_identifier(
    preprocessor_scanner* scanner, const event* ev, int ch);
static int continue_identifier(
    preprocessor_scanner* scanner, const event* ev, int ch);
static int end_identifier(preprocessor_scanner* scanner, const event* ev);
static int start_state(
    preprocessor_scanner* scanner, const event* ev, int state);
static int start_lt_lt(preprocessor_scanner* scanner, const event* ev);
static int start_gt_gt(preprocessor_scanner* scanner, const event* ev);
static int broadcast_simple_token(
    preprocessor_scanner* scanner, const event* ev, simple_event_ctor ctor);
static int broadcast_compound_token(
    preprocessor_scanner* scanner, const event* ev, simple_event_ctor ctor);
static int broadcast_cached_token_and_continue(
    preprocessor_scanner* scanner, const event* ev, simple_event_ctor ctor);
static int broadcast_pipe_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_caret_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_tilde_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_equal_compare_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_not_equal_compare_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_equal_assign_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_or_equal_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_xor_equal_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_compl_equal_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_bitshift_left_equal_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_bitshift_right_equal_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_bitshift_left_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_bitshift_right_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_less_than_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_greater_than_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_less_than_equal_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_greater_than_equal_token(
    preprocessor_scanner* scanner, const event* ev);
static int broadcast_not_token(
    preprocessor_scanner* scanner, const event* ev);

/**
 * \brief Event handler callback for \ref preprocessor_scanner_event_callback.
 *
 * \param context           The context for this handler (the
 *                          \ref preprocessor_scanner instance).
 * \param ev                An event for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(preprocessor_scanner_event_callback)(
    void* context, const CPARSE_SYM(event)* ev)
{
    preprocessor_scanner* scanner = (preprocessor_scanner*)context;

    switch (event_get_type(ev))
    {
        case CPARSE_EVENT_TYPE_EOF:
            return process_eof_event(scanner, ev);

        case CPARSE_EVENT_TYPE_TOKEN_WHITESPACE:
            return process_whitespace_event(scanner, ev);

        case CPARSE_EVENT_TYPE_TOKEN_NEWLINE:
            return process_newline_event(scanner, ev);

        case CPARSE_EVENT_TYPE_RAW_CHARACTER:
            return process_raw_character(scanner, ev);

        default:
            return STATUS_SUCCESS;
    }
}

/**
 * \brief Process an eof event.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The eof event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_eof_event(
    preprocessor_scanner* scanner, const event* ev)
{
    switch (scanner->state)
    {
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_IDENTIFIER:
            return end_identifier(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DASH:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_minus);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PLUS:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_plus);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STAR:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_star);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_SLASH:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_forward_slash);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PERCENT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_percent);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_AMPERSAND:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_ampersand);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PIPE:
            return broadcast_pipe_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CARET:
            return broadcast_caret_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_TILDE:
            return broadcast_tilde_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_EQUAL:
            return broadcast_equal_assign_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_NOT:
            return broadcast_not_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT:
            return broadcast_less_than_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT_LT:
            return broadcast_bitshift_left_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT:
            return broadcast_greater_than_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT_GT:
            return broadcast_bitshift_right_token(scanner, ev);

        default:
            return event_reactor_broadcast(scanner->reactor, ev);
    }
}

/**
 * \brief Process a whitespace event.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The whitespace event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_whitespace_event(
    preprocessor_scanner* scanner, const event* ev)
{
    switch (scanner->state)
    {
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_IDENTIFIER:
            return end_identifier(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DASH:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_minus);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PLUS:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_plus);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STAR:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_star);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_SLASH:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_forward_slash);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PERCENT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_percent);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_AMPERSAND:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_ampersand);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PIPE:
            return broadcast_pipe_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CARET:
            return broadcast_caret_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_TILDE:
            return broadcast_tilde_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_EQUAL:
            return broadcast_equal_assign_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_NOT:
            return broadcast_not_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT:
            return broadcast_less_than_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT_LT:
            return broadcast_bitshift_left_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT:
            return broadcast_greater_than_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT_GT:
            return broadcast_bitshift_right_token(scanner, ev);

        default:
            return STATUS_SUCCESS;
    }
}

/**
 * \brief Process a newline event.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The newline event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_newline_event(
    preprocessor_scanner* scanner, const event* ev)
{
    switch (scanner->state)
    {
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_IDENTIFIER:
            return end_identifier(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DASH:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_minus);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PLUS:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_plus);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STAR:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_star);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_SLASH:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_forward_slash);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PERCENT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_percent);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_AMPERSAND:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_ampersand);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PIPE:
            return broadcast_pipe_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CARET:
            return broadcast_caret_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_TILDE:
            return broadcast_tilde_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_EQUAL:
            return broadcast_equal_assign_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_NOT:
            return broadcast_not_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT:
            return broadcast_less_than_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT_LT:
            return broadcast_bitshift_left_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT:
            return broadcast_greater_than_token(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT_GT:
            return broadcast_bitshift_right_token(scanner, ev);

        default:
            return STATUS_SUCCESS;
    }
}

/**
 * \brief Process a raw character event.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_raw_character(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval;
    event_raw_character* rev;

    /* get the raw character event. */
    retval = event_downcast_to_event_raw_character(&rev, (event*)ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* get the raw character value. */
    int ch = event_raw_character_get(rev);

    /* decode the state. */
    switch (scanner->state)
    {
        case CPARSE_PREPROCESSOR_SCANNER_STATE_INIT:
            if (char_is_alpha_underscore(ch))
            {
                return start_identifier(scanner, ev, ch);
            }
            else
            {
                switch (ch)
                {
                    case '(':
                        return
                            broadcast_simple_token(
                                scanner, ev, &event_init_for_token_left_paren);

                    case ')':
                        return
                            broadcast_simple_token(
                                scanner, ev, &event_init_for_token_right_paren);

                    case '{':
                        return
                            broadcast_simple_token(
                                scanner, ev, &event_init_for_token_left_brace);

                    case '}':
                        return
                            broadcast_simple_token(
                                scanner, ev, &event_init_for_token_right_brace);

                    case '[':
                        return
                            broadcast_simple_token(
                                scanner, ev,
                                &event_init_for_token_left_bracket);

                    case ']':
                        return
                            broadcast_simple_token(
                                scanner, ev,
                                &event_init_for_token_right_bracket);

                    case ',':
                        return
                            broadcast_simple_token(
                                scanner, ev, &event_init_for_token_comma);

                    case ':':
                        return
                            broadcast_simple_token(
                                scanner, ev, &event_init_for_token_colon);

                    case ';':
                        return
                            broadcast_simple_token(
                                scanner, ev, &event_init_for_token_semicolon);

                    case '.':
                        return
                            broadcast_simple_token(
                                scanner, ev, &event_init_for_token_dot);

                    case '-':
                        return
                            start_state(
                                scanner, ev,
                                CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DASH);

                    case '+':
                        return
                            start_state(
                                scanner, ev,
                                CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PLUS);

                    case '*':
                        return
                            start_state(
                                scanner, ev,
                                CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STAR);

                    case '/':
                        return
                            start_state(
                                scanner, ev,
                                CPARSE_PREPROCESSOR_SCANNER_STATE_IN_SLASH);

                    case '%':
                        return
                            start_state(
                                scanner, ev,
                                CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PERCENT);

                    case '&':
                        return
                            start_state(
                                scanner, ev,
                                CPARSE_PREPROCESSOR_SCANNER_STATE_IN_AMPERSAND);

                    case '|':
                        return
                            start_state(
                                scanner, ev,
                                CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PIPE);

                    case '^':
                        return
                            start_state(
                                scanner, ev,
                                CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CARET);

                    case '~':
                        return
                            start_state(
                                scanner, ev,
                                CPARSE_PREPROCESSOR_SCANNER_STATE_IN_TILDE);

                    case '?':
                        return
                            broadcast_simple_token(
                                scanner, ev, &event_init_for_token_question);

                    case '=':
                        return
                            start_state(
                                scanner, ev,
                                CPARSE_PREPROCESSOR_SCANNER_STATE_IN_EQUAL);

                    case '!':
                        return
                            start_state(
                                scanner, ev,
                                CPARSE_PREPROCESSOR_SCANNER_STATE_IN_NOT);

                    case '<':
                        return
                            start_state(
                                scanner, ev,
                                CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT);

                    case '>':
                        return
                            start_state(
                                scanner, ev,
                                CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT);

                    default:
                        return
                            ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
                }
            }
            break;

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DASH:
            switch (ch)
            {
                case '>':
                    return
                        broadcast_compound_token(
                            scanner, ev, &event_init_for_token_arrow);

                case '=':
                    return
                        broadcast_compound_token(
                            scanner, ev, &event_init_for_token_minus_equal);

                case '-':
                    return
                        broadcast_compound_token(
                            scanner, ev, &event_init_for_token_decrement);

                default:
                    return
                        broadcast_cached_token_and_continue(
                            scanner, ev, &event_init_for_token_minus);
            }
            break;

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PLUS:
            switch (ch)
            {
                case '=':
                    return
                        broadcast_compound_token(
                            scanner, ev, &event_init_for_token_plus_equal);

                case '+':
                    return
                        broadcast_compound_token(
                            scanner, ev, &event_init_for_token_increment);

                default:
                    return
                        broadcast_cached_token_and_continue(
                            scanner, ev, &event_init_for_token_plus);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STAR:
            switch (ch)
            {
                case '=':
                    return
                        broadcast_compound_token(
                            scanner, ev, &event_init_for_token_times_equal);

                default:
                    return
                        broadcast_cached_token_and_continue(
                            scanner, ev, &event_init_for_token_star);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_SLASH:
            switch (ch)
            {
                case '=':
                    return
                        broadcast_compound_token(
                            scanner, ev, &event_init_for_token_div_equal);

                default:
                    return
                        broadcast_cached_token_and_continue(
                            scanner, ev, &event_init_for_token_forward_slash);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PERCENT:
            switch (ch)
            {
                case '=':
                    return
                        broadcast_compound_token(
                            scanner, ev, &event_init_for_token_mod_equal);

                default:
                    return
                        broadcast_cached_token_and_continue(
                            scanner, ev, &event_init_for_token_percent);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_AMPERSAND:
            switch (ch)
            {
                case '&':
                    return
                        broadcast_compound_token(
                            scanner, ev, &event_init_for_token_logical_and);

                case '=':
                    return
                        broadcast_compound_token(
                            scanner, ev, &event_init_for_token_and_equal);

                default:
                    return
                        broadcast_cached_token_and_continue(
                            scanner, ev, &event_init_for_token_ampersand);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PIPE:
            switch (ch)
            {
                case '|':
                    return
                        broadcast_compound_token(
                            scanner, ev, &event_init_for_token_logical_or);

                case '=':
                    return broadcast_or_equal_token(scanner, ev);

                default:
                    return broadcast_pipe_token(scanner, ev);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CARET:
            switch (ch)
            {
                case '=':
                    return broadcast_xor_equal_token(scanner, ev);

                default:
                    return broadcast_caret_token(scanner, ev);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_TILDE:
            switch (ch)
            {
                case '=':
                    return broadcast_compl_equal_token(scanner, ev);

                default:
                    return broadcast_tilde_token(scanner, ev);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_EQUAL:
            switch (ch)
            {
                case '=':
                    return broadcast_equal_compare_token(scanner, ev);

                default:
                    return broadcast_equal_assign_token(scanner, ev);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_NOT:
            switch (ch)
            {
                case '=':
                    return broadcast_not_equal_compare_token(scanner, ev);

                default:
                    return broadcast_not_token(scanner, ev);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT:
            switch (ch)
            {
                case '<':
                    return start_lt_lt(scanner, ev);

                case '=':
                    return broadcast_less_than_equal_token(scanner, ev);

                default:
                    return broadcast_less_than_token(scanner, ev);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT_LT:
            switch (ch)
            {
                case '=':
                    return broadcast_bitshift_left_equal_token(scanner, ev);

                default:
                    return broadcast_bitshift_left_token(scanner, ev);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT:
            switch (ch)
            {
                case '>':
                    return start_gt_gt(scanner, ev);

                case '=':
                    return broadcast_greater_than_equal_token(scanner, ev);

                default:
                    return broadcast_greater_than_token(scanner, ev);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT_GT:
            switch (ch)
            {
                case '=':
                    return broadcast_bitshift_right_equal_token(scanner, ev);

                default:
                    return broadcast_bitshift_right_token(scanner, ev);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_IDENTIFIER:
            if (char_is_identifier(ch))
            {
                return continue_identifier(scanner, ev, ch);
            }
            else
            {
                return end_identifier(scanner, ev);
            }
            break;

        default:
            return ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
    }
}

/**
 * \brief Return true if this is an alpha or underscore character.
 */
static bool char_is_alpha_underscore(const int ch)
{
    if (isalpha(ch) || '_' == ch)
    {
        return true;
    }

    return false;
}

/**
 * \brief Return true if this is an identifier character.
 */
static bool char_is_identifier(const int ch)
{
    if (char_is_alpha_underscore(ch) || isnumber(ch))
    {
        return true;
    }

    return false;
}

/**
 * \brief Start an identifier token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character for this identifier.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int start_identifier(
    preprocessor_scanner* scanner, const event* ev, int ch)
{
    int retval;

    /* get the cursor for this event. */
    const cursor* pos = event_get_cursor(ev);

    /* cache the location for the start of this event. */
    retval = file_position_cache_set(scanner->cache, pos->file, pos);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* add this character to the string builder. */
    retval = string_builder_add_character(scanner->builder, ch);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* we are now in the identifier state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_IN_IDENTIFIER;

    return STATUS_SUCCESS;
}

/**
 * \brief Continue an identifier token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character for this identifier.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int continue_identifier(
    preprocessor_scanner* scanner, const event* ev, int ch)
{
    int retval;

    /* extend the cached position to cover this character. */
    retval = file_position_cache_position_extend(scanner->cache, ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }
    
    /* add this character to the string builder. */
    retval = string_builder_add_character(scanner->builder, ch);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    return STATUS_SUCCESS;
}

/**
 * \brief End an identifier token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event that ends this identifier.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int end_identifier(preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    char* str;
    event_identifier iev;

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* Build a string for the identifier. */
    retval = string_builder_build(&str, scanner->builder);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the identifier event. */
    retval = event_identifier_init(&iev, pos, str);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_str;
    }

    /* broadcast this event. */
    retval =
        event_reactor_broadcast(
            scanner->reactor, event_identifier_upcast(&iev));
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_iev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* clear the string builder. */
    string_builder_clear(scanner->builder);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_iev;

cleanup_iev:
    release_retval = event_identifier_dispose(&iev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

cleanup_str:
    string_utils_string_release(str);

done:
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* if we succeed, then recursively process the new event on the way out. */
    return preprocessor_scanner_event_callback(scanner, ev);
}

/**
 * \brief Start a state.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event to process.
 * \param state             The state to start.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int start_state(
    preprocessor_scanner* scanner, const event* ev, int state)
{
    int retval;

    /* get the cursor for this event. */
    const cursor* pos = event_get_cursor(ev);

    /* cache the location for the start of this event. */
    retval = file_position_cache_set(scanner->cache, pos->file, pos);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* start the new state. */
    scanner->state = state;

    return STATUS_SUCCESS;
}

/**
 * \brief Start the lt lt state.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character for this identifier.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int start_lt_lt(preprocessor_scanner* scanner, const event* ev)
{
    int retval;

    /* extend the cached position to cover this character. */
    retval = file_position_cache_position_extend(scanner->cache, ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* we are now in the lt lt state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT_LT;

    return STATUS_SUCCESS;
}

/**
 * \brief Start the gt gt state.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character for this identifier.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int start_gt_gt(preprocessor_scanner* scanner, const event* ev)
{
    int retval;

    /* extend the cached position to cover this character. */
    retval = file_position_cache_position_extend(scanner->cache, ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* we are now in the gt gt state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT_GT;

    return STATUS_SUCCESS;
}

/**
 * \brief Broadcast a pipe token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The event to process AFTER this token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_pipe_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_pipe(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* if we succeed, then recursively process the new event on the way out. */
    return preprocessor_scanner_event_callback(scanner, ev);
}

/**
 * \brief Broadcast a caret token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The event to process AFTER this token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_caret_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_caret(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* if we succeed, then recursively process the new event on the way out. */
    return preprocessor_scanner_event_callback(scanner, ev);
}

/**
 * \brief Broadcast a tilde token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The event to process AFTER this token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_tilde_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_tilde(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* if we succeed, then recursively process the new event on the way out. */
    return preprocessor_scanner_event_callback(scanner, ev);
}

/**
 * \brief Broadcast an equal compare token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_equal_compare_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* extend the cached position to cover this character. */
    retval = file_position_cache_position_extend(scanner->cache, ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_equal_compare(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Broadcast a not equal compare token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_not_equal_compare_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* extend the cached position to cover this character. */
    retval = file_position_cache_position_extend(scanner->cache, ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_not_equal_compare(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Broadcast an equal assign token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The event to process AFTER this token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_equal_assign_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_equal_assign(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* if we succeed, then recursively process the new event on the way out. */
    return preprocessor_scanner_event_callback(scanner, ev);
}

/**
 * \brief Broadcast an or equal token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_or_equal_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* extend the cached position to cover this character. */
    retval = file_position_cache_position_extend(scanner->cache, ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_or_equal(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Broadcast an xor equal token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_xor_equal_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* extend the cached position to cover this character. */
    retval = file_position_cache_position_extend(scanner->cache, ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_xor_equal(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Broadcast a compl equal token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_compl_equal_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* extend the cached position to cover this character. */
    retval = file_position_cache_position_extend(scanner->cache, ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_compl_equal(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Broadcast a bitshift left equal token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_bitshift_left_equal_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* extend the cached position to cover this character. */
    retval = file_position_cache_position_extend(scanner->cache, ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_left_shift_equal(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Broadcast a bitshift right equal token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_bitshift_right_equal_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* extend the cached position to cover this character. */
    retval = file_position_cache_position_extend(scanner->cache, ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_right_shift_equal(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Broadcast a bitshift left token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The event to process AFTER this token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_bitshift_left_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_bitshift_left(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* if we succeed, then recursively process the new event on the way out. */
    return preprocessor_scanner_event_callback(scanner, ev);
}

/**
 * \brief Broadcast a bitshift right token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The event to process AFTER this token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_bitshift_right_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_bitshift_right(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* if we succeed, then recursively process the new event on the way out. */
    return preprocessor_scanner_event_callback(scanner, ev);
}

/**
 * \brief Broadcast a less than token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The event to process AFTER this token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_less_than_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_less_than(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* if we succeed, then recursively process the new event on the way out. */
    return preprocessor_scanner_event_callback(scanner, ev);
}

/**
 * \brief Broadcast a greater than token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The event to process AFTER this token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_greater_than_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_greater_than(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* if we succeed, then recursively process the new event on the way out. */
    return preprocessor_scanner_event_callback(scanner, ev);
}

/**
 * \brief Broadcast a less than equal token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_less_than_equal_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* extend the cached position to cover this character. */
    retval = file_position_cache_position_extend(scanner->cache, ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_less_than_equal(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Broadcast a greater than equal token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_greater_than_equal_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* extend the cached position to cover this character. */
    retval = file_position_cache_position_extend(scanner->cache, ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_greater_than_equal(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Broadcast a not token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The event to process AFTER this token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_not_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_token_not(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* if we succeed, then recursively process the new event on the way out. */
    return preprocessor_scanner_event_callback(scanner, ev);
}

/**
 * \brief Broadcast a simple token event.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event for this operation.
 * \param ctor              The event constructor for this simple token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_simple_token(
    preprocessor_scanner* scanner, const event* ev, simple_event_ctor ctor)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* get the event position. */
    pos = event_get_cursor(ev);

    /* initialize the token event. */
    retval = (*ctor)(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Broadcast a compound token event.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event for this operation.
 * \param ctor              The event constructor for this simple token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_compound_token(
    preprocessor_scanner* scanner, const event* ev, simple_event_ctor ctor)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* extend the cached position to cover this character. */
    retval = file_position_cache_position_extend(scanner->cache, ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = (*ctor)(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Broadcast a cached token and continue.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event for this operation.
 * \param ctor              The event constructor for this simple token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_cached_token_and_continue(
    preprocessor_scanner* scanner, const event* ev, simple_event_ctor ctor)
{
    int retval, release_retval;
    const cursor* pos;
    event tev;

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = (*ctor)(&tev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &tev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* if we succeed, then recursively process the new event on the way out. */
    return preprocessor_scanner_event_callback(scanner, ev);
}
