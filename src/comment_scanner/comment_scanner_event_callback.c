/**
 * \file src/comment_scanner/comment_scanner_event_callback.c
 *
 * \brief The \ref comment_scanner event handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/comment_scanner.h>
#include <libcparse/event.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/event_reactor.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "comment_scanner_internal.h"

CPARSE_IMPORT_comment_scanner;
CPARSE_IMPORT_comment_scanner_internal;
CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_raw_character;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_file_position_cache;

static int process_char_event(comment_scanner* scanner, const event* ev);
static int process_char_event_init(
    comment_scanner* scanner, const event_raw_character* ev, int ch);
static int process_char_event_slash(
    comment_scanner* scanner, const event_raw_character* ev, int ch);
static int process_char_event_block(
    comment_scanner* scanner, const event_raw_character* ev, int ch);
static int process_char_event_block_star(
    comment_scanner* scanner, const event_raw_character* ev, int ch);
static int process_char_event_line(
    comment_scanner* scanner, const event_raw_character* ev, int ch);
static int process_char_event_string(
    comment_scanner* scanner, const event_raw_character* ev, int ch);
static int process_char_event_string_backslash(
    comment_scanner* scanner, const event_raw_character* ev, int ch);
static int process_char_event_char_seq(
    comment_scanner* scanner, const event_raw_character* ev, int ch);
static int process_char_event_char_seq_backslash(
    comment_scanner* scanner, const event_raw_character* ev, int ch);
static int process_eof_event(comment_scanner* scanner, const event* ev);
static int begin_block_comment_broadcast(
    comment_scanner* scanner, const event_raw_character* ev);
static int end_block_comment_broadcast(
    comment_scanner* scanner, const event_raw_character* ev);
static int begin_line_comment_broadcast(
    comment_scanner* scanner, const event_raw_character* ev);
static int end_line_comment_broadcast(
    comment_scanner* scanner, const event* ev);

/**
 * \brief Event handler callback for \ref comment_scanner.
 *
 * \param context           The context for this handler (the
 *                          \ref commant_scanner instance).
 * \param ev                An event for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_scanner_event_callback)(
    void* context, const CPARSE_SYM(event)* ev)
{
    comment_scanner* scanner = (comment_scanner*)context;

    switch (event_get_type(ev))
    {
        case CPARSE_EVENT_TYPE_EOF:
            return process_eof_event(scanner, ev);

        case CPARSE_EVENT_TYPE_RAW_CHARACTER:
            return process_char_event(scanner, ev);

        default:
            return STATUS_SUCCESS;
    }
}

/**
 * \brief Process an eof event.
 *
 * \param scanner           The \ref comment_scanner for this operation.
 * \param ev                The eof event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_eof_event(comment_scanner* scanner, const event* ev)
{
    int retval;

    switch (scanner->state)
    {
        /* in the init state, just send the EOF. */
        case CPARSE_COMMENT_SCANNER_STATE_INIT:
            retval = event_reactor_broadcast(scanner->reactor, ev);
            goto done;

        /* if we've encountered a slash, then we can recover. */
        case CPARSE_COMMENT_SCANNER_STATE_SLASH:
            /* send the previous slash event to all subscribers. */
            retval =
                file_position_cache_raw_character_broadcast(
                    scanner->cache, scanner->reactor, '/');
            if (STATUS_SUCCESS != retval)
            {
                return retval;
            }

            /* clear the cache. */
            file_position_cache_clear(scanner->cache);

            /* broadcast the EOF event. */
            retval = event_reactor_broadcast(scanner->reactor, ev);

            /* reset our state. */
            scanner->state = CPARSE_COMMENT_SCANNER_STATE_INIT;
            goto done;

        /* we are expecting a slash. */
        case CPARSE_COMMENT_SCANNER_STATE_IN_BLOCK_COMMENT_STAR:
            retval = ERROR_LIBCPARSE_COMMENT_EXPECTING_SLASH;
            goto done;

        /* we are expecting a star slash. */
        case CPARSE_COMMENT_SCANNER_STATE_IN_BLOCK_COMMENT:
            retval = ERROR_LIBCPARSE_COMMENT_EXPECTING_STAR_SLASH;
            goto done;

        /* in the line comment, send the end comment and then EOF. */
        case CPARSE_COMMENT_SCANNER_STATE_IN_LINE_COMMENT:
            scanner->state = CPARSE_COMMENT_SCANNER_STATE_INIT;
            retval = end_line_comment_broadcast(scanner, ev);
            goto done;

        /* in the char sequence state, we are expecting a single quote. */
        case CPARSE_COMMENT_SCANNER_STATE_IN_CHAR_SEQUENCE:
            retval = ERROR_LIBCPARSE_COMMENT_EXPECTING_SINGLE_QUOTE;
            goto done;

        /* in the char sequence slash state, expect a char and single quote. */
        case CPARSE_COMMENT_SCANNER_STATE_IN_CHAR_SEQUENCE_BACKSLASH:
            retval = ERROR_LIBCPARSE_COMMENT_EXPECTING_CHAR_SINGLE_QUOTE;
            goto done;

        /* in the string state, we are expecting a double quote. */
        case CPARSE_COMMENT_SCANNER_STATE_IN_STRING:
            retval = ERROR_LIBCPARSE_COMMENT_EXPECTING_DOUBLE_QUOTE;
            goto done;

        /* in the string slash state, expect a char and double quote. */
        case CPARSE_COMMENT_SCANNER_STATE_IN_STRING_BACKSLASH:
            retval = ERROR_LIBCPARSE_COMMENT_EXPECTING_CHAR_DOUBLE_QUOTE;
            goto done;

        /* If we make it here, we are in a bad state. */
        default:
            retval = ERROR_LIBCPARSE_COMMENT_BAD_STATE;
            goto done;
    }

