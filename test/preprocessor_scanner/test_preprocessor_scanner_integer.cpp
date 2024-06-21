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

TEST_SUITE(preprocessor_scanner_integer);

#define INT_TEST_EXPECT_SUCCESS(name, constant) \
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
        TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == f->first); \
        TEST_EXPECT(INPUT_STRING == f->second); \
        TEST_ASSERT( \
            STATUS_SUCCESS == preprocessor_scanner_release(scanner)); \
        TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh)); \
    } \
    REQUIRE_SEMICOLON_HERE

/* Valid integer tokens. */
INT_TEST_EXPECT_SUCCESS(decimal,    "1234");
INT_TEST_EXPECT_SUCCESS(octal,      "07654321");
INT_TEST_EXPECT_SUCCESS(hex,        "0x01abc");
INT_TEST_EXPECT_SUCCESS(HEX,        "0X01abc");
INT_TEST_EXPECT_SUCCESS(zero,       "0");
INT_TEST_EXPECT_SUCCESS(du,         "1234u");
INT_TEST_EXPECT_SUCCESS(dU,         "1234U");
INT_TEST_EXPECT_SUCCESS(dl,         "1234l");
INT_TEST_EXPECT_SUCCESS(dL,         "1234L");
INT_TEST_EXPECT_SUCCESS(dul,        "1234ul");
INT_TEST_EXPECT_SUCCESS(duL,        "1234uL");
INT_TEST_EXPECT_SUCCESS(dUl,        "1234Ul");
INT_TEST_EXPECT_SUCCESS(dUL,        "1234UL");
INT_TEST_EXPECT_SUCCESS(dull,       "1234ull");
INT_TEST_EXPECT_SUCCESS(dulL,       "1234ulL");
INT_TEST_EXPECT_SUCCESS(duLl,       "1234uLl");
INT_TEST_EXPECT_SUCCESS(duLL,       "1234uLL");
INT_TEST_EXPECT_SUCCESS(dUll,       "1234Ull");
INT_TEST_EXPECT_SUCCESS(dUlL,       "1234UlL");
INT_TEST_EXPECT_SUCCESS(dULl,       "1234ULl");
INT_TEST_EXPECT_SUCCESS(dULL,       "1234ULL");
INT_TEST_EXPECT_SUCCESS(dlu,        "1234lu");
INT_TEST_EXPECT_SUCCESS(dlU,        "1234lU");
INT_TEST_EXPECT_SUCCESS(dLu,        "1234Lu");
INT_TEST_EXPECT_SUCCESS(dLU,        "1234LU");
INT_TEST_EXPECT_SUCCESS(dll,        "1234ll");
INT_TEST_EXPECT_SUCCESS(dlL,        "1234lL");
INT_TEST_EXPECT_SUCCESS(dLl,        "1234Ll");
INT_TEST_EXPECT_SUCCESS(dLL,        "1234LL");
INT_TEST_EXPECT_SUCCESS(dllu,       "1234llu");
INT_TEST_EXPECT_SUCCESS(dllU,       "1234llU");
INT_TEST_EXPECT_SUCCESS(dlLu,       "1234lLu");
INT_TEST_EXPECT_SUCCESS(dlLU,       "1234lLU");
INT_TEST_EXPECT_SUCCESS(dLlu,       "1234Llu");
INT_TEST_EXPECT_SUCCESS(dLlU,       "1234LlU");
INT_TEST_EXPECT_SUCCESS(dLLu,       "1234LLu");
INT_TEST_EXPECT_SUCCESS(dLLU,       "1234LLU");
INT_TEST_EXPECT_SUCCESS(zu,         "0u");
INT_TEST_EXPECT_SUCCESS(zU,         "0U");
INT_TEST_EXPECT_SUCCESS(zl,         "0l");
INT_TEST_EXPECT_SUCCESS(zL,         "0L");
INT_TEST_EXPECT_SUCCESS(zul,        "0ul");
INT_TEST_EXPECT_SUCCESS(zuL,        "0uL");
INT_TEST_EXPECT_SUCCESS(zUl,        "0Ul");
INT_TEST_EXPECT_SUCCESS(zUL,        "0UL");
INT_TEST_EXPECT_SUCCESS(zull,       "0ull");
INT_TEST_EXPECT_SUCCESS(zulL,       "0ulL");
INT_TEST_EXPECT_SUCCESS(zuLl,       "0uLl");
INT_TEST_EXPECT_SUCCESS(zuLL,       "0uLL");
INT_TEST_EXPECT_SUCCESS(zUll,       "0Ull");
INT_TEST_EXPECT_SUCCESS(zUlL,       "0UlL");
INT_TEST_EXPECT_SUCCESS(zULl,       "0ULl");
INT_TEST_EXPECT_SUCCESS(zULL,       "0ULL");
INT_TEST_EXPECT_SUCCESS(zll,        "0ll");
INT_TEST_EXPECT_SUCCESS(zlL,        "0lL");
INT_TEST_EXPECT_SUCCESS(zLl,        "0Ll");
INT_TEST_EXPECT_SUCCESS(zLL,        "0LL");
/* TODO - add zero llu variants. */
INT_TEST_EXPECT_SUCCESS(xu,         "0xau");
INT_TEST_EXPECT_SUCCESS(xU,         "0xaU");
INT_TEST_EXPECT_SUCCESS(xl,         "0xal");
INT_TEST_EXPECT_SUCCESS(xL,         "0xaL");
INT_TEST_EXPECT_SUCCESS(xul,        "0xaul");
INT_TEST_EXPECT_SUCCESS(xuL,        "0xauL");
INT_TEST_EXPECT_SUCCESS(xUl,        "0xaUl");
INT_TEST_EXPECT_SUCCESS(xUL,        "0xaUL");
INT_TEST_EXPECT_SUCCESS(xull,       "0xaull");
INT_TEST_EXPECT_SUCCESS(xulL,       "0xaulL");
INT_TEST_EXPECT_SUCCESS(xuLl,       "0xauLl");
INT_TEST_EXPECT_SUCCESS(xuLL,       "0xauLL");
INT_TEST_EXPECT_SUCCESS(xUll,       "0xaUll");
INT_TEST_EXPECT_SUCCESS(xUlL,       "0xaUlL");
INT_TEST_EXPECT_SUCCESS(xULl,       "0xaULl");
INT_TEST_EXPECT_SUCCESS(xULL,       "0xaULL");
INT_TEST_EXPECT_SUCCESS(xll,        "0xall");
INT_TEST_EXPECT_SUCCESS(xlL,        "0xalL");
INT_TEST_EXPECT_SUCCESS(xLl,        "0xaLl");
INT_TEST_EXPECT_SUCCESS(xLL,        "0xaLL");
INT_TEST_EXPECT_SUCCESS(xlu,        "0xalu");
INT_TEST_EXPECT_SUCCESS(xlU,        "0xalU");
INT_TEST_EXPECT_SUCCESS(xLu,        "0xaLu");
INT_TEST_EXPECT_SUCCESS(xLU,        "0xaLU");
INT_TEST_EXPECT_SUCCESS(xllu,       "0xallu");
INT_TEST_EXPECT_SUCCESS(xllU,       "0xallU");
INT_TEST_EXPECT_SUCCESS(xlLu,       "0xalLu");
INT_TEST_EXPECT_SUCCESS(xlLU,       "0xalLU");
INT_TEST_EXPECT_SUCCESS(xLlu,       "0xaLlu");
INT_TEST_EXPECT_SUCCESS(xLlU,       "0xaLlU");
INT_TEST_EXPECT_SUCCESS(xLLu,       "0xaLLu");
INT_TEST_EXPECT_SUCCESS(xLLU,       "0xaLLU");
INT_TEST_EXPECT_SUCCESS(Xu,         "0Xau");
INT_TEST_EXPECT_SUCCESS(Xl,         "0Xal");
INT_TEST_EXPECT_SUCCESS(XL,         "0XaL");
INT_TEST_EXPECT_SUCCESS(XuL,        "0XauL");
INT_TEST_EXPECT_SUCCESS(XUl,        "0XaUl");
INT_TEST_EXPECT_SUCCESS(XUL,        "0XaUL");
INT_TEST_EXPECT_SUCCESS(Xull,       "0Xaull");
INT_TEST_EXPECT_SUCCESS(XulL,       "0XaulL");
INT_TEST_EXPECT_SUCCESS(XuLl,       "0XauLl");
INT_TEST_EXPECT_SUCCESS(XuLL,       "0XauLL");
INT_TEST_EXPECT_SUCCESS(XUll,       "0XaUll");
INT_TEST_EXPECT_SUCCESS(XUlL,       "0XaUlL");
INT_TEST_EXPECT_SUCCESS(XULl,       "0XaULl");
INT_TEST_EXPECT_SUCCESS(XULL,       "0XaULL");
INT_TEST_EXPECT_SUCCESS(Xll,        "0Xall");
INT_TEST_EXPECT_SUCCESS(XlL,        "0XalL");
INT_TEST_EXPECT_SUCCESS(XLl,        "0XaLl");
INT_TEST_EXPECT_SUCCESS(XLL,        "0XaLL");
INT_TEST_EXPECT_SUCCESS(Xlu,        "0Xalu");
INT_TEST_EXPECT_SUCCESS(XlU,        "0XalU");
INT_TEST_EXPECT_SUCCESS(XLu,        "0XaLu");
INT_TEST_EXPECT_SUCCESS(XLU,        "0XaLU");
INT_TEST_EXPECT_SUCCESS(Xllu,       "0Xallu");
INT_TEST_EXPECT_SUCCESS(XllU,       "0XallU");
INT_TEST_EXPECT_SUCCESS(XlLu,       "0XalLu");
INT_TEST_EXPECT_SUCCESS(XlLU,       "0XalLU");
INT_TEST_EXPECT_SUCCESS(XLlu,       "0XaLlu");
INT_TEST_EXPECT_SUCCESS(XLlU,       "0XaLlU");
INT_TEST_EXPECT_SUCCESS(ou,         "07u");
INT_TEST_EXPECT_SUCCESS(oU,         "07U");
INT_TEST_EXPECT_SUCCESS(ol,         "07l");
INT_TEST_EXPECT_SUCCESS(oL,         "07L");
INT_TEST_EXPECT_SUCCESS(oul,        "07ul");
INT_TEST_EXPECT_SUCCESS(ouL,        "07uL");
INT_TEST_EXPECT_SUCCESS(oUl,        "07Ul");
INT_TEST_EXPECT_SUCCESS(oUL,        "07UL");
INT_TEST_EXPECT_SUCCESS(oull,       "07ull");
INT_TEST_EXPECT_SUCCESS(oulL,       "07ulL");
INT_TEST_EXPECT_SUCCESS(ouLl,       "07uLl");
INT_TEST_EXPECT_SUCCESS(ouLL,       "07uLL");
INT_TEST_EXPECT_SUCCESS(oUll,       "07Ull");
INT_TEST_EXPECT_SUCCESS(oUlL,       "07UlL");
INT_TEST_EXPECT_SUCCESS(oULl,       "07ULl");
INT_TEST_EXPECT_SUCCESS(oULL,       "07ULL");
INT_TEST_EXPECT_SUCCESS(ollu,       "07llu");
INT_TEST_EXPECT_SUCCESS(ollU,       "07llU");
INT_TEST_EXPECT_SUCCESS(olLu,       "07lLu");
INT_TEST_EXPECT_SUCCESS(olLU,       "07lLU");
INT_TEST_EXPECT_SUCCESS(oLlu,       "07Llu");
INT_TEST_EXPECT_SUCCESS(oLlU,       "07LlU");
INT_TEST_EXPECT_SUCCESS(oLLu,       "07LLu");
INT_TEST_EXPECT_SUCCESS(oLLU,       "07LLU");
/* TODO - add invalid token tests. */
