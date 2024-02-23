/**
 * \file src/event/event_integer_token_convert_to_unsigned_short.c
 *
 * \brief Attempt to convert an integer token to an unsigned short.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/integer.h>
#include <libcparse/status_codes.h>
#include <limits.h>

#include "event_integer_internal.h"

CPARSE_IMPORT_event_integer_internal;

/**
 * \brief Attempt to convert this \ref event_integer_token to an unsigned short,
 * returning a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_integer_token_convert_to_unsigned_short)(
    unsigned short* val, const CPARSE_SYM(event_integer_token)* ev)
{
    if (event_integer_token_is_signed(ev))
    {
        if (ev->val.signed_val <= USHRT_MAX && ev->val.signed_val >= 0)
        {
            *val = (unsigned short)ev->val.signed_val;
            return STATUS_SUCCESS;
        }
    }
    else
    {
        if (ev->val.unsigned_val <= USHRT_MAX)
        {
            *val = (unsigned short)ev->val.unsigned_val;
            return STATUS_SUCCESS;
        }
    }

    return ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION;
}
