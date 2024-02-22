/**
 * \file src/event/event_integer_token_init_for_signed_long_long.c
 *
 * \brief Initialize a signed long long \ref event_integer_token instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "event_integer_internal.h"

CPARSE_IMPORT_event_integer_internal;

/**
 * \brief Perform an in-place initialization of a signed long long \ref
 * event_integer_token instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The value of this token
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_integer_token_init_for_signed_long_long)(
    CPARSE_SYM(event_integer_token)* ev, const CPARSE_SYM(cursor)* cursor,
    long long val)
{
    return
        event_integer_init_for_signed_internal(
            ev, CPARSE_INTEGER_TYPE_SIGNED_LONG_LONG, cursor, val);
}
