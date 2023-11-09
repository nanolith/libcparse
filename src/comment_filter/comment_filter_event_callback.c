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
#include <libcparse/event_reactor.h>
#include <libcparse/status_codes.h>

#include "comment_filter_internal.h"

CPARSE_IMPORT_comment_filter;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_reactor;

static int process_char_event(comment_filter* filter, const event* ev);

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
    comment_filter* filter = (comment_filter*)context;

    switch (event_get_type(ev))
    {
        case CPARSE_EVENT_TYPE_EOF:
            return event_reactor_broadcast(filter->reactor, ev);

        case CPARSE_EVENT_TYPE_RAW_CHARACTER:
            return process_char_event(filter, ev);

        default:
            return STATUS_SUCCESS;
    }
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
    return event_reactor_broadcast(filter->reactor, ev);
}
