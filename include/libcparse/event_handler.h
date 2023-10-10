/**
 * \file libcparse/event_handler.h
 *
 * \brief The \ref event_handler reacts to an event.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief An event callback function responds to an event.
 *
 * \param context               A user-supplied context pointer given to the
 *                              callback.
 * \param ev                    An event to which this callback is subscribed.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
typedef int (*CPARSE_SYM(event_callback_fn))(
    void* context, const CPARSE_SYM(event)* ev);

/**
 * \brief An event handler accepts an event.
 */
typedef struct CPARSE_SYM(event_handler) CPARSE_SYM(event_handler);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Initialize an \ref event_handler from a callback function and
 * context.
 *
 * \param eh                    The event handler instance to initialize.
 * \param ecb                   The event callback function.
 * \param ectx                  The event handler user context.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_handler_init)(
    CPARSE_SYM(event_handler)* eh, CPARSE_SYM(event_callback_fn) ecb,
    void* ectx);

/**
 * \brief Initialize a \ref event_handler by copying another
 * \ref event_handler.
 *
 * \param eh                    The event handler instance to initialize.
 * \param ehc                   The event handler to copy.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_handler_init_copy)(
    CPARSE_SYM(event_handler)* eh, const CPARSE_SYM(event_handler)* ehc);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Send an event to the given event handler.
 *
 * \param eh                    The event handler to receive this event.
 * \param ev                    The event to send.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_handler_send)(
    CPARSE_SYM(event_handler)* eh, const CPARSE_SYM(event)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_CPARSE_IMPORT_event_handler_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(event_callback_fn) sym ## event_callback_fn; \
    typedef CPARSE_SYM(event_handler) sym ## event_handler; \
    static inline int sym ## event_handler_init( \
        CPARSE_SYM(event_handler)* x, CPARSE_SYM(event_callback_fn) y, \
        void* z) { \
            return CPARSE_SYM(event_handler_init)(x,y,z); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_handler_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_handler_sym(sym ## _)
#define CPARSE_IMPORT_event_handler \
    __INTERNAL_CPARSE_IMPORT_event_handler_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
