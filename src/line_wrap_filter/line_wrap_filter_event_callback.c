/**
 * \file src/line_wrap_filter/line_wrap_filter_event_callback.c
 *
 * \brief The \ref line_wrap_filter event handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/raw_character.h>
#include <libcparse/event_reactor.h>
#include <libcparse/line_wrap_filter.h>
#include <libcparse/status_codes.h>

#include "line_wrap_filter_internal.h"

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_raw_character;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_file_position_cache;
CPARSE_IMPORT_line_wrap_filter;

static int process_char_event(line_wrap_filter* filter, const event* ev);
static int process_eof_event(line_wrap_filter* filter, const event* ev);
static int raw_character_broadcast(
    line_wrap_filter* filter, const event* ev, int ch);
static int line_wrap_broadcast(line_wrap_filter* filter);
static int double_char_broadcast(line_wrap_filter* filter, const event* ev);

/**
 * \brief Event handler callback for \ref line_wrap_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref line_wrap_filter instance).
 * \param ev                An event for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(line_wrap_filter_event_callback)(
    void* context, const CPARSE_SYM(event)* ev)
{
    line_wrap_filter* filter = (line_wrap_filter*)context;

    switch (event_get_type(ev))
    {
        case CPARSE_EVENT_TYPE_EOF:
            return process_eof_event(filter, ev);

        case CPARSE_EVENT_TYPE_RAW_CHARACTER:
            return process_char_event(filter, ev);

        default:
            return STATUS_SUCCESS;
    }
}

/**
 * \brief Process an eof event.
 *
 * \param filter            The \ref line_wrap_filter for this operation.
 * \param ev                The raw character event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_eof_event(line_wrap_filter* filter, const event* ev)
{
    int retval;

    /* if we are in the char state, broadcast a newline. */
    if (CPARSE_LINE_WRAP_FILTER_STATE_CHAR == filter->state)
    {
        retval = raw_character_broadcast(filter, ev, '\n');
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }
    }

    /* broadcast the EOF. */
    return event_reactor_broadcast(filter->reactor, ev);
}

/**
 * \brief Process a character event.
 *
 * \param filter            The \ref line_wrap_filter for this operation.
 * \param ev                The raw character event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_char_event(line_wrap_filter* filter, const event* ev)
{
    event_raw_character* rev;

    /* get the raw character event. */
    int retval = event_downcast_to_event_raw_character(&rev, (event*)ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    int ch = event_raw_character_get(rev);

    switch (filter->state)
    {
        case CPARSE_LINE_WRAP_FILTER_STATE_INIT:
        case CPARSE_LINE_WRAP_FILTER_STATE_CHAR:
            /* reset on newline. */
            if ('\n' == ch)
            {
                filter->state = CPARSE_LINE_WRAP_FILTER_STATE_INIT;

                /* broadcast this event. */
                return event_reactor_broadcast(filter->reactor, ev);
            }
            /* forward non-slash characters. */
            else if ('\\' != ch)
            {
                /* there is a character on this line. */
                filter->state = CPARSE_LINE_WRAP_FILTER_STATE_CHAR;

                /* broadcast this event. */
                return event_reactor_broadcast(filter->reactor, ev);
            }
            else
            {
                /* we are in the slash state now. */
                filter->state = CPARSE_LINE_WRAP_FILTER_STATE_SLASH;

                /* get the position. */
                const cursor* pos = event_get_cursor(ev);

                /* cache this state. */
                return file_position_cache_set(filter->cache, pos->file, pos);
            }

        case CPARSE_LINE_WRAP_FILTER_STATE_SLASH:
            /* replace newline with space. */
            if ('\n' == ch)
            {
                filter->state = CPARSE_LINE_WRAP_FILTER_STATE_INIT;

                /* broadcast both events. */
                return line_wrap_broadcast(filter);
            }
            /* for any other character, broadcast both. */
            else
            {
                filter->state = CPARSE_LINE_WRAP_FILTER_STATE_CHAR;

                /* broadcast both characters. */
                return double_char_broadcast(filter, ev);
            }

        default:
            return ERROR_LIBCPARSE_COMMENT_BAD_STATE;
    }
}

/**
 * \brief Broadcast a raw character event.
 *
 * \param filter            The \ref line_wrap_filter for this operation.
 * \param ev                The event to harvest for position data.
 * \param ch                The character to broadcast.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int raw_character_broadcast(
    line_wrap_filter* filter, const event* ev, int ch)
{
    int retval, release_retval;
    event_raw_character rch;

    /* get the position of the event. */
    const cursor* pos = event_get_cursor(ev);

    /* initialize this event. */
    retval =
        event_raw_character_init(
            &rch, CPARSE_EVENT_TYPE_RAW_CHARACTER, pos, ch);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval =
        event_reactor_broadcast(
            filter->reactor, event_raw_character_upcast(&rch));
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_rch;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_rch;

cleanup_rch:
    release_retval = event_raw_character_dispose(&rch);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Broadcast a line wrap in place of the original escape.
 *
 * \param filter            The \ref line_wrap_filter for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int line_wrap_broadcast(line_wrap_filter* filter)
{
    int retval;

    /* broadcast the truncated space. */
    retval =
        file_position_cache_raw_character_broadcast(
            filter->cache, filter->reactor, ' ');

    /* clear the cache. */
    file_position_cache_clear(filter->cache);

    /* return the broadcast status. */
    return retval;
}

/**
 * \brief Broadcast the backslash and the given character.
 *
 * \param filter            The \ref line_wrap_filter for this operation.
 * \param ch                The character to broadcast.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int double_char_broadcast(line_wrap_filter* filter, const event* ev)
{
    int retval;

    /* broadcast the backslash. */
    retval =
        file_position_cache_raw_character_broadcast(
            filter->cache, filter->reactor, '\\');
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* broadcast the character. */
    return event_reactor_broadcast(filter->reactor, ev);
}
