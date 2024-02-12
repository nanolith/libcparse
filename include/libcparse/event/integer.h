/**
 * \file libcparse/event/integer.h
 *
 * \brief The \ref event_integer_token type represents integer token events.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/function_decl.h>
#include <libcparse/integer_type.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The integer event type represents an integer constant token.
 */
typedef struct CPARSE_SYM(event_integer_token) CPARSE_SYM(event_integer_token);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of a signed int \ref
 * event_integer_token instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The value of this token
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_integer_token_init_for_signed_int)(
    CPARSE_SYM(event_integer_token)* ev, const CPARSE_SYM(cursor)* cursor,
    int val);

/**
 * \brief Perform an in-place initialization of an unsigned int \ref
 * event_integer_token instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The value of this token
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_integer_token_init_for_unsigned_int)(
    CPARSE_SYM(event_integer_token)* ev, const CPARSE_SYM(cursor)* cursor,
    unsigned int val);

/**
 * \brief Perform an in-place initialization of a signed long \ref
 * event_integer_token instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The value of this token
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_integer_token_init_for_signed_long)(
    CPARSE_SYM(event_integer_token)* ev, const CPARSE_SYM(cursor)* cursor,
    long val);

/**
 * \brief Perform an in-place initialization of an unsigned long \ref
 * event_integer_token instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The value of this token
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_integer_token_init_for_unsigned_long)(
    CPARSE_SYM(event_integer_token)* ev, const CPARSE_SYM(cursor)* cursor,
    unsigned long val);

/**
 * \brief Perform an in-place initialization of a signed long long \ref
 * event_integer_token instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The value of this token
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_integer_token_init_for_signed_long_long)(
    CPARSE_SYM(event_integer_token)* ev, const CPARSE_SYM(cursor)* cursor,
    long long val);

/**
 * \brief Perform an in-place initialization of an unsigned long long \ref
 * event_integer_token instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The value of this token
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_integer_token_init_for_unsigned_long_long)(
    CPARSE_SYM(event_integer_token)* ev, const CPARSE_SYM(cursor)* cursor,
    unsigned long long val);

/**
 * \brief Perform an in-place disposal of an \ref event_integer_token instance.
 *
 * \param ev                Pointer to the event to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_integer_token_dispose)(
    CPARSE_SYM(event_integer_token)* ev);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Attempt to downcast an \ref event to an \ref event_integer_token.
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
int CPARSE_SYM(event_downcast_to_event_integer_token)(
    CPARSE_SYM(event_integer_token)** s_ev, CPARSE_SYM(event)* ev);

/**
 * \brief Upcast an \ref event_integer_token to an \ref event.
 *
 * \param ev                The \ref event_integer_token to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_integer_token_upcast)(
    CPARSE_SYM(event_integer_token)* ev);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
