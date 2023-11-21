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

#include <libcparse/function_decl.h>

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

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
