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
#include <libcparse/event/string.h>
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

/**
 * \brief Perform an in-place initialization of an \ref event_raw_string_token
 * instance for the system string type.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The raw string representation of this token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_raw_string_token_init_for_system_string)(
    CPARSE_SYM(event_raw_string_token)* ev, const CPARSE_SYM(cursor)* cursor,
    const char* val);

/**
 * \brief Perform an in-place disposal of an \ref event_raw_string_token
 * instance.
 *
 * \param ev                Pointer to the event to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_raw_string_token_dispose)(
    CPARSE_SYM(event_raw_string_token)* ev);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the raw string value.
 *
 * \param ev                The event for this operation.
 *
 * \returns the string representation of the raw integer value.
 */
const char* CPARSE_SYM(event_raw_string_token_get)(
    const CPARSE_SYM(event_raw_string_token)* ev);

/**
 * \brief Convert this token to a string token.
 *
 * \param s_ev              Pointer to the \ref event_string to be
 *                          initialized with this conversion on success.
 * \param ev                The event to convert.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_raw_string_token_convert)(
    CPARSE_SYM(event_string)* s_ev,
    const CPARSE_SYM(event_raw_string_token)* ev);

/**
 * \brief Attempt to downcast an \ref event to an \ref event_raw_string_token.
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
int CPARSE_SYM(event_downcast_to_event_raw_string_token)(
    CPARSE_SYM(event_raw_string_token)** s_ev, CPARSE_SYM(event)* ev);

/**
 * \brief Upcast an \ref event_raw_string_token to an \ref event.
 *
 * \param ev                The \ref event_raw_string_token to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_raw_string_token_upcast)(
    CPARSE_SYM(event_raw_string_token)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_event_raw_string_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(event_raw_string_token) \
    sym ## event_raw_string_token; \
    static inline int sym ## event_raw_string_token_init( \
        CPARSE_SYM(event_raw_string_token)* x, const CPARSE_SYM(cursor)* y, \
        const char* z) { \
            return CPARSE_SYM(event_raw_string_token_init)(x,y,z); } \
    static inline int sym ## event_raw_string_token_init_for_system_string( \
        CPARSE_SYM(event_raw_string_token)* x, const CPARSE_SYM(cursor)* y, \
        const char* z) { \
            return \
                CPARSE_SYM(event_raw_string_token_init_for_system_string)( \
                    x,y,z); } \
    static inline int sym ## event_raw_string_token_dispose( \
        CPARSE_SYM(event_raw_string_token)* x) { \
            return CPARSE_SYM(event_raw_string_token_dispose)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_raw_string_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_raw_string_sym(sym ## _)
#define CPARSE_IMPORT_event_raw_string \
    __INTERNAL_CPARSE_IMPORT_event_raw_string_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
