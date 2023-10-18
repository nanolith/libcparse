/**
 * \file libcparse/event_reactor.h
 *
 * \brief The \ref event_reactor registers event handlers and broadcasts events
 * to them.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event_handler_fwd.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The event reactor provides event management support for a parser.
 */
typedef struct CPARSE_SYM(event_reactor) CPARSE_SYM(event_reactor);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create an \ref event_reactor instance.
 *
 * \param er                Pointer to the event reactor pointer to receive the
 *                          created instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_reactor_create)(CPARSE_SYM(event_reactor)** er);

/**
 * \brief Release an \ref event_reactor instance.
 *
 * \param er                The event reactor instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_reactor_release)(CPARSE_SYM(event_reactor)* er);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Add an \ref event_handler to the event reactor instance.
 *
 * \param er                The event reactor for this operation.
 * \param eh                The event handler to add to this reactor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_reactor_add)(
    CPARSE_SYM(event_reactor)* er, const CPARSE_SYM(event_handler)* eh);

/**
 * \brief Broadcast an event to all event handlers in this event reactor.
 *
 * \param er                The event reactor for this operation.
 * \param ev                The event to broadcast.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_reactor_broadcast)(
    CPARSE_SYM(event_reactor)* er, const CPARSE_SYM(event)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_event_reactor_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(event_reactor) sym ## event_reactor; \
    static inline int sym ## event_reactor_create( \
        CPARSE_SYM(event_reactor)** x) { \
            return CPARSE_SYM(event_reactor_create)(x); } \
    static inline int sym ## event_reactor_release( \
        CPARSE_SYM(event_reactor)* x) { \
            return CPARSE_SYM(event_reactor_release)(x); } \
    static inline int sym ## event_reactor_add( \
        CPARSE_SYM(event_reactor)* x, const CPARSE_SYM(event_handler)* y) { \
            return CPARSE_SYM(event_reactor_add)(x,y); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_reactor_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_reactor_sym(sym ## _)
#define CPARSE_IMPORT_event_reactor \
    __INTERNAL_CPARSE_IMPORT_event_reactor_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
