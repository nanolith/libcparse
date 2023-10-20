/**
 * \file test/raw_stack_scanner/test_raw_stack_scanner.cpp
 *
 * \brief Tests for the \ref raw_stack_scanner type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/raw_stack_scanner.h>
#include <libcparse/status_codes.h>
#include <list>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_raw_stack_scanner;

TEST_SUITE(raw_stack_scanner);

struct test_context
{
    list<int> vals;
    bool eof;

    test_context()
        : eof(false)
    {
    }
};

static int dummy_callback(void* context, const CPARSE_SYM(event)* ev)
{
    test_context* ctx = (test_context*)context;

    if (CPARSE_EVENT_TYPE_EOF == event_get_type(ev))
    {
        ctx->eof = true;
    }

    return STATUS_SUCCESS;
}

/**
 * Test that we can create and release a raw stack scanner.
 */
TEST(create_release)
{
    raw_stack_scanner* scanner;

    /* we can create the raw_stack_scanner. */
    TEST_ASSERT(STATUS_SUCCESS == raw_stack_scanner_create(&scanner));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == raw_stack_scanner_release(scanner));
}

/**
 * Test that we can subscribe to a raw_stack_scanner.
 */
TEST(subscribe)
{
    raw_stack_scanner* scanner;
    event_handler eh;
    test_context t1;

    /* create the raw_stack_scanner. */
    TEST_ASSERT(STATUS_SUCCESS == raw_stack_scanner_create(&scanner));

    /* create our event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t1));

    /* get the abstract parser. */
    auto ap = raw_stack_scanner_upcast(scanner);

    /* subscribe to the raw stack scanner. */
    TEST_ASSERT(
        STATUS_SUCCESS == abstract_parser_raw_stack_scanner_subscribe(ap, &eh));

    /* precondition: eof is false. */
    TEST_ASSERT(!t1.eof);

    /* run the scanner. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == raw_stack_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}
