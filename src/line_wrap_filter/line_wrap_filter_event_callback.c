/**
 * \file src/line_wrap_filter/line_wrap_filter_event_callback.c
 *
 * \brief The \ref line_wrap_filter event handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_reactor.h>
#include <libcparse/line_wrap_filter.h>
#include <libcparse/status_codes.h>

#include "line_wrap_filter_internal.h"

CPARSE_IMPORT_event;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_line_wrap_filter;

static int process_eof_event(line_wrap_filter* filter, const event* ev);

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
    return event_reactor_broadcast(filter->reactor, ev);
}
