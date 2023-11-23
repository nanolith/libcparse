/**
 * \file libcparse/newline_preserving_whitespace_filter.h
 *
 * \brief The newline preserving whitespace filter merges all non-newline
 * whitespace characters into single whitespace tokens. Newline characters are
 * turned into newline tokens.
 *
 * Subscribers to this scanner will receive whitespace token, newline token, and
 * raw character events as from the comment filter. Runs of raw whitespace will
 * be replaced with either a single whitespace token, or a newline token,
 * depending upon whether the runs contain a newline.
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
 * \brief The \ref newline_preserving_whitespace_filter replaces runs of
 * whitespace with a single whitespace token, and preserves newlines as a
 * newline token.
 */
typedef struct CPARSE_SYM(newline_preserving_whitespace_filter)
CPARSE_SYM(newline_preserving_whitespace_filter);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create a newline preserving whitespace filter.
 *
 * This filter automatically creates a comment filter and injects itself into
 * the message chain for the parser stack.
 *
 * \param filter            Pointer to the
 *                          \ref newline_preserving_whitespace_filter pointer to
 *                          be populated with the filter instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(newline_preserving_whitespace_filter_create)(
    CPARSE_SYM(newline_preserving_whitespace_filter)** filter);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
