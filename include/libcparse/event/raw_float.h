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

/**
 * \brief Attempt to downcast an \ref event to an \ref event_raw_float_token.
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
int CPARSE_SYM(event_downcast_to_event_raw_float_token)(
    CPARSE_SYM(event_raw_float_token)** s_ev, CPARSE_SYM(event)* ev);

/**
 * \brief Upcast an \ref event_raw_float_token to an \ref event.
 *
 * \param ev                The \ref event_raw_float_token to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_raw_float_token_upcast)(
    CPARSE_SYM(event_raw_float_token)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_event_raw_float_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(event_raw_float_token) \
    sym ## event_raw_float_token; \
    static inline int sym ## event_raw_float_token_init( \
        CPARSE_SYM(event_raw_float_token)* x, const CPARSE_SYM(cursor)* y, \
        const char* z) { \
            return CPARSE_SYM(event_raw_float_token_init)(x,y,z); } \
    static inline int sym ## event_raw_float_token_dispose( \
        CPARSE_SYM(event_raw_float_token)* x) { \
            return CPARSE_SYM(event_raw_float_token_dispose)(x); } \
    static inline const char* sym ## event_raw_float_token_string_get( \
        const CPARSE_SYM(event_raw_float_token)* x) { \
            return CPARSE_SYM(event_raw_float_token_string_get)(x); } \
    static inline int sym ## event_raw_float_token_sign_set( \
        CPARSE_SYM(event_raw_float_token)* x, bool y) { \
            return CPARSE_SYM(event_raw_float_token_sign_set)(x,y); } \
    static int sym ## event_downcast_to_event_raw_float_token( \
        CPARSE_SYM(event_raw_float_token)** x, CPARSE_SYM(event)* y) { \
            return CPARSE_SYM(event_downcast_to_event_raw_float_token)(x,y); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_raw_float_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_raw_float_sym(sym ## _)
#define CPARSE_IMPORT_event_raw_float \
    __INTERNAL_CPARSE_IMPORT_event_raw_float_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
