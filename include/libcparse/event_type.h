/**
 * \file libcparse/event_type.h
 *
 * \brief The event_type enumeration describes the type of event.
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
 * \brief The event type abstracts individual lexer or parser events.
 */
enum CPARSE_SYM(event_type)
{
    CPARSE_EVENT_TYPE_EOF =                         0x0000,
    CPARSE_EVENT_TYPE_RAW_CHARACTER =               0x0001,
    CPARSE_EVENT_TYPE_FILTERED_RAW_CHARACTER =      0x0002,
    CPARSE_EVENT_TYPE_COMMENT_BLOCK_BEGIN =         0x0010,
    CPARSE_EVENT_TYPE_COMMENT_BLOCK_END =           0x0011,
    CPARSE_EVENT_TYPE_COMMENT_LINE_BEGIN =          0x0012,
    CPARSE_EVENT_TYPE_COMMENT_LINE_END =            0x0013,
    CPARSE_EVENT_TYPE_PREPROCESSOR_INCLUDE =        0x0014,
    CPARSE_EVENT_TYPE_PREPROCESSOR_DEFINE =         0x0015,
    CPARSE_EVENT_TYPE_PREPROCESSOR_UNDEF =          0x0016,
    CPARSE_EVENT_TYPE_PREPROCESSOR_LINE =           0x0017,
    CPARSE_EVENT_TYPE_PREPROCESSOR_ERROR =          0x0018,
    CPARSE_EVENT_TYPE_PREPROCESSOR_PRAGMA =         0x0019,
    CPARSE_EVENT_TYPE_PREPROCESSOR_ESCAPE_NEWLINE = 0x001A,
    CPARSE_EVENT_TYPE_PREPROCESSOR_IF =             0x001B,
    CPARSE_EVENT_TYPE_PREPROCESSOR_IFDEF =          0x001C,
    CPARSE_EVENT_TYPE_PREPROCESSOR_IFNDEF =         0x001D,
    CPARSE_EVENT_TYPE_UNKNOWN =                     0xFFFF,
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
