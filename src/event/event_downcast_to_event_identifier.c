/**
 * \file src/event/event_downcast_to_event_identifier.c
 *
 * \brief Attempt to downcast an \ref event instance to an \ref event_identifier
 * instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/identifier.h>
#include <libcparse/status_codes.h>

CPARSE_IMPORT_event;
CPARSE_IMPORT_event_identifier;

/**
 * \brief Attempt to downcast an \ref event to an \ref event_identifier.
 *
 * \param i_ev              Pointer to the event pointer to receive the downcast
 *                          instance on success.
 * \param ev                The \ref event pointer to attempt to downcast to the
 *                          derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_downcast_to_event_identifier)(
    CPARSE_SYM(event_identifier)** i_ev, CPARSE_SYM(event)* ev)
{
    switch (event_get_type(ev))
    {
        case CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER:
            *i_ev = (event_identifier*)ev;
            return STATUS_SUCCESS;

        default:
            return ERROR_LIBCPARSE_BAD_CAST;
    }
}