done:
    return retval;
}

/**
 * \brief Process a char event.
 *
 * \param scanner           The \ref comment_scanner for this operation.
 * \param ev                The raw character event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_char_event(comment_scanner* scanner, const event* ev)
{
    int retval;
    event_raw_character* rev;

    /* dynamic cast the message. */
    retval = event_downcast_to_event_raw_character(&rev, (event*)ev);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* cache the character. */
    int ch = event_raw_character_get(rev);

    /* decode the current state. */
    switch (scanner->state)
    {
        case CPARSE_COMMENT_SCANNER_STATE_INIT:
            retval = process_char_event_init(scanner, rev, ch);
            goto done;

        case CPARSE_COMMENT_SCANNER_STATE_SLASH:
            retval = process_char_event_slash(scanner, rev, ch);
            goto done;

        case CPARSE_COMMENT_SCANNER_STATE_IN_BLOCK_COMMENT:
            retval = process_char_event_block(scanner, rev, ch);
            goto done;

        case CPARSE_COMMENT_SCANNER_STATE_IN_BLOCK_COMMENT_STAR:
            retval = process_char_event_block_star(scanner, rev, ch);
            goto done;

        case CPARSE_COMMENT_SCANNER_STATE_IN_LINE_COMMENT:
            retval = process_char_event_line(scanner, rev, ch);
            goto done;

        case CPARSE_COMMENT_SCANNER_STATE_IN_STRING:
            retval = process_char_event_string(scanner, rev, ch);
            goto done;

        case CPARSE_COMMENT_SCANNER_STATE_IN_STRING_BACKSLASH:
            retval = process_char_event_string_backslash(scanner, rev, ch);
            goto done;

        case CPARSE_COMMENT_SCANNER_STATE_IN_CHAR_SEQUENCE:
            retval = process_char_event_char_seq(scanner, rev, ch);
            goto done;

        case CPARSE_COMMENT_SCANNER_STATE_IN_CHAR_SEQUENCE_BACKSLASH:
            retval = process_char_event_char_seq_backslash(scanner, rev, ch);
            goto done;

        /* If we make it here, we are in a bad state. */
        default:
            retval = ERROR_LIBCPARSE_COMMENT_BAD_STATE;
            goto done;
    }

done:
    return retval;
}

/**
 * \brief Process a char event in init state.
 *
 * \param scanner           The \ref comment_scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_char_event_init(
    comment_scanner* scanner, const event_raw_character* ev, int ch)
{
    const cursor* pos;
    int retval;

    /* decode the character. */
    switch (ch)
    {
        case '/':
            /* get the event position. */
            pos =
                event_get_cursor(event_raw_character_upcast(
                    (event_raw_character*)ev));
            /* cache the current position. */
            retval = file_position_cache_set(scanner->cache, pos->file, pos);
            if (STATUS_SUCCESS != retval)
            {
                return retval;
            }
            /* we are now in the slash state. */
            scanner->state = CPARSE_COMMENT_SCANNER_STATE_SLASH;
            return STATUS_SUCCESS;

        case '"':
            /* we are now in the string state. */
            scanner->state = CPARSE_COMMENT_SCANNER_STATE_IN_STRING;
            /* broadcast the quote. */
            return
                event_reactor_broadcast(
                    scanner->reactor,
                    event_raw_character_upcast((event_raw_character*)ev));

        case '\'':
            /* we are now in the char sequence state. */
            scanner->state = CPARSE_COMMENT_SCANNER_STATE_IN_CHAR_SEQUENCE;
            /* broadcast the tick. */
            return
                event_reactor_broadcast(
                    scanner->reactor,
                    event_raw_character_upcast((event_raw_character*)ev));

        default:
            /* broadcast this event to all subscribers. */
            return
                event_reactor_broadcast(
                    scanner->reactor,
                    event_raw_character_upcast((event_raw_character*)ev));
    }
}

