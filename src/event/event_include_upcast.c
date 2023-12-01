/**
 * \file src/event/event_include_upcast.c
 *
 * \brief Upcast an \ref event_include to its base type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/include.h>

/**
 * \brief Upcast an \ref event_include to an \ref event.
 *
 * \param ev                The \ref event_include to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_include_upcast)(
    CPARSE_SYM(event_include)* ev)
{
    return &ev->hdr;
}
