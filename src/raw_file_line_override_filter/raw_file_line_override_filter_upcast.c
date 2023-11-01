/**
 * \file
 * src/raw_file_line_override_filter/raw_file_line_override_filter_upcast.c
 *
 * \brief Upcast a \ref raw_file_line_override_filter to an \ref
 * abstract_parser.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "raw_file_line_override_filter_internal.h"

CPARSE_IMPORT_raw_stack_scanner;

/**
 * \brief Get the \ref abstract_parser interface for this filter.
 *
 * \param filter            The \ref raw_file_line_override_filter instance to
 *                          query.
 *
 * \returns the \ref abstract_parser interface for this filter.
 */
CPARSE_SYM(abstract_parser)* CPARSE_SYM(raw_file_line_override_filter_upcast)(
    CPARSE_SYM(raw_file_line_override_filter)* filter)
{
    return raw_stack_scanner_upcast(filter->parent);
}
