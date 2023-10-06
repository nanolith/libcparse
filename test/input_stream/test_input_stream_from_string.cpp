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
