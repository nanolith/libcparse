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
    CPARSE_EVENT_TYPE_EOF =                                             0x0000,
    CPARSE_EVENT_TYPE_RAW_CHARACTER =                                   0x0001,

    /* Comment events. */
    CPARSE_EVENT_TYPE_COMMENT_BLOCK_BEGIN =                             0x0010,
    CPARSE_EVENT_TYPE_COMMENT_BLOCK_END =                               0x0011,
    CPARSE_EVENT_TYPE_COMMENT_LINE_BEGIN =                              0x0012,
    CPARSE_EVENT_TYPE_COMMENT_LINE_END =                                0x0013,

    /* Add a whitespace token event. */
    CPARSE_EVENT_TYPE_TOKEN_WHITESPACE =                                0x0020,
    CPARSE_EVENT_TYPE_TOKEN_NEWLINE =                                   0x0021,

    /* preprocessor events. */
    CPARSE_EVENT_TYPE_PREPROCESSOR_SYSTEM_INCLUDE =                     0x0040,
    CPARSE_EVENT_TYPE_PREPROCESSOR_LOCAL_INCLUDE =                      0x0041,
    CPARSE_EVENT_TYPE_PREPROCESSOR_DEFINE =                             0x0042,
    CPARSE_EVENT_TYPE_PREPROCESSOR_UNDEF =                              0x0043,
    CPARSE_EVENT_TYPE_PREPROCESSOR_LINE =                               0x0044,
    CPARSE_EVENT_TYPE_PREPROCESSOR_ERROR =                              0x0045,
    CPARSE_EVENT_TYPE_PREPROCESSOR_PRAGMA =                             0x0046,
    CPARSE_EVENT_TYPE_PREPROCESSOR_ESCAPE_NEWLINE =                     0x0047,
    CPARSE_EVENT_TYPE_PREPROCESSOR_IF =                                 0x0048,
    CPARSE_EVENT_TYPE_PREPROCESSOR_IFDEF =                              0x0049,
    CPARSE_EVENT_TYPE_PREPROCESSOR_IFNDEF =                             0x004A,
    CPARSE_EVENT_TYPE_PREPROCESSOR_ELIF =                               0x004B,
    CPARSE_EVENT_TYPE_PREPROCESSOR_ELSE =                               0x004C,
    CPARSE_EVENT_TYPE_PREPROCESSOR_ENDIF =                              0x004D,

    /* token value events. */
    CPARSE_EVENT_TYPE_TOKEN_VALUE_STRING =                              0x0060,
    CPARSE_EVENT_TYPE_TOKEN_VALUE_SYSTEM_STRING =                       0x0061,
    CPARSE_EVENT_TYPE_TOKEN_VALUE_INTEGER =                             0x0062,
    CPARSE_EVENT_TYPE_TOKEN_VALUE_CHARACTER =                           0x0063,
    CPARSE_EVENT_TYPE_TOKEN_VALUE_FLOAT =                               0x0064,

    /* identifier token event. */
    CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER =                                0x0070,

    /* simple token events. */
    CPARSE_EVENT_TYPE_TOKEN_LEFT_PAREN =                                0x0071,
    CPARSE_EVENT_TYPE_TOKEN_RIGHT_PAREN =                               0x0072,
    CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACE =                                0x0073,
    CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACE =                               0x0074,
    CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACKET =                              0x0075,
    CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACKET =                             0x0076,
    CPARSE_EVENT_TYPE_TOKEN_COMMA =                                     0x0077,
    CPARSE_EVENT_TYPE_TOKEN_COLON =                                     0x0078,
    CPARSE_EVENT_TYPE_TOKEN_SEMICOLON =                                 0x0079,
    CPARSE_EVENT_TYPE_TOKEN_DOT =                                       0x007A,
    CPARSE_EVENT_TYPE_TOKEN_ARROW =                                     0x007B,
    CPARSE_EVENT_TYPE_TOKEN_PLUS =                                      0x007C,
    CPARSE_EVENT_TYPE_TOKEN_MINUS =                                     0x007D,
    CPARSE_EVENT_TYPE_TOKEN_STAR =                                      0x007E,
    CPARSE_EVENT_TYPE_TOKEN_FORWARD_SLASH =                             0x007F,
    CPARSE_EVENT_TYPE_TOKEN_PERCENT =                                   0x0080,
    CPARSE_EVENT_TYPE_TOKEN_LOGICAL_AND =                               0x0081,
    CPARSE_EVENT_TYPE_TOKEN_LOGICAL_OR =                                0x0082,
    CPARSE_EVENT_TYPE_TOKEN_AMPERSAND =                                 0x0083,
    CPARSE_EVENT_TYPE_TOKEN_PIPE =                                      0x0084,
    CPARSE_EVENT_TYPE_TOKEN_CARET =                                     0x0085,
    CPARSE_EVENT_TYPE_TOKEN_TILDE =                                     0x0086,
    CPARSE_EVENT_TYPE_TOKEN_QUESTION =                                  0x0087,
    CPARSE_EVENT_TYPE_TOKEN_EQUAL_COMPARE =                             0x0088,
    CPARSE_EVENT_TYPE_TOKEN_NOT_EQUAL_COMPARE =                         0x0089,
    CPARSE_EVENT_TYPE_TOKEN_EQUAL_ASSIGN =                              0x008A,
    CPARSE_EVENT_TYPE_TOKEN_PLUS_EQUAL =                                0x008B,
    CPARSE_EVENT_TYPE_TOKEN_MINUS_EQUAL =                               0x008C,
    CPARSE_EVENT_TYPE_TOKEN_TIMES_EQUAL =                               0x008D,
    CPARSE_EVENT_TYPE_TOKEN_DIV_EQUAL =                                 0x008E,
    CPARSE_EVENT_TYPE_TOKEN_MOD_EQUAL =                                 0x008F,
    CPARSE_EVENT_TYPE_TOKEN_AND_EQUAL =                                 0x0090,
    CPARSE_EVENT_TYPE_TOKEN_OR_EQUAL =                                  0x0091,
    CPARSE_EVENT_TYPE_TOKEN_XOR_EQUAL =                                 0x0092,
    CPARSE_EVENT_TYPE_TOKEN_COMPL_EQUAL =                               0x0093,
    CPARSE_EVENT_TYPE_TOKEN_LEFT_SHIFT_EQUAL =                          0x0094,
    CPARSE_EVENT_TYPE_TOKEN_RIGHT_SHIFT_EQUAL =                         0x0095,
    CPARSE_EVENT_TYPE_TOKEN_BITSHIFT_LEFT =                             0x0096,
    CPARSE_EVENT_TYPE_TOKEN_BITSHIFT_RIGHT =                            0x0097,
    CPARSE_EVENT_TYPE_TOKEN_LESS_THAN =                                 0x0098,
    CPARSE_EVENT_TYPE_TOKEN_GREATER_THAN =                              0x0099,
    CPARSE_EVENT_TYPE_TOKEN_LESS_THAN_EQUAL =                           0x009A,
    CPARSE_EVENT_TYPE_TOKEN_GREATER_THAN_EQUAL =                        0x009B,
    CPARSE_EVENT_TYPE_TOKEN_INCREMENT =                                 0x009C,
    CPARSE_EVENT_TYPE_TOKEN_DECREMENT =                                 0x009D,
    CPARSE_EVENT_TYPE_TOKEN_NOT =                                       0x009E,
    CPARSE_EVENT_TYPE_TOKEN_ELLIPSIS =                                  0x009F,

    /* Preprocessor keyword token events. */
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_IF =                                  0x0120,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_IFDEF =                               0x0121,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_IFNDEF =                              0x0122,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_ELIF =                                0x0123,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_ELSE =                                0x0124,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_ENDIF =                               0x0125,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_INCLUDE =                             0x0126,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_DEFINE =                              0x0127,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_UNDEF =                               0x0128,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_LINE =                                0x0129,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_ERROR =                               0x012A,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_PRAGMA =                              0x012B,

    /* End preprocessor directive event. */
    CPARSE_EVENT_TYPE_PP_END =                                          0x012F,

    /* Preprocessor token events. */
    CPARSE_EVENT_TYPE_TOKEN_PP_STRING_CONCAT =                          0x0130,
    CPARSE_EVENT_TYPE_TOKEN_PP_HASH =                                   0x0131,

    /* Raw constant tokens. */
    CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER =                         0x0140,
    CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING =                          0x0141,
    CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_SYSTEM_STRING =                   0x0142,
    CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_CHARACTER =                       0x0143,
    CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_FLOAT =                           0x0144,

    /* Keyword tokens. */
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ALIGNAS =                          0x0150,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ALIGNOF =                          0x0151,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ATOMIC =                           0x0152,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__BOOL =                             0x0153,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__COMPLEX =                          0x0154,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__GENERIC =                          0x0155,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__IMAGINARY =                        0x0156,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__NORETURN =                         0x0157,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__STATIC_ASSERT =                    0x0158,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__THREAD_LOCAL =                     0x0159,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_AUTO =                              0x015A,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_BREAK =                             0x015B,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CASE =                              0x015C,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CHAR =                              0x015D,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CONST =                             0x015E,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CONTINUE =                          0x015F,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DEFAULT =                           0x0160,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DO =                                0x0161,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DOUBLE =                            0x0162,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ELSE =                              0x0163,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ENUM =                              0x0164,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_EXTERN =                            0x0165,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FLOAT =                             0x0166,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FOR =                               0x0167,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_GOTO =                              0x0168,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_IF =                                0x0169,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_INLINE =                            0x016A,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_INT =                               0x016B,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_LONG =                              0x016C,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_REGISTER =                          0x016D,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_RESTRICT =                          0x016E,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_RETURN =                            0x016F,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SHORT =                             0x0170,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SIGNED =                            0x0171,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SIZEOF =                            0x0172,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_STATIC =                            0x0173,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_STRUCT =                            0x0174,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SWITCH =                            0x0175,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_TYPEDEF =                           0x0176,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_UNION =                             0x0177,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_UNSIGNED =                          0x0178,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_VOID =                              0x0179,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_VOLATILE =                          0x017A,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_WHILE =                             0x017B,

    /* primary expressions. */
    CPARSE_EVENT_TYPE_EXPRESSION_BEGIN =                                0x0200,
    CPARSE_EVENT_TYPE_EXPRESSION_END =                                  0x0201,
    CPARSE_EVENT_TYPE_PRIMARY_EXPRESSION_BEGIN =                        0x0202,
    CPARSE_EVENT_TYPE_PRIMARY_EXPRESSION_END =                          0x0203,
    CPARSE_EVENT_TYPE_EXPRESSION_PART_BEGIN =                           0x0204,
    CPARSE_EVENT_TYPE_EXPRESSION_PART_END =                             0x0205,

    /* postfix expressions. */
    CPARSE_EVENT_TYPE_EXP_ARRAY_SUBSCRIPT_BEGIN =                       0x0206,
    CPARSE_EVENT_TYPE_EXP_ARRAY_SUBSCRIPT_END =                         0x0207,
    CPARSE_EVENT_TYPE_EXP_FUNCTION_CALL_BEGIN =                         0x0208,
    CPARSE_EVENT_TYPE_EXP_FUNCTION_CALL_END =                           0x0209,
    CPARSE_EVENT_TYPE_EXP_DOT_MEMBER_DEREF_BEGIN =                      0x020A,
    CPARSE_EVENT_TYPE_EXP_DOT_MEMBER_DEREF_END =                        0x020B,
    CPARSE_EVENT_TYPE_EXP_ARROW_MEMBER_DEREF_BEGIN =                    0x020C,
    CPARSE_EVENT_TYPE_EXP_ARROW_MEMBER_DEREF_END =                      0x020D,
    CPARSE_EVENT_TYPE_EXP_POSTFIX_INCREMENT_BEGIN =                     0x020E,
    CPARSE_EVENT_TYPE_EXP_POSTFIX_INCREMENT_END =                       0x020F,
    CPARSE_EVENT_TYPE_EXP_POSTFIX_DECREMENT_BEGIN =                     0x0210,
    CPARSE_EVENT_TYPE_EXP_POSTFIX_DECREMENT_END =                       0x0211,
    CPARSE_EVENT_TYPE_EXP_COMPOUND_LITERAL_BEGIN =                      0x0212,
    CPARSE_EVENT_TYPE_EXP_COMPOUND_LITERAL_END =                        0x0213,

    /* unary expressions. */
    CPARSE_EVENT_TYPE_EXP_PREFIX_INCREMENT_BEGIN =                      0x0220,
    CPARSE_EVENT_TYPE_EXP_PREFIX_INCREMENT_END =                        0x0221,
    CPARSE_EVENT_TYPE_EXP_PREFIX_DECREMENT_BEGIN =                      0x0222,
    CPARSE_EVENT_TYPE_EXP_PREFIX_DECREMENT_END =                        0x0223,
    CPARSE_EVENT_TYPE_EXP_UNARY_OPERATION_BEGIN =                       0x0224,
    CPARSE_EVENT_TYPE_EXP_UNARY_OPERATION_END =                         0x0225,
    CPARSE_EVENT_TYPE_EXP_SIZEOF_EXP_BEGIN =                            0x0226,
    CPARSE_EVENT_TYPE_EXP_SIZEOF_EXP_END =                              0x0227,
    CPARSE_EVENT_TYPE_EXP_SIZEOF_TYPE_BEGIN =                           0x0228,
    CPARSE_EVENT_TYPE_EXP_SIZEOF_TYPE_END =                             0x0229,
    CPARSE_EVENT_TYPE_EXP_ALIGNOF_TYPE_BEGIN =                          0x022A,
    CPARSE_EVENT_TYPE_EXP_ALIGNOF_TYPE_END =                            0x022B,

    /* cast expressions. */
    CPARSE_EVENT_TYPE_EXP_CAST_BEGIN =                                  0x0230,
    CPARSE_EVENT_TYPE_EXP_CAST_END =                                    0x0231,

    /* multiplicative expressions. */
    CPARSE_EVENT_TYPE_EXP_MULTIPLY_BEGIN =                              0x0240,
    CPARSE_EVENT_TYPE_EXP_MULTIPLY_END =                                0x0241,
    CPARSE_EVENT_TYPE_EXP_DIVIDE_BEGIN =                                0x0242,
    CPARSE_EVENT_TYPE_EXP_DIVIDE_END =                                  0x0243,
    CPARSE_EVENT_TYPE_EXP_MODULO_BEGIN =                                0x0244,
    CPARSE_EVENT_TYPE_EXP_MODULO_END =                                  0x0245,

    /* additive expressions. */
    CPARSE_EVENT_TYPE_EXP_ADD_BEGIN =                                   0x0250,
    CPARSE_EVENT_TYPE_EXP_ADD_END =                                     0x0251,
    CPARSE_EVENT_TYPE_EXP_SUB_BEGIN =                                   0x0252,
    CPARSE_EVENT_TYPE_EXP_SUB_END =                                     0x0253,

    /* bitshift expressions. */
    CPARSE_EVENT_TYPE_EXP_BITSHIFT_LEFT_BEGIN =                         0x0260,
    CPARSE_EVENT_TYPE_EXP_BITSHIFT_LEFT_END =                           0x0261,
    CPARSE_EVENT_TYPE_EXP_BITSHIFT_RIGHT_BEGIN =                        0x0262,
    CPARSE_EVENT_TYPE_EXP_BITSHIFT_RIGHT_END =                          0x0263,

    /* relational expressions. */
    CPARSE_EVENT_TYPE_EXP_LESS_THAN_BEGIN =                             0x0270,
    CPARSE_EVENT_TYPE_EXP_LESS_THAN_END =                               0x0271,
    CPARSE_EVENT_TYPE_EXP_GREATER_THAN_BEGIN =                          0x0272,
    CPARSE_EVENT_TYPE_EXP_GREATER_THAN_END =                            0x0273,
    CPARSE_EVENT_TYPE_EXP_LESS_THAN_EQUAL_BEGIN =                       0x0274,
    CPARSE_EVENT_TYPE_EXP_LESS_THAN_EQUAL_END =                         0x0275,
    CPARSE_EVENT_TYPE_EXP_GREATER_THAN_EQUAL_BEGIN =                    0x0276,
    CPARSE_EVENT_TYPE_EXP_GREATER_THAN_EQUAL_END =                      0x0277,

    /* equality expressions. */
    CPARSE_EVENT_TYPE_EXP_EQUAL_TO_BEGIN =                              0x0280,
    CPARSE_EVENT_TYPE_EXP_EQUAL_TO_END =                                0x0281,
    CPARSE_EVENT_TYPE_EXP_NOT_EQUAL_TO_BEGIN =                          0x0282,
    CPARSE_EVENT_TYPE_EXP_NOT_EQUAL_TO_END =                            0x0283,

    /* bitwise expressions. */
    CPARSE_EVENT_TYPE_EXP_BITWISE_AND_BEGIN =                           0x0290,
    CPARSE_EVENT_TYPE_EXP_BITWISE_AND_END =                             0x0291,
    CPARSE_EVENT_TYPE_EXP_BITWISE_XOR_BEGIN =                           0x0292,
    CPARSE_EVENT_TYPE_EXP_BITWISE_XOR_END =                             0x0293,
    CPARSE_EVENT_TYPE_EXP_BITWISE_OR_BEGIN =                            0x0294,
    CPARSE_EVENT_TYPE_EXP_BITWISE_OR_END =                              0x0295,

    /* logical expressions. */
    CPARSE_EVENT_TYPE_EXP_LOGICAL_AND_BEGIN =                           0x02A0,
    CPARSE_EVENT_TYPE_EXP_LOGICAL_AND_END =                             0x02A1,
    CPARSE_EVENT_TYPE_EXP_LOGICAL_OR_BEGIN =                            0x02A2,
    CPARSE_EVENT_TYPE_EXP_LOGICAL_OR_END =                              0x02A3,
    CPARSE_EVENT_TYPE_EXP_CONDITIONAL_BEGIN =                           0x02A4,
    CPARSE_EVENT_TYPE_EXP_CONDITIONAL_END =                             0x02A5,

    /* assignment expressions. */
    CPARSE_EVENT_TYPE_EXP_ASSIGNMENT_BEGIN =                            0x02B0,
    CPARSE_EVENT_TYPE_EXP_ASSIGNMENT_END =                              0x02B1,
    CPARSE_EVENT_TYPE_EXP_COMMA_BEGIN =                                 0x02B2,
    CPARSE_EVENT_TYPE_EXP_COMMA_END =                                   0x02B3,

    CPARSE_EVENT_TYPE_UNKNOWN =                                         0xFFFF,
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
