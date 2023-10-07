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
