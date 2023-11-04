/**
 * \file src/comment_scanner/comment_scanner_event_callback.c
 *
 * \brief The \ref comment_scanner event handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "comment_scanner_internal.h"

/**
 * \brief Event handler callback for \ref comment_scanner.
 *
 * \param context           The context for this handler (the
 *                          \ref commant_scanner instance).
 * \param ev                An event for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_scanner_event_callback)(
    void* context, const CPARSE_SYM(event)* ev)
{
    (void)context;
    (void)ev;

    return -1;
}
