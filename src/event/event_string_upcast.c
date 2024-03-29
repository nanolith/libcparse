/**
 * \file src/event/event_string_upcast.c
 *
 * \brief Upcast an \ref event_string to an \ref event.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/string.h>

/**
 * \brief Upcast an \ref event_string to an \ref event.
 *
 * \param ev                The \ref event_string to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_string_upcast)(
    CPARSE_SYM(event_string)* ev)
{
    return &ev->hdr;
}
