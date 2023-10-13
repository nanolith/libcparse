/**
 * \file libcparse/abstract_parser.h
 *
 * \brief The \ref abstract_parser provides a unified interface for scanners and
 * parsers.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event_handler_fwd.h>
#include <libcparse/function_decl.h>
#include <libcparse/input_stream_fwd.h>
#include <libcparse/message_handler_fwd.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The abstract parser is a unified interface for parsers and scanners.
 */
typedef struct CPARSE_SYM(abstract_parser) CPARSE_SYM(abstract_parser);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Initialize an \ref abstract_parser from a root \ref message_handler.
 *
 * \param ap                    The abstract parser instance to initialize.
 * \param mh                    The root \ref message_handler for this parser.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(abstract_parser_init)(
    CPARSE_SYM(abstract_parser)* ap, const CPARSE_SYM(message_handler)* mh);

/**
 * \brief Dispose a \ref abstract_parser instance.
 *
 * \param ap                    The abstract parser instance to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(abstract_parser_dispose)(CPARSE_SYM(abstract_parser)* ap);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Run an abstract parser instance.
 *
 * \param ap                    The abstract parser instance to run.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(abstract_parser_run)(CPARSE_SYM(abstract_parser)* ap);

/**
 * \brief Get the message handler for this abstract parser.
 *
 * \param ap                    The abstract parser instance to query.
 *
 * \returns the \ref message_handler instance for this abstract parser instance.
 */
CPARSE_SYM(message_handler)*
CPARSE_SYM(abstract_parser_message_handler_get)(
    CPARSE_SYM(abstract_parser)* ap);

/**
 * \brief Override the message handler for the given message handler instance
 * with the given message handler.
 *
 * \note When a message event is sent to \p new_handler, it is up to this
 * handler to publish this message event to \p old_handler if it does not
 * override the message, so that the message chain is maintained.
 *
 * \param old_handler       Pointer to a \ref message handler to be set to the
 *                          old handler.
 * \param ap                The \ref abstract_parser instance for this
 *                          operation.
 * \param new_handler       The \ref message_handler instance to install.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int
CPARSE_SYM(abstract_parser_message_handler_override)(
    CPARSE_SYM(message_handler)* old_handler,
    CPARSE_SYM(abstract_parser)* ap,
    CPARSE_SYM(message_handler)* new_handler);

/**
 * \brief Push an \ref input_stream onto the \ref raw_stack_scanner stream.
 *
 * \note Ownership of this \ref input_stream is passed to the \ref
 * abstract_parser.
 *
 * \param ap                The \ref abstract_parser to add this stream to.
 * \param name              The name of this stream.
 * \param stream            The stream to push onto the stack.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int
CPARSE_SYM(abstract_parser_push_input_stream)(
    CPARSE_SYM(abstract_parser)* ap, const char* name,
    CPARSE_SYM(input_stream)* input_stream);

/**
 * \brief Subscribe to \ref raw_stack_scanner events.
 *
 * \param ap                The \ref abstract_parser for this operation.
 * \param eh                The event handler to add to the subscription list.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int
CPARSE_SYM(abstract_parser_raw_stack_scanner_subscribe)(
    CPARSE_SYM(abstract_parser)* ap, CPARSE_SYM(event_handler)* eh);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
