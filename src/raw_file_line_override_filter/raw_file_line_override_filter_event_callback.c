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
#include <libcparse/event_reactor.h>
#include <libcparse/raw_file_line_override_filter.h>
#include <libcparse/status_codes.h>

#include "raw_file_line_override_filter_internal.h"

CPARSE_IMPORT_event;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_raw_file_line_override_filter;

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

        default:
            return STATUS_SUCCESS;
    }
}
