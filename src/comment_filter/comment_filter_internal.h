/**
 * \file comment_filter/comment_filter_internal.h
 *
 * \brief Internal declarations for \ref comment_filter.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/comment_scanner.h>
#include <libcparse/event_reactor_fwd.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct CPARSE_SYM(comment_filter)
CPARSE_SYM(comment_filter);

struct CPARSE_SYM(comment_filter)
{
    CPARSE_SYM(comment_scanner)* parent;
    CPARSE_SYM(event_reactor)* reactor;
    CPARSE_SYM(message_handler) parent_mh;
    char* file;
    CPARSE_SYM(cursor) pos1;
    int state;
};

enum CPARSE_SYM(comment_filter_state)
{
    CPARSE_COMMENT_FILTER_STATE_INIT =                           0,
    CPARSE_COMMENT_FILTER_STATE_IN_COMMENT =                     1,
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
