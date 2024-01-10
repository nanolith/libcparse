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

/**
 * Test that we can create an EOF event.
 */
TEST(eof)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_eof(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_EOF == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a whitespace token event.
 */
TEST(token_whitespace)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_whitespace_token(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_WHITESPACE == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a newline token event.
 */
TEST(token_newline)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_newline_token(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_NEWLINE == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a comment block begin event.
 */
TEST(comment_block_begin)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_comment_block_begin(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_COMMENT_BLOCK_BEGIN == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a comment block end event.
 */
TEST(comment_block_end)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_comment_block_end(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_COMMENT_BLOCK_END == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a comment line begin event.
 */
TEST(comment_line_begin)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_comment_line_begin(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_COMMENT_LINE_BEGIN == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a comment line end event.
 */
TEST(comment_line_end)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_comment_line_end(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_COMMENT_LINE_END == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token left paren event.
 */
TEST(token_left_paren)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_left_paren(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_LEFT_PAREN == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token right paren event.
 */
TEST(token_right_paren)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_right_paren(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_RIGHT_PAREN == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token left brace event.
 */
TEST(token_left_brace)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_left_brace(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACE == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token right brace event.
 */
TEST(token_right_brace)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_right_brace(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACE == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token left bracket event.
 */
TEST(token_left_bracket)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_left_bracket(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACKET == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token right bracket event.
 */
TEST(token_right_bracket)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_right_bracket(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACKET == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token comma event.
 */
TEST(token_comma)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_comma(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_COMMA == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token colon event.
 */
TEST(token_colon)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_colon(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_COLON == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token semicolon event.
 */
TEST(token_semicolon)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_semicolon(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_SEMICOLON == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token dot event.
 */
TEST(token_dot)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_dot(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_DOT == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token arrow event.
 */
TEST(token_arrow)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_arrow(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_ARROW == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token plus event.
 */
TEST(token_plus)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_plus(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PLUS == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token minus event.
 */
TEST(token_minus)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_minus(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_MINUS == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token star event.
 */
TEST(token_star)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_star(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_STAR == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token forward slash event.
 */
TEST(token_forward_slash)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_forward_slash(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_FORWARD_SLASH == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token percent event.
 */
TEST(token_percent)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_percent(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PERCENT == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token logical and event.
 */
TEST(token_logical_and)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_logical_and(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_LOGICAL_AND == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token logical or event.
 */
TEST(token_logical_or)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_logical_or(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_LOGICAL_OR == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token ampersand event.
 */
TEST(token_ampersand)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_ampersand(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_AMPERSAND == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token pipe event.
 */
TEST(token_pipe)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_pipe(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PIPE == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token caret event.
 */
TEST(token_caret)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_caret(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_CARET == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token tilde event.
 */
TEST(token_tilde)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_tilde(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_TILDE == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token question event.
 */
TEST(token_question)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_question(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_QUESTION == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token equal compare event.
 */
TEST(token_equal_compare)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_token_equal_compare(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_EQUAL_COMPARE == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token not equal compare event.
 */
TEST(token_not_equal_compare)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_not_equal_compare(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_NOT_EQUAL_COMPARE == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token equal assign event.
 */
TEST(token_equal_assign)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_equal_assign(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_EQUAL_ASSIGN == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token plus equal event.
 */
TEST(token_plus_equal)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_plus_equal(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_PLUS_EQUAL == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token minus equal event.
 */
TEST(token_minus_equal)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_minus_equal(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_MINUS_EQUAL == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token times equal event.
 */
TEST(token_times_equal)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_times_equal(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_TIMES_EQUAL == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token div equal event.
 */
TEST(token_div_equal)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_div_equal(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_DIV_EQUAL == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token mod equal event.
 */
TEST(token_mod_equal)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_mod_equal(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_MOD_EQUAL == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token and equal event.
 */
TEST(token_and_equal)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_and_equal(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_AND_EQUAL == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token or equal event.
 */
TEST(token_or_equal)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_or_equal(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_OR_EQUAL == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token xor equal event.
 */
TEST(token_xor_equal)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_xor_equal(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_XOR_EQUAL == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can create a token compl equal event.
 */
TEST(token_compl_equal)
{
    event ev;
    cursor c;

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_init_for_token_compl_equal(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_COMPL_EQUAL == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

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
