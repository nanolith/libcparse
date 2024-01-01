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

    /* We can create an eof event. */
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

    /* We can create an eof event. */
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

    /* We can create an eof event. */
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

    /* We can create an eof event. */
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

    /* We can create an eof event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init_for_comment_block_end(&ev, &c));

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_COMMENT_BLOCK_END == event_get_type(&ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}
