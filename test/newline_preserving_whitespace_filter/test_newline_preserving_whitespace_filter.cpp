/**
 * \file
 * test/newline_preserving_whitespace_filter/test_newline_preserving_whitespace_filter.cpp
 *
 * \brief Tests for the \ref newline_preserving_whitespace_filter type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/event_handler.h>
#include <libcparse/newline_preserving_whitespace_filter.h>
#include <libcparse/status_codes.h>
#include <list>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_newline_preserving_whitespace_filter;

TEST_SUITE(newline_preserving_whitespace_filter);

struct test_context
{
    list<int> vals;
    bool eof;
    cursor pos;

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
 * Test that we can create and release a newline preserving whitespace filter.
 */
TEST(create_release)
{
    newline_preserving_whitespace_filter* filter;

    /* we can create the filter. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_create(&filter));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_release(filter));
}

/**
 * Test that we can subscribe to a newline preserving whitespace filter.
 */
TEST(subscribe)
{
    newline_preserving_whitespace_filter* filter;
    event_handler eh;
    test_context t1;

    /* create the filter instance. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_create(&filter));

    /* create our event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t1));

    /* get the abstract parser. */
    auto ap = newline_preserving_whitespace_filter_upcast(filter);

    /* subscribe to the filter. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_newline_preserving_whitespace_filter_subscribe(
                    ap, &eh));

    /* precondition: eof is false. */
    TEST_ASSERT(!t1.eof);

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}
