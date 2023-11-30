/**
 * \file
 * src/newline_preserving_whitespace_filter/newline_preserving_whitespace_filter_upcast.c
 *
 * \brief Upcast the newline preserving whitespace filter to an abstract parser.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "newline_preserving_whitespace_filter_internal.h"

/**
 * \brief Get the \ref abstract_parser interface for this filter.
 *
 * \param filter            The \ref newline_preserving_whitespace_filter
 *                          instance to query.
 *
 * \returns the \ref abstract_parser interface for this filter.
 */
CPARSE_SYM(abstract_parser)*
CPARSE_SYM(newline_preserving_whitespace_filter_upcast)(
    CPARSE_SYM(newline_preserving_whitespace_filter)* filter)
{
    return filter->base;
}
