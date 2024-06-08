/**
 * \file test/preprocessor_scanner/test_preprocessor_scanner_integer.cpp
 *
 * \brief Integer tests for the \ref preprocessor_scanner.
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

/**
 * Test that we can scan a decimal integer.
 */
TEST(decimal_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal integer.
 */
TEST(octal_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07654321";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07654321" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex integer.
 */
TEST(hex_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0x01abc";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0x01abc" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero integer.
 */
TEST(zero_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a lower-case unsigned integer.
 */
TEST(lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234u";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234u" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an upper-case unsigned integer.
 */
TEST(upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234U";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234U" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a lower-case long integer.
 */
TEST(lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234l";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234l" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan ar upper-case long integer.
 */
TEST(upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234L";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234L" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a lower-case unsigned lower-case long integer.
 */
TEST(lower_case_unsigned_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234ul";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234ul" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a lower-case unsigned upper-case long integer.
 */
TEST(lower_case_unsigned_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234uL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234uL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an upper-case unsigned lower-case long integer.
 */
TEST(upper_case_unsigned_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234Ul";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234Ul" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an upper-case unsigned upper-case long integer.
 */
TEST(upper_case_unsigned_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234UL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234UL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a lower-case unsigned lower-case long lower-case long
 * integer.
 */
TEST(lower_case_unsigned_lower_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234ull";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234ull" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a lower-case unsigned lower-case long upper-case long
 * integer.
 */
TEST(lower_case_unsigned_lower_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234ulL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234ulL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a lower-case unsigned upper-case long lower-case long
 * integer.
 */
TEST(lower_case_unsigned_upper_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234uLl";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234uLl" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a lower-case unsigned upper-case long upper-case long
 * integer.
 */
TEST(lower_case_unsigned_upper_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234uLL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234uLL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an upper-case unsigned lower-case long lower-case long
 * integer.
 */
TEST(upper_case_unsigned_lower_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234Ull";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234Ull" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an upper-case unsigned lower-case long upper-case long
 * integer.
 */
TEST(upper_case_unsigned_lower_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234UlL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234UlL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an upper-case unsigned upper-case long lower-case long
 * integer.
 */
TEST(upper_case_unsigned_upper_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234ULl";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234ULl" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an upper-case unsigned upper-case long upper-case long
 * integer.
 */
TEST(upper_case_unsigned_upper_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234ULL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234ULL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a lower-case long lower-case unsigned integer.
 */
TEST(lower_case_long_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234lu";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234lu" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a lower-case long upper-case unsigned integer.
 */
TEST(lower_case_long_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234lU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234lU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an upper-case long lower-case unsigned integer.
 */
TEST(upper_case_long_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234Lu";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234Lu" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an upper-case long upper-case unsigned integer.
 */
TEST(upper_case_long_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234LU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234LU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a lower-case long lower-case long integer.
 */
TEST(lower_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234ll";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234ll" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a lower-case long upper-case long integer.
 */
TEST(lower_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234lL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234lL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a upper-case long lower-case long integer.
 */
TEST(upper_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234Ll";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234Ll" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a upper-case long upper-case long integer.
 */
TEST(upper_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234LL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234LL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a lower-case long lower-case long lower-case unsigned
 * integer.
 */
TEST(lower_case_long_lower_case_long_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234llu";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234llu" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a lower-case long lower-case long upper-case unsigned
 * integer.
 */
TEST(lower_case_long_lower_case_long_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234llU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234llU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a lower-case long upper-case long lower-case unsigned
 * integer.
 */
TEST(lower_case_long_upper_case_long_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234lLu";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234lLu" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a lower-case long upper-case long upper-case unsigned
 * integer.
 */
TEST(lower_case_long_upper_case_long_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234lLU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234lLU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a upper-case long lower-case long lower-case unsigned
 * integer.
 */
TEST(upper_case_long_lower_case_long_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234Llu";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234Llu" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a upper-case long lower-case long upper-case unsigned
 * integer.
 */
TEST(upper_case_long_lower_case_long_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234LlU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234LlU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a upper-case long upper-case long lower-case unsigned
 * integer.
 */
TEST(upper_case_long_upper_case_long_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234LLu";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234LLu" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a upper-case long upper-case long upper-case unsigned
 * integer.
 */
TEST(upper_case_long_upper_case_long_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "1234LLU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("1234LLU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero lower-case unsigned integer.
 */
TEST(zero_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0u";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0u" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero upper-case unsigned integer.
 */
TEST(zero_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0U";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0U" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero lower-case long integer.
 */
TEST(zero_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0l";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0l" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero upper-case long integer.
 */
TEST(zero_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0L";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0L" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero lower-case unsigned lower-case long integer.
 */
TEST(zero_lower_case_unsigned_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0ul";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0ul" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero lower-case unsigned upper-case long integer.
 */
TEST(zero_lower_case_unsigned_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0uL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0uL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero upper-case unsigned lower-case long integer.
 */
TEST(zero_upper_case_unsigned_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0Ul";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0Ul" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero upper-case unsigned upper-case long integer.
 */
TEST(zero_upper_case_unsigned_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0UL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0UL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero lower-case unsigned lower-case long lower-case
 * long integer.
 */
TEST(zero_lower_case_unsigned_lower_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0ull";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0ull" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero lower-case unsigned lower-case long upper-case
 * long integer.
 */
TEST(zero_lower_case_unsigned_lower_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0ulL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0ulL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero lower-case unsigned upper-case long lower-case
 * long integer.
 */
TEST(zero_lower_case_unsigned_upper_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0uLl";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0uLl" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero lower-case unsigned upper-case long upper-case
 * long integer.
 */
TEST(zero_lower_case_unsigned_upper_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0uLL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0uLL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero upper-case unsigned lower-case long lower-case
 * long integer.
 */
TEST(zero_upper_case_unsigned_lower_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0Ull";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0Ull" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero upper-case unsigned lower-case long upper-case
 * long integer.
 */
TEST(zero_upper_case_unsigned_lower_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0UlL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0UlL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero upper-case unsigned upper-case long lower-case
 * long integer.
 */
TEST(zero_upper_case_unsigned_upper_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0ULl";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0ULl" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero upper-case unsigned upper-case long upper-case
 * long integer.
 */
TEST(zero_upper_case_unsigned_upper_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0ULL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0ULL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero lower-case long lower-case long integer.
 */
TEST(zero_lower_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0ll";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0ll" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero lower-case long upper-case long integer.
 */
TEST(zero_lower_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0lL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0lL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero upper-case long lower-case long integer.
 */
TEST(zero_upper_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0Ll";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0Ll" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a zero upper-case long upper-case long integer.
 */
TEST(zero_upper_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0LL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0LL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex lower-case unsigned integer.
 */
TEST(hex_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xau";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xau" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex upper-case unsigned integer.
 */
TEST(hex_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex lower-case long integer.
 */
TEST(hex_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xal";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xal" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex upper-case long integer.
 */
TEST(hex_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex lower-case unsigned lower-case long integer.
 */
TEST(hex_lower_case_unsigned_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaul";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaul" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex lower-case unsigned upper-case long integer.
 */
TEST(hex_lower_case_unsigned_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xauL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xauL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex upper-case unsigned lower-case long integer.
 */
TEST(hex_upper_case_unsigned_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaUl";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaUl" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex upper-case unsigned upper-case long integer.
 */
TEST(hex_upper_case_unsigned_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaUL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaUL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex lower-case unsigned lower-case long lower-case
 * long integer.
 */
TEST(hex_lower_case_unsigned_lower_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaull";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaull" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex lower-case unsigned lower-case long upper-case
 * long integer.
 */
TEST(hex_lower_case_unsigned_lower_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaulL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaulL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex lower-case unsigned upper-case long lower-case
 * long integer.
 */
TEST(hex_lower_case_unsigned_upper_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xauLl";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xauLl" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex lower-case unsigned upper-case long upper-case
 * long integer.
 */
TEST(hex_lower_case_unsigned_upper_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xauLL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xauLL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex upper-case unsigned lower-case long lower-case
 * long integer.
 */
TEST(hex_upper_case_unsigned_lower_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaUll";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaUll" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex upper-case unsigned lower-case long upper-case
 * long integer.
 */
TEST(hex_upper_case_unsigned_lower_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaUlL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaUlL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex upper-case unsigned upper-case long lower-case
 * long integer.
 */
TEST(hex_upper_case_unsigned_upper_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaULl";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaULl" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex upper-case unsigned upper-case long upper-case
 * long integer.
 */
TEST(hex_upper_case_unsigned_upper_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaULL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaULL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex lower-case long lower-case long integer.
 */
TEST(hex_lower_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xall";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xall" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex lower-case long upper-case long integer.
 */
TEST(hex_lower_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xalL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xalL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex upper-case long lower-case long integer.
 */
TEST(hex_upper_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaLl";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaLl" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex upper-case long upper-case long integer.
 */
TEST(hex_upper_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaLL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaLL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex lower-case long lower-case unsigned integer.
 */
TEST(hex_lower_case_long_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xalu";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xalu" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex lower-case long upper-case unsigned integer.
 */
TEST(hex_lower_case_long_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xalU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xalU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex upper-case long lower-case unsigned integer.
 */
TEST(hex_upper_case_long_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaLu";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaLu" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex upper-case long upper-case unsigned integer.
 */
TEST(hex_upper_case_long_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaLU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaLU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex lower-case long lower-case long lower-case
 * unsigned integer.
 */
TEST(hex_lower_case_long_lower_case_long_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xallu";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xallu" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex lower-case long lower-case long upper-case
 * unsigned integer.
 */
TEST(hex_lower_case_long_lower_case_long_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xallU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xallU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex lower-case long upper-case long lower-case
 * unsigned integer.
 */
TEST(hex_lower_case_long_upper_case_long_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xalLu";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xalLu" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex lower-case long upper-case long upper-case
 * unsigned integer.
 */
TEST(hex_lower_case_long_upper_case_long_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xalLU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xalLU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex upper-case long lower-case long lower-case
 * unsigned integer.
 */
TEST(hex_upper_case_long_lower_case_long_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaLlu";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaLlu" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex upper-case long lower-case long upper-case
 * unsigned integer.
 */
TEST(hex_upper_case_long_lower_case_long_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaLlU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaLlU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex upper-case long upper-case long lower-case
 * unsigned integer.
 */
TEST(hex_upper_case_long_upper_case_long_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaLLu";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaLLu" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a hex upper-case long upper-case long upper-case
 * unsigned integer.
 */
TEST(hex_upper_case_long_upper_case_long_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "0xaLLU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("0xaLLU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal lower-case unsigned integer.
 */
TEST(octal_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07u";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07u" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal upper-case unsigned integer.
 */
TEST(octal_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07U";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07U" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal lower-case long integer.
 */
TEST(octal_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07l";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07l" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal upper-case long integer.
 */
TEST(octal_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07L";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07L" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal lower-case unsigned lower-case long integer.
 */
TEST(octal_lower_case_unsigned_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07ul";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07ul" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal lower-case unsigned upper-case long integer.
 */
TEST(octal_lower_case_unsigned_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07uL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07uL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal upper-case unsigned lower-case long integer.
 */
TEST(octal_upper_case_unsigned_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07Ul";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07Ul" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal upper-case unsigned upper-case long integer.
 */
TEST(octal_upper_case_unsigned_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07UL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07UL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal lower-case unsigned lower-case long lower-case
 * long integer.
 */
TEST(octal_lower_case_unsigned_lower_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07ull";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07ull" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal lower-case unsigned lower-case long upper-case
 * long integer.
 */
TEST(octal_lower_case_unsigned_lower_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07ulL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07ulL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal lower-case unsigned upper-case long lower-case
 * long integer.
 */
TEST(octal_lower_case_unsigned_upper_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07uLl";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07uLl" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal lower-case unsigned upper-case long upper-case
 * long integer.
 */
TEST(octal_lower_case_unsigned_upper_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07uLL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07uLL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal upper-case unsigned lower-case long lower-case
 * long integer.
 */
TEST(octal_upper_case_unsigned_lower_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07Ull";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07Ull" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal upper-case unsigned lower-case long upper-case
 * long integer.
 */
TEST(octal_upper_case_unsigned_lower_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07UlL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07UlL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal upper-case unsigned upper-case long lower-case
 * long integer.
 */
TEST(octal_upper_case_unsigned_upper_case_long_lower_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07ULl";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07ULl" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal upper-case unsigned upper-case long upper-case
 * long integer.
 */
TEST(octal_upper_case_unsigned_upper_case_long_upper_case_long_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07ULL";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07ULL" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal lower-case long lower-case long lower-case
 * unsigned integer.
 */
TEST(octal_lower_case_long_lower_case_long_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07llu";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07llu" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal lower-case long lower-case long upper-case
 * unsigned integer.
 */
TEST(octal_lower_case_long_lower_case_long_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07llU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07llU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal lower-case long upper-case long lower-case
 * unsigned integer.
 */
TEST(octal_lower_case_long_upper_case_long_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07lLu";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07lLu" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal lower-case long upper-case long upper-case
 * unsigned integer.
 */
TEST(octal_lower_case_long_upper_case_long_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07lLU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07lLU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal upper-case long lower-case long lower-case
 * unsigned integer.
 */
TEST(octal_upper_case_long_lower_case_long_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07Llu";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07Llu" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal upper-case long lower-case long upper-case
 * unsigned integer.
 */
TEST(octal_upper_case_long_lower_case_long_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07LlU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07LlU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal upper-case long upper-case long lower-case
 * unsigned integer.
 */
TEST(octal_upper_case_long_upper_case_long_lower_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07LLu";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07LLu" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an octal upper-case long upper-case long upper-case
 * unsigned integer.
 */
TEST(octal_upper_case_long_upper_case_long_upper_case_unsigned_integer)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "07LLU";

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

    /* postcondition: there is one value in vals. */
    TEST_ASSERT(1 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a not. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first);
    TEST_EXPECT("07LLU" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}
