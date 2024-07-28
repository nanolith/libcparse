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

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;

TEST_SUITE(event);

#define EVENT_INIT_TYPE_TEST(ctor, type) \
    TEST(ctor) \
    { \
        event ev; \
        cursor c; \
        \
        memset(&c, 0, sizeof(c)); \
        \
        TEST_ASSERT(STATUS_SUCCESS == event_init_for_eof(&ev, &c)); \
        \
        TEST_EXPECT(CPARSE_EVENT_TYPE_EOF == event_get_type(&ev)); \
        \
        TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev)); \
    } \
    REQUIRE_SEMICOLON_HERE

/* token tests. */
EVENT_INIT_TYPE_TEST(event_init_for_eof, CPARSE_EVENT_TYPE_EOF);
EVENT_INIT_TYPE_TEST(
    event_init_for_whitespace_token, CPARSE_EVENT_TYPE_TOKEN_WHITESPACE);
EVENT_INIT_TYPE_TEST(
    event_init_for_newline_token, CPARSE_EVENT_TYPE_TOKEN_NEWLINE);
EVENT_INIT_TYPE_TEST(
    event_init_for_comment_block_begin, CPARSE_EVENT_TYPE_COMMENT_BLOCK_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_comment_block_end, CPARSE_EVENT_TYPE_COMMENT_BLOCK_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_comment_line_begin, CPARSE_EVENT_TYPE_COMMENT_LINE_BEGIN);
EVENT_INIT_TYPE_TEST(
    event_init_for_comment_line_end, CPARSE_EVENT_TYPE_COMMENT_LINE_END);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_left_paren, CPARSE_EVENT_TYPE_TOKEN_LEFT_PAREN);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_right_paren, CPARSE_EVENT_TYPE_TOKEN_RIGHT_PAREN);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_left_brace, CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACE);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_right_brace, CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACE);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_left_bracket, CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACKET);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_right_bracket, CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACKET);
EVENT_INIT_TYPE_TEST(event_init_for_token_comma, CPARSE_EVENT_TYPE_TOKEN_COMMA);
EVENT_INIT_TYPE_TEST(event_init_for_token_colon, CPARSE_EVENT_TYPE_TOKEN_COLON);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_semicolon, CPARSE_EVENT_TYPE_TOKEN_SEMICOLON);
EVENT_INIT_TYPE_TEST(event_init_for_token_dot, CPARSE_EVENT_TYPE_TOKEN_DOT);
EVENT_INIT_TYPE_TEST(event_init_for_token_arrow, CPARSE_EVENT_TYPE_TOKEN_ARROW);
EVENT_INIT_TYPE_TEST(event_init_for_token_plus, CPARSE_EVENT_TYPE_TOKEN_PLUS);
EVENT_INIT_TYPE_TEST(event_init_for_token_minus, CPARSE_EVENT_TYPE_TOKEN_MINUS);
EVENT_INIT_TYPE_TEST(event_init_for_token_star, CPARSE_EVENT_TYPE_TOKEN_STAR);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_forward_slash, CPARSE_EVENT_TYPE_TOKEN_FORWARD_SLASH);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_percent, CPARSE_EVENT_TYPE_TOKEN_PERCENT);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_logical_and, CPARSE_EVENT_TYPE_TOKEN_LOGICAL_AND);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_logical_or, CPARSE_EVENT_TYPE_TOKEN_LOGICAL_OR);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_ampersand, CPARSE_EVENT_TYPE_TOKEN_AMPERSAND);
EVENT_INIT_TYPE_TEST(event_init_for_token_pipe, CPARSE_EVENT_TYPE_TOKEN_PIPE);
EVENT_INIT_TYPE_TEST(event_init_for_token_caret, CPARSE_EVENT_TYPE_TOKEN_CARET);
EVENT_INIT_TYPE_TEST(event_init_for_token_tilde, CPARSE_EVENT_TYPE_TOKEN_TILDE);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_question, CPARSE_EVENT_TYPE_TOKEN_QUESTION);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_equal_compare, CPARSE_EVENT_TYPE_TOKEN_EQUAL_COMPARE);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_not_equal_compare,
    CPARSE_EVENT_TYPE_TOKEN_NOT_EQUAL_COMPARE);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_equal_assign, CPARSE_EVENT_TYPE_TOKEN_EQUAL_ASSIGN);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_plus_equal, CPARSE_EVENT_TYPE_TOKEN_PLUS_EQUAL);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_minus_equal, CPARSE_EVENT_TYPE_TOKEN_MINUS_EQUAL);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_times_equal, CPARSE_EVENT_TYPE_TOKEN_TIMES_EQUAL);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_div_equal, CPARSE_EVENT_TYPE_TOKEN_DIV_EQUAL);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_mod_equal, CPARSE_EVENT_TYPE_TOKEN_MOD_EQUAL);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_and_equal, CPARSE_EVENT_TYPE_TOKEN_AND_EQUAL);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_or_equal, CPARSE_EVENT_TYPE_TOKEN_OR_EQUAL);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_xor_equal, CPARSE_EVENT_TYPE_TOKEN_XOR_EQUAL);
EVENT_INIT_TYPE_TEST(
    event_init_for_token_compl_equal, CPARSE_EVENT_TYPE_TOKEN_COMPL_EQUAL);

/**
 * Test that we can create a token left shift equal event.
 */
