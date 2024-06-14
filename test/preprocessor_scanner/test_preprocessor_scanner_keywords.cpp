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

TEST_SUITE(preprocessor_scanner_keywords);

#define KEYWORD_TEST_EXPECT_SUCCESS(constant, string) \
    TEST(constant) \
    { \
        preprocessor_scanner* scanner; \
        input_stream* stream; \
        event_handler eh; \
        test_context t1; \
        const char* INPUT_STRING = string; \
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
        TEST_EXPECT(constant == f->first); \
        TEST_ASSERT( \
            STATUS_SUCCESS == preprocessor_scanner_release(scanner)); \
        TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh)); \
    } \
    REQUIRE_SEMICOLON_HERE

/* event type constants. */
#define kw_alignas              CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ALIGNAS
#define kw_alignof              CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ALIGNOF
#define kw_atomic               CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ATOMIC
#define kw_bool                 CPARSE_EVENT_TYPE_TOKEN_KEYWORD__BOOL
#define kw_complex              CPARSE_EVENT_TYPE_TOKEN_KEYWORD__COMPLEX
#define kw_generic              CPARSE_EVENT_TYPE_TOKEN_KEYWORD__GENERIC
#define kw_imaginary            CPARSE_EVENT_TYPE_TOKEN_KEYWORD__IMAGINARY
#define kw_noreturn             CPARSE_EVENT_TYPE_TOKEN_KEYWORD__NORETURN
#define kw_static_assert        CPARSE_EVENT_TYPE_TOKEN_KEYWORD__STATIC_ASSERT
#define kw_thread_local         CPARSE_EVENT_TYPE_TOKEN_KEYWORD__THREAD_LOCAL
#define kw_auto                 CPARSE_EVENT_TYPE_TOKEN_KEYWORD_AUTO
#define kw_break                CPARSE_EVENT_TYPE_TOKEN_KEYWORD_BREAK
#define kw_case                 CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CASE
#define kw_char                 CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CHAR
#define kw_const                CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CONST
#define kw_continue             CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CONTINUE
#define kw_default              CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DEFAULT
#define kw_do                   CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DO
#define kw_double               CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DOUBLE
#define kw_else                 CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ELSE
#define kw_enum                 CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ENUM
#define kw_extern               CPARSE_EVENT_TYPE_TOKEN_KEYWORD_EXTERN
#define kw_float                CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FLOAT
#define kw_for                  CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FOR
#define kw_goto                 CPARSE_EVENT_TYPE_TOKEN_KEYWORD_GOTO
#define kw_if                   CPARSE_EVENT_TYPE_TOKEN_KEYWORD_IF
#define kw_inline               CPARSE_EVENT_TYPE_TOKEN_KEYWORD_INLINE
#define kw_int                  CPARSE_EVENT_TYPE_TOKEN_KEYWORD_INT
#define kw_long                 CPARSE_EVENT_TYPE_TOKEN_KEYWORD_LONG
#define kw_register             CPARSE_EVENT_TYPE_TOKEN_KEYWORD_REGISTER
#define kw_restrict             CPARSE_EVENT_TYPE_TOKEN_KEYWORD_RESTRICT
#define kw_return               CPARSE_EVENT_TYPE_TOKEN_KEYWORD_RETURN
#define kw_short                CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SHORT
#define kw_signed               CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SIGNED
#define kw_sizeof               CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SIZEOF
#define kw_static               CPARSE_EVENT_TYPE_TOKEN_KEYWORD_STATIC
#define kw_struct               CPARSE_EVENT_TYPE_TOKEN_KEYWORD_STRUCT
#define kw_switch               CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SWITCH
#define kw_typedef              CPARSE_EVENT_TYPE_TOKEN_KEYWORD_TYPEDEF
#define kw_union                CPARSE_EVENT_TYPE_TOKEN_KEYWORD_UNION
#define kw_unsigned             CPARSE_EVENT_TYPE_TOKEN_KEYWORD_UNSIGNED
#define kw_void                 CPARSE_EVENT_TYPE_TOKEN_KEYWORD_VOID
#define kw_volatile             CPARSE_EVENT_TYPE_TOKEN_KEYWORD_VOLATILE
#define kw_while                CPARSE_EVENT_TYPE_TOKEN_KEYWORD_WHILE

