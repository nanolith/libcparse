/**
 * \file libcparse/event/raw_character_literal.h
 *
 * \brief The \ref event_raw_character_literal type represents a raw character
 * literal token that hasn't yet been fully interpreted.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/cursor.h>
#include <libcparse/event_fwd.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The raw string event type represents a partially interpreted string
 * constant token.
 */
typedef struct CPARSE_SYM(event_raw_character_literal)
CPARSE_SYM(event_raw_character_literal);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of an
 * \ref event_raw_character_literal instance.
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
int FN_DECL_MUST_CHECK CPARSE_SYM(event_raw_character_literal_init)(
    CPARSE_SYM(event_raw_character_literal)* ev,
    const CPARSE_SYM(cursor)* cursor, const char* val);

/**
 * \brief Perform an in-place disposal of an \ref event_raw_character_literal
 * instance.
 *
 * \param ev                Pointer to the event to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_raw_character_literal_dispose)(
    CPARSE_SYM(event_raw_character_literal)* ev);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the raw character literal value.
 *
 * \param ev                The event for this operation.
 *
 * \returns the string representation of the raw integer value.
 */
const char* CPARSE_SYM(event_raw_character_literal_get)(
    const CPARSE_SYM(event_raw_character_literal)* ev);

/**
 * \brief Attempt to downcast an \ref event to an
 * \ref event_raw_character_literal.
 *
 * \param c_ev              Pointer to the event pointer to receive the downcast
 *                          instance on success.
 * \param ev                The \ref event pointer to attempt to downcast to the
 *                          derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_downcast_to_event_raw_character_literal)(
    CPARSE_SYM(event_raw_character_literal)** c_ev, CPARSE_SYM(event)* ev);

/**
 * \brief Upcast an \ref event_raw_character_literal to an \ref event.
 *
 * \param ev                The \ref event_raw_character_literal to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_raw_character_literal_upcast)(
    CPARSE_SYM(event_raw_character_literal)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_event_raw_character_literal_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(event_raw_character_literal) \
    sym ## event_raw_character_literal; \
    static inline int sym ## event_raw_character_literal_init( \
        CPARSE_SYM(event_raw_character_literal)* x, \
        const CPARSE_SYM(cursor)* y, const char* z) { \
            return CPARSE_SYM(event_raw_character_literal_init)(x,y,z); } \
    static inline int sym ## event_raw_character_literal_dispose( \
        CPARSE_SYM(event_raw_character_literal)* x) { \
            return CPARSE_SYM(event_raw_character_literal_dispose)(x); } \
    static inline const char* sym ## event_raw_character_literal_get( \
        const CPARSE_SYM(event_raw_character_literal)* x) { \
            return CPARSE_SYM(event_raw_character_literal_get)(x); } \
    static inline int sym ## event_downcast_to_event_raw_character_literal( \
        CPARSE_SYM(event_raw_character_literal)** x, CPARSE_SYM(event)* y) { \
            return \
                CPARSE_SYM(event_downcast_to_event_raw_character_literal)( \
                    x, y); } \
    static inline CPARSE_SYM(event)* \
    sym ## event_raw_character_literal_upcast( \
        CPARSE_SYM(event_raw_character_literal)* x) { \
            return CPARSE_SYM(event_raw_character_literal_upcast)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_raw_character_literal_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_raw_character_literal_sym(sym ## _)
#define CPARSE_IMPORT_event_raw_character_literal \
    __INTERNAL_CPARSE_IMPORT_event_raw_character_literal_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
