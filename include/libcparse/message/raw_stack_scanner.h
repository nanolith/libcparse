/**
 * \file libcparse/message/raw_stack_scanner.h
 *
 * \brief Messages for the \ref raw_stack_scanner.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/function_decl.h>
#include <libcparse/input_stream.h>
#include <libcparse/message.h>
#include <stdbool.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief the rss_add_input_stream message adds an input stream to the
 * \ref raw_stack_scanner.
 */
typedef struct CPARSE_SYM(message_rss_add_input_stream)
CPARSE_SYM(message_rss_add_input_stream);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Initialize a \ref message_rss_add_input_stream.
 *
 * \note On a successful send of this message, ownership of this input stream is
 * transferred to the accepting message handler.
 *
 * \param msg               The message to initialize.
 * \param name              The name of the stream, used for cursor reporting.
 * \param stream            The input stream to send to the
 *                          \ref raw_stack_scanner.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_rss_add_input_stream_init)(
    CPARSE_SYM(message_rss_add_input_stream)* msg, const char* name,
    CPARSE_SYM(input_stream)* stream);

/**
 * \brief Dispose of a \ref message_rss_add_input_stream message.
 *
 * \param msg               The message to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_rss_add_input_stream_dispose)(
    CPARSE_SYM(message_rss_add_input_stream)* msg);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the filename associated with a \ref message_rss_add_input_stream
 * instance.
 *
 * \param msg               The message to query.
 *
 * \returns the filename associated with this message.
 */
const char* CPARSE_SYM(message_rss_add_input_stream_filename_get)(
    const CPARSE_SYM(message_rss_add_input_stream)* msg);

/**
 * \brief Transfer the \ref input_stream associated with this message to the
 * caller, transferring ownership of this stream to the caller as well.
 *
 * \param stream            Pointer to the \ref input_stream pointer to hold
 *                          this stream on success.
 * \param msg               The message for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_rss_add_input_stream_xfer)(
    CPARSE_SYM(input_stream)** stream,
    CPARSE_SYM(message_rss_add_input_stream)* msg);

/**
 * \brief Attempt to downcast a \ref message to a
 * \ref message_rss_add_input_stream.
 *
 * \param rss_msg           Pointer to the message pointer to receive the
 *                          downcast instance on success.
 * \param msg               The \ref message pointer to attempt to downcast to
 *                          the derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_downcast_to_message_rss_add_input_stream)(
    CPARSE_SYM(message_rss_add_input_stream)** rss_msg,
    CPARSE_SYM(message)* msg);

/**
 * \brief Upcast a \ref message_rss_add_input_stream to a \ref message.
 *
 * \param msg               The \ref message_rss_add_input_stream to upcast.
 *
 * \returns the \ref message instance for this message.
 */
CPARSE_SYM(message)* CPARSE_SYM(message_rss_add_input_stream_upcast)(
    CPARSE_SYM(message_rss_add_input_stream)* msg);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_CPARSE_IMPORT_message_raw_stack_scanner_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(message_rss_add_input_stream) \
    sym ## message_rss_add_input_stream; \
    static inline int sym ## message_rss_add_input_stream_init( \
        CPARSE_SYM(message_rss_add_input_stream)* x, const char* y, \
        CPARSE_SYM(input_stream)* z) { \
            return CPARSE_SYM(message_rss_add_input_stream_init)(x,y,z); } \
    static inline int sym ## message_rss_add_input_stream_dispose( \
        CPARSE_SYM(message_rss_add_input_stream)* x) { \
            return CPARSE_SYM(message_rss_add_input_stream_dispose)(x); } \
    static inline const char* \
    sym ## message_rss_add_input_stream_filename_get( \
        CPARSE_SYM(message_rss_add_input_stream)* x) { \
            return CPARSE_SYM(message_rss_add_input_stream_filename_get)(x); } \
    static inline int sym ## message_rss_add_input_stream_xfer( \
        CPARSE_SYM(input_stream)** x, \
        CPARSE_SYM(message_rss_add_input_stream)* y) { \
            return CPARSE_SYM(message_rss_add_input_stream_xfer)(x,y); } \
    static inline int sym ## message_downcast_to_message_rss_add_input_stream( \
        CPARSE_SYM(message_rss_add_input_stream)** x, \
        CPARSE_SYM(message)* y) { \
            return \
                CPARSE_SYM(message_downcast_to_message_rss_add_input_stream( \
                    x,y); } \
    static inline CPARSE_SYM(message)* \
    CPARSE_SYM(message_rss_add_input_stream_upcast)( \
        CPARSE_SYM(message_rss_add_input_stream)* x) { \
            return CPARSE_SYM(message_rss_add_input_stream_upcast)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_message_raw_stack_scanner_as(sym) \
    __INTERNAL_CPARSE_IMPORT_message_raw_stack_scanner_sym(sym ## _)
#define CPARSE_IMPORT_message_raw_stack_scanner \
    __INTERNAL_CPARSE_IMPORT_message_raw_stack_scanner_sym()
/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
