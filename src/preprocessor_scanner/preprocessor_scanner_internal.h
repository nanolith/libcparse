/**
 * \file preprocessor_scanner/preprocessor_scanner_internal.h
 *
 * \brief Internal declarations and definitions for the preprocessor scanner.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/abstract_parser.h>
#include <libcparse/newline_preserving_whitespace_filter.h>
#include <libcparse/event_reactor_fwd.h>
#include <libcparse/file_position_cache.h>
#include <libcparse/string_builder.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct CPARSE_SYM(preprocessor_scanner)
CPARSE_SYM(preprocessor_scanner);

struct CPARSE_SYM(preprocessor_scanner)
{
    CPARSE_SYM(newline_preserving_whitespace_filter)* parent;
    CPARSE_SYM(abstract_parser)* base;
    CPARSE_SYM(event_reactor)* reactor;
    CPARSE_SYM(message_handler) parent_mh;
    CPARSE_SYM(file_position_cache)* cache;
    CPARSE_SYM(string_builder)* builder;
    int state;
};

enum CPARSE_SYM(preprocessor_scanner_state)
{
    CPARSE_PREPROCESSOR_SCANNER_STATE_INIT =                            0,
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
