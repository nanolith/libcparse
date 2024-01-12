/**
 * \file libcparse/event/string.h
 *
 * \brief The \ref event_string type represents string token events.
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
 * \brief The raw line event type indicates the scan of a single raw
 * preprocessor control line.
 */
typedef struct CPARSE_SYM(event_string) CPARSE_SYM(event_string);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of an \ref event_string instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param str               The string value for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_string_init)(
    CPARSE_SYM(event_string)* ev, const CPARSE_SYM(cursor)* cursor,
    const char* line);

/**
 * \brief Perform an in-place initialization of an \ref event_string instance
 * for system strings.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param str               The string value for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_string_init_for_system_string)(
    CPARSE_SYM(event_string)* ev, const CPARSE_SYM(cursor)* cursor,
    const char* line);

/**
 * \brief Perform an in-place disposal of an \ref event_string instance.
 *
 * \param ev                Pointer to the event to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_string_dispose)(CPARSE_SYM(event_string)* ev);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the string value for this event.
 *
 * \param ev                The event instance to query.
 *
 * \returns the line value for this event.
 */
const char* CPARSE_SYM(event_string_get)(
    const CPARSE_SYM(event_string)* ev);

/**
 * \brief Attempt to downcast an \ref event to an \ref event_string.
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
int CPARSE_SYM(event_downcast_to_event_string)(
    CPARSE_SYM(event_string)** s_ev, CPARSE_SYM(event)* ev);

/**
 * \brief Upcast an \ref event_string to an \ref event.
 *
 * \param ev                The \ref event_string to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_string_upcast)(
    CPARSE_SYM(event_string)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_event_string_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(event_string) sym ## event_string; \
    static inline int sym ## event_string_init( \
        CPARSE_SYM(event_string)* x, const CPARSE_SYM(cursor)* y, \
        const char* z) { \
            return CPARSE_SYM(event_string_init)(x,y,z); } \
    static inline int sym ## event_string_init_for_system_string( \
        CPARSE_SYM(event_string)* x, const CPARSE_SYM(cursor)* y, \
        const char* z) { \
            return CPARSE_SYM(event_string_init_for_system_string)(x,y,z); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_string_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_string_sym(sym ## _)
#define CPARSE_IMPORT_event_string \
    __INTERNAL_CPARSE_IMPORT_event_string_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
