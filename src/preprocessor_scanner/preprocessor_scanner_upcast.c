/**
 * \file src/preprocessor_scanner/preprocessor_scanner_upcast.c
 *
 * \brief Upcast the preprocessor scanner to an abstract parser.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "preprocessor_scanner_internal.h"

/**
 * \brief Get the \ref abstract_parser interface for this scanner.
 *
 * \param scanner           The \ref preprocessor_scanner instance to query.
 *
 * \returns the \ref abstract_parser interface for this scanner.
 */
CPARSE_SYM(abstract_parser)* CPARSE_SYM(preprocessor_scanner_upcast)(
    CPARSE_SYM(preprocessor_scanner)* scanner)
{
    return scanner->base;
}
