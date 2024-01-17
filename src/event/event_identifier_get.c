/**
 * \file src/event/event_identifier_get.c
 *
 * \brief Get the identifier associated with this \ref \ref event_identifier
 * instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/identifier.h>

/**
 * \brief Get the identifier value for this event.
 *
 * \param ev                The event instance to query.
 *
 * \returns the line value for this event.
 */
const char* CPARSE_SYM(event_identifier_get)(
    const CPARSE_SYM(event_identifier)* ev)
{
    return ev->id;
}
