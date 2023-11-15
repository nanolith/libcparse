/**
 * \file src/comment_filter/comment_filter_event_callback.c
 *
 * \brief The \ref comment_filter event handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/comment_filter.h>
#include <libcparse/event.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/event_reactor.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "comment_filter_internal.h"

CPARSE_IMPORT_comment_filter;
CPARSE_IMPORT_comment_filter_internal;
CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_raw_character;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_file_position_cache;

static int process_char_event(comment_filter* filter, const event* ev);
static int process_eof_event(comment_filter* filter, const event* ev);

/**
 * \brief Event handler callback for \ref comment_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref commant_filter instance).
 * \param ev                An event for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_filter_event_callback)(
    void* context, const CPARSE_SYM(event)* ev)
{
    const cursor* pos;
    int retval;
    comment_filter* filter = (comment_filter*)context;

    switch (event_get_type(ev))
    {
        case CPARSE_EVENT_TYPE_EOF:
            return process_eof_event(filter, ev);

        case CPARSE_EVENT_TYPE_RAW_CHARACTER:
            return process_char_event(filter, ev);

        case CPARSE_EVENT_TYPE_COMMENT_BLOCK_BEGIN:
            /* get the current position. */
            pos = event_get_cursor(ev);

            /* cache the current position. */
            retval = file_position_cache_set(filter->cache, pos->file, pos);
            if (STATUS_SUCCESS != retval)
            {
                return retval;
            }

            /* we are now in the block comment state. */
            filter->state = CPARSE_COMMENT_FILTER_STATE_IN_BLOCK_COMMENT;
            return STATUS_SUCCESS;

        case CPARSE_EVENT_TYPE_COMMENT_BLOCK_END:
            /* broadcast a space character event. */
            retval =
                file_position_cache_raw_character_broadcast(
                    filter->cache, filter->reactor, ' ');
            if (STATUS_SUCCESS != retval)
            {
                return retval;
            }

            /* clear the cache. */
            file_position_cache_clear(filter->cache);

            /* we are now in the init state. */
            filter->state = CPARSE_COMMENT_FILTER_STATE_INIT;
            return STATUS_SUCCESS;

        case CPARSE_EVENT_TYPE_COMMENT_LINE_BEGIN:
            /* we are now in the line comment state. */
            filter->state = CPARSE_COMMENT_FILTER_STATE_IN_LINE_COMMENT;
            return STATUS_SUCCESS;

        case CPARSE_EVENT_TYPE_COMMENT_LINE_END:
            /* we are now in the init state. */
            filter->state = CPARSE_COMMENT_FILTER_STATE_INIT;
            return STATUS_SUCCESS;

        default:
            return STATUS_SUCCESS;
    }
}

/**
 * \brief Process an eof event.
 *
 * \param filter            The \ref comment_filter for this operation.
 * \param ev                The raw character event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_eof_event(comment_filter* filter, const event* ev)
{
    return event_reactor_broadcast(filter->reactor, ev);
}

/**
 * \brief Process a raw character event.
 *
 * \param filter            The \ref comment_filter for this operation.
 * \param ev                The raw character event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_char_event(comment_filter* filter, const event* ev)
{
    switch (filter->state)
    {
        /* forward non-comment characters. */
        case CPARSE_COMMENT_FILTER_STATE_INIT:
            return event_reactor_broadcast(filter->reactor, ev);

        /* skip comment characters. */
        case CPARSE_COMMENT_FILTER_STATE_IN_BLOCK_COMMENT:
        case CPARSE_COMMENT_FILTER_STATE_IN_LINE_COMMENT:
            return STATUS_SUCCESS;

        default:
            return ERROR_LIBCPARSE_COMMENT_BAD_STATE;
    }
}
