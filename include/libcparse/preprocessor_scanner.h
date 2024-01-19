/**
 * \file libcparse/preprocessor_scanner.h
 *
 * \brief The preprocessor scanner scans the event stream for tokens that are
 * fed to the preprocessor. It maintains newlines, but consumes other
 * whitespace.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/abstract_parser.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The preprocessor_scanner tokenizes input to be fed to the
 * preprocessor.
 */
typedef struct CPARSE_SYM(preprocessor_scanner)
CPARSE_SYM(preprocessor_scanner);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create a preprocessor scanner.
 *
 * This scanner automatically creates a newline preserving whitespace filter and
 * injects itself into the message chain for the parser stack.
 *
 * \param scanner           Pointer to the \ref preprocessor_scanner pointer to
 *                          be populated with the created preprocessor scanner
 *                          instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(preprocessor_scanner_create)(
    CPARSE_SYM(preprocessor_scanner)** scanner);

/**
 * \brief Release a preprocessor scanner instance, releasing any internal
 * resources it may own.
 *
 * \param scanner           The \ref preprocessor_scanner instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(preprocessor_scanner_release)(
    CPARSE_SYM(preprocessor_scanner)* scanner);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the \ref abstract_parser interface for this scanner.
 *
 * \param scanner           The \ref preprocessor_scanner instance to query.
 *
 * \returns the \ref abstract_parser interface for this scanner.
 */
CPARSE_SYM(abstract_parser)* CPARSE_SYM(preprocessor_scanner_upcast)(
    CPARSE_SYM(preprocessor_scanner)* scanner);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_preprocessor_scanner_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(preprocessor_scanner) preprocessor_scanner; \
    static inline int sym ## preprocessor_scanner_create( \
        CPARSE_SYM(preprocessor_scanner)** x) { \
            return CPARSE_SYM(preprocessor_scanner_create)(x); } \
    static inline int sym ## preprocessor_scanner_release( \
        CPARSE_SYM(preprocessor_scanner)* x) { \
            return CPARSE_SYM(preprocessor_scanner_release)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_preprocessor_scanner_as(sym) \
    __INTERNAL_CPARSE_IMPORT_preprocessor_scanner_sym(sym ## _)
#define CPARSE_IMPORT_preprocessor_scanner \
    __INTERNAL_CPARSE_IMPORT_preprocessor_scanner_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
