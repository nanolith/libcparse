/**
 * \file src/event/event_raw_string_token_get.c
 *
 * \brief Get the source file representation of the \ref event_raw_string_token
 * constant.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/raw_string.h>

/**
 * \brief Get the raw string value.
 *
 * \param ev                The event for this operation.
 *
 * \returns the string representation of the raw integer value.
 */
const char* CPARSE_SYM(event_raw_string_token_get)(
    const CPARSE_SYM(event_raw_string_token)* ev)
{
    return ev->str;
}
