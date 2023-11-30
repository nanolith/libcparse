/**
 * \file test/event_handler/test_event_handler.cpp
 *
 * \brief Tests for the \ref event_handler type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event_handler.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_handler;

TEST_SUITE(event_handler);

namespace
{
    struct test_context
    {
        size_t count;
        const CPARSE_SYM(event)* ev;
    };
}

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

/**
 * Test that we can send an event to the handler.
 */
TEST(send)
{
    event_handler eh;
    event ev;
    test_context t;
    cursor c;

    /* we can initialize the event_handler. */
    TEST_ASSERT(STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t));

    /* clear the test context. */
    memset(&t, 0, sizeof(t));

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* initialize a dummy event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init(&ev, 17, &c));

    /* precondition: test_context count is zero. */
    TEST_ASSERT(0 == t.count);

    /* send this event. */
    TEST_ASSERT(STATUS_SUCCESS == event_handler_send(&eh, &ev));

    /* postcondition: test_context count is 1. */
    TEST_EXPECT(1 == t.count);
    
    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}
