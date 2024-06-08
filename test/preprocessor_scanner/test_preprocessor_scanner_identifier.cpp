/**
 * \file test/preprocessor_scanner/test_preprocessor_scanner_identifier.cpp
 *
 * \brief Identifier tests for the \ref preprocessor_scanner.
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
 * Test that we can scan an identifier.
 */
TEST(identifier1)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "abc123_";

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

    /* this first value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("abc123_" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan multiple identifiers separated by whitespace.
 */
TEST(identifier2)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "abc123_ _12 x";

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

    /* postcondition: there are three values in vals. */
    TEST_ASSERT(3 == t1.vals.size());

    /* get the first value. */
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("abc123_" == f->second);

    /* get the second value. */
    ++f;
    TEST_ASSERT(f != t1.vals.end());

    /* this second value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("_12" == f->second);

    /* get the third value. */
    ++f;
    TEST_ASSERT(f != t1.vals.end());

    /* this third value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("x" == f->second);

    /* there are no more values. */
    TEST_EXPECT(++f == t1.vals.end());

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan multiple identifiers separated by newlines.
 */
TEST(identifier3)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "abc123_\n_12\nx";

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

    /* postcondition: there are three values in vals. */
    TEST_ASSERT(3 == t1.vals.size());

    /* get the first value. */
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("abc123_" == f->second);

    /* get the second value. */
    ++f;
    TEST_ASSERT(f != t1.vals.end());

    /* this second value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("_12" == f->second);

    /* get the third value. */
    ++f;
    TEST_ASSERT(f != t1.vals.end());

    /* this third value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("x" == f->second);

    /* there are no more values. */
    TEST_EXPECT(++f == t1.vals.end());

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}


