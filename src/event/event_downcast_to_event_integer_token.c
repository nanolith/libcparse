/**
 * \file src/event/event_downcast_to_event_integer_token.c
 *
 * \brief Attempt to downcast an \ref event to an \ref event_integer_token.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/integer.h>
#include <libcparse/status_codes.h>

CPARSE_IMPORT_event_integer;

/**
 * \brief Attempt to downcast an \ref event to an \ref event_integer_token.
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
int CPARSE_SYM(event_downcast_to_event_integer_token)(
    CPARSE_SYM(event_integer_token)** s_ev, CPARSE_SYM(event)* ev)
{
    /* verify that this is the correct type. */
    if (CPARSE_EVENT_TYPE_TOKEN_VALUE_INTEGER == ev->event_type)
    {
        *s_ev = (event_integer_token*)ev;
        return STATUS_SUCCESS;
    }

    return ERROR_LIBCPARSE_BAD_CAST;
}
