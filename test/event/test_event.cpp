/**
 * \file test/event/test_event.cpp
 *
 * \brief Tests for the \ref event type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

#include "../../src/event/event_internal.h"

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_internal;

TEST_SUITE(event);

#define EVENT_INIT_TYPE_TEST(ctor, type) \
    TEST(ctor) \
    { \
        event ev; \
        cursor c; \
        \
        memset(&c, 0, sizeof(c)); \
        \
        TEST_ASSERT(STATUS_SUCCESS == ctor(&ev, &c)); \
        \
        TEST_EXPECT(type == event_get_type(&ev)); \
        \
        TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev)); \
    } \
    REQUIRE_SEMICOLON_HERE

#define EVENT_INIT_CAT_TYPE_TEST(ctor, cat, type) \
    TEST(ctor) \
    { \
        event ev; \
        cursor c; \
        \
        memset(&c, 0, sizeof(c)); \
        \
        TEST_ASSERT(STATUS_SUCCESS == ctor(&ev, &c)); \
        \
        TEST_EXPECT(type == event_get_type(&ev)); \
        \
        TEST_EXPECT(cat == event_get_category(&ev)); \
        \
        TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev)); \
    } \
    REQUIRE_SEMICOLON_HERE

/* token tests. */
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_eof, CPARSE_EVENT_CATEGORY_BASE, CPARSE_EVENT_TYPE_EOF);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_whitespace_token, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_WHITESPACE);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_newline_token, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_NEWLINE);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_comment_block_begin, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_COMMENT_BLOCK_BEGIN);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_comment_block_end, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_COMMENT_BLOCK_END);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_comment_line_begin, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_COMMENT_LINE_BEGIN);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_comment_line_end, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_COMMENT_LINE_END);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_left_paren, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_LEFT_PAREN);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_right_paren, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_RIGHT_PAREN);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_left_brace, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACE);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_right_brace, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACE);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_left_bracket, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACKET);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_right_bracket, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACKET);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_comma, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_COMMA);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_colon, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_COLON);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_semicolon, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_SEMICOLON);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_dot, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_DOT);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_arrow, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_ARROW);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_plus, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_PLUS);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_minus, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_MINUS);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_star, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_STAR);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_forward_slash, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_FORWARD_SLASH);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_percent, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_PERCENT);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_logical_and, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_LOGICAL_AND);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_logical_or, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_LOGICAL_OR);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_ampersand, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_AMPERSAND);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_pipe, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_PIPE);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_caret, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_CARET);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_tilde, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_TILDE);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_question, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_QUESTION);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_equal_compare, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_EQUAL_COMPARE);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_not_equal_compare, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_NOT_EQUAL_COMPARE);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_equal_assign, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_EQUAL_ASSIGN);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_plus_equal, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_PLUS_EQUAL);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_minus_equal, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_MINUS_EQUAL);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_times_equal, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_TIMES_EQUAL);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_div_equal, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_DIV_EQUAL);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_mod_equal, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_MOD_EQUAL);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_and_equal, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_AND_EQUAL);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_or_equal, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_OR_EQUAL);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_xor_equal, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_XOR_EQUAL);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_compl_equal, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_COMPL_EQUAL);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_left_shift_equal, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_LEFT_SHIFT_EQUAL);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_right_shift_equal, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_RIGHT_SHIFT_EQUAL);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_bitshift_left, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_BITSHIFT_LEFT);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_bitshift_right, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_BITSHIFT_RIGHT);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_less_than, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_LESS_THAN);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_greater_than, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_GREATER_THAN);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_less_than_equal, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_LESS_THAN_EQUAL);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_greater_than_equal, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_GREATER_THAN_EQUAL);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_increment, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_INCREMENT);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_decrement, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_DECREMENT);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_not, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_NOT);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_ellipsis, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_ELLIPSIS);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_preprocessor_id_if, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_IF);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_preprocessor_id_ifdef, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_IFDEF);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_preprocessor_id_ifndef, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_PP_ID_IFNDEF);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword__Alignas, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ALIGNAS);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword__Alignof, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ALIGNOF);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword__Atomic, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ATOMIC);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword__Bool, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__BOOL);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword__Complex, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__COMPLEX);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword__Generic, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__GENERIC);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword__Imaginary, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__IMAGINARY);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword__Noreturn, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__NORETURN);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword__Static_assert, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__STATIC_ASSERT);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword__Thread_local, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD__THREAD_LOCAL);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_auto, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_AUTO);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_break, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_BREAK);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_case, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CASE);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_char, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CHAR);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_const, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CONST);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_continue, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CONTINUE);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_default, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DEFAULT);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_do, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DO);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_double, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DOUBLE);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_else, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ELSE);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_enum, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ENUM);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_extern, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_EXTERN);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_float, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FLOAT);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_for, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FOR);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_goto, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_GOTO);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_if, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_IF);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_inline, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_INLINE);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_int, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_INT);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_long, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_LONG);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_register, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_REGISTER);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_restrict, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_RESTRICT);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_return, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_RETURN);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_short, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SHORT);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_signed, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SIGNED);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_sizeof, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SIZEOF);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_static, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_STATIC);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_struct, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_STRUCT);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_switch, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SWITCH);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_typedef, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_TYPEDEF);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_union, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_UNION);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_unsigned, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_UNSIGNED);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_void, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_VOID);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_volatile, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_VOLATILE);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_keyword_while, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_KEYWORD_WHILE);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_preprocessor_directive_end, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_PP_END);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_preprocessor_string_concat, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_PP_STRING_CONCAT);
EVENT_INIT_CAT_TYPE_TEST(
    event_init_for_token_preprocessor_hash, CPARSE_EVENT_CATEGORY_BASE,
    CPARSE_EVENT_TYPE_TOKEN_PP_HASH);
