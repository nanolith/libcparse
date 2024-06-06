/**
 * \file libcparse/event/raw_float.h
 *
 * \brief The \ref event_raw_float type represents a raw floating point literal
 * token event before it has been differentiated into a numerical value.
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
 * \brief The raw float event type represents a partially interpreted floating
 * point constant token.
 */
typedef struct CPARSE_SYM(event_raw_float_token)
CPARSE_SYM(event_raw_float_token);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of an \ref event_raw_float_token
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
int CPARSE_SYM(event_raw_float_token_init)(
    CPARSE_SYM(event_raw_float_token)* ev, const CPARSE_SYM(cursor)* cursor,
    const char* val);

/**
 * \brief Perform an in-place disposal of an \ref event_raw_float_token
 * instance.
 *
 * \param ev                Pointer to the event to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_raw_float_token_dispose)(
    CPARSE_SYM(event_raw_float_token)* ev);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the raw float value.
 *
 * \param ev                The event for this operation.
 *
 * \returns the string representation of the raw float value.
 */
const char* CPARSE_SYM(event_raw_float_token_string_get)(
    const CPARSE_SYM(event_raw_float_token)* ev);

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
int CPARSE_SYM(event_raw_float_token_sign_set)(
    CPARSE_SYM(event_raw_float_token)* ev, bool sign);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
