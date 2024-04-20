/**
 * \file src/event/event_raw_string_token_init_for_system_string.c
 *
 * \brief System string init method for the \ref event_raw_string_token type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/raw_string.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "event_raw_string_internal.h"

CPARSE_IMPORT_event_raw_string_internal;

/**
 * \brief Perform an in-place initialization of an \ref event_raw_string_token
 * instance for the system string type.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The raw string representation of this token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_raw_string_token_init_for_system_string)(
    CPARSE_SYM(event_raw_string_token)* ev, const CPARSE_SYM(cursor)* cursor,
    const char* val)
{
    return
        event_raw_string_token_init_internal(
            ev, CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_SYSTEM_STRING, cursor, val);
}
