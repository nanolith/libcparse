/**
 * \file src/event/event_integer_token_is_signed.c
 *
 * \brief Returns true if the integer token type is signed.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "event_integer_internal.h"

/**
 * \brief Return true if the integer type is signed and false otherwise.
 *
 * \param ev                The event to query.
 */
bool CPARSE_SYM(event_integer_token_is_signed)(
    const CPARSE_SYM(event_integer_token)* ev)
{
    switch (ev->integer_type)
    {
        case CPARSE_INTEGER_TYPE_SIGNED_INT:
        case CPARSE_INTEGER_TYPE_SIGNED_LONG:
        case CPARSE_INTEGER_TYPE_SIGNED_LONG_LONG:
            return true;

        default:
            return false;
    }
}
