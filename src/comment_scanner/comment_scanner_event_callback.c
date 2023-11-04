/**
 * \file src/comment_scanner/comment_scanner_event_callback.c
 *
 * \brief The \ref comment_scanner event handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/comment_scanner.h>
#include <libcparse/event.h>
#include <libcparse/event_reactor.h>
#include <libcparse/status_codes.h>

#include "comment_scanner_internal.h"

CPARSE_IMPORT_comment_scanner;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_reactor;

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
    comment_scanner* scanner = (comment_scanner*)context;

    switch (event_get_type(ev))
    {
        case CPARSE_EVENT_TYPE_EOF:
            return event_reactor_broadcast(scanner->reactor, ev);

        default:
            return STATUS_SUCCESS;
    }
}
