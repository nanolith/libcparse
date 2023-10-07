/**
 * \file test/input_stream/test_input_stream_from_descriptor.cpp
 *
 * \brief Tests for the descriptor \ref input_stream.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/input_stream.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <sys/socket.h>
#include <unistd.h>

CPARSE_IMPORT_input_stream;

TEST_SUITE(input_stream_from_descriptor);

/**
 * Reading from an empty descriptor input_stream returns EOF.
 */
TEST(empty_EOF)
{
    input_stream* stream = nullptr;
    int ch;
    int sd[2];

    /* create the socket pair for this stream. */
    TEST_ASSERT(0 == socketpair(AF_UNIX, SOCK_STREAM, 0, sd));

    /* close the output side so the input side gets EOF. */
    close(sd[1]);

    /* Creating a socket descriptor input stream should succeed. */
    TEST_ASSERT(
        STATUS_SUCCESS == input_stream_create_from_descriptor(&stream, sd[0]));

    /* Reading from this stream returns an EOF error. */
    TEST_EXPECT(
        ERROR_LIBCPARSE_INPUT_STREAM_EOF == input_stream_read(stream, &ch));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == input_stream_release(stream));
}
