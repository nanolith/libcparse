/**
 * \file test/message_handler/test_message_handler.cpp
 *
 * \brief Tests for the \ref message_handler type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message.h>
#include <libcparse/message_handler.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

CPARSE_IMPORT_message;
CPARSE_IMPORT_message_handler;

TEST_SUITE(message_handler);

struct test_context
{
    size_t count;
    const CPARSE_SYM(message)* msg;
};

static int dummy_callback(void* context, const CPARSE_SYM(message)* msg)
{
    test_context* ctx = (test_context*)context;
    ctx->count += 1;
    ctx->msg = msg;

    return STATUS_SUCCESS;
}

/**
 * Test the basics of the message_handler type.
 */
TEST(basics)
{
    message_handler mh;

    /* we can initialize the message_handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == message_handler_init(&mh, &dummy_callback, nullptr));

    /* we can dispose the message_handler. */
    TEST_ASSERT(STATUS_SUCCESS == message_handler_dispose(&mh));
}

/**
 * Test that the copy init method works.
 */
TEST(copy)
{
    message_handler mh;
    message_handler mh2;

    /* We can initialize the message_handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == message_handler_init(&mh, &dummy_callback, nullptr));

    /* we can copy this message_handler. */
    TEST_ASSERT(STATUS_SUCCESS == message_handler_init_copy(&mh2, &mh));

    /* the two are identical. */
    TEST_EXPECT(0 == memcmp(&mh, &mh2, sizeof(mh)));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == message_handler_dispose(&mh));
    TEST_ASSERT(STATUS_SUCCESS == message_handler_dispose(&mh2));
}

/**
 * Test that we can send a message to the handler.
 */
TEST(send)
{
    message_handler mh;
    message msg;
    test_context t;

    /* we can initialize the message_handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == message_handler_init(&mh, &dummy_callback, &t));

    /* clear the test context. */
    memset(&t, 0, sizeof(t));

    /* initialize a dummy message. */
    TEST_ASSERT(STATUS_SUCCESS == message_init(&msg, 17));

    /* precondition: test_context count is zero. */
    TEST_ASSERT(0 == t.count);

    /* send this message. */
    TEST_ASSERT(STATUS_SUCCESS == message_handler_send(&mh, &msg));

    /* postcondition: test_context count is 1. */
    TEST_EXPECT(1 == t.count);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == message_handler_dispose(&mh));
    TEST_ASSERT(STATUS_SUCCESS == message_dispose(&msg));
}
