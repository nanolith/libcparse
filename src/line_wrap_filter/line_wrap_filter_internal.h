/**
 * \file line_wrap_filter/line_wrap_filter_internal.h
 *
 * \brief Internal declarations for \ref line_wrap_filter.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/raw_file_line_override_filter.h>
#include <libcparse/event_reactor_fwd.h>
#include <libcparse/file_position_cache.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct CPARSE_SYM(line_wrap_filter)
CPARSE_SYM(line_wrap_filter);

struct CPARSE_SYM(line_wrap_filter)
{
    CPARSE_SYM(raw_file_line_override_filter)* parent;
    CPARSE_SYM(event_reactor)* reactor;
    CPARSE_SYM(message_handler) parent_mh;
    CPARSE_SYM(file_position_cache)* cache;
    int state;
};

enum CPARSE_SYM(line_wrap_filter_state)
{
    CPARSE_LINE_WRAP_FILTER_STATE_INIT =                         0,
    CPARSE_LINE_WRAP_FILTER_STATE_SLASH =                        1,
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
