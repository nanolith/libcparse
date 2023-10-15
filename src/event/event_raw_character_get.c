/**
 * \file src/event/event_raw_character_get.c
 *
 * \brief Get the character value for this event.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/raw_character.h>

/**
 * \brief Get the character value for this event.
 *
 * \param ev                The event instance to query.
 *
 * \returns the character value for this event.
 */
int CPARSE_SYM(event_raw_character_get)(
    const CPARSE_SYM(event_raw_character)* ev)
{
    return ev->raw_character;
}
