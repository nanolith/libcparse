/**
 * \file src/event/event_integer_init_for_unsigned_internal.c
 *
 * \brief Internal init method for unsigned integers.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/integer.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "event_internal.h"

CPARSE_IMPORT_event_internal;

/**
 * \brief Perform an in-place initialization of an unsigned \ref
 * event_integer_token instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param integer_type      The integer type.
 * \param val               The integer value.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_integer_init_for_unsigned_internal)(
    CPARSE_SYM(event_integer_token)* ev, int integer_type,
    const CPARSE_SYM(cursor)* cursor, unsigned long long val)
{
    int retval;

    /* clear instance memory. */
    memset(ev, 0, sizeof(*ev));

    /* initialize base type. */
    retval =
        event_init(
            &ev->hdr, CPARSE_EVENT_TYPE_TOKEN_VALUE_INTEGER,
            CPARSE_EVENT_CATEGORY_INTEGER_TOKEN, cursor);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* fill in event details. */
    ev->integer_type = integer_type;
    ev->val.unsigned_val = val;

    /* success. */
    return STATUS_SUCCESS;
}
