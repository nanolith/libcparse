/**
 * \file
 * src/newline_preserving_whitespace_filter/newline_preserving_whitespace_filter_event_callback.c
 *
 * \brief The \ref newline_preserving_whitespace_filter event handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <ctype.h>
#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/event_reactor.h>
#include <libcparse/file_position_cache.h>
#include <libcparse/newline_preserving_whitespace_filter.h>
#include <libcparse/status_codes.h>

#include "newline_preserving_whitespace_filter_internal.h"

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_raw_character;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_file_position_cache;
CPARSE_IMPORT_newline_preserving_whitespace_filter;

static int process_char_event(
    newline_preserving_whitespace_filter* filter, const event* ev);
static int process_char_event_init_state(
    newline_preserving_whitespace_filter* filter, const event_raw_character* ev,
    int ch);
static int process_char_event_whitespace_state(
    newline_preserving_whitespace_filter* filter, const event_raw_character* ev,
    int ch);
static int process_eof_event(
    newline_preserving_whitespace_filter* filter, const event* ev);
static int broadcast_newline_event(
    newline_preserving_whitespace_filter* filter, const cursor* pos);
static int init_whitespace_transition(
    newline_preserving_whitespace_filter* filter, const cursor* pos);
static int whitespace_init_transition(
    newline_preserving_whitespace_filter* filter,
    const event_raw_character* ev);

/**
 * \brief Event handler callback for
 * \ref newline_preserving_whitespace_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref newline_preserving_whitespace_filter instance).
 * \param ev                An event for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(newline_preserving_whitespace_filter_event_callback)(
    void* context, const CPARSE_SYM(event)* ev)
{
    newline_preserving_whitespace_filter* filter =
        (newline_preserving_whitespace_filter*)context;

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
 * \param filter            The filter for this operation.
 * \param ev                The raw character event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_eof_event(
    newline_preserving_whitespace_filter* filter, const event* ev)
{
    return event_reactor_broadcast(filter->reactor, ev);
}

/**
 * \brief Process a raw character event.
 *
 * \param filter            The filter for this operation.
 * \param ev                The raw character event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_char_event(
    newline_preserving_whitespace_filter* filter, const event* ev)
{
    int retval;
    const event_raw_character* rev;

    /* downcast the character event. */
    retval =
        event_downcast_to_event_raw_character(
            (event_raw_character**)&rev, (event*)ev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* get the character for the event. */
    int ch = event_raw_character_get(rev);

    switch (filter->state)
    {
        /* forward non-whitespace characters. */
        case CPARSE_NL_WHITESPACE_FILTER_STATE_INIT:
            return process_char_event_init_state(filter, rev, ch);

        /* compress whitespace characters. */
        case CPARSE_NL_WHITESPACE_FILTER_STATE_IN_WHITESPACE:
            return process_char_event_whitespace_state(filter, rev, ch);

        default:
            return ERROR_LIBCPARSE_WHITESPACE_BAD_STATE;
    }
}

/**
 * \brief Process a raw character event in the init state.
 *
 * \param filter            The filter for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The raw character to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_char_event_init_state(
    newline_preserving_whitespace_filter* filter, const event_raw_character* ev,
    int ch)
{
    const event* oev = event_raw_character_upcast((event_raw_character*)ev);
    const cursor* pos = event_get_cursor(oev);

    switch (ch)
    {
        case '\n':
            return broadcast_newline_event(filter, pos);

        default:
            if (isspace(ch))
            {
                return init_whitespace_transition(filter, pos);
            }
            else
            {
                return
                    event_reactor_broadcast(filter->reactor, oev);
            }
    }
}

/**
 * \brief Process a raw character event in the whitespace state.
 *
 * \param filter            The filter for this operation.
 * \param ev                The raw character event to process.
 * \param ch                The raw character to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_char_event_whitespace_state(
    newline_preserving_whitespace_filter* filter, const event_raw_character* ev,
    int ch)
{
    switch (ch)
    {
        default:
            if (isspace(ch))
            {
                /* TODO - extend cache position to include this position. */

                /* eat whitespace character. */
                return STATUS_SUCCESS;
            }
            else
            {
                return whitespace_init_transition(filter, ev);
            }
    }
}

/**
 * \brief Broadcast a newline event to all subscribers.
 *
 * \param filter        The filter for this operation.
 * \param pos           The cursor position for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_newline_event(
    newline_preserving_whitespace_filter* filter, const cursor* pos)
{
    int retval, release_retval;
    event ev;

    /* initialize the newline event. */
    retval = event_init(&ev, CPARSE_EVENT_TYPE_TOKEN_NEWLINE, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval = event_reactor_broadcast(filter->reactor, &ev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_ev;
    }

    /* success. */
    retval = STATUS_SUCCESS;
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
 * \brief Transition from the init state to the whitespace state.
 *
 * \param filter            The filter for this operation.
 * \param pos               The cursor position for the whitespace event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int init_whitespace_transition(
    newline_preserving_whitespace_filter* filter, const cursor* pos)
{
    int retval;

    /* cache this position. */
    retval = file_position_cache_set(filter->cache, pos->file, pos);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* we are now in the whitespace state. */
    filter->state = CPARSE_NL_WHITESPACE_FILTER_STATE_IN_WHITESPACE;
    return STATUS_SUCCESS;
}

/**
 * \brief Transition from the whitespace state to the init state.
 *
 * \param filter            The filter for this operation.
 * \param pos               The cursor position for the whitespace event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int whitespace_init_transition(
    newline_preserving_whitespace_filter* filter, const event_raw_character* ev)
{
    int retval;

    /* get the base event. */
    const event* oev = event_raw_character_upcast((event_raw_character*)ev);

    /* TODO - replace this with a proper whitespace event. */
    retval =
        file_position_cache_raw_character_broadcast(
            filter->cache, filter->reactor, ' ');
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* clear the cache. */
    file_position_cache_clear(filter->cache);

    /* send the character event. */
    retval = event_reactor_broadcast(filter->reactor, oev);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* we are now in the init state. */
    filter->state = CPARSE_NL_WHITESPACE_FILTER_STATE_INIT;
    return STATUS_SUCCESS;
}
