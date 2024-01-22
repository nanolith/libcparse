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
                return
                    ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER;
            }
            break;

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
