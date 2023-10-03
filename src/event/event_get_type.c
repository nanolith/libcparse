/**
 * \file src/event/event_get_type.c
 *
 * \brief Get the event type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <string.h>

#include "event_internal.h"

/**
 * \brief Get the event type for the given event.
 *
 * \param ev                    The event to query.
 *
 * \returns the \ref event_type for this event.
 */
int CPARSE_SYM(event_get_type)(const CPARSE_SYM(event)* ev)
{
    return ev->event_type;
}
