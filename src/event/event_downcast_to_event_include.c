/**
 * \file src/event/event_downcast_to_event_include.c
 *
 * \brief Attempt to downcast an \ref event to an \ref event_include.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/include.h>
#include <libcparse/status_codes.h>

CPARSE_IMPORT_event;
CPARSE_IMPORT_event_include;

/**
 * \brief Attempt to downcast an \ref event to an \ref event_include.
 *
 * \param inc_ev            Pointer to the event pointer to receive the downcast
 *                          instance on success.
 * \param ev                The \ref event pointer to attempt to downcast to the
 *                          derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_downcast_to_event_include)(
    CPARSE_SYM(event_include)** inc_ev, CPARSE_SYM(event)* ev)
{
    /* decode the event type. */
    switch (event_get_type(ev))
    {
        case CPARSE_EVENT_TYPE_PREPROCESSOR_SYSTEM_INCLUDE:
        case CPARSE_EVENT_TYPE_PREPROCESSOR_LOCAL_INCLUDE:
            break;

        default:
            return ERROR_LIBCPARSE_BAD_CAST;
    }

    /* cast this event. */
    *inc_ev = (event_include*)ev;
    return STATUS_SUCCESS;
}