/**
 * \brief Process a char event in slash state.
 *
 * \param scanner           The \ref comment_scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_char_event_slash(
    comment_scanner* scanner, const event_raw_character* ev, int ch)
{
    int retval;

    /* decode the character. */
    switch (ch)
    {
        case '*':
            scanner->state = CPARSE_COMMENT_SCANNER_STATE_IN_BLOCK_COMMENT;
            return begin_block_comment_broadcast(scanner, ev);

        case '/':
            scanner->state = CPARSE_COMMENT_SCANNER_STATE_IN_LINE_COMMENT;
            return begin_line_comment_broadcast(scanner, ev);

        default:
            /* send the slash event to all subscribers. */
            retval =
                file_position_cache_raw_character_broadcast(
                    scanner->cache, scanner->reactor, '/');
            if (STATUS_SUCCESS != retval)
            {
                return retval;
            }

            /* clear the cache. */
            file_position_cache_clear(scanner->cache);

            /* we are now in the init state. */
            scanner->state = CPARSE_COMMENT_SCANNER_STATE_INIT;

            /* broadcast this event to all subscribers. */
            return
                event_reactor_broadcast(
                    scanner->reactor,
                    event_raw_character_upcast((event_raw_character*)ev));
    }
}

/**
 * \brief Process a char event in block state.
 *
 * \param scanner           The \ref comment_scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_char_event_block(
    comment_scanner* scanner, const event_raw_character* ev, int ch)
{
    const cursor* pos;
    int retval;

    /* decode the character. */
    switch (ch)
    {
        case '*':
            /* get the event position. */
            pos =
                event_get_cursor(event_raw_character_upcast(
                    (event_raw_character*)ev));
            /* cache the current position. */
            retval = file_position_cache_set(scanner->cache, pos->file, pos);
            if (STATUS_SUCCESS != retval)
            {
                return retval;
            }
            /* we are now in the block star state. */
            scanner->state = CPARSE_COMMENT_SCANNER_STATE_IN_BLOCK_COMMENT_STAR;
            return STATUS_SUCCESS;

        default:
            /* broadcast this event to all subscribers. */
            return
                event_reactor_broadcast(
                    scanner->reactor,
                    event_raw_character_upcast((event_raw_character*)ev));
    }
}

/**
 * \brief Process a char event in block star state.
 *
 * \param scanner           The \ref comment_scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_char_event_block_star(
    comment_scanner* scanner, const event_raw_character* ev, int ch)
{
    const cursor* pos;
    int retval;

    /* decode the character. */
    switch (ch)
    {
        case '/':
            scanner->state = CPARSE_COMMENT_SCANNER_STATE_INIT;
            return end_block_comment_broadcast(scanner, ev);

        case '*':
            /* send the previous star event to all subscribers. */
            retval =
                file_position_cache_raw_character_broadcast(
                    scanner->cache, scanner->reactor, '*');
            if (STATUS_SUCCESS != retval)
            {
                return retval;
            }

            /* clear the cache. */
            file_position_cache_clear(scanner->cache);

            /* get the event position. */
            pos =
                event_get_cursor(event_raw_character_upcast(
                    (event_raw_character*)ev));

            /* cache the current position. */
            retval = file_position_cache_set(scanner->cache, pos->file, pos);
            if (STATUS_SUCCESS != retval)
            {
                return retval;
            }

            /* we are now in the block star state. */
            scanner->state = CPARSE_COMMENT_SCANNER_STATE_IN_BLOCK_COMMENT_STAR;
            return STATUS_SUCCESS;

        default:
            /* send the star event to all subscribers. */
            retval =
                file_position_cache_raw_character_broadcast(
                    scanner->cache, scanner->reactor, '*');
            if (STATUS_SUCCESS != retval)
            {
                return retval;
            }

            /* clear the cache. */
            file_position_cache_clear(scanner->cache);

            /* we are now in the in block comment event state. */
            scanner->state = CPARSE_COMMENT_SCANNER_STATE_IN_BLOCK_COMMENT;

            /* broadcast this event to all subscribers. */
            return
                event_reactor_broadcast(
                    scanner->reactor,
                    event_raw_character_upcast((event_raw_character*)ev));
    }
}

