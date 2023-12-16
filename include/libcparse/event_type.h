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

    /* Comment events. */
    CPARSE_EVENT_TYPE_COMMENT_BLOCK_BEGIN =         0x0010,
    CPARSE_EVENT_TYPE_COMMENT_BLOCK_END =           0x0011,
    CPARSE_EVENT_TYPE_COMMENT_LINE_BEGIN =          0x0012,
    CPARSE_EVENT_TYPE_COMMENT_LINE_END =            0x0013,

    /* Add a whitespace token event. */
    CPARSE_EVENT_TYPE_TOKEN_WHITESPACE =            0x0020,
    CPARSE_EVENT_TYPE_TOKEN_NEWLINE =               0x0021,

    /* preprocessor events. */
    CPARSE_EVENT_TYPE_PREPROCESSOR_SYSTEM_INCLUDE = 0x0040,
    CPARSE_EVENT_TYPE_PREPROCESSOR_LOCAL_INCLUDE =  0x0041,
    CPARSE_EVENT_TYPE_PREPROCESSOR_DEFINE =         0x0042,
    CPARSE_EVENT_TYPE_PREPROCESSOR_UNDEF =          0x0043,
    CPARSE_EVENT_TYPE_PREPROCESSOR_LINE =           0x0044,
    CPARSE_EVENT_TYPE_PREPROCESSOR_ERROR =          0x0045,
    CPARSE_EVENT_TYPE_PREPROCESSOR_PRAGMA =         0x0046,
    CPARSE_EVENT_TYPE_PREPROCESSOR_ESCAPE_NEWLINE = 0x0047,
    CPARSE_EVENT_TYPE_PREPROCESSOR_IF =             0x0048,
    CPARSE_EVENT_TYPE_PREPROCESSOR_IFDEF =          0x0049,
    CPARSE_EVENT_TYPE_PREPROCESSOR_IFNDEF =         0x004A,
    CPARSE_EVENT_TYPE_PREPROCESSOR_ELIF =           0x004B,
    CPARSE_EVENT_TYPE_PREPROCESSOR_ELSE =           0x004C,
    CPARSE_EVENT_TYPE_PREPROCESSOR_ENDIF =          0x004D,

    /* token events. */
    CPARSE_EVENT_TYPE_TOKEN_VALUE_STRING =          0x0060,
    CPARSE_EVENT_TYPE_TOKEN_VALUE_SYSTEM_STRING =   0x0061,
    CPARSE_EVENT_TYPE_TOKEN_VALUE_INTEGER =         0x0062,
    CPARSE_EVENT_TYPE_TOKEN_VALUE_CHARACTER =       0x0063,
    CPARSE_EVENT_TYPE_TOKEN_VALUE_FLOAT =           0x0064,

    CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER =            0x0070,
    CPARSE_EVENT_TYPE_TOKEN_LEFT_PAREN =            0x0071,
    CPARSE_EVENT_TYPE_TOKEN_RIGHT_PAREN =           0x0072,
    CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACE =            0x0073,
    CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACE =           0x0074,
    CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACKET =          0x0075,
    CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACKET =         0x0076,
    CPARSE_EVENT_TYPE_TOKEN_COMMA =                 0x0077,
    CPARSE_EVENT_TYPE_TOKEN_COLON =                 0x0078,
    CPARSE_EVENT_TYPE_TOKEN_SEMICOLON =             0x0079,
    CPARSE_EVENT_TYPE_TOKEN_DOT =                   0x007A,
    CPARSE_EVENT_TYPE_TOKEN_ARROW =                 0x007B,
    CPARSE_EVENT_TYPE_TOKEN_PLUS =                  0x007C,
    CPARSE_EVENT_TYPE_TOKEN_MINUS =                 0x007D,
    CPARSE_EVENT_TYPE_TOKEN_STAR =                  0x007E,
    CPARSE_EVENT_TYPE_TOKEN_FORWARD_SLASH =         0x007F,
    CPARSE_EVENT_TYPE_TOKEN_PERCENT =               0x0080,
    CPARSE_EVENT_TYPE_TOKEN_LOGICAL_AND =           0x0081,
    CPARSE_EVENT_TYPE_TOKEN_LOGICAL_OR =            0x0082,

    CPARSE_EVENT_TYPE_UNKNOWN =                     0xFFFF,
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
