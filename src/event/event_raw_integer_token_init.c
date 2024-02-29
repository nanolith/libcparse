/**
 * \file src/event/event_raw_integer_token_init.c
 *
 * \brief Initialize an \ref event_raw_integer_token.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/raw_integer.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "event_internal.h"

CPARSE_IMPORT_event_internal;

/**
 * \brief Perform an in-place initialization of an \ref event_raw_integer_token
 * instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The string representation of this token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_raw_integer_token_init)(
    CPARSE_SYM(event_raw_integer_token)* ev, const CPARSE_SYM(cursor)* cursor,
    const char* val)
{
    int retval;

    /* clear event memory. */
    memset(ev, 0, sizeof(*ev));

    /* initialize the base event. */
    retval =
        event_init(&ev->hdr, CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER, cursor);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* set the initial values. */
    ev->has_sign = false;
    ev->digits = val;

    /* success. */
    return STATUS_SUCCESS;
}
