/**
 * \file src/event/event_raw_integer_token_upcast.c
 *
 * \brief Upcast an \ref event_raw_integer_token to its base \ref event
 * instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/raw_integer.h>

/**
 * \brief Upcast an \ref event_raw_integer_token to an \ref event.
 *
 * \param ev                The \ref event_raw_integer_token to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_raw_integer_token_upcast)(
    CPARSE_SYM(event_raw_integer_token)* ev)
{
    return &ev->hdr;
}
