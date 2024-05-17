/**
 * \file src/event/event_raw_character_literal_upcast.c
 *
 * \brief Upcast an \ref event_raw_character_literal_upcast to an \ref event.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/raw_character_literal.h>

/**
 * \brief Upcast an \ref event_raw_character_literal to an \ref event.
 *
 * \param ev                The \ref event_raw_character_literal to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_raw_character_literal_upcast)(
    CPARSE_SYM(event_raw_character_literal)* ev)
{
    return &ev->hdr;
}
