/**
 * \file test/input_stream/test_input_stream_from_string.cpp
 *
 * \brief Tests for the string \ref input_stream.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/input_stream.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

CPARSE_IMPORT_input_stream;

TEST_SUITE(input_stream_from_string);

/**
 * Reading from an empty string input_stream returns EOF.
 */
TEST(empty_EOF)
{
    input_stream* stream = nullptr;
    int ch;

    /* Creating an empty string input stream should succeed. */
    TEST_ASSERT(STATUS_SUCCESS == input_stream_create_from_string(&stream, ""));

    /* Reading from this stream returns an EOF error. */
    TEST_EXPECT(
        ERROR_LIBCPARSE_INPUT_STREAM_EOF == input_stream_read(stream, &ch));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == input_stream_release(stream));
}

/**
 * We can read a character from the string input_stream.
 */
TEST(read_character)
{
    input_stream* stream = nullptr;
    int ch;

    /* Creating an empty string input stream should succeed. */
    TEST_ASSERT(
        STATUS_SUCCESS == input_stream_create_from_string(&stream, "a"));

    /* We can read a character. */
    TEST_ASSERT(
        STATUS_SUCCESS == input_stream_read(stream, &ch));
    TEST_EXPECT('a' == ch);

    /* Trying to read any more characters results in an EOF. */
    TEST_EXPECT(
        ERROR_LIBCPARSE_INPUT_STREAM_EOF == input_stream_read(stream, &ch));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == input_stream_release(stream));
}

/**
 * We can read multiple characters from the string input_stream.
 */
TEST(read_multiple_characters)
{
    input_stream* stream = nullptr;
    int ch;

    /* Creating an empty string input stream should succeed. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == input_stream_create_from_string(&stream, "abcdef"));

    /* We can characters. */
    TEST_ASSERT(
        STATUS_SUCCESS == input_stream_read(stream, &ch));
    TEST_EXPECT('a' == ch);
    TEST_ASSERT(
        STATUS_SUCCESS == input_stream_read(stream, &ch));
    TEST_EXPECT('b' == ch);
    TEST_ASSERT(
        STATUS_SUCCESS == input_stream_read(stream, &ch));
    TEST_EXPECT('c' == ch);
    TEST_ASSERT(
        STATUS_SUCCESS == input_stream_read(stream, &ch));
    TEST_EXPECT('d' == ch);
    TEST_ASSERT(
        STATUS_SUCCESS == input_stream_read(stream, &ch));
    TEST_EXPECT('e' == ch);
    TEST_ASSERT(
        STATUS_SUCCESS == input_stream_read(stream, &ch));
    TEST_EXPECT('f' == ch);

    /* Trying to read any more characters results in an EOF. */
    TEST_EXPECT(
        ERROR_LIBCPARSE_INPUT_STREAM_EOF == input_stream_read(stream, &ch));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == input_stream_release(stream));
}
