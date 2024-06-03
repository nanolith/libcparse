/**
 * \file exmaples/syntax_highlight/src/scan_input_and_write_output.c
 *
 * \brief Scan input and write output.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>
#include <libcparse/abstract_parser.h>
#include <libcparse/event.h>
#include <libcparse/event_handler.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "syntax_highlight_internal.h"

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_handler;

static int comment_scanner_event_callback(
    syntax_highlight_config* config, const event* ev);
static int preprocessor_scanner_event_callback(
    syntax_highlight_config* config, const event* ev);
static int markup_position(
    syntax_highlight_config* config, const cursor* pos, int syntax_type);
static int generate_output(syntax_highlight_config* config);
static const char* decode_style(int style);
static void write_decoded_char(syntax_highlight_config* config, char ch);

/**
 * \brief Scan the input file, writing HTML markup to the output file.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int scan_input_and_write_output(syntax_highlight_config* config)
{
    int retval, release_retval;
    event_handler ceh, peh;

    /* create an event handler for comment scanner events. */
    retval =
        event_handler_init(
            &ceh, (event_callback_fn)&comment_scanner_event_callback, config);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* subscribe to comment scanner events. */
    retval = abstract_parser_comment_scanner_subscribe(config->ap, &ceh);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_ceh;
    }

    /* create an event handler for preprocessor scanner events. */
    retval =
        event_handler_init(
            &peh, (event_callback_fn)&preprocessor_scanner_event_callback,
            config);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_ceh;
    }

    /* subscribe to preprocessor scanner events. */
    retval = abstract_parser_preprocessor_scanner_subscribe(config->ap, &peh);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_peh;
    }

    /* run the parser. */
    retval = abstract_parser_run(config->ap);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_peh;
    }

    /* output the marked up source file to the output file. */
    retval = generate_output(config);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_peh;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_peh;

cleanup_peh:
    release_retval = event_handler_dispose(&peh);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

cleanup_ceh:
    release_retval = event_handler_dispose(&ceh);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Event callback for the comment scanner.
 *
 * \param config            The config for this callback.
 * \param ev                The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int comment_scanner_event_callback(
    syntax_highlight_config* config, const event* ev)
{
    int retval;
    const cursor* pos = event_get_cursor(ev);

    switch (event_get_type(ev))
    {
        case CPARSE_EVENT_TYPE_COMMENT_BLOCK_BEGIN:
        case CPARSE_EVENT_TYPE_COMMENT_LINE_BEGIN:
            memcpy(&config->comment_scanner_pos, pos, sizeof(*pos));
            return STATUS_SUCCESS;

        case CPARSE_EVENT_TYPE_COMMENT_BLOCK_END:
        case CPARSE_EVENT_TYPE_COMMENT_LINE_END:
            config->comment_scanner_pos.end_line = pos->end_line;
            config->comment_scanner_pos.end_col = pos->end_col;

            return
                markup_position(
                    config, &config->comment_scanner_pos,
                    HIGHLIGHT_TYPE_COMMENT);

        /* ignore everything else. */
        default:
            return STATUS_SUCCESS;
    }
}

/**
 * \brief Event callback for the proprocessor scanner.
 *
 * \param config            The config for this callback.
 * \param ev                The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int preprocessor_scanner_event_callback(
    syntax_highlight_config* config, const event* ev)
{
    int retval;
    const cursor* pos = event_get_cursor(ev);

    switch (event_get_type(ev))
    {
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
            memcpy(&config->preprocessor_scanner_pos, pos, sizeof(*pos));
            return STATUS_SUCCESS;

        case CPARSE_EVENT_TYPE_PP_END:
            config->preprocessor_scanner_pos.end_line = pos->end_line;
            config->preprocessor_scanner_pos.end_col = pos->end_col;

            return
                markup_position(
                    config, &config->preprocessor_scanner_pos,
                    HIGHLIGHT_TYPE_PREPROCESSOR);

        case CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_FLOAT:
        case CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER:
            return markup_position(config, pos, HIGHLIGHT_TYPE_NUMBER);

        case CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING:
        case CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_SYSTEM_STRING:
            return markup_position(config, pos, HIGHLIGHT_TYPE_STRING);

        case CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_CHARACTER:
            return markup_position(config, pos, HIGHLIGHT_TYPE_CHAR_LITERAL);

        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__BOOL:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__COMPLEX:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__IMAGINARY:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CHAR:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DOUBLE:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ENUM:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FLOAT:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_INT:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_LONG:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SHORT:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_STRUCT:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_TYPEDEF:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_UNION:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_VOID:
            return markup_position(config, pos, HIGHLIGHT_TYPE_TYPE);

        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CASE:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DEFAULT:
            return markup_position(config, pos, HIGHLIGHT_TYPE_LABEL);

        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_BREAK:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CONTINUE:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DO:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ELSE:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FOR:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_GOTO:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_IF:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_RETURN:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SIZEOF:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SWITCH:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_WHILE:
            return markup_position(config, pos, HIGHLIGHT_TYPE_KEYWORD);

        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ATOMIC:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__NORETURN:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__THREAD_LOCAL:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_AUTO:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CONST:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_EXTERN:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_INLINE:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_REGISTER:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_RESTRICT:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SIGNED:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_STATIC:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_UNSIGNED:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_VOLATILE:
            return markup_position(config, pos, HIGHLIGHT_TYPE_MODIFIER);

        /* ignore everything else. */
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ALIGNAS:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ALIGNOF:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__GENERIC:
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__STATIC_ASSERT:
        default:
            return STATUS_SUCCESS;
    }
}

