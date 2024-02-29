/**
 * \file src/event/event_raw_integer_token_sign_set.c
 *
 * \brief Set the sign of the raw integer token.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/raw_integer.h>
#include <libcparse/status_codes.h>
#include <string.h>

/**
 * \brief Set the sign flag.
 *
 * \param ev                The event for this operation.
 * \param sign              The sign flag.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_raw_integer_token_sign_set)(
    CPARSE_SYM(event_raw_integer_token)* ev, bool sign)
{
    ev->has_sign = sign;

    return STATUS_SUCCESS;
}
