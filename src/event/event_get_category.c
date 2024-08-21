/**
 * \file src/event/event_get_category.c
 *
 * \brief Get the event category.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/status_codes.h>
#include <string.h>

/**
 * \brief Get the event category for the given event.
 *
 * \param ev                    The event to query.
 *
 * \returns the \ref event_type for this event.
 */
int CPARSE_SYM(event_get_category)(const CPARSE_SYM(event)* ev)
{
    return ev->event_category;
}