/* Valid keyword tokens. */
KEYWORD_TEST_EXPECT_SUCCESS(kw_alignas,             "_Alignas");
KEYWORD_TEST_EXPECT_SUCCESS(kw_alignof,             "_Alignof");
KEYWORD_TEST_EXPECT_SUCCESS(kw_atomic,              "_Atomic");
KEYWORD_TEST_EXPECT_SUCCESS(kw_bool,                "_Bool");
KEYWORD_TEST_EXPECT_SUCCESS(kw_complex,             "_Complex");
KEYWORD_TEST_EXPECT_SUCCESS(kw_generic,             "_Generic");
KEYWORD_TEST_EXPECT_SUCCESS(kw_imaginary,           "_Imaginary");
KEYWORD_TEST_EXPECT_SUCCESS(kw_noreturn,            "_Noreturn");
KEYWORD_TEST_EXPECT_SUCCESS(kw_static_assert,       "_Static_assert");
KEYWORD_TEST_EXPECT_SUCCESS(kw_thread_local,        "_Thread_local");
KEYWORD_TEST_EXPECT_SUCCESS(kw_auto,                "auto");
KEYWORD_TEST_EXPECT_SUCCESS(kw_break,               "break");
KEYWORD_TEST_EXPECT_SUCCESS(kw_case,                "case");
KEYWORD_TEST_EXPECT_SUCCESS(kw_char,                "char");
KEYWORD_TEST_EXPECT_SUCCESS(kw_const,               "const");
KEYWORD_TEST_EXPECT_SUCCESS(kw_continue,            "continue");
KEYWORD_TEST_EXPECT_SUCCESS(kw_default,             "default");
KEYWORD_TEST_EXPECT_SUCCESS(kw_do,                  "do");
KEYWORD_TEST_EXPECT_SUCCESS(kw_double,              "double");
KEYWORD_TEST_EXPECT_SUCCESS(kw_else,                "else");
KEYWORD_TEST_EXPECT_SUCCESS(kw_enum,                "enum");
KEYWORD_TEST_EXPECT_SUCCESS(kw_extern,              "extern");
KEYWORD_TEST_EXPECT_SUCCESS(kw_float,               "float");
KEYWORD_TEST_EXPECT_SUCCESS(kw_for,                 "for");
KEYWORD_TEST_EXPECT_SUCCESS(kw_goto,                "goto");
KEYWORD_TEST_EXPECT_SUCCESS(kw_if,                  "if");
KEYWORD_TEST_EXPECT_SUCCESS(kw_inline,              "inline");
KEYWORD_TEST_EXPECT_SUCCESS(kw_int,                 "int");
KEYWORD_TEST_EXPECT_SUCCESS(kw_long,                "long");
KEYWORD_TEST_EXPECT_SUCCESS(kw_register,            "register");
KEYWORD_TEST_EXPECT_SUCCESS(kw_restrict,            "restrict");
KEYWORD_TEST_EXPECT_SUCCESS(kw_return,              "return");
KEYWORD_TEST_EXPECT_SUCCESS(kw_short,               "short");
KEYWORD_TEST_EXPECT_SUCCESS(kw_signed,              "signed");
KEYWORD_TEST_EXPECT_SUCCESS(kw_sizeof,              "sizeof");
KEYWORD_TEST_EXPECT_SUCCESS(kw_static,              "static");
KEYWORD_TEST_EXPECT_SUCCESS(kw_struct,              "struct");
KEYWORD_TEST_EXPECT_SUCCESS(kw_switch,              "switch");
KEYWORD_TEST_EXPECT_SUCCESS(kw_typedef,             "typedef");
KEYWORD_TEST_EXPECT_SUCCESS(kw_union,               "union");
KEYWORD_TEST_EXPECT_SUCCESS(kw_unsigned,            "unsigned");
KEYWORD_TEST_EXPECT_SUCCESS(kw_void,                "void");
KEYWORD_TEST_EXPECT_SUCCESS(kw_volatile,            "volatile");
KEYWORD_TEST_EXPECT_SUCCESS(kw_while,               "while");

/* TODO - add invalid token tests. */
