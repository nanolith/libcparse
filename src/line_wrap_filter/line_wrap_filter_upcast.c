/**
 * \file src/line_wrap_filter/line_wrap_filter_upcast.c
 *
 * \brief Upcast method for \ref line_wrap_filter.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "line_wrap_filter_internal.h"

CPARSE_IMPORT_raw_file_line_override_filter;

/**
 * \brief Get the \ref abstract_parser interface for this filter.
 *
 * \param filter            The \ref line_wrap_filter instance to query.
 *
 * \returns the \ref abstract_parser interface for this filter.
 */
CPARSE_SYM(abstract_parser)* CPARSE_SYM(line_wrap_filter_upcast)(
    CPARSE_SYM(line_wrap_filter)* filter)
{
    return raw_file_line_override_filter_upcast(filter->parent);
}
