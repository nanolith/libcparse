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
    CPARSE_NL_WHITESPACE_FILTER_STATE_IN_CHARACTER_SEQUENCE =       3,
    CPARSE_NL_WHITESPACE_FILTER_STATE_IN_CHARACTER_SEQUENCE_SLASH = 4,
    CPARSE_NL_WHITESPACE_FILTER_STATE_IN_WHITESPACE =               5,
};

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Message handler callback for
 * \ref newline_preserving_whitespace_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref newline_preserving_whitespace_filter instance).
 * \param msg               A message for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(newline_preserving_whitespace_filter_message_callback)(
    void* context, const CPARSE_SYM(message)* msg);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
