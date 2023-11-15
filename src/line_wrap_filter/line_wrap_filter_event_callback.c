/**
 * \file src/line_wrap_filter/line_wrap_filter_event_callback.c
 *
 * \brief The \ref line_wrap_filter event handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>

#include "line_wrap_filter_internal.h"

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
    (void)context;
    (void)ev;

    return STATUS_SUCCESS;
}
