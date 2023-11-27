/**
 * \file
 * src/newline_preserving_whitespace_filter/newline_preserving_whitespace_filter_event_callback.c
 *
 * \brief The \ref newline_preserving_whitespace_filter event handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event_reactor.h>
#include <libcparse/newline_preserving_whitespace_filter.h>
#include <libcparse/status_codes.h>

#include "newline_preserving_whitespace_filter_internal.h"

CPARSE_IMPORT_event;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_newline_preserving_whitespace_filter;

static int process_char_event(
    newline_preserving_whitespace_filter* filter, const event* ev);
static int process_eof_event(
    newline_preserving_whitespace_filter* filter, const event* ev);

/**
 * \brief Event handler callback for
 * \ref newline_preserving_whitespace_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref newline_preserving_whitespace_filter instance).
 * \param ev                An event for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(newline_preserving_whitespace_filter_event_callback)(
    void* context, const CPARSE_SYM(event)* ev)
{
    newline_preserving_whitespace_filter* filter =
        (newline_preserving_whitespace_filter*)context;

    switch (event_get_type(ev))
    {
        case CPARSE_EVENT_TYPE_EOF:
            return process_eof_event(filter, ev);

        case CPARSE_EVENT_TYPE_RAW_CHARACTER:
            return process_char_event(filter, ev);

        default:
            return STATUS_SUCCESS;
    }
}

/**
 * \brief Process an eof event.
 *
 * \param filter            The filter for this operation.
 * \param ev                The raw character event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_eof_event(
    newline_preserving_whitespace_filter* filter, const event* ev)
{
    return event_reactor_broadcast(filter->reactor, ev);
}

/**
 * \brief Process a raw character event.
 *
 * \param filter            The filter for this operation.
 * \param ev                The raw character event to process.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int process_char_event(
    newline_preserving_whitespace_filter* filter, const event* ev)
{
    switch (filter->state)
    {
        /* forward non-comment characters. */
        case CPARSE_NL_WHITESPACE_FILTER_STATE_INIT:
            return event_reactor_broadcast(filter->reactor, ev);

        default:
            return ERROR_LIBCPARSE_WHITESPACE_BAD_STATE;
    }
}
