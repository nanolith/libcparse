/**
 * \file test/line_wrap_filter/test_line_wrap_filter.cpp
 *
 * \brief Tests for the \ref line_wrap_filter type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/line_wrap_filter.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_line_wrap_filter;

TEST_SUITE(line_wrap_filter);

struct test_context
{
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
    else
    {
        return -1;
    }

    return STATUS_SUCCESS;
}

/**
 * Test that we can create and release a line wrap filter.
 */
TEST(create_release)
{
    line_wrap_filter* filter;

    /* we can create a line_wrap_filter. */
    TEST_ASSERT(STATUS_SUCCESS == line_wrap_filter_create(&filter));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == line_wrap_filter_release(filter));
}

/**
 * Test that we can subscribe to a line_wrap_filter.
 */
TEST(subscribe)
{
    line_wrap_filter* filter;
    event_handler eh;
    test_context t1;

    /* we can create a line_wrap_filter. */
    TEST_ASSERT(STATUS_SUCCESS == line_wrap_filter_create(&filter));

    /* initialize our event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t1));

    /* get the abstract parser. */
    auto ap = line_wrap_filter_upcast(filter);

    /* subscribe to the filter. */
    TEST_ASSERT(
        STATUS_SUCCESS == abstract_parser_line_wrap_filter_subscribe(ap, &eh));

    /* precondition: eof is false. */
    TEST_ASSERT(!t1.eof);

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == line_wrap_filter_release(filter));
}