TEST(token_left_shift_equal)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_left_shift_equal(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_LEFT_SHIFT_EQUAL == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token right shift equal event.
 */
TEST(token_right_shift_equal)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_right_shift_equal(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_RIGHT_SHIFT_EQUAL == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token bitshift left event.
 */
TEST(token_bitshift_left)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_bitshift_left(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_BITSHIFT_LEFT == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token bitshift right event.
 */
TEST(token_bitshift_right)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_bitshift_right(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_BITSHIFT_RIGHT == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token less than event.
 */
TEST(token_less_than)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_less_than(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_LESS_THAN == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token greater than event.
 */
TEST(token_greater_than)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_greater_than(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_GREATER_THAN == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token less than equal event.
 */
TEST(token_less_than_equal)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_less_than_equal(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_LESS_THAN_EQUAL == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token greater than equal event.
 */
TEST(token_greater_than_equal)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_greater_than_equal(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_GREATER_THAN_EQUAL == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token increment event.
 */
TEST(token_increment)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_increment(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_INCREMENT == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token decrement event.
 */
TEST(token_decrement)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_decrement(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_DECREMENT == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token not event.
 */
TEST(token_not)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_not(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_NOT == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token ellipsis event.
 */
TEST(token_ellipsis)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_ellipsis(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_ELLIPSIS == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token preprocessor id if event.
 */
TEST(token_preprocessor_id_if)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_preprocessor_id_if(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_PP_ID_IF == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token preprocessor id ifdef event.
 */
TEST(token_preprocessor_id_ifdef)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_preprocessor_id_ifdef(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_PP_ID_IFDEF == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token preprocessor id ifndef event.
 */
TEST(token_preprocessor_id_ifndef)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_preprocessor_id_ifndef(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_PP_ID_IFNDEF == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create an _Alignas keyword token event.
 */
TEST(_Alignas_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword__Alignas(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ALIGNAS == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create an _Alignof keyword token event.
 */
TEST(_Alignof_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword__Alignof(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ALIGNOF == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create an _Atomic keyword token event.
 */
TEST(_Atomic_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword__Atomic(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ATOMIC == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a _Bool keyword token event.
 */
TEST(_Bool_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword__Bool(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD__BOOL == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a _Complex keyword token event.
 */
TEST(_Complex_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword__Complex(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD__COMPLEX == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a _Generic keyword token event.
 */
TEST(_Generic_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword__Generic(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD__GENERIC == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create an _Imaginary keyword token event.
 */
TEST(_Imaginary_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword__Imaginary(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD__IMAGINARY == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a _Noreturn keyword token event.
 */
TEST(_Noreturn_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword__Noreturn(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD__NORETURN == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a _Static_assert keyword token event.
 */
TEST(_Static_assert_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword__Static_assert(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD__STATIC_ASSERT == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a _Thread_local keyword token event.
 */
TEST(_Thread_local_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword__Thread_local(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD__THREAD_LOCAL == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create an auto keyword token event.
 */
TEST(auto_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_auto(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_AUTO == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a break keyword token event.
 */
TEST(break_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_break(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_BREAK == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a case keyword token event.
 */
TEST(case_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_case(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CASE == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a char keyword token event.
 */
TEST(char_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_char(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CHAR == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a const keyword token event.
 */
TEST(const_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_const(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CONST == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a continue keyword token event.
 */
TEST(continue_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_continue(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CONTINUE == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a default keyword token event.
 */
TEST(default_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_default(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DEFAULT == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a do keyword token event.
 */
TEST(do_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_do(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DO == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a double keyword token event.
 */
TEST(double_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_double(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DOUBLE == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create an else keyword token event.
 */
TEST(else_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_else(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ELSE == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create an enum keyword token event.
 */
TEST(enum_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_enum(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ENUM == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create an extern keyword token event.
 */
TEST(extern_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_extern(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_EXTERN == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a float keyword token event.
 */
TEST(float_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_float(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FLOAT == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a for keyword token event.
 */
TEST(for_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_for(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FOR == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a goto keyword token event.
 */
TEST(goto_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_goto(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_GOTO == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create an if keyword token event.
 */
TEST(if_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_if(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_IF == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create an inline keyword token event.
 */
TEST(inline_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_inline(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_INLINE == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create an int keyword token event.
 */
TEST(int_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_int(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_INT == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a long keyword token event.
 */
TEST(long_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_long(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_LONG == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a register keyword token event.
 */
TEST(register_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_register(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_REGISTER == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a restrict keyword token event.
 */
TEST(restrict_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_restrict(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_RESTRICT == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a return keyword token event.
 */
TEST(return_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_return(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_RETURN == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a short keyword token event.
 */
TEST(short_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_short(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SHORT == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a signed keyword token event.
 */
TEST(signed_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_signed(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SIGNED == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a sizeof keyword token event.
 */
TEST(sizeof_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_sizeof(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SIZEOF == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a static keyword token event.
 */
TEST(static_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_static(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_STATIC == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a struct keyword token event.
 */
TEST(struct_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_struct(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_STRUCT == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a switch keyword token event.
 */
TEST(switch_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_switch(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SWITCH == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a typedef keyword token event.
 */
TEST(typedef_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_typedef(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_TYPEDEF == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a union keyword token event.
 */
TEST(union_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_union(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_UNION == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a unsigned keyword token event.
 */
TEST(unsigned_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_unsigned(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_UNSIGNED == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a void keyword token event.
 */
TEST(void_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_void(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_VOID == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a volatile keyword token event.
 */
TEST(volatile_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_volatile(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_VOLATILE == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a while keyword token event.
 */
TEST(while_keyword_token)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_keyword_while(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_KEYWORD_WHILE == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a preprocessor directive end event.
 */
TEST(preprocessor_directive_end)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_preprocessor_directive_end(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_PP_END == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}
