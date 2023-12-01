/**
 * \file libcparse/event/raw_line.h
 *
 * \brief The \ref event_raw_line type indicates the scan of a raw preprocessor
 * control line.
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
typedef struct CPARSE_SYM(event_raw_line) CPARSE_SYM(event_raw_line);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of an \ref event_raw_line instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param event_type        The type of the event.
 * \param cursor            The event cursor.
 * \param line              The raw line for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_raw_line_init)(
    CPARSE_SYM(event_raw_line)* ev, int event_type,
    const CPARSE_SYM(cursor)* cursor, const char* line);

/**
 * \brief Perform an in-place disposal of an \ref event_raw_line instance.
 *
 * \param ev                Pointer to the event to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_raw_line_dispose)(CPARSE_SYM(event_raw_line)* ev);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the line value for this event.
 *
 * \param ev                The event instance to query.
 *
 * \returns the line value for this event.
 */
const char* CPARSE_SYM(event_raw_line_get)(
    const CPARSE_SYM(event_raw_line)* ev);

/**
 * \brief Attempt to downcast an \ref event to an \ref event_raw_line.
 *
 * \param rl_ev             Pointer to the event pointer to receive the downcast
 *                          instance on success.
 * \param ev                The \ref event pointer to attempt to downcast to the
 *                          derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_downcast_to_event_raw_line)(
    CPARSE_SYM(event_raw_line)** rl_ev, CPARSE_SYM(event)* ev);

/**
 * \brief Upcast an \ref event_raw_line to an \ref event.
 *
 * \param ev                The \ref event_raw_line to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_raw_line_upcast)(
    CPARSE_SYM(event_raw_line)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_event_raw_line_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(event_raw_line) sym ## event_raw_line; \
    static inline int sym ## event_raw_line_init( \
        CPARSE_SYM(event_raw_line)* w, int x, const CPARSE_SYM(cursor)* y, \
        const char* z) { \
            return CPARSE_SYM(event_raw_line_init)(w,x,y,z); } \
    static inline int sym ## event_raw_line_dispose( \
        CPARSE_SYM(event_raw_line)* x) { \
            return CPARSE_SYM(event_raw_line_dispose)(x); } \
    static inline const char* sym ## event_raw_line_get( \
        const CPARSE_SYM(event_raw_line)* x) { \
            return CPARSE_SYM(event_raw_line_get)(x); } \
    static inline int sym ## event_downcast_to_event_raw_line( \
        CPARSE_SYM(event_raw_line)** x, CPARSE_SYM(event)* y) { \
            return CPARSE_SYM(event_downcast_to_event_raw_line)(x,y); } \
    static inline CPARSE_SYM(event)* sym ## event_raw_line_upcast( \
        CPARSE_SYM(event_raw_line)* x) { \
            return CPARSE_SYM(event_raw_line_upcast)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_raw_line_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_raw_line_sym(sym ## _)
#define CPARSE_IMPORT_event_raw_line \
    __INTERNAL_CPARSE_IMPORT_event_raw_line_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
