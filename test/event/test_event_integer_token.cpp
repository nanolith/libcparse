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
#include <limits.h>
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

/**
 * We get a conversion error if the signed value is > SCHAR_MAX.
 */
TEST(signed_integer_to_char_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 512;
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

/**
 * Test that we can convert an unsigned integer token to a char.
 */
TEST(unsigned_integer_to_char)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    char val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
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
 * We get a conversion error if the unsigned value is > UCHAR_MAX.
 */
TEST(unsigned_integer_to_char_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 512;
    char val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_char(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed integer token to an unsigned char.
 */
TEST(signed_integer_to_unsigned_char)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    unsigned char val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a char. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_convert_to_unsigned_char(&val, &ev));

    /* the char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is < 0.
 */
TEST(signed_integer_to_unsigned_char_negative_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = -12;
    unsigned char val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_unsigned_char(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is > UCHAR_MAX.
 */
TEST(signed_integer_to_unsigned_char_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 256;
    unsigned char val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_unsigned_char(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert an unsigned integer token to an unsigned char.
 */
TEST(unsigned_integer_to_unsigned_char)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    unsigned char val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a char. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_convert_to_unsigned_char(&val, &ev));

    /* the char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the unsigned value is > UCHAR_MAX.
 */
TEST(unsigned_integer_to_unsigned_char_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 256;
    unsigned char val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_unsigned_char(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed integer token to a short.
 */
TEST(signed_integer_to_short)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    short val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a short. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_short(&val, &ev));

    /* the char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is < SHRT_MIN.
 */
TEST(signed_integer_to_short_negative_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = -40000;
    short val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_short(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is > SHRT_MAX.
 */
TEST(signed_integer_to_short_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 40000;
    short val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_short(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert an unsigned integer token to a short.
 */
TEST(unsigned_integer_to_short)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    short val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a short. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_short(&val, &ev));

    /* thi short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the unsigned value is > SHRT_MAX.
 */
TEST(unsigned_integer_to_short_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 40000;
    short val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_short(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed integer token to an unsigned short.
 */
TEST(signed_integer_to_unsigned_short)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    unsigned short val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned short. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_convert_to_unsigned_short(&val, &ev));

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is < 0.
 */
TEST(signed_integer_to_unsigned_short_negative_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = -5;
    unsigned short val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_unsigned_short(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is > USHRT_MAX.
 */
TEST(signed_integer_to_unsigned_short_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 70000;
    unsigned short val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_unsigned_short(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert an unsigned integer token to an unsigned short.
 */
TEST(unsigned_integer_to_unsigned_short)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    unsigned short val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned short. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_convert_to_unsigned_short(&val, &ev));

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the unsigned value is > USHRT_MAX.
 */
TEST(unsigned_integer_to_unsigned_short_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 70000;
    unsigned short val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_unsigned_short(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed long token to an int.
 */
TEST(signed_long_to_int)
{
    cursor pos;
    event_integer_token ev;
    const long TEST_VAL = 12;
    int val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_int(&val, &ev));

    /* the char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is < INT_MIN.
 */
TEST(signed_long_to_int_negative_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const long TEST_VAL = ((long)INT_MIN) - 1000L;
    int val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_int(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is > INT_MAX.
 */
TEST(signed_long_to_int_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const long TEST_VAL = ((long)INT_MAX) + 1000L;
    int val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_int(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert an unsigned long token to an int.
 */
TEST(unsigned_long_to_int)
{
    cursor pos;
    event_integer_token ev;
    const unsigned long TEST_VAL = 12;
    int val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_int(&val, &ev));

    /* the char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the unsigned value is > INT_MAX.
 */
TEST(unsigned_long_to_int_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const unsigned long TEST_VAL = ((long)INT_MAX) + 1000;
    int val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_long(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_int(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed long token to an unsigned short.
 */
TEST(signed_long_to_unsigned_int)
{
    cursor pos;
    event_integer_token ev;
    const long TEST_VAL = 12;
    unsigned int val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned int. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_convert_to_unsigned_int(&val, &ev));

    /* the unsigned int value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is < 0.
 */
TEST(signed_long_to_unsigned_int_negative_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const long TEST_VAL = -5;
    unsigned int val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_unsigned_int(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is > UINT_MAX.
 */
TEST(signed_long_to_unsigned_int_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const long TEST_VAL = ((long)UINT_MAX) + 1000;
    unsigned int val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_unsigned_int(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert an unsigned long token to an unsigned short.
 */
TEST(unsigned_long_to_unsigned_int)
{
    cursor pos;
    event_integer_token ev;
    const unsigned long TEST_VAL = 12;
    unsigned int val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned int. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_convert_to_unsigned_int(&val, &ev));

    /* the unsigned int value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the unsigned value is > UINT_MAX.
 */
TEST(unsigned_long_to_unsigned_int_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const unsigned long TEST_VAL = ((long)UINT_MAX) + 1000;
    unsigned int val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_long(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_unsigned_int(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed long long token to a long.
 */
TEST(signed_long_long_to_long)
{
    cursor pos;
    event_integer_token ev;
    const long long TEST_VAL = 12;
    long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a long. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_long(&val, &ev));

    /* the char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert an unsigned long long token to a long.
 */
TEST(unsigned_long_long_to_long)
{
    cursor pos;
    event_integer_token ev;
    const unsigned long long TEST_VAL = 12;
    long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_long_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a long. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_long(&val, &ev));

    /* the char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed long long token to an unsigned long.
 */
TEST(signed_long_long_to_unsigned_long)
{
    cursor pos;
    event_integer_token ev;
    const long long TEST_VAL = 12;
    unsigned long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned long. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_convert_to_unsigned_long(&val, &ev));

    /* the char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is < 0.
 */
TEST(signed_long_long_to_unsigned_long_negative_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const long long TEST_VAL = -5;
    unsigned long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long_long(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_unsigned_long(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert an unsigned long long token to an unsigned long.
 */
TEST(unsigned_long_long_to_unsigned_long)
{
    cursor pos;
    event_integer_token ev;
    const unsigned long long TEST_VAL = 12;
    unsigned long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_long_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned long. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_convert_to_unsigned_long(&val, &ev));

    /* the char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed long long token to a long long.
 */
TEST(signed_long_long_to_long_long)
{
    cursor pos;
    event_integer_token ev;
    const long long TEST_VAL = 12;
    long long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a long long. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_long_long(&val, &ev));

    /* the char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert an unsigned long long token to a long long.
 */
TEST(unsigned_long_long_to_long_long)
{
    cursor pos;
    event_integer_token ev;
    const unsigned long long TEST_VAL = 12;
    long long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_long_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a long long. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_long_long(&val, &ev));

    /* the char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed long long token to an unsigned long long.
 */
TEST(signed_long_long_to_unsigned_long_long)
{
    cursor pos;
    event_integer_token ev;
    const long long TEST_VAL = 12;
    unsigned long long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned long long. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_convert_to_unsigned_long_long(&val, &ev));

    /* the char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert an unsigned long long token to an unsigned long
 * long.
 */
TEST(unsigned_long_long_to_unsigned_long_long)
{
    cursor pos;
    event_integer_token ev;
    const unsigned long long TEST_VAL = 12;
    unsigned long long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_long_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned long long. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_convert_to_unsigned_long_long(&val, &ev));

    /* the char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed integer token to an int8.
 */
TEST(signed_integer_to_int8)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    int8_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int8. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_int8(&val, &ev));

    /* the int8 value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is < INT8_MIN.
 */
TEST(signed_integer_to_int8_negative_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = -130;
    int8_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int8. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_int8(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is > INT8_MAX.
 */
TEST(signed_integer_to_int8_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 130;
    int8_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int8. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_int8(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert an unsigned integer token to an int8.
 */
TEST(unsigned_integer_to_int8)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    int8_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int8. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_int8(&val, &ev));

    /* the int8 value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the unsigned value is > INT8_MAX.
 */
TEST(unsigned_integer_to_int8_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 130;
    int8_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_int8(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed integer token to a uint8.
 */
TEST(signed_integer_to_uint8)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    uint8_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int8. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_uint8(&val, &ev));

    /* the uint8 value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is < 0.
 */
TEST(signed_integer_to_uint8_negative_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = -5;
    uint8_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_uint8(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is > UINT8_MAX.
 */
TEST(signed_integer_to_uint8_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 300;
    uint8_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_uint8(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert an unsigned integer token to a uint8.
 */
TEST(unsigned_integer_to_uint8)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    uint8_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a uint8. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_uint8(&val, &ev));

    /* the uint8 value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the unsigned value is > UINT8_MAX.
 */
TEST(unsigned_integer_to_uint8_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 300;
    uint8_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* conversion error. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_uint8(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed integer token to an int16.
 */
TEST(signed_integer_to_int16)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    int16_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int16. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_int16(&val, &ev));

    /* the int16 value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is < INT16_MIN.
 */
TEST(signed_integer_to_int16_negative_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = -40000;
    int16_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_int16(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is > INT16_MAX.
 */
TEST(signed_integer_to_int16_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 40000;
    int16_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_int16(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert an unsigned integer token to an int16.
 */
TEST(unsigned_integer_to_int16)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    int16_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int16. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_int16(&val, &ev));

    /* the int16 value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the unsigned value is > INT16_MAX.
 */
TEST(unsigned_integer_to_int16_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 40000;
    int16_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_int16(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed integer token to a uint16.
 */
TEST(signed_integer_to_uint16)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    uint16_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a uint16. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_uint16(&val, &ev));

    /* the uint16 value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is < 0.
 */
TEST(signed_integer_to_uint16_negative_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = -5;
    uint16_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_uint16(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is > UINT16_MAX.
 */
TEST(signed_integer_to_uint16_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 70000;
    uint16_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* conversion fails. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_uint16(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert an unsigned integer token to a uint16.
 */
TEST(unsigned_integer_to_uint16)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    uint16_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a uint16. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_uint16(&val, &ev));

    /* the uint16 value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the unsigned value is > UINT16_MAX.
 */
TEST(unsigned_integer_to_uint16_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 70000;
    uint16_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* conversion error. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_uint16(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed long token to an int32.
 */
TEST(signed_long_to_int32)
{
    cursor pos;
    event_integer_token ev;
    const long TEST_VAL = 12;
    int32_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int32. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_int32(&val, &ev));

    /* the int32 value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is < INT32_MIN.
 */
TEST(signed_long_to_int32_negative_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const long TEST_VAL = ((long)INT32_MIN) - 1000;
    int32_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long(
                    &ev, &pos, TEST_VAL));

    /* conversion error. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_int32(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is > INT32_MAX.
 */
TEST(signed_long_to_int32_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const long TEST_VAL = ((long)INT32_MAX) + 1000;
    int32_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long(
                    &ev, &pos, TEST_VAL));

    /* conversion error. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_int32(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert an unsigned long token to an int32.
 */
TEST(unsigned_long_to_int32)
{
    cursor pos;
    event_integer_token ev;
    const unsigned long TEST_VAL = 12;
    int32_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int32. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_int32(&val, &ev));

    /* the int32 value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the unsigned value is > INT32_MAX.
 */
TEST(unsigned_long_to_int32_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const unsigned long TEST_VAL = ((long)INT32_MAX) + 1000;
    int32_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_long(
                    &ev, &pos, TEST_VAL));

    /* conversion error. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_int32(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed long token to a uint32.
 */
TEST(signed_long_to_uint32)
{
    cursor pos;
    event_integer_token ev;
    const long TEST_VAL = 12;
    uint32_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a uint32. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_uint32(&val, &ev));

    /* the uint32 value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is < 0.
 */
TEST(signed_long_to_uint32_negative_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const long TEST_VAL = -5;
    uint32_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long(
                    &ev, &pos, TEST_VAL));

    /* conversion error. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_uint32(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the signed value is > UINT32_MAX.
 */
TEST(signed_long_to_uint32_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const long TEST_VAL = ((long)UINT32_MAX) + 1000;
    uint32_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long(
                    &ev, &pos, TEST_VAL));

    /* conversion error. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_uint32(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a unsigned long token to a uint32.
 */
TEST(unsigned_long_to_uint32)
{
    cursor pos;
    event_integer_token ev;
    const unsigned long TEST_VAL = 12;
    uint32_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a uint32. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_uint32(&val, &ev));

    /* the uint32 value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * We get a conversion error if the unsigned value is > UINT32_MAX.
 */
TEST(unsigned_long_to_uint32_positive_conversion_error)
{
    cursor pos;
    event_integer_token ev;
    const unsigned long TEST_VAL = ((unsigned long)UINT32_MAX) + 1000;
    uint32_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_long(
                    &ev, &pos, TEST_VAL));

    /* conversion error. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION
            == event_integer_token_convert_to_uint32(&val, &ev));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed long token to an int64.
 */
TEST(signed_long_to_int64)
{
    cursor pos;
    event_integer_token ev;
    const long TEST_VAL = 12;
    int64_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int64. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_int64(&val, &ev));

    /* the int64 value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert an unsigned long token to an int64.
 */
TEST(unsigned_long_to_int64)
{
    cursor pos;
    event_integer_token ev;
    const unsigned long TEST_VAL = 12;
    int64_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int64. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_int64(&val, &ev));

    /* the int64 value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert a signed long token to a uint64.
 */
TEST(signed_long_to_uint64)
{
    cursor pos;
    event_integer_token ev;
    const long TEST_VAL = 12;
    uint64_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a uint64. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_uint64(&val, &ev));

    /* the uint64 value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can convert an unsigned long token to a uint64.
 */
TEST(unsigned_long_to_uint64)
{
    cursor pos;
    event_integer_token ev;
    const unsigned long TEST_VAL = 12;
    uint64_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_long(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a uint64. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_integer_token_convert_to_uint64(&val, &ev));

    /* the uint64 value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce a signed integer to char.
 */
TEST(signed_integer_coerce_to_char)
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
    val = event_integer_token_coerce_char(&ev);

    /* the char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an unsigned integer to char.
 */
TEST(unsigned_integer_coerce_to_char)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    char val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a char. */
    val = event_integer_token_coerce_char(&ev);

    /* the char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce a signed integer to unsigned char.
 */
TEST(signed_integer_coerce_to_unsigned_char)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    unsigned char val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned char. */
    val = event_integer_token_coerce_unsigned_char(&ev);

    /* the unsigned char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an unsigned integer to unsigned char.
 */
TEST(unsigned_integer_coerce_to_unsigned_char)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    unsigned char val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned char. */
    val = event_integer_token_coerce_unsigned_char(&ev);

    /* the unsigned char value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce a signed integer to short.
 */
TEST(signed_integer_coerce_to_short)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    short val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a short. */
    val = event_integer_token_coerce_short(&ev);

    /* the short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an unsigned integer to short.
 */
TEST(unsigned_integer_coerce_to_short)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    short val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a short. */
    val = event_integer_token_coerce_short(&ev);

    /* the short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce a signed integer to unsigned short.
 */
TEST(signed_integer_coerce_to_unsigned_short)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    unsigned short val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned short. */
    val = event_integer_token_coerce_unsigned_short(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an unsigned integer to unsigned short.
 */
TEST(unsigned_integer_coerce_to_unsigned_short)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    unsigned short val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned short. */
    val = event_integer_token_coerce_unsigned_short(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an integer to an int.
 */
TEST(signed_integer_coerce_to_int)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    int val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int. */
    val = event_integer_token_coerce_int(&ev);

    /* the int value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an unsigned integer to an int.
 */
TEST(unsigned_integer_coerce_to_int)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    int val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int. */
    val = event_integer_token_coerce_int(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an integer to an unsigned int.
 */
TEST(signed_integer_coerce_to_unsigned_int)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    unsigned int val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned int. */
    val = event_integer_token_coerce_unsigned_int(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an unsigned integer to an unsigned int.
 */
TEST(unsigned_integer_coerce_to_unsigned_int)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    unsigned int val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned int. */
    val = event_integer_token_coerce_unsigned_int(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an integer to a long.
 */
TEST(signed_integer_coerce_to_long)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a long. */
    val = event_integer_token_coerce_long(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an unsigned integer to a long.
 */
TEST(unsigned_integer_coerce_to_long)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a long. */
    val = event_integer_token_coerce_long(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an integer to an unsigned long.
 */
TEST(signed_integer_coerce_to_unsigned_long)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    unsigned long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned long. */
    val = event_integer_token_coerce_unsigned_long(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an unsigned integer to an unsigned long.
 */
TEST(unsigned_integer_coerce_to_unsigned_long)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    unsigned long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned long. */
    val = event_integer_token_coerce_unsigned_long(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an integer to a long long.
 */
TEST(signed_integer_coerce_to_long_long)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    long long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a long long. */
    val = event_integer_token_coerce_long_long(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an unsigned integer to a long long.
 */
TEST(unsigned_integer_coerce_to_long_long)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    long long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a long long. */
    val = event_integer_token_coerce_long_long(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an integer to an unsigned long long.
 */
TEST(signed_integer_coerce_to_unsigned_long_long)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    unsigned long long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned long long. */
    val = event_integer_token_coerce_unsigned_long_long(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an unsigned integer to an unsigned long long.
 */
TEST(unsigned_integer_coerce_to_unsigned_long_long)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    unsigned long long val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an unsigned long long. */
    val = event_integer_token_coerce_unsigned_long_long(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an integer to an int8.
 */
TEST(signed_integer_coerce_to_int8)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    int8_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int8_t. */
    val = event_integer_token_coerce_int8(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an unsigned integer to an int8.
 */
TEST(unsigned_integer_coerce_to_int8)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    int8_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to an int8_t. */
    val = event_integer_token_coerce_int8(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an integer to a uint8.
 */
TEST(signed_integer_coerce_to_uint8)
{
    cursor pos;
    event_integer_token ev;
    const int TEST_VAL = 12;
    uint8_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_signed_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a uint8_t. */
    val = event_integer_token_coerce_uint8(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}

/**
 * Test that we can coerce an unsigned integer to a uint8.
 */
TEST(unsigned_integer_coerce_to_uint8)
{
    cursor pos;
    event_integer_token ev;
    const unsigned int TEST_VAL = 12;
    uint8_t val = 0;

    memset(&pos, 0, sizeof(pos));

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_integer_token_init_for_unsigned_int(
                    &ev, &pos, TEST_VAL));

    /* we can convert this value to a uint8_t. */
    val = event_integer_token_coerce_uint8(&ev);

    /* the unsigned short value matches. */
    TEST_EXPECT(TEST_VAL == val);

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_integer_token_dispose(&ev));
}
