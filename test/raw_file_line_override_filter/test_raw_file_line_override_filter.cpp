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
#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/event_handler.h>
#include <libcparse/input_stream.h>
#include <libcparse/raw_file_line_override_filter.h>
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
CPARSE_IMPORT_raw_file_line_override_filter;

TEST_SUITE(raw_file_line_override_filter);

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

/**
 * Test that we receive all input from an input stream.
 */
TEST(input_stream_1)
{
    raw_file_line_override_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* TEST_STRING = "abc 123";

    /* create the raw_file_line_override_filter. */
    TEST_ASSERT(
        STATUS_SUCCESS == raw_file_line_override_filter_create(&filter));

    /* create our event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t1));

    /* get the abstract parser. */
    auto ap = raw_file_line_override_filter_upcast(filter);

    /* subscribe to the rflo. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_raw_file_line_override_filter_subscribe(
                    ap, &eh));

    /* create our input stream. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == input_stream_create_from_string(&stream, TEST_STRING));

    /* add our input stream to the parser. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_push_input_stream(ap, "stdin", stream));

    /* precondition: eof is false. */
    TEST_ASSERT(!t1.eof);

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the scanner. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: vals is not empty. */
    TEST_EXPECT(!t1.vals.empty());

    /* postcondition: vals matches our string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == TEST_STRING);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == raw_file_line_override_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can override the line.
 */
TEST(line_override)
{
    raw_file_line_override_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* TEST_STRING = "abc 123";
    const unsigned int TEST_LINE = 10;

    /* create the raw_file_line_override_filter. */
    TEST_ASSERT(
        STATUS_SUCCESS == raw_file_line_override_filter_create(&filter));

    /* create our event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t1));

    /* get the abstract parser. */
    auto ap = raw_file_line_override_filter_upcast(filter);

    /* subscribe to the rflo. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_raw_file_line_override_filter_subscribe(
                    ap, &eh));

    /* create our input stream. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == input_stream_create_from_string(&stream, TEST_STRING));

    /* add our input stream to the parser. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_push_input_stream(ap, "stdin", stream));

    /* override the line for the parser. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_file_line_override(ap, TEST_LINE, NULL));

    /* precondition: eof is false. */
    TEST_ASSERT(!t1.eof);

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the scanner. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: vals is not empty. */
    TEST_EXPECT(!t1.vals.empty());

    /* postcondition: vals matches our string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == TEST_STRING);

    /* postcondition: the line of the position has been updated. */
    TEST_EXPECT(TEST_LINE == t1.pos.begin_line);
    TEST_EXPECT(!strcmp(t1.pos.file, "stdin"));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == raw_file_line_override_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can override the file and line.
 */
TEST(file_line_override)
{
    raw_file_line_override_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* TEST_STRING = "abc 123";
    const unsigned int TEST_LINE = 10;
    const char* TEST_FILE = "foo.txt";

    /* create the raw_file_line_override_filter. */
    TEST_ASSERT(
        STATUS_SUCCESS == raw_file_line_override_filter_create(&filter));

    /* create our event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t1));

    /* get the abstract parser. */
    auto ap = raw_file_line_override_filter_upcast(filter);

    /* subscribe to the rflo. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_raw_file_line_override_filter_subscribe(
                    ap, &eh));

    /* create our input stream. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == input_stream_create_from_string(&stream, TEST_STRING));

    /* add our input stream to the parser. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_push_input_stream(ap, "stdin", stream));

    /* override the line for the parser. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_file_line_override(ap, TEST_LINE, TEST_FILE));

    /* precondition: eof is false. */
    TEST_ASSERT(!t1.eof);

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the scanner. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: vals is not empty. */
    TEST_EXPECT(!t1.vals.empty());

    /* postcondition: vals matches our string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == TEST_STRING);

    /* postcondition: the file and line of the position has been updated. */
    TEST_EXPECT(TEST_LINE == t1.pos.begin_line);
    TEST_EXPECT(!strcmp(t1.pos.file, TEST_FILE));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == raw_file_line_override_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}
