/**
 * \file test/event_raw_integer_token/test_event_raw_integer_token.cpp
 *
 * \brief Tests for the \ref event_raw_integer_token type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <cstring>
#include <libcparse/event/raw_integer.h>
#include <libcparse/event_type.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event_raw_integer;

TEST_SUITE(event_raw_integer_token);

/**
 * Test that we can init and dispose an event_raw_integer_token type.
 */
TEST(init_dispose)
{
    cursor pos;
    event_raw_integer_token ev;
    const char* TEST_INT = "123";

    /* set up the position. */
    memset(&pos, 0, sizeof(pos));
    pos.file = "stdin";
    pos.begin_line = pos.end_line = 1;
    pos.begin_col = pos.end_col = 1;

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_raw_integer_token_init(&ev, &pos, TEST_INT));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_integer_token_dispose(&ev));
}

/**
 * Test that we can get the raw integer string value.
 */
TEST(string_get)
{
    cursor pos;
    event_raw_integer_token ev;
    const char* TEST_INT = "123";

    /* set up the position. */
    memset(&pos, 0, sizeof(pos));
    pos.file = "stdin";
    pos.begin_line = pos.end_line = 1;
    pos.begin_col = pos.end_col = 1;

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_raw_integer_token_init(&ev, &pos, TEST_INT));

    /* the string value should match our constructor value. */
    auto val = event_raw_integer_token_string_get(&ev);
    TEST_ASSERT(nullptr != val);
    TEST_EXPECT(!strcmp(TEST_INT, val));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_integer_token_dispose(&ev));
}

/**
 * Test that we can set the sign.
 */
TEST(sign_set)
{
    cursor pos;
    event_raw_integer_token ev;
    const char* TEST_INT = "123";

    /* set up the position. */
    memset(&pos, 0, sizeof(pos));
    pos.file = "stdin";
    pos.begin_line = pos.end_line = 1;
    pos.begin_col = pos.end_col = 1;

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_raw_integer_token_init(&ev, &pos, TEST_INT));

    /* set should succeed. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_integer_token_sign_set(&ev, true));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_integer_token_dispose(&ev));
}

/**
 * Test that we can upcast and downcast the raw integer token event.
 */
TEST(upcast_downcast)
{
    cursor pos;
    event_raw_integer_token ev;
    event_raw_integer_token* rev;
    const char* TEST_INT = "123";

    /* set up the position. */
    memset(&pos, 0, sizeof(pos));
    pos.file = "stdin";
    pos.begin_line = pos.end_line = 1;
    pos.begin_col = pos.end_col = 1;

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_raw_integer_token_init(&ev, &pos, TEST_INT));

    /* upcast the event. */
    auto oev = event_raw_integer_token_upcast(&ev);

    /* we can downcast this event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_downcast_to_event_raw_integer_token(&rev, oev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_integer_token_dispose(&ev));
}
