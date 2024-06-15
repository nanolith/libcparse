/**
 * \file test/preprocessor_scanner/test_preprocessor_scanner_float.cpp
 *
 * \brief Float tests for the \ref preprocessor_scanner.
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

TEST_SUITE(preprocessor_scanner_float);

#define FLOAT_TEST_EXPECT_SUCCESS(name, constant) \
    TEST(name) \
    { \
        preprocessor_scanner* scanner; \
        input_stream* stream; \
        event_handler eh; \
        test_context t1; \
        const char* INPUT_STRING = constant; \
        TEST_ASSERT( \
            STATUS_SUCCESS == preprocessor_scanner_create(&scanner)); \
        TEST_ASSERT( \
            STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t1)); \
        auto ap = preprocessor_scanner_upcast(scanner); \
        TEST_ASSERT( \
            STATUS_SUCCESS \
                == abstract_parser_preprocessor_scanner_subscribe(ap, &eh)); \
        TEST_ASSERT( \
            STATUS_SUCCESS \
                == input_stream_create_from_string(&stream, INPUT_STRING)); \
        TEST_ASSERT( \
            STATUS_SUCCESS \
                == abstract_parser_push_input_stream(ap, "stdin", stream)); \
        TEST_ASSERT(!t1.eof); \
        TEST_ASSERT(t1.vals.empty()); \
        TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap)); \
        TEST_EXPECT(t1.eof); \
        TEST_ASSERT(1 == t1.vals.size()); \
        auto f = t1.vals.begin(); \
        TEST_ASSERT(f != t1.vals.end()); \
        TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_FLOAT == f->first); \
        TEST_EXPECT(INPUT_STRING == f->second); \
        TEST_ASSERT( \
            STATUS_SUCCESS == preprocessor_scanner_release(scanner)); \
        TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh)); \
    } \
    REQUIRE_SEMICOLON_HERE

#define FLOAT_TEST_EXPECT_FAILURE(name, constant, error) \
    TEST(name) \
    { \
        preprocessor_scanner* scanner; \
        input_stream* stream; \
        event_handler eh; \
        test_context t1; \
        const char* INPUT_STRING = constant; \
        TEST_ASSERT( \
            STATUS_SUCCESS == preprocessor_scanner_create(&scanner)); \
        TEST_ASSERT( \
            STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t1)); \
        auto ap = preprocessor_scanner_upcast(scanner); \
        TEST_ASSERT( \
            STATUS_SUCCESS \
                == abstract_parser_preprocessor_scanner_subscribe(ap, &eh)); \
        TEST_ASSERT( \
            STATUS_SUCCESS \
                == input_stream_create_from_string(&stream, INPUT_STRING)); \
        TEST_ASSERT( \
            STATUS_SUCCESS \
                == abstract_parser_push_input_stream(ap, "stdin", stream)); \
        TEST_ASSERT(!t1.eof); \
        TEST_ASSERT(t1.vals.empty()); \
        TEST_ASSERT(error == abstract_parser_run(ap)); \
        TEST_ASSERT( \
            STATUS_SUCCESS == preprocessor_scanner_release(scanner)); \
        TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh)); \
    } \
    REQUIRE_SEMICOLON_HERE

/* Valid float tokens. */
FLOAT_TEST_EXPECT_SUCCESS(float_zero_dot_zero,          "0.0");
FLOAT_TEST_EXPECT_SUCCESS(float_123_dot_456,            "123.456");
FLOAT_TEST_EXPECT_SUCCESS(float_zero_dot,               "0.");
FLOAT_TEST_EXPECT_SUCCESS(float_123_dot,                "123.");
FLOAT_TEST_EXPECT_SUCCESS(float_dot_zero,               ".0");
FLOAT_TEST_EXPECT_SUCCESS(float_dot_456,                ".456");
FLOAT_TEST_EXPECT_SUCCESS(float_1_dot_4e7,              "1.4e7");
FLOAT_TEST_EXPECT_SUCCESS(float_1_dot_4e_plus_7,        "1.4e+7");
FLOAT_TEST_EXPECT_SUCCESS(float_1_dot_4e_minus_7,       "1.4e-7");
FLOAT_TEST_EXPECT_SUCCESS(float_1_dot_4E7,              "1.4E7");
FLOAT_TEST_EXPECT_SUCCESS(float_1_dot_4E_plus_7,        "1.4E+7");
FLOAT_TEST_EXPECT_SUCCESS(float_1_dot_4E_minus_7,       "1.4E-7");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_zero_dot_p0,        "0x0.p0");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_one_dot_p0,         "0x1.p0");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_one_dot_one_p0,     "0x1.1p0");

#define expect_digit ERROR_LIBCPARSE_PP_SCANNER_EXPECTING_DIGIT

/* Invalid float tokens. */
FLOAT_TEST_EXPECT_FAILURE(no_exp_digit,         "1.4e",     expect_digit);
FLOAT_TEST_EXPECT_FAILURE(no_pos_exp_digit,     "1.4e+",    expect_digit);
FLOAT_TEST_EXPECT_FAILURE(no_neg_exp_digit,     "1.4e-",    expect_digit);
FLOAT_TEST_EXPECT_FAILURE(no_EXP_digit,         "1.4E",     expect_digit);
FLOAT_TEST_EXPECT_FAILURE(no_pos_EXP_digit,     "1.4E+",    expect_digit);
FLOAT_TEST_EXPECT_FAILURE(no_neg_EXP_digit,     "1.4E-",    expect_digit);
