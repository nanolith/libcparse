/**
 * \file libcparse/event/raw_integer.h
 *
 * \brief The \ref event_raw_integer_token type represents a raw integer token
 * event before it has been differentiated into positive or negative values.
 *
 * The unary minus token, which is used to indicate that an integer constant is
 * in the negative two's complement form must be applied during a parsing step.
 * For instance, the parser must differentiate between the expressions
 * "x-5" and "-5". This matters because the constant -2147483648 is a valid
 * int value, but 2147483648 is not. So, we store this constant as a string,
 * and allow it to be converted to a \ref event_integer_token with or without a
 * negative sign applied.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/function_decl.h>
#include <libcparse/integer_type.h>
#include <stdint.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The raw integer event type represents a partially interpreted integer
 * constant token.
 */
typedef struct CPARSE_SYM(event_raw_integer_token)
CPARSE_SYM(event_raw_integer_token);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

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
    const char* val);

/**
 * \brief Perform an in-place disposal of an \ref event_raw_integer_token
 * instance.
 *
 * \param ev                Pointer to the event to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_raw_integer_token_dispose)(
    CPARSE_SYM(event_raw_integer_token)* ev);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

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
    CPARSE_SYM(event_raw_integer_token)* ev, bool sign);

/**
 * \brief Attempt to downcast an \ref event to an \ref event_raw_integer_token.
 *
 * \param s_ev              Pointer to the event pointer to receive the downcast
 *                          instance on success.
 * \param ev                The \ref event pointer to attempt to downcast to the
 *                          derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_downcast_to_event_raw_integer_token)(
    CPARSE_SYM(event_raw_integer_token)** s_ev, CPARSE_SYM(event)* ev);

/**
 * \brief Upcast an \ref event_raw_integer_token to an \ref event.
 *
 * \param ev                The \ref event_raw_integer_token to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_raw_integer_token_upcast)(
    CPARSE_SYM(event_raw_integer_token)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_event_raw_integer_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(event_raw_integer_token) \
    sym ## event_raw_integer_token; \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_raw_integer_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_raw_integer_sym(sym ## _)
#define CPARSE_IMPORT_event_raw_integer \
    __INTERNAL_CPARSE_IMPORT_event_raw_integer_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