/**
 * \brief Process a char event in line state.
 *
 * \param scanner           The \ref comment_scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_char_event_line(
    comment_scanner* scanner, const event_raw_character* ev, int ch)
{
    /* decode the character. */
    switch (ch)
    {
        case '\n':
            scanner->state = CPARSE_COMMENT_SCANNER_STATE_INIT;
            return
                end_line_comment_broadcast(
                    scanner,
                    event_raw_character_upcast((event_raw_character*)ev));

        default:
            /* broadcast this event to all subscribers. */
            return
                event_reactor_broadcast(
                    scanner->reactor,
                    event_raw_character_upcast((event_raw_character*)ev));
    }
}

/**
 * \brief Process a char event in string state.
 *
 * \param scanner           The \ref comment_scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_char_event_string(
    comment_scanner* scanner, const event_raw_character* ev, int ch)
{
    /* decode the character. */
    switch (ch)
    {
        case '"':
            /* an end quote ends our string state. */
            scanner->state = CPARSE_COMMENT_SCANNER_STATE_INIT;
            /* broadcast the quote. */
            return
                event_reactor_broadcast(
                    scanner->reactor,
                    event_raw_character_upcast((event_raw_character*)ev));

        case '\\':
            /* a backslash starts an escape. */
            scanner->state = CPARSE_COMMENT_SCANNER_STATE_IN_STRING_BACKSLASH;
            /* broadcast the backslash. */
            return
                event_reactor_broadcast(
                    scanner->reactor,
                    event_raw_character_upcast((event_raw_character*)ev));

        default:
            /* broadcast this event to all subscribers. */
            return
                event_reactor_broadcast(
                    scanner->reactor,
                    event_raw_character_upcast((event_raw_character*)ev));
    }
}

/**
 * \brief Process a char event in string bockslash state.
 *
 * \param scanner           The \ref comment_scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_char_event_string_backslash(
    comment_scanner* scanner, const event_raw_character* ev, int ch)
{
    (void)ch;

    /* no matter the character, we return to string state. */
    scanner->state = CPARSE_COMMENT_SCANNER_STATE_IN_STRING;

    /* broadcast the character. */
    return
        event_reactor_broadcast(
            scanner->reactor,
            event_raw_character_upcast((event_raw_character*)ev));
}

/**
 * \brief Process a char event in char sequence state.
 *
 * \param scanner           The \ref comment_scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_char_event_char_seq(
    comment_scanner* scanner, const event_raw_character* ev, int ch)
{
    /* decode the character. */
    switch (ch)
    {
        case '\'':
            /* an end quote ends our character sequence state. */
            scanner->state = CPARSE_COMMENT_SCANNER_STATE_INIT;
            /* broadcast the quote. */
            return
                event_reactor_broadcast(
                    scanner->reactor,
                    event_raw_character_upcast((event_raw_character*)ev));

        case '\\':
            /* a backslash starts an escape. */
            scanner->state =
                CPARSE_COMMENT_SCANNER_STATE_IN_CHAR_SEQUENCE_BACKSLASH;
            /* broadcast the backslash. */
            return
                event_reactor_broadcast(
                    scanner->reactor,
                    event_raw_character_upcast((event_raw_character*)ev));

        default:
            /* broadcast this event to all subscribers. */
            return
                event_reactor_broadcast(
                    scanner->reactor,
                    event_raw_character_upcast((event_raw_character*)ev));
    }
}

/**
 * \brief Process a char event in char sequence bockslash state.
 *
 * \param scanner           The \ref comment_scanner for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The character to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_char_event_char_seq_backslash(
    comment_scanner* scanner, const event_raw_character* ev, int ch)
{
    (void)ch;

    /* no matter the character, we return to character sequence state. */
    scanner->state = CPARSE_COMMENT_SCANNER_STATE_IN_CHAR_SEQUENCE;

    /* broadcast the character. */
    return
        event_reactor_broadcast(
            scanner->reactor,
            event_raw_character_upcast((event_raw_character*)ev));
}

