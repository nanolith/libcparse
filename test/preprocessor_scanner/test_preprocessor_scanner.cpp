/**
 * \file test/preprocessor_scanner/test_preprocessor_scanner.cpp
 *
 * \brief Tests for the \ref preprocessor_scanner type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/identifier.h>
#include <libcparse/event_handler.h>
#include <libcparse/event_type.h>
#include <libcparse/input_stream.h>
#include <libcparse/preprocessor_scanner.h>
#include <libcparse/status_codes.h>
#include <list>
#include <minunit/minunit.h>
#include <string>

using namespace std;

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_identifier;
CPARSE_IMPORT_input_stream;
CPARSE_IMPORT_preprocessor_scanner;

TEST_SUITE(preprocessor_scanner);

namespace
{
    typedef pair<int, string> test_token;

    struct test_context
    {
        list<test_token> vals;
        bool eof;

        test_context()
            : eof(false)
        {
        }
    };
}

static int dummy_callback(void* context, const CPARSE_SYM(event)* ev)
{
    int retval;
    test_context* ctx = (test_context*)context;

    auto token_type = event_get_type(ev);

    if (CPARSE_EVENT_TYPE_EOF == token_type)
    {
        ctx->eof = true;
    }
    else if (CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == token_type)
    {
        event_identifier* iev;
        retval = event_downcast_to_event_identifier(&iev, (event*)ev);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        auto str = event_identifier_get(iev);

        ctx->vals.push_back(make_pair(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER, str));
    }
    else
    {
        switch (token_type)
        {
        case CPARSE_EVENT_TYPE_TOKEN_LEFT_PAREN:
            ctx->vals.push_back(make_pair(token_type, "("));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_RIGHT_PAREN:
            ctx->vals.push_back(make_pair(token_type, ")"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACE:
            ctx->vals.push_back(make_pair(token_type, "{"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACE:
            ctx->vals.push_back(make_pair(token_type, "}"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACKET:
            ctx->vals.push_back(make_pair(token_type, "["));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACKET:
            ctx->vals.push_back(make_pair(token_type, "]"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_COMMA:
            ctx->vals.push_back(make_pair(token_type, ","));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_COLON:
            ctx->vals.push_back(make_pair(token_type, ":"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_SEMICOLON:
            ctx->vals.push_back(make_pair(token_type, ";"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_DOT:
            ctx->vals.push_back(make_pair(token_type, "."));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_ARROW:
            ctx->vals.push_back(make_pair(token_type, "->"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PLUS:
            ctx->vals.push_back(make_pair(token_type, "+"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_MINUS:
            ctx->vals.push_back(make_pair(token_type, "-"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_STAR:
            ctx->vals.push_back(make_pair(token_type, "*"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_FORWARD_SLASH:
            ctx->vals.push_back(make_pair(token_type, "/"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PERCENT:
            ctx->vals.push_back(make_pair(token_type, "%"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_LOGICAL_AND:
            ctx->vals.push_back(make_pair(token_type, "&&"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_LOGICAL_OR:
            ctx->vals.push_back(make_pair(token_type, "||"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_AMPERSAND:
            ctx->vals.push_back(make_pair(token_type, "&"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PIPE:
            ctx->vals.push_back(make_pair(token_type, "|"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_CARET:
            ctx->vals.push_back(make_pair(token_type, "^"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_TILDE:
            ctx->vals.push_back(make_pair(token_type, "~"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_QUESTION:
            ctx->vals.push_back(make_pair(token_type, "?"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_EQUAL_COMPARE:
            ctx->vals.push_back(make_pair(token_type, "=="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_NOT_EQUAL_COMPARE:
            ctx->vals.push_back(make_pair(token_type, "!="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_EQUAL_ASSIGN:
            ctx->vals.push_back(make_pair(token_type, "="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PLUS_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "+="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_MINUS_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "-="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_TIMES_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "*="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_DIV_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "/="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_MOD_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "%="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_AND_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "&="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_OR_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "|="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_XOR_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "^="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_COMPL_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "~="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_LEFT_SHIFT_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "<<="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_RIGHT_SHIFT_EQUAL:
            ctx->vals.push_back(make_pair(token_type, ">>="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_BITSHIFT_LEFT:
            ctx->vals.push_back(make_pair(token_type, "<<"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_BITSHIFT_RIGHT:
            ctx->vals.push_back(make_pair(token_type, ">>"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_LESS_THAN:
            ctx->vals.push_back(make_pair(token_type, "<"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_GREATER_THAN:
            ctx->vals.push_back(make_pair(token_type, ">"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_LESS_THAN_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "<="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_GREATER_THAN_EQUAL:
            ctx->vals.push_back(make_pair(token_type, ">="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_INCREMENT:
            ctx->vals.push_back(make_pair(token_type, "++"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_DECREMENT:
            ctx->vals.push_back(make_pair(token_type, "--"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_NOT:
            ctx->vals.push_back(make_pair(token_type, "!"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ALIGNAS:
            ctx->vals.push_back(make_pair(token_type, "_Alignas"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ALIGNOF:
            ctx->vals.push_back(make_pair(token_type, "_Alignof"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ATOMIC:
            ctx->vals.push_back(make_pair(token_type, "_Atomic"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__BOOL:
            ctx->vals.push_back(make_pair(token_type, "_Bool"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__COMPLEX:
            ctx->vals.push_back(make_pair(token_type, "_Complex"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__GENERIC:
            ctx->vals.push_back(make_pair(token_type, "_Generic"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__IMAGINARY:
            ctx->vals.push_back(make_pair(token_type, "_Imaginary"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__NORETURN:
            ctx->vals.push_back(make_pair(token_type, "_Noreturn"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__STATIC_ASSERT:
            ctx->vals.push_back(make_pair(token_type, "_Static_assert"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__THREAD_LOCAL:
            ctx->vals.push_back(make_pair(token_type, "_Thread_local"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_AUTO:
            ctx->vals.push_back(make_pair(token_type, "auto"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_BREAK:
            ctx->vals.push_back(make_pair(token_type, "break"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CASE:
            ctx->vals.push_back(make_pair(token_type, "case"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CHAR:
            ctx->vals.push_back(make_pair(token_type, "char"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CONST:
            ctx->vals.push_back(make_pair(token_type, "const"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CONTINUE:
            ctx->vals.push_back(make_pair(token_type, "continue"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DEFAULT:
            ctx->vals.push_back(make_pair(token_type, "default"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DO:
            ctx->vals.push_back(make_pair(token_type, "do"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DOUBLE:
            ctx->vals.push_back(make_pair(token_type, "double"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ELSE:
            ctx->vals.push_back(make_pair(token_type, "else"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ENUM:
            ctx->vals.push_back(make_pair(token_type, "enum"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_EXTERN:
            ctx->vals.push_back(make_pair(token_type, "extern"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FLOAT:
            ctx->vals.push_back(make_pair(token_type, "float"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FOR:
            ctx->vals.push_back(make_pair(token_type, "for"));
            break;

        default:
            return -1;
        }
    }

    return STATUS_SUCCESS;
}

/**
 * Test that we can create and release a preprocessor scanner.
 */
