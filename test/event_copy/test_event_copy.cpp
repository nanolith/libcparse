/**
 * \file test/event_copy/test_event_copy.cpp
 *
 * \brief Tests for the \ref event_copy type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event_copy.h>
#include <libcparse/event/identifier.h>
#include <libcparse/event/include.h>
#include <libcparse/event/integer.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/event/raw_character_literal.h>
#include <libcparse/event/raw_float.h>
#include <libcparse/event/raw_integer.h>
#include <libcparse/event/raw_string.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_copy;
CPARSE_IMPORT_event_identifier;
CPARSE_IMPORT_event_include;
CPARSE_IMPORT_event_integer;
CPARSE_IMPORT_event_raw_character;
CPARSE_IMPORT_event_raw_character_literal;
CPARSE_IMPORT_event_raw_float;
CPARSE_IMPORT_event_raw_integer;
CPARSE_IMPORT_event_raw_string;

TEST_SUITE(event_copy);

static const char* TESTFILE = "test.c";

#define EVENT_BASE_COPY_TEST(ctor) \
    TEST(ctor) \
    { \
        event ev; \
        cursor c; \
        event_copy* cpy; \
        const event* clone; \
        const cursor* clone_c; \
        int type; \
        \
        memset(&c, 0, sizeof(c)); \
        c.begin_line = 23; \
        c.end_line = 24; \
        c.begin_col = 1; \
        c.end_col = 5; \
        c.file = TESTFILE; \
        \
        TEST_ASSERT(STATUS_SUCCESS == ctor(&ev, &c)); \
        TEST_ASSERT(STATUS_SUCCESS == event_copy_create(&cpy, &ev)); \
        \
        type = event_get_type(&ev); \
        \
        TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev)); \
        \
        clone = event_copy_get_event(cpy); \
        TEST_ASSERT(NULL != clone); \
        \
        TEST_EXPECT(type == event_get_type(clone)); \
        \
        clone_c = event_get_cursor(clone); \
        TEST_ASSERT(NULL != clone_c); \
        TEST_EXPECT(clone_c->begin_line == c.begin_line); \
        TEST_EXPECT(clone_c->end_line == c.end_line); \
        TEST_EXPECT(clone_c->begin_col == c.begin_col); \
        TEST_EXPECT(clone_c->end_col == c.end_col); \
        TEST_ASSERT(NULL != clone_c->file); \
        TEST_EXPECT(!strcmp(c.file, clone_c->file)); \
        \
        TEST_ASSERT(STATUS_SUCCESS == event_copy_release(cpy)); \
    }

EVENT_BASE_COPY_TEST(event_init_for_eof);
EVENT_BASE_COPY_TEST(event_init_for_whitespace_token);
EVENT_BASE_COPY_TEST(event_init_for_newline_token);
EVENT_BASE_COPY_TEST(event_init_for_comment_block_begin);
EVENT_BASE_COPY_TEST(event_init_for_comment_block_end);
EVENT_BASE_COPY_TEST(event_init_for_comment_line_begin);
EVENT_BASE_COPY_TEST(event_init_for_comment_line_end);
EVENT_BASE_COPY_TEST(event_init_for_token_left_paren);
EVENT_BASE_COPY_TEST(event_init_for_token_right_paren);
EVENT_BASE_COPY_TEST(event_init_for_token_left_brace);
EVENT_BASE_COPY_TEST(event_init_for_token_right_brace);
EVENT_BASE_COPY_TEST(event_init_for_token_left_bracket);
EVENT_BASE_COPY_TEST(event_init_for_token_right_bracket);
EVENT_BASE_COPY_TEST(event_init_for_token_comma);
EVENT_BASE_COPY_TEST(event_init_for_token_colon);
EVENT_BASE_COPY_TEST(event_init_for_token_semicolon);
EVENT_BASE_COPY_TEST(event_init_for_token_dot);
EVENT_BASE_COPY_TEST(event_init_for_token_arrow);
EVENT_BASE_COPY_TEST(event_init_for_token_plus);
EVENT_BASE_COPY_TEST(event_init_for_token_minus);
EVENT_BASE_COPY_TEST(event_init_for_token_star);
EVENT_BASE_COPY_TEST(event_init_for_token_forward_slash);
EVENT_BASE_COPY_TEST(event_init_for_token_percent);
EVENT_BASE_COPY_TEST(event_init_for_token_logical_and);
EVENT_BASE_COPY_TEST(event_init_for_token_logical_or);
EVENT_BASE_COPY_TEST(event_init_for_token_ampersand);
EVENT_BASE_COPY_TEST(event_init_for_token_pipe);
EVENT_BASE_COPY_TEST(event_init_for_token_caret);
EVENT_BASE_COPY_TEST(event_init_for_token_tilde);
EVENT_BASE_COPY_TEST(event_init_for_token_question);
EVENT_BASE_COPY_TEST(event_init_for_token_equal_compare);
EVENT_BASE_COPY_TEST(event_init_for_token_not_equal_compare);
EVENT_BASE_COPY_TEST(event_init_for_token_equal_assign);
EVENT_BASE_COPY_TEST(event_init_for_token_plus_equal);
EVENT_BASE_COPY_TEST(event_init_for_token_minus_equal);
EVENT_BASE_COPY_TEST(event_init_for_token_times_equal);
EVENT_BASE_COPY_TEST(event_init_for_token_div_equal);
EVENT_BASE_COPY_TEST(event_init_for_token_mod_equal);
EVENT_BASE_COPY_TEST(event_init_for_token_and_equal);
EVENT_BASE_COPY_TEST(event_init_for_token_or_equal);
EVENT_BASE_COPY_TEST(event_init_for_token_xor_equal);
EVENT_BASE_COPY_TEST(event_init_for_token_compl_equal);
EVENT_BASE_COPY_TEST(event_init_for_token_left_shift_equal);
EVENT_BASE_COPY_TEST(event_init_for_token_right_shift_equal);
EVENT_BASE_COPY_TEST(event_init_for_token_bitshift_left);
EVENT_BASE_COPY_TEST(event_init_for_token_bitshift_right);
EVENT_BASE_COPY_TEST(event_init_for_token_less_than);
EVENT_BASE_COPY_TEST(event_init_for_token_greater_than);
EVENT_BASE_COPY_TEST(event_init_for_token_less_than_equal);
EVENT_BASE_COPY_TEST(event_init_for_token_greater_than_equal);
EVENT_BASE_COPY_TEST(event_init_for_token_increment);
EVENT_BASE_COPY_TEST(event_init_for_token_decrement);
EVENT_BASE_COPY_TEST(event_init_for_token_not);
EVENT_BASE_COPY_TEST(event_init_for_token_ellipsis);
EVENT_BASE_COPY_TEST(event_init_for_token_preprocessor_id_if);
EVENT_BASE_COPY_TEST(event_init_for_token_preprocessor_id_ifdef);
EVENT_BASE_COPY_TEST(event_init_for_token_preprocessor_id_ifndef);
EVENT_BASE_COPY_TEST(event_init_for_token_preprocessor_id_elif);
EVENT_BASE_COPY_TEST(event_init_for_token_preprocessor_id_else);
EVENT_BASE_COPY_TEST(event_init_for_token_preprocessor_id_endif);
EVENT_BASE_COPY_TEST(event_init_for_token_preprocessor_id_include);
EVENT_BASE_COPY_TEST(event_init_for_token_preprocessor_id_define);
EVENT_BASE_COPY_TEST(event_init_for_token_preprocessor_id_undef);
EVENT_BASE_COPY_TEST(event_init_for_token_preprocessor_id_line);
EVENT_BASE_COPY_TEST(event_init_for_token_preprocessor_id_error);
EVENT_BASE_COPY_TEST(event_init_for_token_preprocessor_id_pragma);
EVENT_BASE_COPY_TEST(event_init_for_token_preprocessor_string_concat);
EVENT_BASE_COPY_TEST(event_init_for_token_preprocessor_hash);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword__Alignas);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword__Alignof);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword__Atomic);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword__Bool);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword__Complex);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword__Generic);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword__Imaginary);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword__Noreturn);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword__Static_assert);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword__Thread_local);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_auto);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_break);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_case);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_char);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_const);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_continue);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_default);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_do);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_double);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_else);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_enum);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_extern);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_float);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_for);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_goto);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_if);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_inline);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_int);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_long);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_register);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_restrict);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_return);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_short);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_signed);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_sizeof);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_static);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_struct);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_switch);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_typedef);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_union);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_unsigned);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_void);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_volatile);
EVENT_BASE_COPY_TEST(event_init_for_token_keyword_while);
EVENT_BASE_COPY_TEST(event_init_for_preprocessor_directive_end);
EVENT_BASE_COPY_TEST(event_init_for_expression_begin);
EVENT_BASE_COPY_TEST(event_init_for_expression_end);
EVENT_BASE_COPY_TEST(event_init_for_primary_expression_begin);
EVENT_BASE_COPY_TEST(event_init_for_primary_expression_end);
EVENT_BASE_COPY_TEST(event_init_for_expression_part_begin);
EVENT_BASE_COPY_TEST(event_init_for_expression_part_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_array_subscript_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_array_subscript_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_function_call_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_function_call_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_dot_member_deref_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_dot_member_deref_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_arrow_member_deref_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_arrow_member_deref_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_postfix_increment_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_postfix_increment_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_postfix_decrement_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_postfix_decrement_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_compound_literal_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_compound_literal_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_prefix_increment_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_prefix_increment_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_prefix_decrement_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_prefix_decrement_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_unary_operation_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_unary_operation_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_sizeof_exp_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_sizeof_exp_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_sizeof_type_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_sizeof_type_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_alignof_type_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_alignof_type_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_cast_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_cast_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_multiply_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_multiply_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_divide_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_divide_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_modulo_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_modulo_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_add_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_add_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_sub_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_sub_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_bitshift_left_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_bitshift_left_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_bitshift_right_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_bitshift_right_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_less_than_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_less_than_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_greater_than_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_greater_than_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_less_than_equal_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_less_than_equal_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_greater_than_equal_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_greater_than_equal_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_equal_to_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_equal_to_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_not_equal_to_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_not_equal_to_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_bitwise_and_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_bitwise_and_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_bitwise_xor_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_bitwise_xor_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_bitwise_or_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_bitwise_or_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_logical_and_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_logical_and_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_logical_or_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_logical_or_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_conditional_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_conditional_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_assignment_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_assignment_end);
EVENT_BASE_COPY_TEST(event_init_for_exp_comma_begin);
EVENT_BASE_COPY_TEST(event_init_for_exp_comma_end);

TEST(event_identifier_init)
{
    event_identifier iev;
    event* ev;
    event_identifier* clone_iev;
    cursor c;
    event_copy* cpy;
    const event* clone;
    const cursor* clone_c;
    int type;
    const char* ID = "foo";

    memset(&c, 0, sizeof(c));
    c.begin_line = 23;
    c.end_line = 24;
    c.begin_col = 1;
    c.end_col = 5;
    c.file = TESTFILE;

    TEST_ASSERT(STATUS_SUCCESS == event_identifier_init(&iev, &c, ID));
    ev = event_identifier_upcast(&iev);
    TEST_ASSERT(STATUS_SUCCESS == event_copy_create(&cpy, ev));

    type = event_get_type(ev);

    TEST_ASSERT(STATUS_SUCCESS == event_identifier_dispose(&iev));

    clone = event_copy_get_event(cpy);
    TEST_ASSERT(NULL != clone);

    TEST_EXPECT(type == event_get_type(clone));

    clone_c = event_get_cursor(clone);
    TEST_ASSERT(NULL != clone_c);
    TEST_EXPECT(clone_c->begin_line == c.begin_line);
    TEST_EXPECT(clone_c->end_line == c.end_line);
    TEST_EXPECT(clone_c->begin_col == c.begin_col);
    TEST_EXPECT(clone_c->end_col == c.end_col);
    TEST_ASSERT(NULL != clone_c->file);
    TEST_EXPECT(!strcmp(c.file, clone_c->file));

    TEST_ASSERT(
        STATUS_SUCCESS
            == event_downcast_to_event_identifier(&clone_iev, (event*)clone));
    TEST_ASSERT(NULL != event_identifier_get(clone_iev));
    TEST_EXPECT(!strcmp(ID, event_identifier_get(clone_iev)));

    TEST_ASSERT(STATUS_SUCCESS == event_copy_release(cpy));
}

#define EVENT_INCLUDE_COPY_TEST(ctor, type) \
    TEST(ctor) \
    { \
        event_include iev; \
        event* ev; \
        event_include* clone_iev; \
        cursor c; \
        event_copy* cpy; \
        const event* clone; \
        const cursor* clone_c; \
        const char* INCLUDE = "foo.h"; \
        \
        memset(&c, 0, sizeof(c)); \
        c.begin_line = 23; \
        c.end_line = 24; \
        c.begin_col = 1; \
        c.end_col = 5; \
        c.file = TESTFILE; \
        \
        TEST_ASSERT( \
            STATUS_SUCCESS \
                == event_include_init_for_system_include(&iev, &c, INCLUDE)); \
        ev = event_include_upcast(&iev); \
        TEST_ASSERT(STATUS_SUCCESS == event_copy_create(&cpy, ev)); \
        \
        TEST_ASSERT(STATUS_SUCCESS == event_include_dispose(&iev)); \
        \
        clone = event_copy_get_event(cpy); \
        TEST_ASSERT(NULL != clone); \
        \
        TEST_EXPECT( \
            CPARSE_EVENT_TYPE_PREPROCESSOR_SYSTEM_INCLUDE \
                == event_get_type(clone)); \
        \
        clone_c = event_get_cursor(clone); \
        TEST_ASSERT(NULL != clone_c); \
        TEST_EXPECT(clone_c->begin_line == c.begin_line); \
        TEST_EXPECT(clone_c->end_line == c.end_line); \
        TEST_EXPECT(clone_c->begin_col == c.begin_col); \
        TEST_EXPECT(clone_c->end_col == c.end_col); \
        TEST_ASSERT(NULL != clone_c->file); \
        TEST_EXPECT(!strcmp(c.file, clone_c->file)); \
        \
        TEST_ASSERT( \
            STATUS_SUCCESS \
                == event_downcast_to_event_include( \
                        &clone_iev, (event*)clone)); \
        TEST_ASSERT(NULL != event_include_file_get(clone_iev)); \
        TEST_EXPECT(!strcmp(INCLUDE, event_include_file_get(clone_iev))); \
        \
        TEST_ASSERT(STATUS_SUCCESS == event_copy_release(cpy)); \
    } \

EVENT_INCLUDE_COPY_TEST(
    event_include_init_for_system_include,
    CPARSE_EVENT_TYPE_PREPROCESSOR_SYSTEM_INCLUDE);
EVENT_INCLUDE_COPY_TEST(
    event_include_init_for_local_include,
    CPARSE_EVENT_TYPE_PREPROCESSOR_LOCAL_INCLUDE);

TEST(event_integer_token_init_for_signed_int)
{
    event_integer_token iev;
    event_integer_token* iev_clone;
    event* ev;
    cursor c;
    event_copy* cpy;
    const event* clone;
    const cursor* clone_c;
    const int VAL = -1999;

    memset(&c, 0, sizeof(c));
    c.begin_line = 23;
    c.end_line = 24;
    c.begin_col = 1;
    c.end_col = 5;
    c.file = TESTFILE;

    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(&iev, &c, VAL));
    ev = event_integer_token_upcast(&iev);
    TEST_ASSERT(STATUS_SUCCESS == event_copy_create(&cpy, ev));

    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&iev));

    clone = event_copy_get_event(cpy);
    TEST_ASSERT(NULL != clone);

    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_INTEGER == event_get_type(clone));

    clone_c = event_get_cursor(clone);
    TEST_ASSERT(NULL != clone_c);
    TEST_EXPECT(clone_c->begin_line == c.begin_line);
    TEST_EXPECT(clone_c->end_line == c.end_line);
    TEST_EXPECT(clone_c->begin_col == c.begin_col);
    TEST_EXPECT(clone_c->end_col == c.end_col);
    TEST_ASSERT(NULL != clone_c->file);
    TEST_EXPECT(!strcmp(c.file, clone_c->file));

    TEST_ASSERT(
        STATUS_SUCCESS
            == event_downcast_to_event_integer_token(
                    &iev_clone, (event*)clone));
    TEST_ASSERT(VAL == event_integer_token_coerce_int(iev_clone));

    TEST_ASSERT(STATUS_SUCCESS == event_copy_release(cpy));
}

TEST(event_integer_token_init_for_unsigned_int)
{
    event_integer_token iev;
    event_integer_token* iev_clone;
    event* ev;
    cursor c;
    event_copy* cpy;
    const event* clone;
    const cursor* clone_c;
    const unsigned int VAL = 1999;

    memset(&c, 0, sizeof(c));
    c.begin_line = 23;
    c.end_line = 24;
    c.begin_col = 1;
    c.end_col = 5;
    c.file = TESTFILE;

    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(&iev, &c, VAL));
    ev = event_integer_token_upcast(&iev);
    TEST_ASSERT(STATUS_SUCCESS == event_copy_create(&cpy, ev));

    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&iev));

    clone = event_copy_get_event(cpy);
    TEST_ASSERT(NULL != clone);

    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_INTEGER == event_get_type(clone));

    clone_c = event_get_cursor(clone);
    TEST_ASSERT(NULL != clone_c);
    TEST_EXPECT(clone_c->begin_line == c.begin_line);
    TEST_EXPECT(clone_c->end_line == c.end_line);
    TEST_EXPECT(clone_c->begin_col == c.begin_col);
    TEST_EXPECT(clone_c->end_col == c.end_col);
    TEST_ASSERT(NULL != clone_c->file);
    TEST_EXPECT(!strcmp(c.file, clone_c->file));

    TEST_ASSERT(
        STATUS_SUCCESS
            == event_downcast_to_event_integer_token(
                    &iev_clone, (event*)clone));
    TEST_ASSERT(VAL == event_integer_token_coerce_unsigned_int(iev_clone));

    TEST_ASSERT(STATUS_SUCCESS == event_copy_release(cpy));
}

TEST(event_raw_character_init)
{
    event_raw_character cev;
    event_raw_character* cev_clone;
    event* ev;
    cursor c;
    event_copy* cpy;
    const event* clone;
    const cursor* clone_c;
    const unsigned int CH = 'Z';

    memset(&c, 0, sizeof(c));
    c.begin_line = 23;
    c.end_line = 24;
    c.begin_col = 1;
    c.end_col = 5;
    c.file = TESTFILE;

    TEST_ASSERT(
        STATUS_SUCCESS
            == event_raw_character_init(&cev, &c, CH));
    ev = event_raw_character_upcast(&cev);
    TEST_ASSERT(STATUS_SUCCESS == event_copy_create(&cpy, ev));

    TEST_ASSERT(STATUS_SUCCESS == event_raw_character_dispose(&cev));

    clone = event_copy_get_event(cpy);
    TEST_ASSERT(NULL != clone);

    TEST_EXPECT(CPARSE_EVENT_TYPE_RAW_CHARACTER == event_get_type(clone));

    clone_c = event_get_cursor(clone);
    TEST_ASSERT(NULL != clone_c);
    TEST_EXPECT(clone_c->begin_line == c.begin_line);
    TEST_EXPECT(clone_c->end_line == c.end_line);
    TEST_EXPECT(clone_c->begin_col == c.begin_col);
    TEST_EXPECT(clone_c->end_col == c.end_col);
    TEST_ASSERT(NULL != clone_c->file);
    TEST_EXPECT(!strcmp(c.file, clone_c->file));

    TEST_ASSERT(
        STATUS_SUCCESS
            == event_downcast_to_event_raw_character(
                    &cev_clone, (event*)clone));
    TEST_ASSERT(CH == event_raw_character_get(cev_clone));

    TEST_ASSERT(STATUS_SUCCESS == event_copy_release(cpy));
}

TEST(event_raw_character_literal_init)
{
    event_raw_character_literal cev;
    event_raw_character_literal* cev_clone;
    event* ev;
    cursor c;
    event_copy* cpy;
    const event* clone;
    const cursor* clone_c;
    const char* VAL = "'\n'";

    memset(&c, 0, sizeof(c));
    c.begin_line = 23;
    c.end_line = 24;
    c.begin_col = 1;
    c.end_col = 5;
    c.file = TESTFILE;

    TEST_ASSERT(
        STATUS_SUCCESS
            == event_raw_character_literal_init(&cev, &c, VAL));
    ev = event_raw_character_literal_upcast(&cev);
    TEST_ASSERT(STATUS_SUCCESS == event_copy_create(&cpy, ev));

    TEST_ASSERT(STATUS_SUCCESS == event_raw_character_literal_dispose(&cev));

    clone = event_copy_get_event(cpy);
    TEST_ASSERT(NULL != clone);

    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_CHARACTER == event_get_type(clone));

    clone_c = event_get_cursor(clone);
    TEST_ASSERT(NULL != clone_c);
    TEST_EXPECT(clone_c->begin_line == c.begin_line);
    TEST_EXPECT(clone_c->end_line == c.end_line);
    TEST_EXPECT(clone_c->begin_col == c.begin_col);
    TEST_EXPECT(clone_c->end_col == c.end_col);
    TEST_ASSERT(NULL != clone_c->file);
    TEST_EXPECT(!strcmp(c.file, clone_c->file));

    TEST_ASSERT(
        STATUS_SUCCESS
            == event_downcast_to_event_raw_character_literal(
                    &cev_clone, (event*)clone));
    TEST_ASSERT(!strcmp(VAL, event_raw_character_literal_get(cev_clone)));

    TEST_ASSERT(STATUS_SUCCESS == event_copy_release(cpy));
}

TEST(event_raw_float_token_init)
{
    event_raw_float_token fev;
    event_raw_float_token* fev_clone;
    event* ev;
    cursor c;
    event_copy* cpy;
    const event* clone;
    const cursor* clone_c;
    const char* VAL = "123.45";

    memset(&c, 0, sizeof(c));
    c.begin_line = 23;
    c.end_line = 24;
    c.begin_col = 1;
    c.end_col = 5;
    c.file = TESTFILE;

    TEST_ASSERT(
        STATUS_SUCCESS
            == event_raw_float_token_init(&fev, &c, VAL));
    ev = event_raw_float_token_upcast(&fev);
    TEST_ASSERT(STATUS_SUCCESS == event_copy_create(&cpy, ev));

    TEST_ASSERT(STATUS_SUCCESS == event_raw_float_token_dispose(&fev));

    clone = event_copy_get_event(cpy);
    TEST_ASSERT(NULL != clone);

    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_FLOAT == event_get_type(clone));

    clone_c = event_get_cursor(clone);
    TEST_ASSERT(NULL != clone_c);
    TEST_EXPECT(clone_c->begin_line == c.begin_line);
    TEST_EXPECT(clone_c->end_line == c.end_line);
    TEST_EXPECT(clone_c->begin_col == c.begin_col);
    TEST_EXPECT(clone_c->end_col == c.end_col);
    TEST_ASSERT(NULL != clone_c->file);
    TEST_EXPECT(!strcmp(c.file, clone_c->file));

    TEST_ASSERT(
        STATUS_SUCCESS
            == event_downcast_to_event_raw_float_token(
                    &fev_clone, (event*)clone));
    TEST_ASSERT(!strcmp(VAL, event_raw_float_token_string_get(fev_clone)));

    TEST_ASSERT(STATUS_SUCCESS == event_copy_release(cpy));
}

TEST(event_raw_integer_token_init)
{
    event_raw_integer_token iev;
    event_raw_integer_token* iev_clone;
    event* ev;
    cursor c;
    event_copy* cpy;
    const event* clone;
    const cursor* clone_c;
    const char* VAL = "1991";

    memset(&c, 0, sizeof(c));
    c.begin_line = 23;
    c.end_line = 24;
    c.begin_col = 1;
    c.end_col = 5;
    c.file = TESTFILE;

    TEST_ASSERT(
        STATUS_SUCCESS
            == event_raw_integer_token_init(&iev, &c, VAL));
    ev = event_raw_integer_token_upcast(&iev);
    TEST_ASSERT(STATUS_SUCCESS == event_copy_create(&cpy, ev));

    TEST_ASSERT(STATUS_SUCCESS == event_raw_integer_token_dispose(&iev));

    clone = event_copy_get_event(cpy);
    TEST_ASSERT(NULL != clone);

    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == event_get_type(clone));

    clone_c = event_get_cursor(clone);
    TEST_ASSERT(NULL != clone_c);
    TEST_EXPECT(clone_c->begin_line == c.begin_line);
    TEST_EXPECT(clone_c->end_line == c.end_line);
    TEST_EXPECT(clone_c->begin_col == c.begin_col);
    TEST_EXPECT(clone_c->end_col == c.end_col);
    TEST_ASSERT(NULL != clone_c->file);
    TEST_EXPECT(!strcmp(c.file, clone_c->file));

    TEST_ASSERT(
        STATUS_SUCCESS
            == event_downcast_to_event_raw_integer_token(
                    &iev_clone, (event*)clone));
    TEST_ASSERT(!strcmp(VAL, event_raw_integer_token_string_get(iev_clone)));

    TEST_ASSERT(STATUS_SUCCESS == event_copy_release(cpy));
}

TEST(event_raw_string_token_init)
{
    event_raw_string_token sev;
    event_raw_string_token* sev_clone;
    event* ev;
    cursor c;
    event_copy* cpy;
    const event* clone;
    const cursor* clone_c;
    const char* VAL = "\"foo bar\"";

    memset(&c, 0, sizeof(c));
    c.begin_line = 23;
    c.end_line = 24;
    c.begin_col = 1;
    c.end_col = 5;
    c.file = TESTFILE;

    TEST_ASSERT(
        STATUS_SUCCESS
            == event_raw_string_token_init(&sev, &c, VAL));
    ev = event_raw_string_token_upcast(&sev);
    TEST_ASSERT(STATUS_SUCCESS == event_copy_create(&cpy, ev));

    TEST_ASSERT(STATUS_SUCCESS == event_raw_string_token_dispose(&sev));

    clone = event_copy_get_event(cpy);
    TEST_ASSERT(NULL != clone);

    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == event_get_type(clone));

    clone_c = event_get_cursor(clone);
    TEST_ASSERT(NULL != clone_c);
    TEST_EXPECT(clone_c->begin_line == c.begin_line);
    TEST_EXPECT(clone_c->end_line == c.end_line);
    TEST_EXPECT(clone_c->begin_col == c.begin_col);
    TEST_EXPECT(clone_c->end_col == c.end_col);
    TEST_ASSERT(NULL != clone_c->file);
    TEST_EXPECT(!strcmp(c.file, clone_c->file));

    TEST_ASSERT(
        STATUS_SUCCESS
            == event_downcast_to_event_raw_string_token(
                    &sev_clone, (event*)clone));
    TEST_ASSERT(!strcmp(VAL, event_raw_string_token_get(sev_clone)));

    TEST_ASSERT(STATUS_SUCCESS == event_copy_release(cpy));
}
