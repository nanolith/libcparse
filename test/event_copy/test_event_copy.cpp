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
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_copy;

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
        clone = event_copy_get_event(cpy); \
        TEST_ASSERT(NULL != clone); \
        \
        TEST_EXPECT(event_get_type(&ev) == event_get_type(clone)); \
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
        TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev)); \
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
