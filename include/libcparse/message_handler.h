/**
 * \file libcparse/message_handler.h
 *
 * \brief The \ref message_handler reacts to a message.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/message.h>
#include <libcparse/message_handler/detail.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief A message callback function responds to a message.
 *
 * \param context               A user-supplied context pointer given to the
 *                              callback.
 * \param msg                   A message to which this callback is subscribed.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
typedef int (*CPARSE_SYM(message_callback_fn))(
    void* context, const CPARSE_SYM(message)* msg);

/**
 * \brief A message handler accepts a message.
 */
typedef struct CPARSE_SYM(message_handler) CPARSE_SYM(message_handler);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Initialize a \ref message_handler from a callback function and
 * context.
 *
 * \param mh                    The message handler instance to initialize.
 * \param mcb                   The message callback function.
 * \param mctx                  The message handler user context.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(message_handler_init)(
    CPARSE_SYM(message_handler)* mh, CPARSE_SYM(message_callback_fn) mcb,
    void* mctx);

/**
 * \brief Initialize a \ref message_handler by copying another
 * \ref message_handler.
 *
 * \param mh                    The message handler instance to initialize.
 * \param mhc                   The message handler to copy.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(message_handler_init_copy)(
    CPARSE_SYM(message_handler)* mh, const CPARSE_SYM(message_handler)* mhc);

/**
 * \brief Dispose a \ref message_handler instance.
 *
 * \param mh                    The message handler instance to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(message_handler_dispose)(CPARSE_SYM(message_handler)* mh);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Send a message to the given message handler.
 *
 * \param mh                    The message handler to receive this message.
 * \param msg                   The message to send.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(message_handler_send)(
    CPARSE_SYM(message_handler)* mh, const CPARSE_SYM(message)* msg);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_CPARSE_IMPORT_message_handler_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(message_callback_fn) sym ## message_callback_fn; \
    typedef CPARSE_SYM(message_handler) sym ## message_handler; \
    static inline int FN_DECL_MUST_CHECK sym ## message_handler_init(\
        CPARSE_SYM(message_handler)* x, CPARSE_SYM(message_callback_fn) y, \
        void* z) { \
            return CPARSE_SYM(message_handler_init)(x,y,z); } \
    static inline int FN_DECL_MUST_CHECK sym ## message_handler_init_copy(\
        CPARSE_SYM(message_handler)* x, const CPARSE_SYM(message_handler)* y) {\
            return CPARSE_SYM(message_handler_init_copy)(x,y); } \
    static inline int FN_DECL_MUST_CHECK sym ## message_handler_dispose( \
        CPARSE_SYM(message_handler)* x) { \
            return CPARSE_SYM(message_handler_dispose)(x); } \
    static inline int sym ## message_handler_send(\
        CPARSE_SYM(message_handler)* x, const CPARSE_SYM(message)* y) { \
            return CPARSE_SYM(message_handler_send)(x,y); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_message_handler_as(sym) \
    __INTERNAL_CPARSE_IMPORT_message_handler_sym(sym ## _)
#define CPARSE_IMPORT_message_handler \
    __INTERNAL_CPARSE_IMPORT_message_handler_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
