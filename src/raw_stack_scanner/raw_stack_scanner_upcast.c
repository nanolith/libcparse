/**
 * \file src/raw_stack_scanner/raw_stack_scanner_upcast.c
 *
 * \brief Upcast a \ref raw_stack_scanner to an \ref abstract_parser.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "raw_stack_scanner_internal.h"

/**
 * \brief Get the \ref abstract_parser interface for this scanner.
 *
 * \param scanner           The \ref raw_stack_scanner instance to query.
 *
 * \returns the \ref abstract_parser interface for this scanner.
 */
CPARSE_SYM(abstract_parser)* CPARSE_SYM(raw_stack_scanner_upcast)(
    CPARSE_SYM(raw_stack_scanner)* scanner)
{
    return &scanner->hdr;
}
