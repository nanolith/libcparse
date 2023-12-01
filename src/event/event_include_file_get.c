/**
 * \file src/event/event_include_file_get.c
 *
 * \brief Get the file value for this event.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/include.h>

/**
 * \brief Get the file value for this event.
 *
 * \param ev                The event instance to query.
 *
 * \returns the line value for this event.
 */
const char* CPARSE_SYM(event_include_file_get)(
    const CPARSE_SYM(event_include)* ev)
{
    return ev->file;
}
