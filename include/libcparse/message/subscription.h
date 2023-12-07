/**
 * \file libcparse/message/subscription.h
 *
 * \brief Messages to subscribe to parser endpoints.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event_handler.h>
#include <libcparse/function_decl.h>
#include <libcparse/message.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief the subscribe message allows a user to subscribe to an endpoint.
 */
typedef struct CPARSE_SYM(message_subscribe)
CPARSE_SYM(message_subscribe);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Initialize a \ref message_subscribe instance.
 *
 * \param msg               The message to initialize.
 * \param msg_type          The type of subscription message.
 * \param handler           The \ref event_handler to add to this endpoint.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_subscribe_init)(
    CPARSE_SYM(message_subscribe)* msg, int msg_type,
    CPARSE_SYM(event_handler)* handler);

/**
 * \brief Initialize a \ref message_subscribe instance for subscribing to the
 * comment filter.
 *
 * \param msg               The message to initialize.
 * \param handler           The \ref event_handler to add to this endpoint.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_subscribe_init_for_comment_filter)(
    CPARSE_SYM(message_subscribe)* msg, CPARSE_SYM(event_handler)* handler);

/**
 * \brief Initialize a \ref message_subscribe instance for subscribing to the
 * comment scanner.
 *
 * \param msg               The message to initialize.
 * \param handler           The \ref event_handler to add to this endpoint.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_subscribe_init_for_comment_scanner)(
    CPARSE_SYM(message_subscribe)* msg, CPARSE_SYM(event_handler)* handler);

/**
 * \brief Initialize a \ref message_subscribe instance for subscribing to the
 * line wrap filter.
 *
 * \param msg               The message to initialize.
 * \param handler           The \ref event_handler to add to this endpoint.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_subscribe_init_for_line_wrap_filter)(
    CPARSE_SYM(message_subscribe)* msg, CPARSE_SYM(event_handler)* handler);

/**
 * \brief Initialize a \ref message_subscribe instance for subscribing to the
 * newline preserving whitespace filter.
 *
 * \param msg               The message to initialize.
 * \param handler           The \ref event_handler to add to this endpoint.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_subscribe_init_for_nl_ws_filter)(
    CPARSE_SYM(message_subscribe)* msg, CPARSE_SYM(event_handler)* handler);

/**
 * \brief Initialize a \ref message_subscribe instance for subscribing to the
 * raw file line override filter.
 *
 * \param msg               The message to initialize.
 * \param handler           The \ref event_handler to add to this endpoint.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_subscribe_init_for_rflo_filter)(
    CPARSE_SYM(message_subscribe)* msg, CPARSE_SYM(event_handler)* handler);

/**
 * \brief Initialize a \ref message_subscribe instance for subscribing to the
 * raw stack scanner.
 *
 * \param msg               The message to initialize.
 * \param handler           The \ref event_handler to add to this endpoint.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_subscribe_init_for_raw_stack_scanner)(
    CPARSE_SYM(message_subscribe)* msg, CPARSE_SYM(event_handler)* handler);

/**
 * \brief Dispose of a \ref message_subscribe instance.
 *
 * \param msg               The message to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_subscribe_dispose)(CPARSE_SYM(message_subscribe)* msg);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the \ref event_handler associated with a \ref message_subscribe
 * instance.
 *
 * \param msg               The message to query.
 *
 * \returns the \ref event_handler associated with this message.
 */
const CPARSE_SYM(event_handler)*
CPARSE_SYM(message_subscribe_event_handler_get)(
    const CPARSE_SYM(message_subscribe)* msg);

/**
 * \brief Attempt to downcast a \ref message to a
 * \ref message_subscribe.
 *
 * \param sub_msg           Pointer to the message pointer to receive the
 *                          downcast instance on success.
 * \param msg               The \ref message pointer to attempt to downcast to
 *                          the derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_downcast_to_message_subscribe)(
    CPARSE_SYM(message_subscribe)** sub_msg, CPARSE_SYM(message)* msg);

/**
 * \brief Upcast a \ref message_subscribe to a \ref message.
 *
 * \param msg               The \ref message_subscribe to upcast.
 *
 * \returns the \ref message instance for this message.
 */
CPARSE_SYM(message)* CPARSE_SYM(message_subscribe_upcast)(
    CPARSE_SYM(message_subscribe)* msg);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_message_subscription_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(message_subscribe) sym ## message_subscribe; \
    static inline int sym ## message_subscribe_init(\
        CPARSE_SYM(message_subscribe)* x, int y, \
        CPARSE_SYM(event_handler)* z) { \
            return CPARSE_SYM(message_subscribe_init)(x,y,z); } \
    static inline int sym ## message_subscribe_init_for_comment_filter(\
        CPARSE_SYM(message_subscribe)* x, CPARSE_SYM(event_handler)* y) { \
            return \
                CPARSE_SYM(message_subscribe_init_for_comment_filter)(x,y); } \
    static inline int sym ## message_subscribe_init_for_comment_scanner(\
        CPARSE_SYM(message_subscribe)* x, CPARSE_SYM(event_handler)* y) { \
            return \
                CPARSE_SYM(message_subscribe_init_for_comment_scanner)(x,y); } \
    static inline int sym ## message_subscribe_init_for_line_wrap_filter(\
        CPARSE_SYM(message_subscribe)* x, CPARSE_SYM(event_handler)* y) { \
            return \
                CPARSE_SYM(message_subscribe_init_for_line_wrap_filter)( \
                    x,y); } \
    static inline int sym ## message_subscribe_init_for_nl_ws_filter(\
        CPARSE_SYM(message_subscribe)* x, CPARSE_SYM(event_handler)* y) { \
            return \
                CPARSE_SYM(message_subscribe_init_for_nl_ws_filter)(x,y); } \
    static inline int sym ## message_subscribe_init_for_rflo_filter(\
        CPARSE_SYM(message_subscribe)* x, CPARSE_SYM(event_handler)* y) { \
            return \
                CPARSE_SYM(message_subscribe_init_for_rflo_filter)(x,y); } \
    static inline int sym ## message_subscribe_init_for_raw_stack_scanner(\
        CPARSE_SYM(message_subscribe)* x, CPARSE_SYM(event_handler)* y) { \
            return \
                CPARSE_SYM(message_subscribe_init_for_raw_stack_scanner)( \
                    x,y); } \
    static inline int sym ## message_subscribe_dispose(\
        CPARSE_SYM(message_subscribe)* x) { \
            return CPARSE_SYM(message_subscribe_dispose)(x); } \
    static inline const CPARSE_SYM(event_handler)* \
    sym ## message_subscribe_event_handler_get( \
        const CPARSE_SYM(message_subscribe)* x) { \
            return CPARSE_SYM(message_subscribe_event_handler_get)(x); } \
    static inline int sym ## message_downcast_to_message_subscribe( \
        CPARSE_SYM(message_subscribe)** x, CPARSE_SYM(message)* y) { \
            return CPARSE_SYM(message_downcast_to_message_subscribe)(x,y); } \
    static inline CPARSE_SYM(message)* \
    sym ## message_subscribe_upcast(CPARSE_SYM(message_subscribe)* x) { \
            return CPARSE_SYM(message_subscribe_upcast)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_message_subscription_as(sym) \
    __INTERNAL_CPARSE_IMPORT_message_subscription_sym(sym ## _)
#define CPARSE_IMPORT_message_subscription \
    __INTERNAL_CPARSE_IMPORT_message_subscription_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
