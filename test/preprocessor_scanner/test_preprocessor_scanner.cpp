/**
 * \file test/preprocessor_scanner/test_preprocessor_scanner.cpp
 *
 * \brief Tests for the \ref preprocessor_scanner type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event_handler.h>
#include <libcparse/event_type.h>
#include <libcparse/preprocessor_scanner.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_preprocessor_scanner;

TEST_SUITE(preprocessor_scanner);

namespace
{
    struct test_context
    {
        bool eof;

        test_context()
            : eof(false)
        {
        }
    };
}

static int dummy_callback(void* context, const CPARSE_SYM(event)* ev)
{
    test_context* ctx = (test_context*)context;

    if (CPARSE_EVENT_TYPE_EOF == event_get_type(ev))
    {
        ctx->eof = true;
    }
    else
    {
        return -1;
    }

    return STATUS_SUCCESS;
}

/**
 * Test that we can create and release a preprocessor scanner.
 */
TEST(create_release)
{
    preprocessor_scanner* scanner;

    /* we can create the scanner. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_create(&scanner));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
}

/**
 * Test that we can subscribe to a preprocessor scanner.
 */
TEST(subscribe)
{
    preprocessor_scanner* scanner;
    event_handler eh;
    test_context t1;

    /* Create the scanner instance. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_create(&scanner));

    /* create an event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t1));

    /* get the abstract parser. */
    auto ap = preprocessor_scanner_upcast(scanner);

    /* subscribe to the scanner. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_preprocessor_scanner_subscribe(ap, &eh));

    /* precondition: eof is false. */
    TEST_ASSERT(!t1.eof);

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}
