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
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_CPARSE_IMPORT_message_raw_stack_scanner_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(message_rss_add_input_stream) \
    sym ## message_rss_add_input_stream; \
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
