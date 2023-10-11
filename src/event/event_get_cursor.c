/**
 * \file src/event/event_get_cursor.c
 *
 * \brief Get the event cursor.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/status_codes.h>
#include <string.h>

/**
 * \brief Get the cursor for the given event.
 *
 * \param ev                    The event to query.
 *
 * \returns the \ref cursor for this event.
 */
const CPARSE_SYM(cursor)*
CPARSE_SYM(event_get_cursor)(const CPARSE_SYM(event)* ev)
{
    return &ev->event_cursor;
}
