/**
 * \file test/event_handler/test_event_handler.cpp
 *
 * \brief Tests for the \ref event_handler type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_handler.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

CPARSE_IMPORT_event_handler;

TEST_SUITE(event_handler);

struct test_context
{
    size_t count;
    const CPARSE_SYM(event)* ev;
};

static int dummy_callback(void* context, const CPARSE_SYM(event)* ev)
{
    test_context* ctx = (test_context*)context;
    ctx->count += 1;
    ctx->ev = ev;

    return STATUS_SUCCESS;
}

/**
 * Test the basics of the event_handler type.
 */
TEST(basics)
{
    event_handler eh;

    /* we can initialize the event_handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, nullptr));

    /* we can dispose the event_handler. */
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that the copy init method works.
 */
TEST(copy)
{
    event_handler eh;
    event_handler eh2;

    /* we can initialize the event_handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, nullptr));

    /* we can copy this event_handler. */
    TEST_ASSERT(STATUS_SUCCESS == event_handler_init_copy(&eh2, &eh));

    /* the two are identical. */
    TEST_EXPECT(0 == memcmp(&eh, &eh, sizeof(eh)));

    /* we can dispose the event_handler. */
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh2));
}
