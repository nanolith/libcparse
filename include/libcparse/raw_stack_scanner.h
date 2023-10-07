/**
 * \file libcparse/raw_stack_scanner.h
 *
 * \brief The raw stack scanner maintains a stack of input streams, walking each
 * byte read to its event callback from each input stream until EOF in turn
 * before returning EOF after all input streams are exhausted.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event.h>
#include <libcparse/event_handler.h>
#include <libcparse/event_type.h>
#include <libcparse/function_decl.h>
#include <libcparse/input_stream.h>
#include <libcparse/message_handler.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The \ref raw_stack_scanner reacts to a stack of input streams.
 */
typedef struct CPARSE_SYM(raw_stack_scanner) CPARSE_SYM(raw_stack_scanner);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create a raw stack scanner.
 *
 * \param scanner           Pointer to the \ref raw_stack_scanner pointer to be
 *                          populated with the created raw stack scanner on
 *                          success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(raw_stack_scanner_create)(
    CPARSE_SYM(raw_stack_scanner)** scanner);

/**
 * \brief Release a raw stack scanner instance, releasing any internal resources
 * it may own.
 *
 * \param scanner           The \ref raw_stack_scanner instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(raw_stack_scanner_release)(
    CPARSE_SYM(raw_stack_scanner)* scanner);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the message handler for the given raw stack scanner instance.
 *
 * \note This method maintains the ownership that this scanner instance has of
 * this message handler instance. The caller does not own the returned
 * instance.
 *
 * \param scanner           The \ref raw_stack_scanner instance to query.
 *
 * \returns the \ref message_handler instance for this scanner instance.
 */
CPARSE_SYM(message_handler)*
CPARSE_SYM(raw_stack_scanner_message_handler_get)(
    CPARSE_SYM(raw_stack_scanner)* scanner);

/**
 * \brief Override the message handler for the given raw stack scanner instance
 * with the given message handler.
 *
 * \note On success, this method transfers ownership of \p new_handler to this
 * scanner instance, and ownership of \p old_handler is transferred to the
 * caller. The caller is responsible for releasing \p old_handler when it is no
 * longer used. When a message event is sent to \p new_handler, it is up to this
 * handler to also publish this message event to \p old_handler so that the
 * message chain is maintained.
 *
 * \param old_handler       Pointer to the \ref message_handler pointer to
 *                          receive the old handler instance on success.
 * \param scanner           The \ref raw_stack_scanner instance for this
 *                          operation.
 * \param new_handler       The \ref message_handler instance to install.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int
CPARSE_SYM(raw_stack_scanner_message_handler_override)(
    CPARSE_SYM(message_handler)** old_handler,
    CPARSE_SYM(raw_stack_scanner)* scanner,
    CPARSE_SYM(message_handler)* new_handler);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_CPARSE_IMPORT_raw_stack_scanner_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(raw_stack_scanner) sym ## raw_stack_scanner; \
    static inline int sym ## raw_stack_scanner_create( \
        CPARSE_SYM(raw_stack_scanner)** x) { \
            return CPARSE_SYM(raw_stack_scanner_create)(x); } \
    static inline int sym ## raw_stack_scanner_release( \
        CPARSE_SYM(raw_stack_scanner)* x) { \
            return CPARSE_SYM(raw_stack_scanner_release)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_raw_stack_scanner_as(sym) \
    __INTERNAL_CPARSE_IMPORT_raw_stack_scanner_sym(sym ## _)
#define CPARSE_IMPORT_raw_stack_scanner \
    __INTERNAL_CPARSE_IMPORT_raw_stack_scanner_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
