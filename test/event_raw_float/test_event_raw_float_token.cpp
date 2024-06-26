/**
 * \file test/event_raw_float/test_event_raw_float_token.cpp
 *
 * \brief Tests for the \ref event_raw_float_token type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <cstring>
#include <libcparse/event/raw_float.h>
#include <libcparse/event_type.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event_raw_float;

TEST_SUITE(event_raw_float_token);

/**
 * Test that we can init and dispose an event_raw_float_token type.
 */
TEST(init_dispose)
{
    cursor pos;
    event_raw_float_token ev;
    const char* TEST_FLOAT = "123.0";

    /* set up the position. */
    memset(&pos, 0, sizeof(pos));
    pos.file = "stdin";
    pos.begin_line = pos.end_line = 1;
    pos.begin_col = pos.end_col = 1;

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_raw_float_token_init(&ev, &pos, TEST_FLOAT));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_float_token_dispose(&ev));
}

/**
 * Test that we can get the raw float string value.
 */
TEST(string_get)
{
    cursor pos;
    event_raw_float_token ev;
    const char* TEST_FLOAT = "123.0";

    /* set up the position. */
    memset(&pos, 0, sizeof(pos));
    pos.file = "stdin";
    pos.begin_line = pos.end_line = 1;
    pos.begin_col = pos.end_col = 1;

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_raw_float_token_init(&ev, &pos, TEST_FLOAT));

    /* the string value should match our constructor value. */
    auto val = event_raw_float_token_string_get(&ev);
    TEST_ASSERT(nullptr != val);
    TEST_EXPECT(!strcmp(TEST_FLOAT, val));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_float_token_dispose(&ev));
}

/**
 * Test that we can set the sign.
 */
TEST(sign_set)
{
    cursor pos;
    event_raw_float_token ev;
    const char* TEST_FLOAT = "123.0";

    /* set up the position. */
    memset(&pos, 0, sizeof(pos));
    pos.file = "stdin";
    pos.begin_line = pos.end_line = 1;
    pos.begin_col = pos.end_col = 1;

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_raw_float_token_init(&ev, &pos, TEST_FLOAT));

    /* set should succeed. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_float_token_sign_set(&ev, true));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_float_token_dispose(&ev));
}

/**
 * Test that we can upcast and downcast the raw float token event.
 */
TEST(upcast_downcast)
{
    cursor pos;
    event_raw_float_token ev;
    event_raw_float_token* rev;
    const char* TEST_FLOAT = "123.0";

    /* set up the position. */
    memset(&pos, 0, sizeof(pos));
    pos.file = "stdin";
    pos.begin_line = pos.end_line = 1;
    pos.begin_col = pos.end_col = 1;

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_raw_float_token_init(&ev, &pos, TEST_FLOAT));

    /* upcast the event. */
    auto oev = event_raw_float_token_upcast(&ev);

    /* we can downcast this event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_downcast_to_event_raw_float_token(&rev, oev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_float_token_dispose(&ev));
}
