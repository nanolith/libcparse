/**
 * \file src/event/event_integer_token_coerce_int8.c
 *
 * \brief Perform a potentially lossy conversion to an int8.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/integer.h>

#include "event_integer_internal.h"

CPARSE_IMPORT_event_integer_internal;

/**
 * \brief Perform a potentially lossy conversion to int8_t.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int8_t CPARSE_SYM(event_integer_token_coerce_int8)(
    const CPARSE_SYM(event_integer_token)* ev)
{
    if (event_integer_token_is_signed(ev))
    {
        return (int8_t)ev->val.signed_val;
    }
    else
    {
        return (int8_t)ev->val.unsigned_val;
    }
}
