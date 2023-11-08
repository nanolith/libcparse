/**
 * \file libcparse/comment_filter.h
 *
 * \brief The comment filter consumes events from the comment scanner and
 * replaces comments with a single whitespace character.
 *
 * Subscribers to this scanner will receive raw character events as from the
 * comment scanner, except that both line comments and block comments will be
 * replaced with a single space.
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
 * \brief The \ref comment_filter filters comments out of an input stream.
 */
typedef struct CPARSE_SYM(comment_filter)
CPARSE_SYM(comment_filter);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
