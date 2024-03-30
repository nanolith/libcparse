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
#include <stdlib.h>
#include <string.h>

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
typedef int (*bsearch_compare_func)(const void*, const void*);
typedef struct keyword_ctor keyword_ctor;
struct keyword_ctor
{
    const char* keyword;
    simple_event_ctor ctor;
};

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
static int transition_state(
    preprocessor_scanner* scanner, const event* ev, int state);
static int broadcast_simple_token(
    preprocessor_scanner* scanner, const event* ev, simple_event_ctor ctor);
static int broadcast_compound_token(
    preprocessor_scanner* scanner, const event* ev, simple_event_ctor ctor);
static int broadcast_cached_token_and_continue(
    preprocessor_scanner* scanner, const event* ev, simple_event_ctor ctor);
static int keyword_compare(const char* key, const keyword_ctor* entry);
static int keyword_search(const keyword_ctor** keyword_entry, const char* str);
static int keyword_event_broadcast(
    preprocessor_scanner* scanner, const keyword_ctor* keyword_entry,
    const cursor* pos);

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
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_pipe);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CARET:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_caret);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_TILDE:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_tilde);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_EQUAL:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_equal_assign);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_NOT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_not);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_less_than);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT_LT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_bitshift_left);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_greater_than);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT_GT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_bitshift_right);

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
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_pipe);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CARET:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_caret);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_TILDE:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_tilde);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_EQUAL:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_equal_assign);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_NOT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_not);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_less_than);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT_LT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_bitshift_left);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_greater_than);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT_GT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_bitshift_right);

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
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_pipe);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CARET:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_caret);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_TILDE:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_tilde);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_EQUAL:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_equal_assign);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_NOT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_not);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_less_than);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT_LT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_bitshift_left);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_greater_than);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT_GT:
            return
                broadcast_cached_token_and_continue(
                    scanner, ev, &event_init_for_token_bitshift_right);

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
                    return
                        broadcast_compound_token(
                            scanner, ev, &event_init_for_token_or_equal);

                default:
                    return
                        broadcast_cached_token_and_continue(
                            scanner, ev, &event_init_for_token_pipe);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CARET:
            switch (ch)
            {
                case '=':
                    return
                        broadcast_compound_token(
                            scanner, ev, &event_init_for_token_xor_equal);

                default:
                    return
                        broadcast_cached_token_and_continue(
                            scanner, ev, &event_init_for_token_caret);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_TILDE:
            switch (ch)
            {
                case '=':
                    return
                        broadcast_compound_token(
                            scanner, ev, &event_init_for_token_compl_equal);

                default:
                    return
                        broadcast_cached_token_and_continue(
                            scanner, ev, &event_init_for_token_tilde);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_EQUAL:
            switch (ch)
            {
                case '=':
                    return
                        broadcast_compound_token(
                            scanner, ev, &event_init_for_token_equal_compare);

                default:
                    return
                        broadcast_cached_token_and_continue(
                            scanner, ev, &event_init_for_token_equal_assign);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_NOT:
            switch (ch)
            {
                case '=':
                    return
                        broadcast_compound_token(
                            scanner, ev,
                            &event_init_for_token_not_equal_compare);

                default:
                    return
                        broadcast_cached_token_and_continue(
                            scanner, ev, &event_init_for_token_not);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT:
            switch (ch)
            {
                case '<':
                    return
                        transition_state(
                            scanner, ev,
                            CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT_LT);

                case '=':
                    return
                        broadcast_compound_token(
                            scanner, ev, &event_init_for_token_less_than_equal);

                default:
                    return
                        broadcast_cached_token_and_continue(
                            scanner, ev, &event_init_for_token_less_than);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT_LT:
            switch (ch)
            {
                case '=':
                    return
                        broadcast_compound_token(
                            scanner, ev,
                            &event_init_for_token_left_shift_equal);

                default:
                    return
                        broadcast_cached_token_and_continue(
                            scanner, ev, &event_init_for_token_bitshift_left);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT:
            switch (ch)
            {
                case '>':
                    return
                        transition_state(
                            scanner, ev,
                            CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT_GT);

                case '=':
                    return
                        broadcast_compound_token(
                            scanner, ev,
                            &event_init_for_token_greater_than_equal);

                default:
                    return
                        broadcast_cached_token_and_continue(
                            scanner, ev, &event_init_for_token_greater_than);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT_GT:
            switch (ch)
            {
                case '=':
                    return
                        broadcast_compound_token(
                            scanner, ev,
                            &event_init_for_token_right_shift_equal);

                default:
                    return
                        broadcast_cached_token_and_continue(
                            scanner, ev, &event_init_for_token_bitshift_right);
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
 * \brief This is the list of C keywords with event constructors.
 */
static const keyword_ctor keywords[] = {
    { "_Alignas", &event_init_for_token_keyword__Alignas },
    { "_Alignof", &event_init_for_token_keyword__Alignof },
    { "_Atomic", &event_init_for_token_keyword__Atomic },
    { "_Bool", &event_init_for_token_keyword__Bool },
    { "_Complex", &event_init_for_token_keyword__Complex },
    { "_Generic", &event_init_for_token_keyword__Generic },
    { "_Imaginary", &event_init_for_token_keyword__Imaginary },
    { "_Noreturn", &event_init_for_token_keyword__Noreturn },
    { "_Static_assert", &event_init_for_token_keyword__Static_assert },
    { "_Thread_local", &event_init_for_token_keyword__Thread_local },
    { "auto", &event_init_for_token_keyword_auto },
    { "break", &event_init_for_token_keyword_break },
    { "case", &event_init_for_token_keyword_case },
    { "char", &event_init_for_token_keyword_char },
    { "const", &event_init_for_token_keyword_const },
    { "continue", &event_init_for_token_keyword_continue },
    { "default", &event_init_for_token_keyword_default },
    { "do", &event_init_for_token_keyword_do },
    { "double", &event_init_for_token_keyword_double },
    { "else", &event_init_for_token_keyword_else },
    { "enum", &event_init_for_token_keyword_enum },
    { "extern", &event_init_for_token_keyword_extern },
    { "float", &event_init_for_token_keyword_float },
    { "for", &event_init_for_token_keyword_for },
    { "goto", &event_init_for_token_keyword_goto },
    { "if", &event_init_for_token_keyword_if },
    { "inline", &event_init_for_token_keyword_inline },
    { "int", &event_init_for_token_keyword_int },
    { "long", &event_init_for_token_keyword_long },
    { "register", &event_init_for_token_keyword_register },
    { "restrict", &event_init_for_token_keyword_restrict },
    { "return", &event_init_for_token_keyword_return },
    { "short", &event_init_for_token_keyword_short },
    { "signed", &event_init_for_token_keyword_signed },
};

/**
 * \brief Compare a keyword entry with the key.
 *
 * \param key               The key to compare.
 * \param entry             The entry to compare.
 *
 * \returns the comparison result.
 *      - a negative value if key < entry.
 *      - a positive value if key > entry.
 *      - zero if key == entry.
 */
static int keyword_compare(const char* key, const keyword_ctor* entry)
{
    return strcmp(key, entry->keyword);
}

/**
 * \brief Search the keyword list for a given string, returning success and
 * populating the entry if found.
 *
 * \param keyword_entry     Pointer to keyword entry pointer to populate on
 *                          success.
 * \param str               The string to search.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int keyword_search(const keyword_ctor** keyword_entry, const char* str)
{
    const size_t entry_size = sizeof(keyword_ctor);
    const size_t entry_count = sizeof(keywords) / entry_size;

    /* perform a binary search on the keyword array. */
    *keyword_entry =
        bsearch(
            str, keywords, entry_count, entry_size,
            (bsearch_compare_func)&keyword_compare);

    /* if the search succeeded, return success. */
    if (NULL != *keyword_entry)
    {
        return STATUS_SUCCESS;
    }
    else
    {
        return ERROR_LIBCPARSE_ENTRY_NOT_FOUND;
    }
}

/**
 * \brief Broadcast a keyword event.
 *
 * \param scanner           The scanner for this operation.
 * \param keyword_entry     The entry for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int keyword_event_broadcast(
    preprocessor_scanner* scanner, const keyword_ctor* keyword_entry,
    const cursor* pos)
{
    int retval, release_retval;
    event ev;

    /* initialize the token event. */
    retval = (keyword_entry->ctor)(&ev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &ev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_ev;
    }

    /* success. */
    goto cleanup_ev;

cleanup_ev:
    release_retval = event_dispose(&ev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
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
    const keyword_ctor* keyword_entry;
    event_identifier iev;
    bool iev_initialized = false;

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

    /* is this a keyword? */
    retval = keyword_search(&keyword_entry, str);
    if (STATUS_SUCCESS == retval)
    {
        /* send the keyword event. */
        retval = keyword_event_broadcast(scanner, keyword_entry, pos);

        /* we are done, so just clean up the string and reset state. */
        goto reset_state;
    }

    /* initialize the identifier event. */
    retval = event_identifier_init(&iev, pos, str);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_str;
    }

    /* the event was initialized. */
    iev_initialized = true;

    /* broadcast this event. */
    retval =
        event_reactor_broadcast(
            scanner->reactor, event_identifier_upcast(&iev));
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_iev;
    }

    /* success. */
    goto reset_state;

reset_state:
    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* clear the string builder. */
    string_builder_clear(scanner->builder);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

cleanup_iev:
    if (iev_initialized)
    {
        release_retval = event_identifier_dispose(&iev);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
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
 * \brief Transition to the next state.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event to process.
 * \param state             The state to start.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int transition_state(
    preprocessor_scanner* scanner, const event* ev, int state)
{
    int retval;

    /* extend the cached position to cover this character. */
    retval = file_position_cache_position_extend(scanner->cache, ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* we are now in the transitioned state. */
    scanner->state = state;

    return STATUS_SUCCESS;
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
