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

    /* token value events. */
    CPARSE_EVENT_TYPE_TOKEN_VALUE_STRING =          0x0060,
    CPARSE_EVENT_TYPE_TOKEN_VALUE_SYSTEM_STRING =   0x0061,
    CPARSE_EVENT_TYPE_TOKEN_VALUE_INTEGER =         0x0062,
    CPARSE_EVENT_TYPE_TOKEN_VALUE_CHARACTER =       0x0063,
    CPARSE_EVENT_TYPE_TOKEN_VALUE_FLOAT =           0x0064,

    /* identifier token event. */
    CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER =            0x0070,

    /* simple token events. */
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
    CPARSE_EVENT_TYPE_TOKEN_AMPERSAND =             0x0083,
    CPARSE_EVENT_TYPE_TOKEN_PIPE =                  0x0084,
    CPARSE_EVENT_TYPE_TOKEN_CARET =                 0x0085,
    CPARSE_EVENT_TYPE_TOKEN_TILDE =                 0x0086,
    CPARSE_EVENT_TYPE_TOKEN_QUESTION =              0x0087,
    CPARSE_EVENT_TYPE_TOKEN_EQUAL_COMPARE =         0x0088,
    CPARSE_EVENT_TYPE_TOKEN_NOT_EQUAL_COMPARE =     0x0089,
    CPARSE_EVENT_TYPE_TOKEN_EQUAL_ASSIGN =          0x008A,
    CPARSE_EVENT_TYPE_TOKEN_PLUS_EQUAL =            0x008B,
    CPARSE_EVENT_TYPE_TOKEN_MINUS_EQUAL =           0x008C,
    CPARSE_EVENT_TYPE_TOKEN_TIMES_EQUAL =           0x008D,
    CPARSE_EVENT_TYPE_TOKEN_DIV_EQUAL =             0x008E,
    CPARSE_EVENT_TYPE_TOKEN_MOD_EQUAL =             0x008F,
    CPARSE_EVENT_TYPE_TOKEN_AND_EQUAL =             0x0090,
    CPARSE_EVENT_TYPE_TOKEN_OR_EQUAL =              0x0091,
    CPARSE_EVENT_TYPE_TOKEN_XOR_EQUAL =             0x0092,
    CPARSE_EVENT_TYPE_TOKEN_COMPL_EQUAL =           0x0093,
    CPARSE_EVENT_TYPE_TOKEN_LEFT_SHIFT_EQUAL =      0x0094,
    CPARSE_EVENT_TYPE_TOKEN_RIGHT_SHIFT_EQUAL =     0x0095,
    CPARSE_EVENT_TYPE_TOKEN_BITSHIFT_LEFT =         0x0096,
    CPARSE_EVENT_TYPE_TOKEN_BITSHIFT_RIGHT =        0x0097,
    CPARSE_EVENT_TYPE_TOKEN_LESS_THAN =             0x0098,
    CPARSE_EVENT_TYPE_TOKEN_GREATER_THAN =          0x0099,
    CPARSE_EVENT_TYPE_TOKEN_LESS_THAN_EQUAL =       0x009A,
    CPARSE_EVENT_TYPE_TOKEN_GREATER_THAN_EQUAL =    0x009B,

    /* Preprocessor identifier token events. */
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_IF =              0x0120,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_IFDEF =           0x0121,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_IFNDEF =          0x0122,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_ELIF =            0x0123,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_ELSE =            0x0124,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_ENDIF =           0x0125,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_INCLUDE =         0x0126,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_DEFINE =          0x0127,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_UNDEF =           0x0128,

    CPARSE_EVENT_TYPE_UNKNOWN =                     0xFFFF,
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
