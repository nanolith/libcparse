/**
 * \file
 * src/raw_file_line_override_filter/raw_file_line_override_filter_event_callback.c
 *
 * \brief The \ref raw_file_line_override_filter event handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/event_reactor.h>
#include <libcparse/raw_file_line_override_filter.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "raw_file_line_override_filter_internal.h"

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_raw_character;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_raw_file_line_override_filter;

static int broadcast_char_event(
    raw_file_line_override_filter* filter, const event* ev);
static void update_cursor(cursor* pos, int ch);

/**
 * \brief Event handler callback for \ref raw_file_line_override_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref raw_file_line_override_filter instance).
 * \param ev                An event for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(raw_file_line_override_filter_event_callback)(
    void* context, const CPARSE_SYM(event)* ev)
{
    raw_file_line_override_filter* filter =
        (raw_file_line_override_filter*)context;

    switch (event_get_type(ev))
    {
        case CPARSE_EVENT_TYPE_EOF:
            return event_reactor_broadcast(filter->reactor, ev);

        case CPARSE_EVENT_TYPE_RAW_CHARACTER:
            return broadcast_char_event(filter, ev);

        default:
            return STATUS_SUCCESS;
    }
}

/**
 * \brief Broadcast a character event, possibly overriding the cursor position.
 *
 * \param filter            The filter for this operation.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_char_event(
    raw_file_line_override_filter* filter, const event* ev)
{
    int retval, release_retval;
    event_raw_character* rev;
    event_raw_character newrev;
    cursor pos;

    /* dynamic cast the message. */
    retval = event_downcast_to_event_raw_character(&rev, (event*)ev);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    const cursor* ev_pos = event_get_cursor(ev);
    int ch = event_raw_character_get(rev);

    /* override the file and line. */
    if (filter->use_pos)
    {
        /* copy our override position. */
        memcpy(&pos, &filter->pos, sizeof(pos));

        /* set the file if not overridden. */
        if (NULL == pos.file)
        {
            pos.file = ev_pos->file;
        }

        /* update our position. */
        update_cursor(&filter->pos, ch);
    }
    /* use the original position. */
    else
    {
        /* copy the position from the event. */
        memcpy(&pos, ev_pos, sizeof(pos));
    }

    /* initialize our override event. */
    retval = event_raw_character_init(&newrev, &pos, ch);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_pos;
    }

    /* broadcast this event to all subscribers. */
    retval =
        event_reactor_broadcast(
            filter->reactor, event_raw_character_upcast(&newrev));
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_newrev;
    }

    /* success. */
    goto cleanup_newrev;

cleanup_pos:
    memset(&pos, 0, sizeof(pos));

cleanup_newrev:
    release_retval = event_raw_character_dispose(&newrev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Update a cursor with the given character.
 *
 * \param pos               The cursor to update.
 * \param ch                The character to use to update this cursor.
 */
static void update_cursor(cursor* pos, int ch)
{
    switch (ch)
    {
        case '\n':
            pos->begin_line += 1;
            pos->end_line = pos->begin_line;
            pos->begin_col = pos->end_col = 1;
            break;

        default:
            pos->begin_col += 1;
            pos->end_col = pos->begin_col;
            break;
    }
}
