/**
 * \file raw_stack_scanner/raw_file_line_override_filter_internal.h
 *
 * \brief Internal declarations for \ref raw_file_line_override_filter.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/raw_stack_scanner.h>
#include <libcparse/cursor.h>
#include <libcparse/event_reactor_fwd.h>
#include <libcparse/function_decl.h>
#include <stdbool.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct CPARSE_SYM(raw_file_line_override_filter)
CPARSE_SYM(file_line_override_filter);

struct CPARSE_SYM(file_line_override_filter)
{
    CPARSE_SYM(raw_stack_scanner)* parent;
    CPARSE_SYM(event_reactor)* reactor;
    bool use_pos;
    CPARSE_SYM(cursor) pos;
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