TEST(create_release)
{
    preprocessor_scanner* scanner;

    /* we can create the scanner. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_create(&scanner));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
}

/**
 * Test that we can subscribe to a preprocessor scanner.
 */
TEST(subscribe)
{
    preprocessor_scanner* scanner;
    event_handler eh;
    test_context t1;

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

    /* precondition: eof is false. */
    TEST_ASSERT(!t1.eof);

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

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

/**
 * Test that we can scan a left parenthesis.
 */
TEST(left_paren1)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "(";

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

    /* this first value is a left paren. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_LEFT_PAREN == f->first);
    TEST_EXPECT("(" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an identifier and a left paren.
 */
TEST(left_paren2)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "foo(";

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

    /* this first value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("foo" == f->second);

    /* get the second value. */
    ++f;
    TEST_ASSERT(f != t1.vals.end());

    /* this second value is a left paren. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_LEFT_PAREN == f->first);
    TEST_EXPECT("(" == f->second);

    /* there are no more values. */
    TEST_EXPECT(++f == t1.vals.end());

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a right parenthesis.
 */
TEST(right_paren)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = ")";

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

    /* this first value is a right paren. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_RIGHT_PAREN == f->first);
    TEST_EXPECT(")" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a left brace.
 */
TEST(left_brace)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "{";

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

    /* this first value is a left brace. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACE == f->first);
    TEST_EXPECT("{" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a right brace.
 */
TEST(right_brace)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "}";

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

    /* this first value is a right brace. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACE == f->first);
    TEST_EXPECT("}" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a left bracket.
 */
TEST(left_bracket)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "[";

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

    /* this first value is a left bracket. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACKET == f->first);
    TEST_EXPECT("[" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a right bracket.
 */
TEST(right_bracket)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "]";

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

    /* this first value is a right bracket. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACKET == f->first);
    TEST_EXPECT("]" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a comma.
 */
TEST(comma)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = ",";

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

    /* this first value is a comma. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_COMMA == f->first);
    TEST_EXPECT("," == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a colon.
 */
TEST(colon)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = ":";

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

    /* this first value is a colon. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_COLON == f->first);
    TEST_EXPECT(":" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a semicolon.
 */
TEST(semicolon)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = ";";

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

    /* this first value is a semicolon. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_SEMICOLON == f->first);
    TEST_EXPECT(";" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a dot.
 */
TEST(dot)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = ".";

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

    /* this first value is a dot. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_DOT == f->first);
    TEST_EXPECT("." == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an arrow.
 */
TEST(arrow)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "->";

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

    /* this first value is a dot. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_ARROW == f->first);
    TEST_EXPECT("->" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a plus.
 */
TEST(plus)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "+";

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

    /* this first value is a plus. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PLUS == f->first);
    TEST_EXPECT("+" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a minus.
 */
TEST(minus1)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "-";

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

    /* this first value is a minus. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_MINUS == f->first);
    TEST_EXPECT("-" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a minus between two identifiers.
 */
TEST(minus2)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "x-y";

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
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("x" == f->second);

    /* get the second token. */
    ++f;
    TEST_ASSERT(f != t1.vals.end());

    /* this second value is a minus. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_MINUS == f->first);
    TEST_EXPECT("-" == f->second);

    /* get the third token. */
    ++f;
    TEST_ASSERT(f != t1.vals.end());

    /* this second value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("y" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a minus between two identifiers.
 */
TEST(minus3)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "x - y";

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
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("x" == f->second);

    /* get the second token. */
    ++f;
    TEST_ASSERT(f != t1.vals.end());

    /* this second value is a minus. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_MINUS == f->first);
    TEST_EXPECT("-" == f->second);

    /* get the third token. */
    ++f;
    TEST_ASSERT(f != t1.vals.end());

    /* this second value is an identifier. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == f->first);
    TEST_EXPECT("y" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a star.
 */
TEST(star)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "*";

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

    /* this first value is a star. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_STAR == f->first);
    TEST_EXPECT("*" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a slash.
 */
TEST(slash)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "/";

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

    /* this first value is a slash. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_FORWARD_SLASH == f->first);
    TEST_EXPECT("/" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a percent.
 */
TEST(percent)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "%";

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

    /* this first value is a percent. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PERCENT == f->first);
    TEST_EXPECT("%" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a logical AND.
 */
TEST(logical_and)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "&&";

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

    /* this first value is a logical and. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_LOGICAL_AND == f->first);
    TEST_EXPECT("&&" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a logical OR.
 */
TEST(logical_or)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "||";

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

    /* this first value is a logical or. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_LOGICAL_OR == f->first);
    TEST_EXPECT("||" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an ampersand.
 */
TEST(ampersand)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "&";

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

    /* this first value is an ampersand. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_AMPERSAND == f->first);
    TEST_EXPECT("&" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a pipe.
 */
TEST(pipe)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "|";

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

    /* this first value is a pipe. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PIPE == f->first);
    TEST_EXPECT("|" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a caret.
 */
TEST(caret)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "^";

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

    /* this first value is a caret. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_CARET == f->first);
    TEST_EXPECT("^" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a caret before a whitespace.
 */
TEST(caret_whitespace)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "^ a";

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
    TEST_ASSERT(2 == t1.vals.size());
    auto f = t1.vals.begin();
    TEST_ASSERT(f != t1.vals.end());

    /* this first value is a caret. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_CARET == f->first);
    TEST_EXPECT("^" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a tilde.
 */
TEST(tilde)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "~";

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

    /* this first value is a tilde. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_TILDE == f->first);
    TEST_EXPECT("~" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a question.
 */
TEST(question)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "?";

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

    /* this first value is a question. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_QUESTION == f->first);
    TEST_EXPECT("?" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an equal-compare.
 */
TEST(equal_compare)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "==";

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

    /* this first value is an equal-compare. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_EQUAL_COMPARE == f->first);
    TEST_EXPECT("==" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a not-equal.
 */
TEST(not_equal)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "!=";

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

    /* this first value is a not equal. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_NOT_EQUAL_COMPARE == f->first);
    TEST_EXPECT("!=" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an equal-assign.
 */
TEST(equal_assign)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "=";

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

    /* this first value is an equal-assign. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_EQUAL_ASSIGN == f->first);
    TEST_EXPECT("=" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a plus-equal.
 */
TEST(plus_equal)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "+=";

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

    /* this first value is a plus-equal. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_PLUS_EQUAL == f->first);
    TEST_EXPECT("+=" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a minus-equal.
 */
TEST(minus_equal)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "-=";

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

    /* this first value is a minus-equal. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_MINUS_EQUAL == f->first);
    TEST_EXPECT("-=" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a times-equal.
 */
TEST(times_equal)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "*=";

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

    /* this first value is a times-equal. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_TIMES_EQUAL == f->first);
    TEST_EXPECT("*=" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a div-equal.
 */
TEST(div_equal)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "/=";

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

    /* this first value is a div-equal. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_DIV_EQUAL == f->first);
    TEST_EXPECT("/=" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an and-equal.
 */
TEST(and_equal)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "&=";

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

    /* this first value is an and-equal. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_AND_EQUAL == f->first);
    TEST_EXPECT("&=" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an or-equal.
 */
TEST(or_equal)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "|=";

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

    /* this first value is an or-equal. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_OR_EQUAL == f->first);
    TEST_EXPECT("|=" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an xor-equal.
 */
TEST(xor_equal)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "^=";

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

    /* this first value is an xor-equal. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_XOR_EQUAL == f->first);
    TEST_EXPECT("^=" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a compl-equal.
 */
TEST(compl_equal)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "~=";

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

    /* this first value is a compl-equal. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_COMPL_EQUAL == f->first);
    TEST_EXPECT("~=" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a left-shift-equal.
 */
TEST(left_shift_equal)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "<<=";

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

    /* this first value is a left-shift-equal. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_LEFT_SHIFT_EQUAL == f->first);
    TEST_EXPECT("<<=" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a right-shift-equal.
 */
TEST(right_shift_equal)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = ">>=";

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

    /* this first value is a right-shift-equal. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_RIGHT_SHIFT_EQUAL == f->first);
    TEST_EXPECT(">>=" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a bitshift left.
 */
TEST(bitshift_left)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "<<";

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

    /* this first value is a bitshift left. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_BITSHIFT_LEFT == f->first);
    TEST_EXPECT("<<" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a bitshift right.
 */
TEST(bitshift_right)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = ">>";

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

    /* this first value is a bitshift right. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_BITSHIFT_RIGHT == f->first);
    TEST_EXPECT(">>" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a less than.
 */
TEST(less_than)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "<";

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

    /* this first value is a less than. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_LESS_THAN == f->first);
    TEST_EXPECT("<" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a greater than.
 */
TEST(greater_than)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = ">";

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

    /* this first value is a greater than. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_GREATER_THAN == f->first);
    TEST_EXPECT(">" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a less than equal.
 */
TEST(less_than_equal)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "<=";

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

    /* this first value is a less than equal. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_LESS_THAN_EQUAL == f->first);
    TEST_EXPECT("<=" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a greater than equal.
 */
TEST(greater_than_equal)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = ">=";

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

    /* this first value is a greater than equal. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_GREATER_THAN_EQUAL == f->first);
    TEST_EXPECT(">=" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an increment.
 */
TEST(increment)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "++";

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

    /* this first value is an increment. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_INCREMENT == f->first);
    TEST_EXPECT("++" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a decrement.
 */
TEST(decrement)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "--";

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

    /* this first value is a decrement. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_DECREMENT == f->first);
    TEST_EXPECT("--" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a not.
 */
TEST(not_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "!";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_NOT == f->first);
    TEST_EXPECT("!" == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an _Alignas keyword.
 */
TEST(_Alignas_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "_Alignas";

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

    /* this first value is an _Alignas keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ALIGNAS == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an _Alignof keyword.
 */
TEST(_Alignof_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "_Alignof";

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

    /* this first value is an _Alignof keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ALIGNOF == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an _Atomic keyword.
 */
TEST(_Atomic_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "_Atomic";

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

    /* this first value is an _Atomic keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ATOMIC == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a _Bool keyword.
 */
TEST(_Bool_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "_Bool";

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

    /* this first value is a _Bool keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD__BOOL == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a _Complex keyword.
 */
TEST(_Complex_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "_Complex";

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

    /* this first value is a _Complex keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD__COMPLEX == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a _Generic keyword.
 */
TEST(_Generic_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "_Generic";

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

    /* this first value is a _Generic keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD__GENERIC == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an _Imaginary keyword.
 */
TEST(_Imaginary_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "_Imaginary";

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

    /* this first value is an _Imaginary keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD__IMAGINARY == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a _Noreturn keyword.
 */
TEST(_Noreturn_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "_Noreturn";

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

    /* this first value is an _Noreturn keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD__NORETURN == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a _Static_assert keyword.
 */
TEST(_Static_assert_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "_Static_assert";

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

    /* this first value is a _Static_assert keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD__STATIC_ASSERT == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a _Thread_local keyword.
 */
TEST(_Thread_local_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "_Thread_local";

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

    /* this first value is a _Thread_local keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD__THREAD_LOCAL == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an auto keyword.
 */
TEST(auto_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "auto";

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

    /* this first value is an auto keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_AUTO == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a break keyword.
 */
TEST(break_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "break";

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

    /* this first value is a break keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_BREAK == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a case keyword.
 */
TEST(case_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "case";

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

    /* this first value is a case keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CASE == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a char keyword.
 */
TEST(char_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "char";

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

    /* this first value is a char keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CHAR == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a const keyword.
 */
TEST(const_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "const";

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

    /* this first value is a const keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CONST == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a continue keyword.
 */
TEST(continue_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "continue";

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

    /* this first value is a continue keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CONTINUE == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a default keyword.
 */
TEST(default_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "default";

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

    /* this first value is a default keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DEFAULT == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a do keyword.
 */
TEST(do_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "do";

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

    /* this first value is a do keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DO == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a double keyword.
 */
TEST(double_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "double";

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

    /* this first value is a double keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DOUBLE == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an else keyword.
 */
TEST(else_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "else";

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

    /* this first value is an else keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ELSE == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an enum keyword.
 */
TEST(enum_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "enum";

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

    /* this first value is an enum keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ENUM == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an extern keyword.
 */
TEST(extern_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "extern";

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

    /* this first value is an extern keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_EXTERN == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a float keyword.
 */
TEST(float_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "float";

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

    /* this first value is a float keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FLOAT == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a for keyword.
 */
TEST(for_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "for";

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

    /* this first value is a for keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FOR == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}
