/**
 * \file src/event/event_string_init.c
 *
 * \brief Init method for the \ref event_string type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/string.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "event_string_internal.h"

CPARSE_IMPORT_event_string_internal;

/**
 * \brief Perform an in-place initialization of an \ref event_string instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param str               The string value for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_string_init)(
    CPARSE_SYM(event_string)* ev, const CPARSE_SYM(cursor)* cursor,
    const char* str)
{
    return
        event_string_init_internal(
            ev, CPARSE_EVENT_TYPE_TOKEN_VALUE_STRING, cursor, str);
}
