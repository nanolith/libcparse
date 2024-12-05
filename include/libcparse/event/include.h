/**
 * \file libcparse/event/include.h
 *
 * \brief The \ref event_include type indicates the scan of a system
 * or local include preprocessor control line.
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
 * \brief The include event type indicates the scan of a single include
 * preprocessor control line.
 */
typedef struct CPARSE_SYM(event_include)
CPARSE_SYM(event_include);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of an \ref event_include instance
 * for a system include.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param file              The file to include for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_include_init_for_system_include)(
    CPARSE_SYM(event_include)* ev, const CPARSE_SYM(cursor)* cursor,
    const char* file);

/**
 * \brief Perform an in-place initialization of an \ref event_include instance
 * for a local include.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param file              The file to include for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_include_init_for_local_include)(
    CPARSE_SYM(event_include)* ev, const CPARSE_SYM(cursor)* cursor,
    const char* file);

/**
 * \brief Perform an in-place disposal of an \ref event_include instance.
 *
 * \param ev                Pointer to the event to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_include_dispose)(CPARSE_SYM(event_include)* ev);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the file value for this event.
 *
 * \param ev                The event instance to query.
 *
 * \returns the line value for this event.
 */
const char* CPARSE_SYM(event_include_file_get)(
    const CPARSE_SYM(event_include)* ev);

/**
 * \brief Attempt to downcast an \ref event to an \ref event_include.
 *
 * \param inc_ev            Pointer to the event pointer to receive the downcast
 *                          instance on success.
 * \param ev                The \ref event pointer to attempt to downcast to the
 *                          derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_downcast_to_event_include)(
    CPARSE_SYM(event_include)** inc_ev, CPARSE_SYM(event)* ev);

/**
 * \brief Upcast an \ref event_include to an \ref event.
 *
 * \param ev                The \ref event_include to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_include_upcast)(
    CPARSE_SYM(event_include)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_event_include_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(event_include) sym ## event_include; \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_include_init_for_system_include( \
        CPARSE_SYM(event_include)* x, const CPARSE_SYM(cursor)* y, \
        const char* z) { \
            return CPARSE_SYM(event_include_init_for_system_include)(x,y,z); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_include_init_for_local_include( \
        CPARSE_SYM(event_include)* x, const CPARSE_SYM(cursor)* y, \
        const char* z) { \
            return CPARSE_SYM(event_include_init_for_local_include)(x,y,z); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_include_dispose( \
        CPARSE_SYM(event_include)* x) { \
            return CPARSE_SYM(event_include_dispose)(x); } \
    static inline const char* sym ## event_include_file_get( \
        const CPARSE_SYM(event_include)* x) { \
            return CPARSE_SYM(event_include_file_get)(x); } \
    static inline int sym ## event_downcast_to_event_include( \
        CPARSE_SYM(event_include)** x, CPARSE_SYM(event)* y) { \
            return CPARSE_SYM(event_downcast_to_event_include)(x,y); } \
    static inline CPARSE_SYM(event)* sym ## event_include_upcast( \
        CPARSE_SYM(event_include)* x) { \
            return CPARSE_SYM(event_include_upcast)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_include_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_include_sym(sym ## _)
#define CPARSE_IMPORT_event_include \
    __INTERNAL_CPARSE_IMPORT_event_include_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
