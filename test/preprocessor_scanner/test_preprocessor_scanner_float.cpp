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
FLOAT_TEST_EXPECT_SUCCESS(hex_float_1_dot_1_p_neg_5,    "0x1.1p-5");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_1_dot_1_p_pos_5,    "0x1.1p+5");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_dot_p0,             "0x.p0");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_zero_dot_P0,        "0x0.P0");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_one_dot_P0,         "0x1.P0");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_one_dot_one_P0,     "0x1.1P0");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_1_dot_1_P_neg_5,    "0x1.1P-5");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_1_dot_1_P_pos_5,    "0x1.1P+5");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_dot_P0,             "0x.P0");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_zero_p0,            "0x0p0");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_one_p0,             "0x1p0");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_one_one_p0,         "0x11p0");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_1_1_p_neg_5,        "0x11p-5");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_1_1_p_pos_5,        "0x11p+5");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_zero_P0,            "0x0P0");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_one_P0,             "0x1P0");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_one_one_P0,         "0x11P0");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_1_1_P_neg_5,        "0x11P-5");
FLOAT_TEST_EXPECT_SUCCESS(hex_float_1_1_P_pos_5,        "0x11P+5");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_zero_dot_p0,        "0X0.p0");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_one_dot_p0,         "0X1.p0");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_one_dot_one_p0,     "0X1.1p0");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_1_dot_1_p_neg_5,    "0X1.1p-5");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_1_dot_1_p_pos_5,    "0X1.1p+5");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_dot_p0,             "0X.p0");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_zero_dot_P0,        "0X0.P0");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_one_dot_P0,         "0X1.P0");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_one_dot_one_P0,     "0X1.1P0");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_1_dot_1_P_neg_5,    "0X1.1P-5");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_1_dot_1_P_pos_5,    "0X1.1P+5");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_dot_P0,             "0X.P0");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_zero_p0,            "0X0p0");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_one_p0,             "0X1p0");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_one_one_p0,         "0X11p0");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_1_1_p_neg_5,        "0X11p-5");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_1_1_p_pos_5,        "0X11p+5");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_zero_P0,            "0X0P0");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_one_P0,             "0X1P0");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_one_one_P0,         "0X11P0");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_1_1_P_neg_5,        "0X11P-5");
FLOAT_TEST_EXPECT_SUCCESS(HEX_float_1_1_P_pos_5,        "0X11P+5");
FLOAT_TEST_EXPECT_SUCCESS(float_zero_dot_zero_suffix_f, "0.0f");
FLOAT_TEST_EXPECT_SUCCESS(float_zero_dot_zero_suffix_F, "0.0F");
FLOAT_TEST_EXPECT_SUCCESS(float_zero_dot_zero_suffix_l, "0.0l");
FLOAT_TEST_EXPECT_SUCCESS(float_zero_dot_zero_suffix_L, "0.0L");
FLOAT_TEST_EXPECT_SUCCESS(float_zero_dot_suffix_f,      "0.f");
FLOAT_TEST_EXPECT_SUCCESS(float_zero_dot_suffix_F,      "0.F");
FLOAT_TEST_EXPECT_SUCCESS(float_zero_dot_suffix_l,      "0.l");
FLOAT_TEST_EXPECT_SUCCESS(float_zero_dot_suffix_L,      "0.L");
FLOAT_TEST_EXPECT_SUCCESS(float_dot_zero_suffix_f,      ".0f");
FLOAT_TEST_EXPECT_SUCCESS(float_dot_zero_suffix_F,      ".0F");
FLOAT_TEST_EXPECT_SUCCESS(float_dot_zero_suffix_l,      ".0l");

#define expect_digit ERROR_LIBCPARSE_PP_SCANNER_EXPECTING_DIGIT
#define expect_p     ERROR_LIBCPARSE_PP_SCANNER_HEX_FLOAT_EXPECTING_P
#define p_digit      ERROR_LIBCPARSE_PP_SCANNER_HEX_P_EXPECTING_DIGIT

/* Invalid float tokens. */
FLOAT_TEST_EXPECT_FAILURE(no_exp_digit,         "1.4e",     expect_digit);
FLOAT_TEST_EXPECT_FAILURE(no_pos_exp_digit,     "1.4e+",    expect_digit);
FLOAT_TEST_EXPECT_FAILURE(no_neg_exp_digit,     "1.4e-",    expect_digit);
FLOAT_TEST_EXPECT_FAILURE(no_EXP_digit,         "1.4E",     expect_digit);
FLOAT_TEST_EXPECT_FAILURE(no_pos_EXP_digit,     "1.4E+",    expect_digit);
FLOAT_TEST_EXPECT_FAILURE(no_neg_EXP_digit,     "1.4E-",    expect_digit);
FLOAT_TEST_EXPECT_FAILURE(hex_no_p,             "0x1.",     expect_p);
FLOAT_TEST_EXPECT_FAILURE(hex_no_p_digit,       "0x1.p",    expect_digit);
FLOAT_TEST_EXPECT_FAILURE(hex_no_pos_p_digit,   "0x1.p+",   expect_digit);
FLOAT_TEST_EXPECT_FAILURE(hex_no_neg_p_digit,   "0x1.p-",   expect_digit);
FLOAT_TEST_EXPECT_FAILURE(hex_no_P_digit,       "0x1.P",    expect_digit);
FLOAT_TEST_EXPECT_FAILURE(hex_no_pos_P_digit,   "0x1.P+",   expect_digit);
FLOAT_TEST_EXPECT_FAILURE(hex_no_neg_P_digit,   "0x1.P-",   expect_digit);
FLOAT_TEST_EXPECT_FAILURE(hex_float_p0,         "0xp0",     p_digit);
FLOAT_TEST_EXPECT_FAILURE(hex_float_P0,         "0xP0",     p_digit);
FLOAT_TEST_EXPECT_FAILURE(HEX_no_p,             "0X1.",     expect_p);
FLOAT_TEST_EXPECT_FAILURE(HEX_no_p_digit,       "0X1.p",    expect_digit);
FLOAT_TEST_EXPECT_FAILURE(HEX_no_pos_p_digit,   "0X1.p+",   expect_digit);
FLOAT_TEST_EXPECT_FAILURE(HEX_no_neg_p_digit,   "0X1.p-",   expect_digit);
FLOAT_TEST_EXPECT_FAILURE(HEX_no_P_digit,       "0X1.P",    expect_digit);
FLOAT_TEST_EXPECT_FAILURE(HEX_no_pos_P_digit,   "0X1.P+",   expect_digit);
FLOAT_TEST_EXPECT_FAILURE(HEX_no_neg_P_digit,   "0X1.P-",   expect_digit);
FLOAT_TEST_EXPECT_FAILURE(HEX_float_p0,         "0Xp0",     p_digit);
FLOAT_TEST_EXPECT_FAILURE(HEX_float_P0,         "0XP0",     p_digit);