/**
 * \brief Mark up a source file position with the given markup code.
 *
 * \param config            The config for this operation.
 * \param pos               The position for this operation.
 * \param syntax_type       The syntax type to mark up.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int markup_position(
    syntax_highlight_config* config, const cursor* pos, int syntax_type)
{
    size_t begin_offset = pos->begin_line - 1;
    size_t end_offset = pos->end_line - 1;
    size_t col_offset = pos->begin_col - 1;

    /* bounds check. */
    if (begin_offset >= config->count || end_offset >= config->count)
    {
        return ERROR_LIBCPARSE_OUT_OF_BOUNDS;
    }

    /* iterate through each line. */
    source_line* l = NULL;
    for (
        size_t offset = begin_offset;
        offset <= end_offset;
        ++offset, col_offset = 0)
    {
        l = config->lines[offset];

        /* compute the end column offset. */
        size_t end_col_offset;
        if (offset == end_offset)
        {
            end_col_offset = pos->end_col;
        }
        else
        {
            end_col_offset = l->length;
        }

        /* mark all characters between the two offsets. */
        for (size_t i = col_offset; i < end_col_offset; ++i)
        {
            l->highlight_line[i] = syntax_type;
        }
    }

    return STATUS_SUCCESS;
}

/**
 * \brief Generate the output file.
 *
 * \param config            The config for this callback.
 * \param ev                The event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int generate_output(syntax_highlight_config* config)
{
    /* start the HTML file. */
    fprintf(config->out, "<html>\n");

    /* include a stylesheet. */
    fprintf(
        config->out,
        "<head><link rel=\"stylesheet\" href=\"codelisting.css\"/></head>\n");

    /* start the body. */
    fprintf(config->out, "<body><div class=\"codelisting\">\n");

    /* iterate over each line of the source file. */
    for (source_line* i = config->head; NULL != i; i = i->next)
    {
        int prev_style = 0;

        /* start the source line. */
        fprintf(config->out, "<div class=\"codelisting_line\">");
        /* start a normal span. */
        fprintf(config->out, "<span class=\"codestyle_normal\">");

        /* iterate over each character in the line. */
        bool nonspace_found = false;
        for (size_t offset = 0; offset < i->length; ++offset)
        {
            /* do we need to change styles? */
            if (prev_style != i->highlight_line[offset])
            {
                /* change the style. */
                fprintf(
                    config->out, "</span><span class=\"codestyle_%s\">",
                    decode_style(i->highlight_line[offset]));
                prev_style = i->highlight_line[offset];
            }

            /* output this character. */
            write_decoded_char(config, i->line[offset]);

            /* if non-whitespace is found, we don't need to buffer the line. */
            if (!isspace(i->line[offset]))
            {
                nonspace_found = true;
            }
        }

        /* add some nbsp if only whitespace is on the line. */
        if (!nonspace_found)
        {
            fprintf(config->out, "&nbsp;");
        }

        /* end the source line. */
        fprintf(config->out, "</span></div>\n");
    }

    /* end the HTML file. */
    fprintf(config->out, "</div></body></html>\n");

    return STATUS_SUCCESS;
}

/**
 * \brief Decode the highlight style.
 *
 * \param style             The style to decode.
 *
 * \returns a symbolic name for the given style.
 */
static const char* decode_style(int style)
{
    switch (style)
    {
        case HIGHLIGHT_TYPE_COMMENT:
            return "comment";

        case HIGHLIGHT_TYPE_PREPROCESSOR:
            return "preprocessor";

        case HIGHLIGHT_TYPE_TYPE:
            return "type";

        case HIGHLIGHT_TYPE_CHAR_LITERAL:
            return "char";

        case HIGHLIGHT_TYPE_STRING:
            return "string";

        case HIGHLIGHT_TYPE_NUMBER:
            return "number";

        case HIGHLIGHT_TYPE_KEYWORD:
            return "keyword";

        case HIGHLIGHT_TYPE_MODIFIER:
            return "modifier";

        case HIGHLIGHT_TYPE_LABEL:
            return "label";

        case HIGHLIGHT_TYPE_NORMAL:
        default:
            return "normal";
    }
}

/**
 * \brief Write a character safe for HTML output.
 *
 * \param config            The config for this operation.
 * \param ch                The character to decode.
 *
 * \returns a symbolic name for the given style.
 */
static void write_decoded_char(syntax_highlight_config* config, char ch)
{
    switch (ch)
    {
        case '\t':
            fprintf(config->out, "&nbsp;&nbsp;");
            break;

        case ' ':
            fprintf(config->out, "&nbsp;");
            break;

        case '<':
            fprintf(config->out, "&lt;");
            break;

        case '>':
            fprintf(config->out, "&gt;");
            break;

        default:
            fprintf(config->out, "%c", ch);
    }
}
