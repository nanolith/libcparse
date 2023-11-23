/**
 * \file libcparse/newline_preserving_whitespace_filter_internal.h
 *
 * \brief Internal declarations and definitions for the newline preserving
 * whitespace filter.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/comment_filter.h>
#include <libcparse/event_reactor_fwd.h>
#include <libcparse/file_position_cache.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct CPARSE_SYM(newline_preserving_whitespace_filter_internal)
CPARSE_SYM(newline_preserving_whitespace_filter_internal);

struct CPARSE_SYM(newline_preserving_whitespace_filter_internal)
{
    CPARSE_SYM(comment_filter)* parent;
    CPARSE_SYM(event_reactor)* reactor;
    CPARSE_SYM(message_handler) parent_mh;
    CPARSE_SYM(file_position_cache)* cache;
    int state;
};

enum CPARSE_SYM(newline_preserving_whitespace_filter_state)
{
    CPARSE_NL_WHITESPACE_FILTER_STATE_INIT =                        0,
    CPARSE_NL_WHITESPACE_FILTER_STATE_IN_STRING =                   1,
    CPARSE_NL_WHITESPACE_FILTER_STATE_IN_STRING_SLASH =             2,
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
