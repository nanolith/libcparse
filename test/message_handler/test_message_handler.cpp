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
