/**
 * \file src/preprocessor_scanner/preprocessor_scanner_event_callback.c
 *
 * \brief The \ref preprocessor_scanner event handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event_reactor.h>
#include <libcparse/preprocessor_scanner.h>
#include <libcparse/status_codes.h>

#include "preprocessor_scanner_internal.h"

CPARSE_IMPORT_event;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_preprocessor_scanner;

static int process_eof_event(
    preprocessor_scanner* scanner, const event* ev);

/**
 * \brief Event handler callback for \ref preprocessor_scanner_event_callback.
 *
 * \param context           The context for this handler (the
 *                          \ref preprocessor_scanner instance).
 * \param ev                An event for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(preprocessor_scanner_event_callback)(
    void* context, const CPARSE_SYM(event)* ev)
{
    preprocessor_scanner* scanner = (preprocessor_scanner*)context;

    switch (event_get_type(ev))
    {
        case CPARSE_EVENT_TYPE_EOF:
            return process_eof_event(scanner, ev);

        default:
            return STATUS_SUCCESS;
    }
}

/**
 * \brief Process an eof event.
 *
 * \param scanner           The scanner for this operation.
 * \param ev                The raw character event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_eof_event(
    preprocessor_scanner* scanner, const event* ev)
{
    switch (scanner->state)
    {
        default:
            return event_reactor_broadcast(scanner->reactor, ev);
    }
}
