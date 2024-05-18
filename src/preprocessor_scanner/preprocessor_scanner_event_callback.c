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
#include <libcparse/event/raw_character_literal.h>
#include <libcparse/event/raw_integer.h>
#include <libcparse/event/raw_string.h>
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
CPARSE_IMPORT_event_raw_character_literal;
CPARSE_IMPORT_event_raw_integer;
CPARSE_IMPORT_event_raw_string;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_file_position_cache;
CPARSE_IMPORT_preprocessor_scanner;
CPARSE_IMPORT_preprocessor_scanner_internal;
CPARSE_IMPORT_string_builder;
CPARSE_IMPORT_string_utils;

typedef int (*simple_event_ctor)(event*, const cursor*);
typedef int (*scanner_variable_updater)(preprocessor_scanner*);
typedef int (*bsearch_compare_func)(const void*, const void*);
typedef struct keyword_ctor keyword_ctor;
struct keyword_ctor
{
    const char* keyword;
    simple_event_ctor ctor;
    scanner_variable_updater var_update;
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
static bool char_is_decimal_digit(const int ch);
static bool char_is_octal_digit(const int ch);
static bool char_is_non_zero_digit(const int ch);
static bool char_is_unsigned_specifier(const int ch);
static bool char_is_long_specifier(const int ch);
static int start_hash(
    preprocessor_scanner* scanner, const event* ev);
static int end_hash(
    preprocessor_scanner* scanner, const event* ev, bool process_event);
static int start_identifier(
    preprocessor_scanner* scanner, const event* ev, int ch);
static int continue_identifier(
    preprocessor_scanner* scanner, const event* ev, int ch);
static int end_identifier(preprocessor_scanner* scanner, const event* ev);
static int start_string(
    preprocessor_scanner* scanner, const event* ev, int ch);
static int continue_string(
    preprocessor_scanner* scanner, const event* ev, int ch);
static int end_string(preprocessor_scanner* scanner, const event* ev, int ch);
static int start_char(
    preprocessor_scanner* scanner, const event* ev, int ch);
static int continue_char(
    preprocessor_scanner* scanner, const event* ev, int ch);
static int end_char(preprocessor_scanner* scanner, const event* ev, int ch);
static int start_decimal_integer(
    preprocessor_scanner* scanner, const event* ev, int ch);
static int start_zero_integer(
    preprocessor_scanner* scanner, const event* ev, int ch);
static int continue_integer(
    preprocessor_scanner* scanner, const event* ev, int ch);
static int end_integer(preprocessor_scanner* scanner, const event* ev);
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
static int broadcast_pp_end(preprocessor_scanner* scanner);
static int keyword_compare(const char* key, const keyword_ctor* entry);
static int keyword_search(const keyword_ctor** keyword_entry, const char* str);
static int keyword_event_broadcast(
    preprocessor_scanner* scanner, const keyword_ctor* keyword_entry,
    const cursor* pos);
static int preprocessor_keyword_search(
    const keyword_ctor** keyword_entry, const char* str);
static int preprocessor_include_update_state(
    preprocessor_scanner* scanner);
static int broadcast_double_hash_token(
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
    int retval;
    preprocessor_scanner* scanner = (preprocessor_scanner*)context;

    /* reset the state to begin line if reset_state is set. */
    if (scanner->state_reset)
    {
        /* end a preprocessor directive on a newline. */
        switch (scanner->preprocessor_state)
        {
            case CPARSE_PREPROCESSOR_DIRECTIVE_STATE_ENABLED:
            case CPARSE_PREPROCESSOR_DIRECTIVE_STATE_ENABLED_INCLUDE:
            case CPARSE_PREPROCESSOR_DIRECTIVE_STATE_ENABLED_INCLUDE_SYSTEM_STRING:
                retval = broadcast_pp_end(scanner);
                if (STATUS_SUCCESS != retval)
                {
                    return retval;
                }
                break;
        }

        file_position_cache_clear(scanner->newline_cache);
        scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_BEGIN_LINE;
        scanner->preprocessor_state = CPARSE_PREPROCESSOR_DIRECTIVE_STATE_INIT;
        scanner->state_reset = false;
    }

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

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_SLASH:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_OCTAL_1:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_OCTAL_2:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_HEX:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_HEX_OPT:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U1:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U2:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U3:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U1:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U2:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U3:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U4:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U5:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U6:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U7:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_SLASH:
            return ERROR_LIBCPARSE_PP_SCANNER_EXPECTING_CHARACTER;

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_OCTAL_INTEGER:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_HEX_INTEGER:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_0_INTEGER:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_U:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_UL:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_L:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_LL:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_END:
            return end_integer(scanner, ev);

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

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_SLASH:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_OCTAL_1:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_OCTAL_2:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_HEX:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_HEX_OPT:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U1:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U2:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U3:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U1:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U2:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U3:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U4:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U5:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U6:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U7:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_SLASH:
            return ERROR_LIBCPARSE_PP_SCANNER_EXPECTING_CHARACTER;

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_OCTAL_INTEGER:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_HEX_INTEGER:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_0_INTEGER:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_U:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_UL:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_L:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_LL:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_END:
            return end_integer(scanner, ev);

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
    int retval;

    /* cache the newline state. */
    scanner->state_reset = true;
    const cursor* pos = event_get_cursor(ev);
    retval = file_position_cache_set(scanner->newline_cache, pos->file, pos);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    switch (scanner->state)
    {
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_IDENTIFIER:
            return end_identifier(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_SLASH:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_OCTAL_1:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_OCTAL_2:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_HEX:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_HEX_OPT:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U1:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U2:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U3:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U1:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U2:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U3:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U4:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U5:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U6:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U7:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_SLASH:
            return ERROR_LIBCPARSE_PP_SCANNER_EXPECTING_CHARACTER;

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_OCTAL_INTEGER:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_HEX_INTEGER:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_0_INTEGER:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_U:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_UL:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_L:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_LL:
        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_END:
            return end_integer(scanner, ev);

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
        case CPARSE_PREPROCESSOR_SCANNER_STATE_BEGIN_LINE:
            if ('#' == ch)
            {
                return start_hash(scanner, ev);
            }
            else
            {
                /* for any other character, break out of begin line and process
                 * as normal. */
                scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;
                return process_raw_character(scanner, ev);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_INIT:
            if (char_is_alpha_underscore(ch))
            {
                return start_identifier(scanner, ev, ch);
            }
            else if (char_is_non_zero_digit(ch))
            {
                return start_decimal_integer(scanner, ev, ch);
            }
            else
            {
                switch (ch)
                {
                    case '0':
                        return
                            start_zero_integer(scanner, ev, ch);

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
                        if (
                            CPARSE_PREPROCESSOR_DIRECTIVE_STATE_ENABLED_INCLUDE
                                == scanner->preprocessor_state)
                        {
                            scanner->preprocessor_state =
                                CPARSE_PREPROCESSOR_DIRECTIVE_STATE_ENABLED_INCLUDE_SYSTEM_STRING;
                            return start_string(scanner, ev, ch);
                        }
                        else
                        {
                            return
                                start_state(
                                    scanner, ev,
                                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT);
                        }

                    case '>':
                        return
                            start_state(
                                scanner, ev,
                                CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT);

                    case '"':
                        return start_string(scanner, ev, ch);

                    case '\'':
                        return start_char(scanner, ev, ch);

                    case '#':
                        retval = start_hash(scanner, ev);
                        if (STATUS_SUCCESS != retval)
                        {
                            return retval;
                        }

                        /* We aren't in a preprocessor directive here. */
                        scanner->preprocessor_state =
                            CPARSE_PREPROCESSOR_DIRECTIVE_STATE_DISABLED;

                        return STATUS_SUCCESS;

                    default:
                        return
                            ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
                }
            }
            break;

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_HASH:
            if (char_is_alpha_underscore(ch))
            {
                if (
                    CPARSE_PREPROCESSOR_DIRECTIVE_STATE_INIT
                        == scanner->preprocessor_state)
                {
                    /* we might be in a preprocessor directive. */
                    scanner->preprocessor_state =
                        CPARSE_PREPROCESSOR_DIRECTIVE_STATE_MAYBE;
                }

                return start_identifier(scanner, ev, ch);
            }
            else if ('#' == ch)
            {
                return broadcast_double_hash_token(scanner, ev);
            }
            else
            {
                return end_hash(scanner, ev, true);
            }

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

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING:
            switch (ch)
            {
                case '\\':
                    scanner->state =
                        CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_SLASH;
                    return continue_string(scanner, ev, ch);

                case '"':
                    if (
                        CPARSE_PREPROCESSOR_DIRECTIVE_STATE_ENABLED_INCLUDE_SYSTEM_STRING
                            == scanner->preprocessor_state)
                    {
                        return continue_string(scanner, ev, ch);
                    }
                    else
                    {
                      return end_string(scanner, ev, ch);
                    }

                case '>':
                    if (
                        CPARSE_PREPROCESSOR_DIRECTIVE_STATE_ENABLED_INCLUDE_SYSTEM_STRING
                            == scanner->preprocessor_state)
                    {
                        return end_string(scanner, ev, ch);
                    }
                    else
                    {
                        return continue_string(scanner, ev, ch);
                    }

                default:
                    return continue_string(scanner, ev, ch);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR:
            switch (ch)
            {
                case '\\':
                    scanner->state =
                        CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_SLASH;
                    return continue_char(scanner, ev, ch);

                case '\'':
                    return end_char(scanner, ev, ch);

                default:
                    return continue_char(scanner, ev, ch);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_SLASH:
            switch (ch)
            {
                case '\'':
                case '"':
                case '?':
                case '\\':
                case 'a':
                case 'b':
                case 'f':
                case 'n':
                case 'r':
                case 't':
                case 'v':
                    scanner->state =
                        CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING;
                    return continue_string(scanner, ev, ch);

                case 'x':
                case 'X':
                    scanner->state =
                        CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_HEX;
                    return continue_string(scanner, ev, ch);

                case 'u':
                    scanner->state =
                        CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U;
                    return continue_string(scanner, ev, ch);

                case 'U':
                    scanner->state =
                        CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U;
                    return continue_string(scanner, ev, ch);

                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                    scanner->state =
                        CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_OCTAL_1;
                    return continue_string(scanner, ev, ch);

                default:
                    return ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_SLASH:
            switch (ch)
            {
                case '\'':
                case '"':
                case '?':
                case '\\':
                case 'a':
                    scanner->state =
                        CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR;
                    return continue_char(scanner, ev, ch);

                default:
                    return ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U:
            if (isxdigit(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U1;
                return continue_string(scanner, ev, ch);
            }
            else
            {
                return ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U1:
            if (isxdigit(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U2;
                return continue_string(scanner, ev, ch);
            }
            else
            {
                return ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U2:
            if (isxdigit(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U3;
                return continue_string(scanner, ev, ch);
            }
            else
            {
                return ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U3:
            if (isxdigit(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U4;
                return continue_string(scanner, ev, ch);
            }
            else
            {
                return ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U4:
            if (isxdigit(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U5;
                return continue_string(scanner, ev, ch);
            }
            else
            {
                return ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U5:
            if (isxdigit(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U6;
                return continue_string(scanner, ev, ch);
            }
            else
            {
                return ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U6:
            if (isxdigit(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U7;
                return continue_string(scanner, ev, ch);
            }
            else
            {
                return ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U7:
            if (isxdigit(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING;
                return continue_string(scanner, ev, ch);
            }
            else
            {
                return ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U:
            if (isxdigit(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U1;
                return continue_string(scanner, ev, ch);
            }
            else
            {
                return ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U1:
            if (isxdigit(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U2;
                return continue_string(scanner, ev, ch);
            }
            else
            {
                return ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U2:
            if (isxdigit(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U3;
                return continue_string(scanner, ev, ch);
            }
            else
            {
                return ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U3:
            if (isxdigit(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING;
                return continue_string(scanner, ev, ch);
            }
            else
            {
                return ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_OCTAL_1:
            switch (ch)
            {
                case '"':
                    return end_string(scanner, ev, ch);

                case '\\':
                    scanner->state =
                        CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_SLASH;
                    return continue_string(scanner, ev, ch);

                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                    scanner->state =
                        CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_OCTAL_2;
                    return continue_string(scanner, ev, ch);

                default:
                    scanner->state =
                        CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING;
                    return continue_string(scanner, ev, ch);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_OCTAL_2:
            switch (ch)
            {
                case '"':
                    return end_string(scanner, ev, ch);

                case '\\':
                    scanner->state =
                        CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_SLASH;
                    return continue_string(scanner, ev, ch);

                default:
                    scanner->state =
                        CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING;
                    return continue_string(scanner, ev, ch);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_HEX:
            if (isxdigit(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_HEX_OPT;
                return continue_string(scanner, ev, ch);
            }
            else
            {
                return ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_HEX_OPT:
            if (isxdigit(ch))
            {
                return continue_string(scanner, ev, ch);
            }
            else
            {
                switch (ch)
                {
                    case '"':
                        return end_string(scanner, ev, ch);

                    case '\\':
                        scanner->state =
                            CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_SLASH;
                        return continue_string(scanner, ev, ch);

                    default:
                        scanner->state =
                            CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING;
                        return continue_string(scanner, ev, ch);
                }
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER:
            if (char_is_decimal_digit(ch))
            {
                return continue_integer(scanner, ev, ch);
            }
            else if (char_is_unsigned_specifier(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_U;
                return continue_integer(scanner, ev, ch);
            }
            else if (char_is_long_specifier(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_L;
                return continue_integer(scanner, ev, ch);
            }
            else
            {
                return end_integer(scanner, ev);
            }
            break;

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_U:
            if (char_is_long_specifier(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_UL;
                return continue_integer(scanner, ev, ch);
            }
            else
            {
                return end_integer(scanner, ev);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_UL:
            if (char_is_long_specifier(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_END;
                return continue_integer(scanner, ev, ch);
            }
            else
            {
                return end_integer(scanner, ev);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_END:
            return end_integer(scanner, ev);

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_L:
            if (char_is_unsigned_specifier(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_END;
                return continue_integer(scanner, ev, ch);
            }
            else if (char_is_long_specifier(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_LL;
                return continue_integer(scanner, ev, ch);
            }
            else
            {
                return end_integer(scanner, ev);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_LL:
            if (char_is_unsigned_specifier(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_END;
                return continue_integer(scanner, ev, ch);
            }
            else
            {
                return end_integer(scanner, ev);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_0_INTEGER:
            if (char_is_octal_digit(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_OCTAL_INTEGER;
                return continue_integer(scanner, ev, ch);
            }
            else if (char_is_unsigned_specifier(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_U;
                return continue_integer(scanner, ev, ch);
            }
            else if (char_is_long_specifier(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_L;
                return continue_integer(scanner, ev, ch);
            }
            else if ('x' == ch)
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_HEX_INTEGER;
                return continue_integer(scanner, ev, ch);
            }
            else
            {
                return end_integer(scanner, ev);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_OCTAL_INTEGER:
            if (char_is_octal_digit(ch))
            {
                return continue_integer(scanner, ev, ch);
            }
            else if (char_is_unsigned_specifier(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_U;
                return continue_integer(scanner, ev, ch);
            }
            else if (char_is_long_specifier(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_L;
                return continue_integer(scanner, ev, ch);
            }
            else
            {
                return end_integer(scanner, ev);
            }

        case CPARSE_PREPROCESSOR_SCANNER_STATE_IN_HEX_INTEGER:
            if (isxdigit(ch))
            {
                return continue_integer(scanner, ev, ch);
            }
            else if (char_is_unsigned_specifier(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_U;
                return continue_integer(scanner, ev, ch);
            }
            else if (char_is_long_specifier(ch))
            {
                scanner->state =
                    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_L;
                return continue_integer(scanner, ev, ch);
            }
            else
            {
                return end_integer(scanner, ev);
            }

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
    if (char_is_alpha_underscore(ch) || isdigit(ch))
    {
        return true;
    }

    return false;
}

/**
 * \brief Return true if this is a decimal digit.
 */
static bool char_is_decimal_digit(const int ch)
{
    if (isdigit(ch))
    {
        return true;
    }

    return false;
}

/**
 * \brief Return true if this is a octal digit.
 */
static bool char_is_octal_digit(const int ch)
{
    if (isdigit(ch) && '9' != ch && '8' != ch)
    {
        return true;
    }

    return false;
}

/**
 * \brief Return true if this is a non-zero digit.
 */
static bool char_is_non_zero_digit(const int ch)
{
    if (isdigit(ch) && '0' != ch)
    {
        return true;
    }

    return false;
}

/**
 * \brief Return true if this is a long specifier digit.
 */
static bool char_is_long_specifier(const int ch)
{
    switch (ch)
    {
        case 'L':
        case 'l':
            return true;

        default:
            return false;
    }
}

/**
 * \brief Return true if this is an unsigned specifier digit.
 */
static bool char_is_unsigned_specifier(const int ch)
{
    switch (ch)
    {
        case 'U':
        case 'u':
            return true;

        default:
            return false;
    }
}

/**
 * \brief Start the hash state, and record the hash position.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int start_hash(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval;

    /* get the cursor for this event. */
    const cursor* pos = event_get_cursor(ev);

    /* save this location. */
    retval = file_position_cache_set(scanner->hash_cache, pos->file, pos);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* we are now in the hash state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_IN_HASH;

    return STATUS_SUCCESS;
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
 * \brief Start a string token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character for this string.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int start_string(
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
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING;

    return STATUS_SUCCESS;
}

/**
 * \brief Start a char token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character for this character literal.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int start_char(
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

    /* we are now in the char state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR;

    return STATUS_SUCCESS;
}

/**
 * \brief Start a decimal integer token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The digit for this integer.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int start_decimal_integer(
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

    /* we are now in the decimal integer state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER;

    return STATUS_SUCCESS;
}

/**
 * \brief Start a zero integer token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The digit for this integer.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int start_zero_integer(
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

    /* we are now in the zero integer state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_IN_0_INTEGER;

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
 * \brief Continue a string token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character for this string.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int continue_string(
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
 * \brief Continue a char token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character for this character literal.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int continue_char(
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
 * \brief Continue an integer token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The digit for this integer.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int continue_integer(
    preprocessor_scanner* scanner, const event* ev, int ch)
{
    int retval;

    /* extend the cached position to cover this character. */
    retval = file_position_cache_position_extend(scanner->cache, ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* add this digit to the string builder. */
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
    { "_Alignas", &event_init_for_token_keyword__Alignas, NULL },
    { "_Alignof", &event_init_for_token_keyword__Alignof, NULL },
    { "_Atomic", &event_init_for_token_keyword__Atomic, NULL },
    { "_Bool", &event_init_for_token_keyword__Bool, NULL },
    { "_Complex", &event_init_for_token_keyword__Complex, NULL },
    { "_Generic", &event_init_for_token_keyword__Generic, NULL },
    { "_Imaginary", &event_init_for_token_keyword__Imaginary, NULL },
    { "_Noreturn", &event_init_for_token_keyword__Noreturn, NULL },
    { "_Static_assert", &event_init_for_token_keyword__Static_assert, NULL },
    { "_Thread_local", &event_init_for_token_keyword__Thread_local, NULL },
    { "auto", &event_init_for_token_keyword_auto, NULL },
    { "break", &event_init_for_token_keyword_break, NULL },
    { "case", &event_init_for_token_keyword_case, NULL },
    { "char", &event_init_for_token_keyword_char, NULL },
    { "const", &event_init_for_token_keyword_const, NULL },
    { "continue", &event_init_for_token_keyword_continue, NULL },
    { "default", &event_init_for_token_keyword_default, NULL },
    { "do", &event_init_for_token_keyword_do, NULL },
    { "double", &event_init_for_token_keyword_double, NULL },
    { "else", &event_init_for_token_keyword_else, NULL },
    { "enum", &event_init_for_token_keyword_enum, NULL },
    { "extern", &event_init_for_token_keyword_extern, NULL },
    { "float", &event_init_for_token_keyword_float, NULL },
    { "for", &event_init_for_token_keyword_for, NULL },
    { "goto", &event_init_for_token_keyword_goto, NULL },
    { "if", &event_init_for_token_keyword_if, NULL },
    { "inline", &event_init_for_token_keyword_inline, NULL },
    { "int", &event_init_for_token_keyword_int, NULL },
    { "long", &event_init_for_token_keyword_long, NULL },
    { "register", &event_init_for_token_keyword_register, NULL },
    { "restrict", &event_init_for_token_keyword_restrict, NULL },
    { "return", &event_init_for_token_keyword_return, NULL },
    { "short", &event_init_for_token_keyword_short, NULL },
    { "signed", &event_init_for_token_keyword_signed, NULL },
    { "sizeof", &event_init_for_token_keyword_sizeof, NULL },
    { "static", &event_init_for_token_keyword_static, NULL },
    { "struct", &event_init_for_token_keyword_struct, NULL },
    { "switch", &event_init_for_token_keyword_switch, NULL },
    { "typedef", &event_init_for_token_keyword_typedef, NULL },
    { "union", &event_init_for_token_keyword_union, NULL },
    { "unsigned", &event_init_for_token_keyword_unsigned, NULL },
    { "void", &event_init_for_token_keyword_void, NULL },
    { "volatile", &event_init_for_token_keyword_volatile, NULL },
    { "while", &event_init_for_token_keyword_while, NULL },
};

/**
 * \brief This is the list of C preprocessor keywords with event constructors.
 */
static const keyword_ctor preprocessor_keywords[] = {
    { "define", &event_init_for_token_preprocessor_id_define, NULL },
    { "elif", &event_init_for_token_preprocessor_id_elif, NULL },
    { "else", &event_init_for_token_preprocessor_id_else, NULL },
    { "endif", &event_init_for_token_preprocessor_id_endif, NULL },
    { "error", &event_init_for_token_preprocessor_id_error, NULL },
    { "if", &event_init_for_token_preprocessor_id_if, NULL },
    { "ifdef", &event_init_for_token_preprocessor_id_ifdef, NULL },
    { "ifndef", &event_init_for_token_preprocessor_id_ifndef, NULL },
    { "include", &event_init_for_token_preprocessor_id_include,
      &preprocessor_include_update_state },
    { "line", &event_init_for_token_preprocessor_id_line, NULL },
    { "pragma", &event_init_for_token_preprocessor_id_pragma, NULL },
    { "undef", &event_init_for_token_preprocessor_id_undef, NULL },
};

/**
 * \brief This is the list of C string prefixes.
 */
static const char* string_prefixes[] = {
    "L",
    "U",
    "u",
    "u8",
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
 * \brief Compare a string prefixes entry with the key.
 *
 * \param key               The key to compare.
 * \param entry             The entry to compare.
 *
 * \returns the comparison result.
 *      - a negative value if key < entry.
 *      - a positive value if key > entry.
 *      - zero if key == entry.
 */
static int string_prefix_compare(const char* key, const char** entry)
{
    return strcmp(key, *entry);
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
 * \brief Search the preprocessor keyword list for a given string, returning
 * success and populating the entry if found.
 *
 * \param keyword_entry     Pointer to keyword entry pointer to populate on
 *                          success.
 * \param str               The string to search.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int preprocessor_keyword_search(
    const keyword_ctor** keyword_entry, const char* str)
{
    const size_t entry_size = sizeof(keyword_ctor);
    const size_t entry_count = sizeof(preprocessor_keywords) / entry_size;

    /* perform a binary search on the keyword array. */
    *keyword_entry =
        bsearch(
            str, preprocessor_keywords, entry_count, entry_size,
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

    /* update scanner variables if updater set. */
    if (NULL != keyword_entry->var_update)
    {
        retval = (keyword_entry->var_update)(scanner);
        if (STATUS_SUCCESS != retval)
        {
            goto cleanup_ev;
        }
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
 * \brief Return true if this is a string prefix and if the next event is the
 * start of the string.
 *
 * The quote character is populated if this is a string.
 */
static bool is_string(const char* str, const event* ev, int* ch)
{
    const size_t entry_size = sizeof(const char*);
    const size_t entry_count = sizeof(string_prefixes) / entry_size;
    const char* prefix;
    int retval;
    event_raw_character* rev;

    /* perform a binary search on the string prefix list. */
    prefix =
        bsearch(
            str, string_prefixes, entry_count, entry_size,
            (bsearch_compare_func)&string_prefix_compare);

    /* If this is not a string prefix, then this isn't a string. */
    if (NULL == prefix)
    {
        return false;
    }

    /* attempt to cast this event to a raw character. */
    retval = event_downcast_to_event_raw_character(&rev, (event*)ev);
    if (STATUS_SUCCESS != retval)
    {
        /* if this is not a raw character, this can't be a string. */
        return false;
    }

    /* get the raw character value. */
    *ch = event_raw_character_get(rev);

    /* if this is not a double quote, then this is not a string. */
    if (*ch != '"')
    {
        return false;
    }

    /* otherwise, this is a string with a prefix. */
    return true;
}

/**
 * \brief End the hash state, emitting a hash token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event that ends this hash.
 * \param process_event     Flag to determine whether the event should be
 *                          processed next.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int end_hash(
    preprocessor_scanner* scanner, const event* ev, bool process_event)
{
    int retval, release_retval;
    event tev;
    const cursor* pos;

    /* get the cached hash position. */
    retval = file_position_cache_position_get(scanner->hash_cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the hash token event. */
    retval = event_init_for_token_preprocessor_hash(&tev, pos);
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

    /* reset the hash cache. */
    file_position_cache_clear(scanner->hash_cache);

    /* success. */
    goto cleanup_tev;

cleanup_tev:
    release_retval = event_dispose(&tev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    if (STATUS_SUCCESS != retval || process_event)
    {
        return retval;
    }

    /* if we succeed, then recursively process the new event on the way out. */
    return preprocessor_scanner_event_callback(scanner, ev);
}

/**
 * \brief Broadcast a double hash token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event for the second hash.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_double_hash_token(
    preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    event tev;
    const cursor* pos;

    /* extend the cached position to cover this character. */
    retval = file_position_cache_position_extend(scanner->hash_cache, ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* get the cached hash position. */
    retval = file_position_cache_position_get(scanner->hash_cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the string concat token event. */
    retval = event_init_for_token_preprocessor_string_concat(&tev, pos);
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

    /* reset the hash cache. */
    file_position_cache_clear(scanner->hash_cache);

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
    int ch;

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

    /* could this be a preprocessor keyword? */
    if (
        CPARSE_PREPROCESSOR_DIRECTIVE_STATE_MAYBE
            == scanner->preprocessor_state)
    {
        /* is this a preprocessor keyword? */
        retval = preprocessor_keyword_search(&keyword_entry, str);
        if (STATUS_SUCCESS == retval)
        {
            /* we are now in a preprocessor directive. */
            scanner->preprocessor_state =
                CPARSE_PREPROCESSOR_DIRECTIVE_STATE_ENABLED;

            /* send the keyword event. */
            /* TODO - use the complete pos. */
            retval = keyword_event_broadcast(scanner, keyword_entry, pos);

            /* reset the hash cache. */
            file_position_cache_clear(scanner->hash_cache);

            /* we are done, so just clean up the string and reset state. */
            goto reset_state;
        }
        else
        {
            /* send the hash symbol. */
            retval = end_hash(scanner, ev, false);
            if (STATUS_SUCCESS != retval)
            {
                goto cleanup_str;
            }

            /* we are not in a preprocessor directive. */
            scanner->preprocessor_state =
                CPARSE_PREPROCESSOR_DIRECTIVE_STATE_INIT;
        }
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

    /* is this a string prefix? */
    if (is_string(str, ev, &ch))
    {
        scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING;
        retval = continue_string(scanner, ev, ch);
        string_utils_string_release(str);
        return retval;
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
 * \brief End a string token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event that ends this string.
 * \param ch                The raw character that ends this string.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int end_string(preprocessor_scanner* scanner, const event* ev, int ch)
{
    int retval, release_retval;
    const cursor* pos;
    char* str;
    event_raw_string_token sev;

    /* append the character to the raw string. */
    retval = continue_string(scanner, ev, ch);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* Build a string for the raw string token. */
    retval = string_builder_build(&str, scanner->builder);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* is this a system include string? */
    if (
        CPARSE_PREPROCESSOR_DIRECTIVE_STATE_ENABLED_INCLUDE_SYSTEM_STRING
            == scanner->preprocessor_state)
    {
        /* initialize the raw system string event. */
        retval = event_raw_string_token_init_for_system_string(&sev, pos, str);
        if (STATUS_SUCCESS != retval)
        {
            goto cleanup_str;
        }

        /* fall back to the include state. */
        scanner->preprocessor_state =
            CPARSE_PREPROCESSOR_DIRECTIVE_STATE_ENABLED_INCLUDE;
    }
    else
    {
        /* initialize the raw string event. */
        retval = event_raw_string_token_init(&sev, pos, str);
        if (STATUS_SUCCESS != retval)
        {
            goto cleanup_str;
        }
    }

    /* broadcast this event. */
    retval =
        event_reactor_broadcast(
            scanner->reactor, event_raw_string_token_upcast(&sev));
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_sev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* clear the string builder. */
    string_builder_clear(scanner->builder);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_sev;

cleanup_sev:
    release_retval = event_raw_string_token_dispose(&sev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

cleanup_str:
    string_utils_string_release(str);

done:
    return retval;
}

/**
 * \brief End a char token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event that ends this literal.
 * \param ch                The raw character that ends this literal.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int end_char(preprocessor_scanner* scanner, const event* ev, int ch)
{
    int retval, release_retval;
    const cursor* pos;
    char* str;
    event_raw_character_literal cev;

    /* append the character to the raw character literal. */
    retval = continue_char(scanner, ev, ch);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* Build a string for the raw character literal. */
    retval = string_builder_build(&str, scanner->builder);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the raw character literal event. */
    retval = event_raw_character_literal_init(&cev, pos, str);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_str;
    }

    /* broadcast this event. */
    retval =
        event_reactor_broadcast(
            scanner->reactor, event_raw_character_literal_upcast(&cev));
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_cev;
    }

    /* clear the file / position cache. */
    file_position_cache_clear(scanner->cache);

    /* clear the string builder. */
    string_builder_clear(scanner->builder);

    /* we are now in the init state. */
    scanner->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_cev;

cleanup_cev:
    release_retval = event_raw_character_literal_dispose(&cev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

cleanup_str:
    string_utils_string_release(str);

done:
    return retval;
}

/**
 * \brief End an integer token.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event that ends this integer.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int end_integer(preprocessor_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    const cursor* pos;
    char* str;
    event_raw_integer_token iev;

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* Build a string for the integer. */
    retval = string_builder_build(&str, scanner->builder);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the identifier event. */
    retval = event_raw_integer_token_init(&iev, pos, str);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_str;
    }

    /* broadcast this event. */
    retval =
        event_reactor_broadcast(
            scanner->reactor, event_raw_integer_token_upcast(&iev));
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
    release_retval = event_raw_integer_token_dispose(&iev);
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
 * \brief Broadcast a preprocessor directive end event.
 *
 * \param scanner           The scanner for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_pp_end(preprocessor_scanner* scanner)
{
    int retval, release_retval;
    event pev;
    const cursor* pos;

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->newline_cache, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the token event. */
    retval = event_init_for_preprocessor_directive_end(&pev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(scanner->reactor, &pev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_pev;
    }

    /* we are no longer in a preprocessor directive. */
    scanner->preprocessor_state = CPARSE_PREPROCESSOR_DIRECTIVE_STATE_INIT;

    /* success. */
    goto cleanup_pev;

cleanup_pev:
    release_retval = event_dispose(&pev);
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

/**
 * \brief Update the scanner preprocessor state to show that we are in an
 * include directive.
 *
 * \param scanner           The scanner for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int preprocessor_include_update_state(
    preprocessor_scanner* scanner)
{
    scanner->preprocessor_state =
        CPARSE_PREPROCESSOR_DIRECTIVE_STATE_ENABLED_INCLUDE;

    return STATUS_SUCCESS;
}
