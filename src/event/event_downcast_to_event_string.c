/**
 * \file src/event/event_downcast_to_event_string.c
 *
 * \brief Attempt to downcast an \ref event instance to an \ref event_string
 * instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/string.h>
#include <libcparse/status_codes.h>

CPARSE_IMPORT_event;
CPARSE_IMPORT_event_string;

/**
 * \brief Attempt to downcast an \ref event to an \ref event_string.
 *
 * \param s_ev              Pointer to the event pointer to receive the downcast
 *                          instance on success.
 * \param ev                The \ref event pointer to attempt to downcast to the
 *                          derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_downcast_to_event_string)(
    CPARSE_SYM(event_string)** s_ev, CPARSE_SYM(event)* ev)
{
    switch (event_get_type(ev))
    {
        case CPARSE_EVENT_TYPE_TOKEN_VALUE_STRING:
        case CPARSE_EVENT_TYPE_TOKEN_VALUE_SYSTEM_STRING:
            *s_ev = (event_string*)ev;
            return STATUS_SUCCESS;

        default:
            return ERROR_LIBCPARSE_BAD_CAST;
    }
}
