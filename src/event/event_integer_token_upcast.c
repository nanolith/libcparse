/**
 * \file src/event/event_integer_token_upcast.c
 *
 * \brief Upcast this \ref event_integer_token to an \ref event instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/integer.h>
#include <libcparse/status_codes.h>

CPARSE_IMPORT_event_integer;

/**
 * \brief Upcast an \ref event_integer_token to an \ref event.
 *
 * \param ev                The \ref event_integer_token to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_integer_token_upcast)(
    CPARSE_SYM(event_integer_token)* ev)
{
    return &ev->hdr;
}
