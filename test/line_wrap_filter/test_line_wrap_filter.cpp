/**
 * \file test/line_wrap_filter/test_line_wrap_filter.cpp
 *
 * \brief Tests for the \ref line_wrap_filter type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <cstring>
#include <libcparse/event/raw_character.h>
#include <libcparse/input_stream.h>
#include <libcparse/line_wrap_filter.h>
#include <libcparse/status_codes.h>
#include <list>
#include <minunit/minunit.h>
#include <string>

using namespace std;

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_raw_character;
CPARSE_IMPORT_input_stream;
CPARSE_IMPORT_line_wrap_filter;

TEST_SUITE(line_wrap_filter);

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
        memcpy(&ctx->pos, event_get_cursor(ev), sizeof(ctx->pos));
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

/**
 * Test that a string with no line wraps is passed correctly.
 */
TEST(no_line_wraps)
{
    line_wrap_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "abc\n123";
    const char* OUTPUT_STRING = "abc\n123\n";

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

    /* create an input stream. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == input_stream_create_from_string(&stream, INPUT_STRING));

    /* add the input stream to the parser. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_push_input_stream(ap, "stdin", stream));

    /* precondition: eof is false. */
    TEST_ASSERT(!t1.eof);

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: vals matches our output string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == OUTPUT_STRING);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == line_wrap_filter_release(filter));
}

/**
 * Test that a string with line wraps is properly handled.
 */
TEST(line_wrap)
{
    line_wrap_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "abc\\\n123";
    const char* OUTPUT_STRING = "abc 123\n";

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

    /* create an input stream. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == input_stream_create_from_string(&stream, INPUT_STRING));

    /* add the input stream to the parser. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_push_input_stream(ap, "stdin", stream));

    /* precondition: eof is false. */
    TEST_ASSERT(!t1.eof);

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: vals matches our output string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == OUTPUT_STRING);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == line_wrap_filter_release(filter));
}

/**
 * Test that escape sequences are passed unscathed.
 */
TEST(escape_sequence)
{
    line_wrap_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "abc\\n123";
    const char* OUTPUT_STRING = "abc\\n123\n";

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

    /* create an input stream. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == input_stream_create_from_string(&stream, INPUT_STRING));

    /* add the input stream to the parser. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_push_input_stream(ap, "stdin", stream));

    /* precondition: eof is false. */
    TEST_ASSERT(!t1.eof);

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: vals matches our output string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == OUTPUT_STRING);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == line_wrap_filter_release(filter));
}
