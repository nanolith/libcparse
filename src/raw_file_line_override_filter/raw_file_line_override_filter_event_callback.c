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

#include "raw_file_line_override_filter_internal.h"

CPARSE_IMPORT_event;
CPARSE_IMPORT_event_raw_character;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_raw_file_line_override_filter;

static int broadcast_char_event(
    raw_file_line_override_filter* filter, const event* ev);

/**
 * \brief Event handler callback for \ref raw_file_line_override_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref raw_file_line_override_filter instance).
 * \param ev                A message for this handler.
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
    int retval;
    event_raw_character* rev;

    /* dynamic cast the message. */
    retval = event_downcast_to_event_raw_character(&rev, (event*)ev);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* TODO - initialize a local raw character event so we can override the
     * cursor position.
     */

    /* broadcast this event to all subscribers. */
    retval = event_reactor_broadcast(filter->reactor, ev);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* success. */
    goto done;

done:
    return retval;
}
