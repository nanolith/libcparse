/**
 * \file libcparse/event_copy.h
 *
 * \brief The event copy type allows an event to be cloned so that its lifetime
 * exceeds the lifetime of the original event on which it was based.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event_fwd.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The event copy type abstracts cloned events.
 */
typedef struct CPARSE_SYM(event_copy) CPARSE_SYM(event_copy);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create an event copy from the given event.
 *
 * \param cpy                   Pointer to the \ref event_copy pointer to
 *                              receive this \ref event_copy on success.
 * \param ev                    The event to copy.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_copy_create)(
    CPARSE_SYM(event_copy)** cpy, const CPARSE_SYM(event)* ev);

/**
 * \brief Release an \ref event_copy instance.
 *
 * \param cpy                   Pointer to the \ref event_copy to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_copy_release)(CPARSE_SYM(event_copy)* cpy);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get a pointer to the \ref event for this \ref event_copy.
 *
 * \param cpy                   The \ref event_copy to query.
 *
 * \returns the \ref event for this copy.
 */
const CPARSE_SYM(event)*  CPARSE_SYM(event_copy_get_event)(
    const CPARSE_SYM(event_copy)* cpy);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_event_copy_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(event_copy) sym ## event_copy; \
    static inline int FN_DECL_MUST_CHECK sym ## event_copy_create( \
        CPARSE_SYM(event_copy)** x, const CPARSE_SYM(event)* y) { \
            return CPARSE_SYM(event_copy_create)(x,y); } \
    static inline int sym ## event_copy_release( \
        CPARSE_SYM(event_copy)* x) { \
            return CPARSE_SYM(event_copy_release)(x); } \
    static inline const CPARSE_SYM(event)* sym ## event_copy_get_event( \
        const CPARSE_SYM(event_copy)* x) { \
            return CPARSE_SYM(event_copy_get_event)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_copy_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_copy_sym(sym ## _)
#define CPARSE_IMPORT_event_copy \
    __INTERNAL_CPARSE_IMPORT_event_copy_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
