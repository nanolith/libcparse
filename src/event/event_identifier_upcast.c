/**
 * \file src/event/event_identifier_upcast.c
 *
 * \brief Upcast an \ref event_identifier to an \ref event.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/identifier.h>

/**
 * \brief Upcast an \ref event_identifier to an \ref event.
 *
 * \param ev                The \ref event_identifier to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_identifier_upcast)(
    CPARSE_SYM(event_identifier)* ev)
{
    return &ev->hdr;
}
