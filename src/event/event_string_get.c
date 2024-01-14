/**
 * \file src/event/event_string_get.c
 *
 * \brief Get the string associated with this \ref \ref event_string instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/string.h>

/**
 * \brief Get the string value for this event.
 *
 * \param ev                The event instance to query.
 *
 * \returns the line value for this event.
 */
const char* CPARSE_SYM(event_string_get)(
    const CPARSE_SYM(event_string)* ev)
{
    return ev->str;
}
