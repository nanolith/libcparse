/**
 * \file src/event/event_raw_character_literal_get.c
 *
 * \brief Get the source file representation of the
 * \ref event_raw_character_literal constant.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/raw_character_literal.h>

/**
 * \brief Get the raw character literal value.
 *
 * \param ev                The event for this operation.
 *
 * \returns the string representation of the raw integer value.
 */
const char* CPARSE_SYM(event_raw_character_literal_get)(
    const CPARSE_SYM(event_raw_character_literal)* ev)
{
    return ev->val;
}
