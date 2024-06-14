/**
 * \file test/preprocessor_scanner/test_preprocessor_scanner_char.cpp
 *
 * \brief Character tests for the \ref preprocessor_scanner.
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

TEST_SUITE(preprocessor_scanner_char_literal);

#define CHAR_TEST_EXPECT_SUCCESS(name, constant) \
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
        TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_CHARACTER == f->first); \
        TEST_EXPECT(INPUT_STRING == f->second); \
        TEST_ASSERT( \
            STATUS_SUCCESS == preprocessor_scanner_release(scanner)); \
        TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh)); \
    } \
    REQUIRE_SEMICOLON_HERE

#define CHAR_TEST_EXPECT_FAILURE(name, constant, error) \
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

/* Valid char tokens. */
CHAR_TEST_EXPECT_SUCCESS(whitespace,                        "' '");
CHAR_TEST_EXPECT_SUCCESS(simple,                            "'x'");
CHAR_TEST_EXPECT_SUCCESS(tick_esc_seq,                      R"('\'')");
CHAR_TEST_EXPECT_SUCCESS(quote_esc_seq,                     R"('\"')");
CHAR_TEST_EXPECT_SUCCESS(question_esc_seq,                  R"('\?')");
CHAR_TEST_EXPECT_SUCCESS(backslash_esc_seq,                 R"('\\')");
CHAR_TEST_EXPECT_SUCCESS(alert_esc_seq,                     R"('\a')");
CHAR_TEST_EXPECT_SUCCESS(bs_esc_seq,                        R"('\b')");
CHAR_TEST_EXPECT_SUCCESS(ff_esc_seq,                        R"('\f')");
CHAR_TEST_EXPECT_SUCCESS(nl_esc_seq,                        R"('\n')");
CHAR_TEST_EXPECT_SUCCESS(cr_esc_seq,                        R"('\r')");
CHAR_TEST_EXPECT_SUCCESS(tab_esc_seq,                       R"('\t')");
CHAR_TEST_EXPECT_SUCCESS(vtab_esc_seq,                      R"('\v')");
CHAR_TEST_EXPECT_SUCCESS(octal_1_esc_seq,                   R"('\1')");
CHAR_TEST_EXPECT_SUCCESS(octal_2_esc_seq,                   R"('\12')");
CHAR_TEST_EXPECT_SUCCESS(octal_3_esc_seq,                   R"('\123')");
CHAR_TEST_EXPECT_SUCCESS(hex_1_esc_seq,                     R"('\x1')");
CHAR_TEST_EXPECT_SUCCESS(hex_multi_esc_seq,                 R"('\xabc123')");
CHAR_TEST_EXPECT_SUCCESS(little_u_esc_seq,                  R"('\u11f3')");
CHAR_TEST_EXPECT_SUCCESS(big_U_esc_seq,                     R"('\U0123abcd')");
CHAR_TEST_EXPECT_SUCCESS(long_prefix,                       R"(L'x')");
CHAR_TEST_EXPECT_SUCCESS(u_prefix,                          R"(u'x')");
CHAR_TEST_EXPECT_SUCCESS(U_prefix,                          R"(U'x')");

#define unexpected_char ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER

/* Invalid char tokens. */
CHAR_TEST_EXPECT_FAILURE(hex_no_digit,      R"('\x')",         unexpected_char);
CHAR_TEST_EXPECT_FAILURE(little_u_0_digit,  R"('\u')",         unexpected_char);
CHAR_TEST_EXPECT_FAILURE(little_u_1_digit,  R"('\u1')",        unexpected_char);
CHAR_TEST_EXPECT_FAILURE(little_u_2_digit,  R"('\u12')",       unexpected_char);
CHAR_TEST_EXPECT_FAILURE(little_u_3_digit,  R"('\u123')",      unexpected_char);
CHAR_TEST_EXPECT_FAILURE(big_u_0_digit,     R"('\U')",         unexpected_char);
CHAR_TEST_EXPECT_FAILURE(big_u_1_digit,     R"('\U1')",        unexpected_char);
CHAR_TEST_EXPECT_FAILURE(big_u_2_digit,     R"('\U12')",       unexpected_char);
CHAR_TEST_EXPECT_FAILURE(big_u_3_digit,     R"('\U123')",      unexpected_char);
CHAR_TEST_EXPECT_FAILURE(big_u_4_digit,     R"('\U1234')",     unexpected_char);
CHAR_TEST_EXPECT_FAILURE(big_u_5_digit,     R"('\U12345')",    unexpected_char);
CHAR_TEST_EXPECT_FAILURE(big_u_6_digit,     R"('\U123456')",   unexpected_char);
CHAR_TEST_EXPECT_FAILURE(big_u_7_digit,     R"('\U1234567')",  unexpected_char);