EVENT_INIT_TYPE_TEST(
    event_init_for_expression_begin, CPARSE_EVENT_TYPE_EXPRESSION_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_expression_end, CPARSE_EVENT_TYPE_EXPRESSION_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_primary_expression_begin,
    CPARSE_EVENT_TYPE_PRIMARY_EXPRESSION_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_primary_expression_end,
    CPARSE_EVENT_TYPE_PRIMARY_EXPRESSION_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_expression_part_begin,
    CPARSE_EVENT_TYPE_EXPRESSION_PART_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_expression_part_end, CPARSE_EVENT_TYPE_EXPRESSION_PART_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_array_subscript_begin,
    CPARSE_EVENT_TYPE_EXP_ARRAY_SUBSCRIPT_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_array_subscript_end,
    CPARSE_EVENT_TYPE_EXP_ARRAY_SUBSCRIPT_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_function_call_begin,
    CPARSE_EVENT_TYPE_EXP_FUNCTION_CALL_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_function_call_end,
    CPARSE_EVENT_TYPE_EXP_FUNCTION_CALL_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_dot_member_deref_begin,
    CPARSE_EVENT_TYPE_EXP_DOT_MEMBER_DEREF_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_dot_member_deref_end,
    CPARSE_EVENT_TYPE_EXP_DOT_MEMBER_DEREF_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_arrow_member_deref_begin,
    CPARSE_EVENT_TYPE_EXP_ARROW_MEMBER_DEREF_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_arrow_member_deref_end,
    CPARSE_EVENT_TYPE_EXP_ARROW_MEMBER_DEREF_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_postfix_increment_begin,
    CPARSE_EVENT_TYPE_EXP_POSTFIX_INCREMENT_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_postfix_increment_end,
    CPARSE_EVENT_TYPE_EXP_POSTFIX_INCREMENT_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_postfix_decrement_begin,
    CPARSE_EVENT_TYPE_EXP_POSTFIX_DECREMENT_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_postfix_decrement_end,
    CPARSE_EVENT_TYPE_EXP_POSTFIX_DECREMENT_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_compound_literal_begin,
    CPARSE_EVENT_TYPE_EXP_COMPOUND_LITERAL_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_compound_literal_end,
    CPARSE_EVENT_TYPE_EXP_COMPOUND_LITERAL_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_prefix_increment_begin,
    CPARSE_EVENT_TYPE_EXP_PREFIX_INCREMENT_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_prefix_increment_end,
    CPARSE_EVENT_TYPE_EXP_PREFIX_INCREMENT_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_prefix_decrement_begin,
    CPARSE_EVENT_TYPE_EXP_PREFIX_DECREMENT_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_prefix_decrement_end,
    CPARSE_EVENT_TYPE_EXP_PREFIX_DECREMENT_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_unary_operation_begin,
    CPARSE_EVENT_TYPE_EXP_UNARY_OPERATION_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_unary_operation_end,
    CPARSE_EVENT_TYPE_EXP_UNARY_OPERATION_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_sizeof_exp_begin,
    CPARSE_EVENT_TYPE_EXP_SIZEOF_EXP_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_sizeof_exp_end, CPARSE_EVENT_TYPE_EXP_SIZEOF_EXP_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_sizeof_type_begin,
    CPARSE_EVENT_TYPE_EXP_SIZEOF_TYPE_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_sizeof_type_end, CPARSE_EVENT_TYPE_EXP_SIZEOF_TYPE_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_alignof_type_begin,
    CPARSE_EVENT_TYPE_EXP_ALIGNOF_TYPE_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_alignof_type_end,
    CPARSE_EVENT_TYPE_EXP_ALIGNOF_TYPE_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_cast_begin, CPARSE_EVENT_TYPE_EXP_CAST_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_cast_end, CPARSE_EVENT_TYPE_EXP_CAST_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_multiply_begin, CPARSE_EVENT_TYPE_EXP_MULTIPLY_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_multiply_end, CPARSE_EVENT_TYPE_EXP_MULTIPLY_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_divide_begin, CPARSE_EVENT_TYPE_EXP_DIVIDE_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_divide_end, CPARSE_EVENT_TYPE_EXP_DIVIDE_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_modulo_begin, CPARSE_EVENT_TYPE_EXP_MODULO_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_modulo_end, CPARSE_EVENT_TYPE_EXP_MODULO_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_add_begin, CPARSE_EVENT_TYPE_EXP_ADD_BEGIN);
