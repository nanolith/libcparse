/**
 * \file src/comment_scanner/comment_scanner_upcast.c
 *
 * \brief Upcast the comment scanner to an abstract parser.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "comment_scanner_internal.h"

CPARSE_IMPORT_line_wrap_filter;

/**
 * \brief Get the \ref abstract_parser interface for this scanner.
 *
 * \param scanner           The \ref comment_scanner instance to query.
 *
 * \returns the \ref abstract_parser interface for this scanner.
 */
CPARSE_SYM(abstract_parser)* CPARSE_SYM(comment_scanner_upcast)(
    CPARSE_SYM(comment_scanner)* scanner)
{
    return line_wrap_filter_upcast(scanner->parent);
}
