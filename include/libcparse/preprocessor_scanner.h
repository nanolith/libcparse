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

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
