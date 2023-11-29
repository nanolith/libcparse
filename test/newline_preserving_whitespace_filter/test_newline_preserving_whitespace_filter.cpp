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
#include <libcparse/event/raw_character.h>
#include <libcparse/event_handler.h>
#include <libcparse/input_stream.h>
#include <libcparse/newline_preserving_whitespace_filter.h>
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
    else if (CPARSE_EVENT_TYPE_TOKEN_NEWLINE == event_get_type(ev))
    {
        ctx->vals.push_back('\n');
        memcpy(&ctx->pos, event_get_cursor(ev), sizeof(ctx->pos));
    }
    else if (CPARSE_EVENT_TYPE_TOKEN_WHITESPACE == event_get_type(ev))
    {
        ctx->vals.push_back(' ');
        memcpy(&ctx->pos, event_get_cursor(ev), sizeof(ctx->pos));
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

/**
 * Test that a string with no whitespace is passed verbatim.
 */
TEST(no_whitespace)
{
    newline_preserving_whitespace_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "abc123";
    const char* OUTPUT_STRING = "abc123\n";

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

    /* postcondition: vals matches our string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == OUTPUT_STRING);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * A string with a newline character has the newline preserved as a token.
 */
TEST(newline_preserved)
{
    newline_preserving_whitespace_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "abc\n123";
    const char* OUTPUT_STRING = "abc\n123\n";

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

    /* postcondition: vals matches our string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == OUTPUT_STRING);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * A sequence of many whitespace characters is reduced to a single whitespace
 * character token.
 */
TEST(whitespace_compressed)
{
    newline_preserving_whitespace_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "abc    \t           123";
    const char* OUTPUT_STRING = "abc 123\n";

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

    /* postcondition: vals matches our string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == OUTPUT_STRING);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * A sequence of many whitespace characters followed by a newline is compressed
 * to a single newline.
 */
TEST(whitespace_newline_compressed)
{
    newline_preserving_whitespace_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "abc    \t           \n123";
    const char* OUTPUT_STRING = "abc\n123\n";

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

    /* postcondition: vals matches our string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == OUTPUT_STRING);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Whitespace after the newline is compressed into the newline.
 */
TEST(whitespace_newline_whitespace_compressed)
{
    newline_preserving_whitespace_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "abc    \t           \n    \t \v   123";
    const char* OUTPUT_STRING = "abc\n123\n";

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

    /* postcondition: vals matches our string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == OUTPUT_STRING);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Multiple newlines are compressed into a single newline.
 */
TEST(multiple_newlines)
{
    newline_preserving_whitespace_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "abc\n\n\n\n123";
    const char* OUTPUT_STRING = "abc\n123\n";

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

    /* postcondition: vals matches our string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == OUTPUT_STRING);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Whitespace in a string is ignored.
 */
TEST(whitespace_string)
{
    newline_preserving_whitespace_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING =  "\"abc  \t   \v \f   123\"";
    const char* OUTPUT_STRING = "\"abc  \t   \v \f   123\"\n";

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

    /* postcondition: vals matches our string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == OUTPUT_STRING);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Whitespace in a string is ignored, even if there is an escaped double quote.
 */
TEST(whitespace_string_with_escaped_double_quote)
{
    newline_preserving_whitespace_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING =  "\"abc  \t \\\"  \v \f   123\"";
    const char* OUTPUT_STRING = "\"abc  \t \\\"  \v \f   123\"\n";

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

    /* postcondition: vals matches our string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == OUTPUT_STRING);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * If we enter a string state, we return an error if we get EOF before a double
 * quote terminator.
 */
TEST(string_state_eof)
{
    newline_preserving_whitespace_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING =  "\"abc";

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

    /* create an input stream. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == input_stream_create_from_string(&stream, INPUT_STRING));

    /* add the input stream to the parser. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_push_input_stream(ap, "stdin", stream));

    /* The filter fails. */
    TEST_ASSERT(STATUS_SUCCESS != abstract_parser_run(ap));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Whitespace in a character sequence is ignored.
 */
TEST(whitespace_char)
{
    newline_preserving_whitespace_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING =  "'abc  \t   \v \f   123'";
    const char* OUTPUT_STRING = "'abc  \t   \v \f   123'\n";

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

    /* postcondition: vals matches our string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == OUTPUT_STRING);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Whitespace in a character sequence is ignored, even if there is an escaped
 * single quote.
 */
TEST(whitespace_char_with_escaped_single_quote)
{
    newline_preserving_whitespace_filter* filter;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING =  "'abc  \t \\\'  \v \f   123'";
    const char* OUTPUT_STRING = "'abc  \t \\\'  \v \f   123'\n";

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

    /* postcondition: vals matches our string. */
    string out(t1.vals.begin(), t1.vals.end());
    TEST_EXPECT(out == OUTPUT_STRING);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_release(filter));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}
