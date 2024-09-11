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

/**
 * Test that we can init and dispose a signed long long token event.
 */
TEST(signed_long_long_init_dispose)
{
    cursor pos;
    event_integer_token ev;
    const long long TEST_VAL = 12;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long_long(
                    &ev, &pos, TEST_VAL));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can init and dispose an unsigned long long token event.
 */
TEST(unsigned_long_long_init_dispose)
{
    cursor pos;
    event_integer_token ev;
    const unsigned long long TEST_VAL = 12;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_long_long(
                    &ev, &pos, TEST_VAL));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed integer token to a char.
 */
TEST(signed_integer_to_char)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    char val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a char. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_char(&val, &ev));

    /* the char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is < SCHAR_MIN.
 */
TEST(signed_integer_to_char_negative_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = -512;
    char val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_char(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}
