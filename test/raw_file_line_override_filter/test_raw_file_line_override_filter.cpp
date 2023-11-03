/**
 * \file
 * test/raw_file_line_override_filter/test_raw_file_line_override_filter.cpp
 *
 * \brief Tests for the \ref raw_file_line_override_filter type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/event.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/event_handler.h>
#include <libcparse/raw_file_line_override_filter.h>
#include <libcparse/status_codes.h>
#include <list>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_raw_character;
CPARSE_IMPORT_raw_file_line_override_filter;

TEST_SUITE(raw_file_line_override_filter);

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
    int retval;
    test_context* ctx = (test_context*)context;

    if (CPARSE_EVENT_TYPE_EOF == event_get_type(ev))
    {
        ctx->eof = true;
    }
    else if (CPARSE_EVENT_TYPE_RAW_CHARACTER == event_get_type(ev))
    {
        event_raw_character* rev;
        retval = event_downcast_to_event_raw_character(&rev, (event*)ev);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        ctx->vals.push_back(event_raw_character_get(rev));
    }
    else
    {
        return -1;
    }

    return STATUS_SUCCESS;
}

/**
 * Test that we can create and release a raw file line override filter.
 */
TEST(create_release)
{
    raw_file_line_override_filter* filter;

    /* we can create the raw_file_line_override_filter. */
    TEST_ASSERT(
        STATUS_SUCCESS == raw_file_line_override_filter_create(&filter));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == raw_file_line_override_filter_release(filter));
}

/**
 * Test that we can subscribe to a raw_file_line_override_filter.
 */
TEST(subscribe)
{
    raw_file_line_override_filter* filter;
    event_handler eh;
    test_context t1;

    /* create the filter instance. */
    TEST_ASSERT(
        STATUS_SUCCESS == raw_file_line_override_filter_create(&filter));

    /* create our event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t1));

    /* get the abstract parser. */
    auto ap = raw_file_line_override_filter_upcast(filter);

    /* subscribe to the filter. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_raw_file_line_override_filter_subscribe(
                    ap, &eh));

    /* precondition: eof is false. */
    TEST_ASSERT(!t1.eof);

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == raw_file_line_override_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}
