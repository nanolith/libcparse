/**
 * \file test/event_integer_token/test_event_integer_token.cpp
 *
 * \brief Tests for the \ref event_integer_token type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <cstring>
#include <libcparse/cursor.h>
#include <libcparse/event/integer.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event_integer;

TEST_SUITE(event_integer_token);

/**
 * Test that we can init and dispose a signed int token event.
 */
TEST(signed_int_init_dispose)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(&ev, &pos, TEST_VAL));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can init and dispose an unsigned int token event.
 */
TEST(unsigned_int_init_dispose)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(&ev, &pos, TEST_VAL));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can init and dispose a signed long token event.
 */
TEST(signed_long_init_dispose)
{
    cursor pos;
    event_integer_token ev;
    const long TEST_VAL = 12;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long(&ev, &pos, TEST_VAL));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can init and dispose an unsigned long token event.
 */
TEST(unsigned_long_init_dispose)
{
    cursor pos;
    event_integer_token ev;
    const unsigned long TEST_VAL = 12;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_long(&ev, &pos, TEST_VAL));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}
