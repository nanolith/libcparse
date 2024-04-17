/**
 * \file libcparse/event/raw_string.h
 *
 * \brief The \ref event_raw_string_token type represents a raw string token
 * that hasn't yet been fully interpreted.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/function_decl.h>
#include <stdint.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The raw string event type represents a partially interpreted string
 * constant token.
 */
typedef struct CPARSE_SYM(event_raw_string_token)
CPARSE_SYM(event_raw_string_token);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of an \ref event_raw_string_token
 * instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The raw string representation of this token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_raw_string_token_init)(
    CPARSE_SYM(event_raw_string_token)* ev, const CPARSE_SYM(cursor)* cursor,
    const char* val);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
