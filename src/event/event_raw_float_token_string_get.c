/**
 * \file src/event/event_raw_float_token_string_get.c
 *
 * \brief Get the string representation of this raw float token.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/raw_float.h>

/**
 * \brief Get the raw float value.
 *
 * \param ev                The event for this operation.
 *
 * \returns the string representation of the raw float value.
 */
const char* CPARSE_SYM(event_raw_float_token_string_get)(
    const CPARSE_SYM(event_raw_float_token)* ev)
{
    return ev->val;
}
