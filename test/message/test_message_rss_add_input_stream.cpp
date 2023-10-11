/**
 * \file test/message/test_message_rss_add_input_stream.cpp
 *
 * \brief Tests for the \ref message_rss_add_input_stream type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message.h>
#include <libcparse/message/raw_stack_scanner.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

CPARSE_IMPORT_input_stream;
CPARSE_IMPORT_message;
CPARSE_IMPORT_message_raw_stack_scanner;

TEST_SUITE(message);

/**
 * Test the basics of the message_rss_add_input_stream type.
 */
TEST(basics)
{
    message_rss_add_input_stream msg;
    input_stream* stream;
    const char* FILENAME = "test.input";

    /* we can create a string input stream. */
    TEST_ASSERT(
        STATUS_SUCCESS == input_stream_create_from_string(&stream, "test"));

    /* we can initialize the message. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == message_rss_add_input_stream_init(&msg, FILENAME, stream));

    /* the message type matches what we expect. */
    TEST_EXPECT(
        CPARSE_MESSAGE_TYPE_RSS_ADD_INPUT_STREAM
            == message_get_type(message_rss_add_input_stream_upcast(&msg)));

    /* the filename matches. */
    TEST_EXPECT(
        !strcmp(FILENAME, message_rss_add_input_stream_filename_get(&msg)));

    /* we can dispose the message. */
    TEST_ASSERT(STATUS_SUCCESS == message_rss_add_input_stream_dispose(&msg));
}

/**
 * Test that we can transfer an input stream to the caller.
 */
TEST(input_stream_xfer)
{
    message_rss_add_input_stream msg;
    input_stream* stream;
    const char* FILENAME = "test.input";

    /* we can create a string input stream. */
    TEST_ASSERT(
        STATUS_SUCCESS == input_stream_create_from_string(&stream, "test"));

    /* we can initialize the message. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == message_rss_add_input_stream_init(&msg, FILENAME, stream));

    /* we can transfer the input stream to the caller. */
    stream = nullptr;
    TEST_ASSERT(
        STATUS_SUCCESS == message_rss_add_input_stream_xfer(&stream, &msg));
    TEST_ASSERT(nullptr != stream);

    /* we can dispose the message. */
    TEST_ASSERT(STATUS_SUCCESS == message_rss_add_input_stream_dispose(&msg));
    /* we can release the stream. */
    TEST_ASSERT(STATUS_SUCCESS == input_stream_release(stream));
}

/**
 * Test that we can upcast and downcast this message.
 */
TEST(upcast_downcast)
{
    message_rss_add_input_stream msg;
    message* upcast_msg;
    message_rss_add_input_stream* downcast_msg;
    input_stream* stream;
    const char* FILENAME = "test.input";

    /* we can create a string input stream. */
    TEST_ASSERT(
        STATUS_SUCCESS == input_stream_create_from_string(&stream, "test"));

    /* we can initialize the message. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == message_rss_add_input_stream_init(&msg, FILENAME, stream));

    /* we can upcast the message. */
    upcast_msg = message_rss_add_input_stream_upcast(&msg);
    TEST_ASSERT(NULL != upcast_msg);

    /* we can downcast the message. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == message_downcast_to_message_rss_add_input_stream(
                    &downcast_msg, upcast_msg));

    /* we can dispose the message. */
    TEST_ASSERT(STATUS_SUCCESS == message_rss_add_input_stream_dispose(&msg));
}
