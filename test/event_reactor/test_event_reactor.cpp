/**
 * \file test/event_event_reactor/test_event_reactor.cpp
 *
 * \brief Tests for the \ref event_reactor type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_handler.h>
#include <libcparse/event_reactor.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_reactor;

TEST_SUITE(event_reactor);

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
 * Test the basics of the event_reactor type.
 */
TEST(basics)
{
    event_reactor* er;

    /* we can create the event_reactor. */
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_create(&er));

    /* we can release the event_reactor. */
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_release(er));
}

/**
 * Test that we can broadcast an event to zero handlers.
 */
TEST(broadcast_zero)
{
    event_reactor* er;
    event ev;
    cursor c;

    /* we can create an event_reactor. */
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_create(&er));

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* initialize a dummy event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init(&ev, 17, &c));

    /* broadcast this event. */
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_broadcast(er, &ev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_release(er));
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can broadcast an event to a single handler.
 */
TEST(broadcast_one)
{
    event_reactor* er;
    event_handler eh;
    event ev;
    test_context t;
    cursor c;

    /* we can create an event_reactor. */
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_create(&er));

    /* initialize an event_handler. */
    TEST_ASSERT(STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t));

    /* add this handler to the reactor. */
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_add(er, &eh));

    /* clear the test context. */
    memset(&t, 0, sizeof(t));

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* initialize a dummy event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init(&ev, 17, &c));

    /* precondition: test_context count is zero. */
    TEST_ASSERT(0 == t.count);

    /* broadcast this event. */
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_broadcast(er, &ev));

    /* postcondition: test_context count is 1. */
    TEST_EXPECT(1 == t.count);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_release(er));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}

/**
 * Test that we can broadcast an event to multiple handlers.
 */
TEST(broadcast_multiple)
{
    event_reactor* er;
    event_handler eh1, eh2, eh3;
    event ev;
    test_context t1, t2, t3;
    cursor c;

    /* we can create an event_reactor. */
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_create(&er));

    /* initialize the event_handlers. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh1, &dummy_callback, &t1));
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh2, &dummy_callback, &t2));
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh3, &dummy_callback, &t3));

    /* add these handlers to the reactor. */
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_add(er, &eh1));
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_add(er, &eh2));
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_add(er, &eh3));

    /* clear the test contexts. */
    memset(&t1, 0, sizeof(t1));
    memset(&t2, 0, sizeof(t2));
    memset(&t3, 0, sizeof(t3));

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* initialize a dummy event. */
    TEST_ASSERT(STATUS_SUCCESS == event_init(&ev, 17, &c));

    /* precondition: test_context counts are zero. */
    TEST_ASSERT(0 == t1.count);
    TEST_ASSERT(0 == t2.count);
    TEST_ASSERT(0 == t3.count);

    /* broadcast this event. */
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_broadcast(er, &ev));

    /* postcondition: test_context counts are 1. */
    TEST_EXPECT(1 == t1.count);
    TEST_EXPECT(1 == t2.count);
    TEST_EXPECT(1 == t3.count);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_release(er));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh1));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh2));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh3));
    TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev));
}
