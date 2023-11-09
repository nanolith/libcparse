/**
 * \file src/comment_filter/comment_filter_upcast.c
 *
 * \brief Upcast the comment filter to an abstract parser.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "comment_filter_internal.h"

CPARSE_IMPORT_comment_scanner;

/**
 * \brief Get the \ref abstract_parser interface for this filter.
 *
 * \param filter            The \ref comment_filter instance to query.
 *
 * \returns the \ref abstract_parser interface for this filter.
 */
CPARSE_SYM(abstract_parser)* CPARSE_SYM(comment_filter_upcast)(
    CPARSE_SYM(comment_filter)* filter)
{
    return comment_scanner_upcast(filter->parent);
}
