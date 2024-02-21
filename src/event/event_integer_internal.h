/**
 * \file event/event_integer_internal.h
 *
 * \brief Internal declarations for the \ref event_integer_token type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event/integer.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/******************************************************************************/
/* Start of private constructors.                                             */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of a signed \ref
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
int CPARSE_SYM(event_integer_init_for_signed_internal)(
    CPARSE_SYM(event_string)* ev, int event_type,
    const CPARSE_SYM(cursor)* cursor, const char* str);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
