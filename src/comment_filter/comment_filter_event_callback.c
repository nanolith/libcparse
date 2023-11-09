/**
 * \file src/comment_filter/comment_filter_event_callback.c
 *
 * \brief The \ref comment_filter event handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>

#include "comment_filter_internal.h"

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
    (void)context;
    (void)ev;

    return STATUS_SUCCESS;
}
