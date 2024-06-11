/**
 * \file test/preprocessor_scanner/test_preprocessor_scanner_preprocessor.cpp
 *
 * \brief Preprocessor token tests for the \ref preprocessor_scanner.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/event_handler.h>
#include <libcparse/input_stream.h>
#include <libcparse/preprocessor_scanner.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

#include "test_preprocessor_scanner_helper.h"

using namespace std;
using namespace test_preprocessor_scanner_helper;

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_input_stream;
CPARSE_IMPORT_preprocessor_scanner;

TEST_SUITE(preprocessor_scanner_preprocessor);

/**
 * Test that the state is reset between newlines.
 */
TEST(newline_reset_state)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "test\ntest";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(2 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("test" == f->second);

    ++f;

    /* the second value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("test" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that #for is parsed as two tokens.
 */
TEST(hash_for_tokens)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "#for";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(2 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is an endif token. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_HASH == f->first);
    TEST_EXPECT("#" == f->second);

    ++f;

    /* the second value is a for keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FOR == f->first);
    TEST_EXPECT("for" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}
/**
 * Test that we can scan an #endif token.
 */
TEST(endif_preprocessor_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "#endif";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(2 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is an endif token. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_ID_ENDIF == f->first);
    TEST_EXPECT("#endif" == f->second);

    ++f;

    /* the second value is an end preprocessor event. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_PP_END == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan #if 0 expression tokens.
 */
TEST(pp_if_0_tokens)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "#if 0";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(3 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is an if token. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_ID_IF == f->first);
    TEST_EXPECT("#if" == f->second);

    ++f;

    /* the second value is a raw integer. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0" == f->second);

    ++f;

    /* the third value is an end preprocessor event. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_PP_END == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan #ifdef FOO expression tokens.
 */
TEST(pp_ifdef_FOO_tokens)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "#ifdef FOO";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(3 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is an if token. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_ID_IFDEF == f->first);
    TEST_EXPECT("#ifdef" == f->second);

    ++f;

    /* the second value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("FOO" == f->second);

    ++f;

    /* the third value is an end preprocessor event. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_PP_END == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan #  ifdef FOO expression tokens.
 */
TEST(pp_ifdef_FOO_tokens_with_hash_space)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "#  ifdef FOO";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(3 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is an if token. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_ID_IFDEF == f->first);
    TEST_EXPECT("#ifdef" == f->second);

    ++f;

    /* the second value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("FOO" == f->second);

    ++f;

    /* the third value is an end preprocessor event. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_PP_END == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan #ifndef FOO expression tokens.
 */
TEST(pp_ifndef_FOO_tokens)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "#ifndef FOO";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(3 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is an ifndef token. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_ID_IFNDEF == f->first);
    TEST_EXPECT("#ifndef" == f->second);

    ++f;

    /* the second value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("FOO" == f->second);

    ++f;

    /* the third value is an end preprocessor event. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_PP_END == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan #elif FOO expression tokens.
 */
TEST(pp_elif_FOO_tokens)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "#elif FOO";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(3 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is an ifndef token. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_ID_ELIF == f->first);
    TEST_EXPECT("#elif" == f->second);

    ++f;

    /* the second value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("FOO" == f->second);

    ++f;

    /* the third value is an end preprocessor event. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_PP_END == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an #else token.
 */
TEST(pp_else_FOO_tokens)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "#else";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(2 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is an else token. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_ID_ELSE == f->first);
    TEST_EXPECT("#else" == f->second);

    ++f;

    /* the second value is an end preprocessor event. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_PP_END == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan #define FOO expression tokens.
 */
TEST(pp_define_FOO_tokens)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "#define FOO";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(3 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is a define token. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_ID_DEFINE == f->first);
    TEST_EXPECT("#define" == f->second);

    ++f;

    /* the second value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("FOO" == f->second);

    ++f;

    /* the third value is an end preprocessor event. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_PP_END == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan #undef FOO expression tokens.
 */
TEST(pp_undef_FOO_tokens)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "#undef FOO";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(3 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is a define token. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_ID_UNDEF == f->first);
    TEST_EXPECT("#undef" == f->second);

    ++f;

    /* the second value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("FOO" == f->second);

    ++f;

    /* the third value is an end preprocessor event. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_PP_END == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan #line 1234 expression tokens.
 */
TEST(pp_line_1234_tokens)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "#line 1234";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(3 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is a line token. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_ID_LINE == f->first);
    TEST_EXPECT("#line" == f->second);

    ++f;

    /* the second value is a raw integer. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234" == f->second);

    ++f;

    /* the third value is an end preprocessor event. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_PP_END == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan #error x expression tokens.
 */
TEST(pp_error_x_tokens)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"(#error x)";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(3 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is an error token. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_ID_ERROR == f->first);
    TEST_EXPECT("#error" == f->second);

    ++f;

    /* the second value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("x" == f->second);

    ++f;

    /* the third value is an end preprocessor event. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_PP_END == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan #error "foo" expression tokens.
 */
TEST(pp_error_foo_string_tokens)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"(#error "foo")";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(3 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is an error token. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_ID_ERROR == f->first);
    TEST_EXPECT("#error" == f->second);

    ++f;

    /* the second value is a raw string. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT("\"foo\"" == f->second);

    ++f;

    /* the third value is an end preprocessor event. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_PP_END == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan #pragma once expression tokens.
 */
TEST(pp_pragma_once_tokens)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"(#pragma once)";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(3 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is an error token. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_ID_PRAGMA == f->first);
    TEST_EXPECT("#pragma" == f->second);

    ++f;

    /* the second value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("once" == f->second);

    ++f;

    /* the third value is an end preprocessor event. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_PP_END == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan #include "localfile.h" expression tokens.
 */
TEST(pp_include_localfile_h_string_tokens)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"(#include "localfile.h")";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(3 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is an include token. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_ID_INCLUDE == f->first);
    TEST_EXPECT("#include" == f->second);

    ++f;

    /* the second value is a raw string. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT("\"localfile.h\"" == f->second);

    ++f;

    /* the third value is an end preprocessor event. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_PP_END == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan #include <stdio.h> expression tokens.
 */
TEST(pp_include_stdio_h_system_string_tokens)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"(#include <stdio.h>)";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(3 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is an include token. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_ID_INCLUDE == f->first);
    TEST_EXPECT("#include" == f->second);

    ++f;

    /* the second value is a raw system string. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_SYSTEM_STRING == f->first);
    TEST_EXPECT("<stdio.h>" == f->second);

    ++f;

    /* the third value is an end preprocessor event. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_PP_END == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string concat token.
 */
TEST(pp_string_concat_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "x ## y";

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

    /* precondition: vals is empty. */
    TEST_ASSERT(t1.vals.empty());

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* postcondition: there are two values in vals. */
    TEST_ASSERT(3 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* the first value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("x" == f->second);

    ++f;

    /* the second value is a string concat operator. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PP_STRING_CONCAT == f->first);
    TEST_EXPECT("##" == f->second);

    ++f;

    /* the third value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("y" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}
