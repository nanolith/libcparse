/**
 * \file test/comment_filter/test_comment_filter.cpp
 *
 * \brief Tests for the \ref comment_filter type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <cstring>
#include <libcparse/abstract_parser.h>
#include <libcparse/comment_filter.h>
#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/event_handler.h>
#include <libcparse/status_codes.h>
#include <list>
#include <minunit/minunit.h>
#include <string>

using namespace std;

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_comment_filter;
CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_raw_character;
CPARSE_IMPORT_input_stream;

TEST_SUITE(comment_filter);

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
 * Test that we can create and release a comment filter.
 */
TEST(create_release)
{
    comment_filter* filter;

    /* we can create the comment_filter. */
    TEST_ASSERT(
        STATUS_SUCCESS == comment_filter_create(&filter));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == comment_filter_release(filter));
}

/**
 * Test that we can subscribe to a comment_filter.
 */
TEST(subscribe)
{
    comment_filter* filter;
    event_handler eh;
    test_context t1;

    /* create the filter instance. */
    TEST_ASSERT(
        STATUS_SUCCESS == comment_filter_create(&filter));

    /* create our event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t1));

    /* get the abstract parser. */
    auto ap = comment_filter_upcast(filter);

    /* subscribe to the filter. */
    TEST_ASSERT(
        STATUS_SUCCESS == abstract_parser_comment_filter_subscribe(ap, &eh));

    /* precondition: eof is false. */
    TEST_ASSERT(!t1.eof);

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == comment_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that a string with no comments is passed verbatim.
 */
TEST(no_comments)
{
    comment_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STREAM = "abc 123";
    const char* OUTPUT_STREAM = "abc 123\n";

    /* create the filter instance. */
    TEST_ASSERT(
        STATUS_SUCCESS == comment_filter_create(&filter));

    /* create our event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t1));

    /* get the abstract parser. */
    auto ap = comment_filter_upcast(filter);

    /* subscribe to the filter. */
    TEST_ASSERT(
        STATUS_SUCCESS == abstract_parser_comment_filter_subscribe(ap, &eh));

    /* create an input stream. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == input_stream_create_from_string(&stream, INPUT_STREAM));

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

    /* postcondition: vals matches our string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == OUTPUT_STREAM);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == comment_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that a block comment is replaced with a space.
 */
TEST(block_comment)
{
    comment_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* TEST_STRING = "abc/* nothing */123";
    const char* TEST_STRING_XFORM = "abc 123\n";

    /* create the filter instance. */
    TEST_ASSERT(
        STATUS_SUCCESS == comment_filter_create(&filter));

    /* create our event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t1));

    /* get the abstract parser. */
    auto ap = comment_filter_upcast(filter);

    /* subscribe to the filter. */
    TEST_ASSERT(
        STATUS_SUCCESS == abstract_parser_comment_filter_subscribe(ap, &eh));

    /* create an input stream. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == input_stream_create_from_string(&stream, TEST_STRING));

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

    /* postcondition: vals matches our string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == TEST_STRING_XFORM);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == comment_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that a line comment is skipped.
 */
TEST(line_comment)
{
    comment_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* TEST_STRING = "abc// nothing\n123";
    const char* TEST_STRING_XFORM = "abc\n123\n";

    /* create the filter instance. */
    TEST_ASSERT(
        STATUS_SUCCESS == comment_filter_create(&filter));

    /* create our event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t1));

    /* get the abstract parser. */
    auto ap = comment_filter_upcast(filter);

    /* subscribe to the filter. */
    TEST_ASSERT(
        STATUS_SUCCESS == abstract_parser_comment_filter_subscribe(ap, &eh));

    /* create an input stream. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == input_stream_create_from_string(&stream, TEST_STRING));

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

    /* postcondition: vals matches our string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == TEST_STRING_XFORM);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == comment_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}
