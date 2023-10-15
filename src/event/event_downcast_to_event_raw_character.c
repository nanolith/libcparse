/**
 * \file src/event/event_downcast_to_event_raw_character.c
 *
 * \brief Attempt to downcast an \ref event to an \ref event_raw_character.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/status_codes.h>

CPARSE_IMPORT_event;
CPARSE_IMPORT_event_raw_character;

/**
 * \brief Attempt to downcast an \ref event to an \ref event_raw_character.
 *
 * \param rc_ev             Pointer to the event pointer to receive the downcast
 *                          instance on success.
 * \param ev                The \ref event pointer to attempt to downcast to the
 *                          derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_downcast_to_event_raw_character)(
    CPARSE_SYM(event_raw_character)** rc_ev, CPARSE_SYM(event)* ev)
{
    /* verify that this is a raw character event. */
    if (CPARSE_EVENT_TYPE_RAW_CHARACTER != event_get_type(ev))
    {
        return ERROR_LIBCPARSE_BAD_CAST;
    }

    /* cast this event. */
    *rc_ev = (event_raw_character*)ev;
    return STATUS_SUCCESS;
}
