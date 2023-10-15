/**
 * \file libcparse/event/raw_character.h
 *
 * \brief The \ref event_raw_character type indicates the scan of a raw
 * character.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The raw character event type indicates the scan of a single raw
 * character.
 */
typedef struct CPARSE_SYM(event_raw_character) CPARSE_SYM(event_raw_character);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of an \ref event_raw_character
 * instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param event_type        The type of the event.
 * \param cursor            The event cursor.
 * \param ch                The raw character for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_raw_character_init)(
    CPARSE_SYM(event_raw_character)* ev, int event_type,
    const CPARSE_SYM(cursor)* cursor, int ch);

/**
 * \brief Perform an in-place disposal of an \ref event_raw_character instance.
 *
 * \param ev                Pointer to the event to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_raw_character_dispose)(
    CPARSE_SYM(event_raw_character)* ev);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the character value for this event.
 *
 * \param ev                The event instance to query.
 *
 * \returns the character value for this event.
 */
int CPARSE_SYM(event_raw_character_get)(
    const CPARSE_SYM(event_raw_character)* ev);

/**
 * \brief Attempt to downcast an \ref event to an \ref event_raw_character.
 *
 * \param rc_ev             Pointer to the event pointer to receive the downcast
 *                          instance on success.
 * \param ev                The \ref event pointer to attempt to downcast to the
 *                          derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_downcast_to_event_raw_character)(
    CPARSE_SYM(event_raw_character)** rc_ev, CPARSE_SYM(event)* ev);

/**
 * \brief Upcast an \ref event_raw_character to an \ref event.
 *
 * \param ev                The \ref event_raw_character to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_raw_character_upcast)(
    CPARSE_SYM(event_raw_character)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_event_raw_character_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(event_raw_character) sym ## event_raw_character; \
    static inline int sym ## event_raw_character_init( \
        CPARSE_SYM(event_raw_character)* w, int x, const CPARSE_SYM(cursor)* y,\
        int z) { \
            return CPARSE_SYM(event_raw_character_init)(w,x,y,z); } \
    static inline int sym ## event_raw_character_dispose( \
        CPARSE_SYM(event_raw_character)* x) { \
            return CPARSE_SYM(event_raw_character_dispose)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_raw_character_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_raw_character_sym(sym ## _)
#define CPARSE_IMPORT_event_raw_character \
    __INTERNAL_CPARSE_IMPORT_event_raw_character_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