EVENT_INIT_TYPE_TEST(event_init_for_exp_add_end, CPARSE_EVENT_TYPE_EXP_ADD_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_sub_begin, CPARSE_EVENT_TYPE_EXP_SUB_BEGIN);
EVENT_INIT_TYPE_TEST(event_init_for_exp_sub_end, CPARSE_EVENT_TYPE_EXP_SUB_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_bitshift_left_begin,
    CPARSE_EVENT_TYPE_EXP_BITSHIFT_LEFT_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_bitshift_left_end,
    CPARSE_EVENT_TYPE_EXP_BITSHIFT_LEFT_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_bitshift_right_begin,
    CPARSE_EVENT_TYPE_EXP_BITSHIFT_RIGHT_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_bitshift_right_end,
    CPARSE_EVENT_TYPE_EXP_BITSHIFT_RIGHT_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_less_than_begin, CPARSE_EVENT_TYPE_EXP_LESS_THAN_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_less_than_end, CPARSE_EVENT_TYPE_EXP_LESS_THAN_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_greater_than_begin,
    CPARSE_EVENT_TYPE_EXP_GREATER_THAN_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_greater_than_end,
    CPARSE_EVENT_TYPE_EXP_GREATER_THAN_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_less_than_equal_begin,
    CPARSE_EVENT_TYPE_EXP_LESS_THAN_EQUAL_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_less_than_equal_end,
    CPARSE_EVENT_TYPE_EXP_LESS_THAN_EQUAL_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_greater_than_equal_begin,
    CPARSE_EVENT_TYPE_EXP_GREATER_THAN_EQUAL_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_greater_than_equal_end,
    CPARSE_EVENT_TYPE_EXP_GREATER_THAN_EQUAL_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_equal_to_begin, CPARSE_EVENT_TYPE_EXP_EQUAL_TO_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_equal_to_end, CPARSE_EVENT_TYPE_EXP_EQUAL_TO_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_not_equal_to_begin,
    CPARSE_EVENT_TYPE_EXP_NOT_EQUAL_TO_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_not_equal_to_end,
    CPARSE_EVENT_TYPE_EXP_NOT_EQUAL_TO_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_bitwise_and_begin,
    CPARSE_EVENT_TYPE_EXP_BITWISE_AND_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_bitwise_and_end, CPARSE_EVENT_TYPE_EXP_BITWISE_AND_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_bitwise_xor_begin,
    CPARSE_EVENT_TYPE_EXP_BITWISE_XOR_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_bitwise_xor_end, CPARSE_EVENT_TYPE_EXP_BITWISE_XOR_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_bitwise_or_begin,
    CPARSE_EVENT_TYPE_EXP_BITWISE_OR_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_bitwise_or_end, CPARSE_EVENT_TYPE_EXP_BITWISE_OR_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_logical_and_begin,
    CPARSE_EVENT_TYPE_EXP_LOGICAL_AND_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_logical_and_end, CPARSE_EVENT_TYPE_EXP_LOGICAL_AND_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_logical_or_begin,
    CPARSE_EVENT_TYPE_EXP_LOGICAL_OR_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_logical_or_end, CPARSE_EVENT_TYPE_EXP_LOGICAL_OR_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_conditional_begin,
    CPARSE_EVENT_TYPE_EXP_CONDITIONAL_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_conditional_end, CPARSE_EVENT_TYPE_EXP_CONDITIONAL_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_assignment_begin,
    CPARSE_EVENT_TYPE_EXP_ASSIGNMENT_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_assignment_end, CPARSE_EVENT_TYPE_EXP_ASSIGNMENT_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_comma_begin, CPARSE_EVENT_TYPE_EXP_COMMA_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_exp_comma_end, CPARSE_EVENT_TYPE_EXP_COMMA_END);
