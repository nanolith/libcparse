/**
 * \file libcparse/preprocessor_scanner.h
 *
 * \brief The preprocessor scanner scans the event stream for preprocessor
 * control line and control flow instructions.
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
 * \brief The preprocessor_control_scanner detects preprocessor control lines
 * and control flow instructions in the input stream.
 */
typedef struct CPARSE_SYM(preprocessor_control_scanner)
CPARSE_SYM(preprocessor_control_scanner);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create a preprocessor control scanner.
 *
 * This scanner automatically creates a comment filter and injects itself into
 * the message chain for the parser stack.
 *
 * \param scanner           Pointer to the \ref preprocessor_control_scanner
 *                          pointer to be populated with the created
 *                          preprocessor control scanner instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(preprocessor_control_scanner_create)(
    CPARSE_SYM(preprocessor_control_scanner)** scanner);

/**
 * \brief Release a preprocessor control scanner instance, releasing any
 * internal resources it may own.
 *
 * \param scanner           The \ref preprocessor_control_scanner instance to
 *                          release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(preprocessor_control_scanner_release)(
    CPARSE_SYM(preprocessor_control_scanner)* scanner);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the \ref abstract_parser interface for this scanner.
 *
 * \param scanner           The \ref preprocessor_control_scanner instance to
 *                          query.
 *
 * \returns the \ref abstract_parser interface for this scanner.
 */
CPARSE_SYM(abstract_parser)* CPARSE_SYM(preprocessor_control_scanner_upcast)(
    CPARSE_SYM(preprocessor_control_scanner)* scanner);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_preprocessor_control_scanner_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(preprocessor_control_scanner) \
    sym ## preprocessor_control_scanner; \
    static inline int sym ## preprocessor_control_scanner_create( \
        CPARSE_SYM(preprocessor_control_scanner)** x) { \
            return CPARSE_SYM(preprocessor_control_scanner_create)(x); } \
    static inline int sym ## preprocessor_control_scanner_release( \
        CPARSE_SYM(preprocessor_control_scanner)* x) { \
            return CPARSE_SYM(preprocessor_control_scanner_release)(x); } \
    static CPARSE_SYM(abstract_parser)* \
    sym ## preprocessor_control_scanner_upcast( \
        CPARSE_SYM(preprocessor_control_scanner)* x) { \
            return CPARSE_SYM(preprocessor_control_scanner_upcast)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_preprocessor_control_scanner_as(sym) \
    __INTERNAL_CPARSE_IMPORT_preprocessor_control_scanner_sym(sym ## _)
#define CPARSE_IMPORT_preprocessor_control_scanner \
    __INTERNAL_CPARSE_IMPORT_preprocessor_control_scanner_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