/**
 * \brief Broadcast a begin block comment event.
 *
 * \param scanner           The \ref comment_scanner for this operation.
 * \param ev                The raw character event for the star.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int begin_block_comment_broadcast(
    comment_scanner* scanner, const event_raw_character* ev)
{
    int retval, release_retval;
    const cursor* pos1;
    cursor pos;
    event bev;

    const cursor* starpos =
        event_get_cursor(event_raw_character_upcast((event_raw_character*)ev));

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos1);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* copy the cached position. */
    memcpy(&pos, pos1, sizeof(pos));

    /* update the end column and line. */
    pos.end_line = starpos->end_line;
    pos.end_col = starpos->end_col;

    /* initialize the begin block comment event. */
    retval = event_init_for_comment_block_begin(&bev, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this message. */
    retval = event_reactor_broadcast(scanner->reactor, &bev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_bev;
    }

    /* clear the cache. */
    file_position_cache_clear(scanner->cache);

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_bev;

cleanup_bev:
    release_retval = event_dispose(&bev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    memset(&pos, 0, sizeof(pos));

    return retval;
}

/**
 * \brief Broadcast an end block comment event.
 *
 * \param scanner           The \ref comment_scanner for this operation.
 * \param ev                The raw character event for the star.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int end_block_comment_broadcast(
    comment_scanner* scanner, const event_raw_character* ev)
{
    int retval, release_retval;
    const cursor* pos1;
    cursor pos;
    event bev;

    const cursor* slashpos =
        event_get_cursor(event_raw_character_upcast((event_raw_character*)ev));

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos1);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* copy the cached position. */
    memcpy(&pos, pos1, sizeof(pos));

    /* update the end column and line. */
    pos.end_line = slashpos->end_line;
    pos.end_col = slashpos->end_col;

    /* initialize the end block comment event. */
    retval = event_init_for_comment_block_end(&bev, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this message. */
    retval = event_reactor_broadcast(scanner->reactor, &bev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_bev;
    }

    /* clear the cache. */
    file_position_cache_clear(scanner->cache);

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_bev;

cleanup_bev:
    release_retval = event_dispose(&bev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    memset(&pos, 0, sizeof(pos));

    return retval;
}

/**
 * \brief Broadcast a begin line comment event.
 *
 * \param scanner           The \ref comment_scanner for this operation.
 * \param ev                The raw character event for the star.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int begin_line_comment_broadcast(
    comment_scanner* scanner, const event_raw_character* ev)
{
    int retval, release_retval;
    const cursor* pos1;
    cursor pos;
    event lev;

    const cursor* slashpos =
        event_get_cursor(event_raw_character_upcast((event_raw_character*)ev));

    /* get the cached position. */
    retval = file_position_cache_position_get(scanner->cache, &pos1);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* copy the cached position. */
    memcpy(&pos, pos1, sizeof(pos));

    /* update the end column and line. */
    pos.end_line = slashpos->end_line;
    pos.end_col = slashpos->end_col;

    /* initialize the begin line comment event. */
    retval = event_init_for_comment_line_begin(&lev, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this message. */
    retval = event_reactor_broadcast(scanner->reactor, &lev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_lev;
    }

    /* clear the cache. */
    file_position_cache_clear(scanner->cache);

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_lev;

cleanup_lev:
    release_retval = event_dispose(&lev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    memset(&pos, 0, sizeof(pos));

    return retval;
}

/**
 * \brief Broadcast an end line comment event.
 *
 * \param scanner           The \ref comment_scanner for this operation.
 * \param ev                The raw character event for the star.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int end_line_comment_broadcast(
    comment_scanner* scanner, const event* ev)
{
    int retval, release_retval;
    cursor pos;
    event lev;

    const cursor* newlinepos = event_get_cursor(ev);

    /* copy the cached position. */
    memcpy(&pos, newlinepos, sizeof(pos));

    /* initialize the end line comment event. */
    retval = event_init_for_comment_line_end(&lev, &pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this message. */
    retval = event_reactor_broadcast(scanner->reactor, &lev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_lev;
    }

    /* rebroadcast the newline / EOF event. */
    retval = event_reactor_broadcast(scanner->reactor, ev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_lev;
    }

    /* clear the cache. */
    file_position_cache_clear(scanner->cache);

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_lev;

cleanup_lev:
    release_retval = event_dispose(&lev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    memset(&pos, 0, sizeof(pos));

    return retval;
}
