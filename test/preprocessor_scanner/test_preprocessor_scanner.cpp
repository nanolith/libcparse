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
#include <libcparse/event/raw_integer.h>
#include <libcparse/event/raw_string.h>
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
CPARSE_IMPORT_event_raw_integer;
CPARSE_IMPORT_event_raw_string;
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
    else if (CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == token_type)
    {
        event_raw_string_token* sev;
        retval = event_downcast_to_event_raw_string_token(&sev, (event*)ev);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        auto str = event_raw_string_token_get(sev);

        ctx->vals.push_back(
            make_pair(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING, str));
    }
    else if (CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == token_type)
    {
        event_raw_integer_token* iev;
        retval = event_downcast_to_event_raw_integer_token(&iev, (event*)ev);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        auto str = event_raw_integer_token_string_get(iev);

        ctx->vals.push_back(make_pair(token_type, str));
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
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_GOTO:
            ctx->vals.push_back(make_pair(token_type, "goto"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_IF:
            ctx->vals.push_back(make_pair(token_type, "if"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_INLINE:
            ctx->vals.push_back(make_pair(token_type, "inline"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_INT:
            ctx->vals.push_back(make_pair(token_type, "int"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_LONG:
            ctx->vals.push_back(make_pair(token_type, "long"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_REGISTER:
            ctx->vals.push_back(make_pair(token_type, "register"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_RESTRICT:
            ctx->vals.push_back(make_pair(token_type, "restrict"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_RETURN:
            ctx->vals.push_back(make_pair(token_type, "return"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SHORT:
            ctx->vals.push_back(make_pair(token_type, "short"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SIGNED:
            ctx->vals.push_back(make_pair(token_type, "signed"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SIZEOF:
            ctx->vals.push_back(make_pair(token_type, "sizeof"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_STATIC:
            ctx->vals.push_back(make_pair(token_type, "static"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_STRUCT:
            ctx->vals.push_back(make_pair(token_type, "struct"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SWITCH:
            ctx->vals.push_back(make_pair(token_type, "switch"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_TYPEDEF:
            ctx->vals.push_back(make_pair(token_type, "typedef"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_UNION:
            ctx->vals.push_back(make_pair(token_type, "union"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_UNSIGNED:
            ctx->vals.push_back(make_pair(token_type, "unsigned"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_VOID:
            ctx->vals.push_back(make_pair(token_type, "void"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_VOLATILE:
            ctx->vals.push_back(make_pair(token_type, "volatile"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_WHILE:
            ctx->vals.push_back(make_pair(token_type, "while"));
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

/**
 * Test that we can scan a goto keyword.
 */
TEST(goto_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "goto";

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

    /* this first value is a goto keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_GOTO == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an if keyword.
 */
TEST(if_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "if";

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

    /* this first value is an if keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_IF == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an inline keyword.
 */
TEST(inline_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "inline";

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

    /* this first value is an inline keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_INLINE == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an int keyword.
 */
TEST(int_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "int";

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

    /* this first value is an int keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_INT == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a long keyword.
 */
TEST(long_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "long";

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

    /* this first value is a long keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_LONG == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a register keyword.
 */
TEST(register_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "register";

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

    /* this first value is a register keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_REGISTER == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a restrict keyword.
 */
TEST(restrict_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "restrict";

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

    /* this first value is a restrict keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_RESTRICT == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a return keyword.
 */
TEST(return_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "return";

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

    /* this first value is a return keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_RETURN == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a short keyword.
 */
TEST(short_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "short";

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

    /* this first value is a short keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SHORT == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a signed keyword.
 */
TEST(signed_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "signed";

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

    /* this first value is a signed keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SIGNED == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a sizeof keyword.
 */
TEST(sizeof_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "sizeof";

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

    /* this first value is a sizeof keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SIZEOF == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a static keyword.
 */
TEST(static_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "static";

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

    /* this first value is a static keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_STATIC == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a struct keyword.
 */
TEST(struct_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "struct";

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

    /* this first value is a struct keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_STRUCT == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a switch keyword.
 */
TEST(switch_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "switch";

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

    /* this first value is a switch keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SWITCH == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a typedef keyword.
 */
TEST(typedef_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "typedef";

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

    /* this first value is a typedef keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_TYPEDEF == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a union keyword.
 */
TEST(union_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "union";

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

    /* this first value is a union keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_UNION == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan an unsigned keyword.
 */
TEST(unsigned_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "unsigned";

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

    /* this first value is an unsigned keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_UNSIGNED == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a void keyword.
 */
TEST(void_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "void";

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

    /* this first value is a void keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_VOID == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a volatile keyword.
 */
TEST(volatile_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "volatile";

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

    /* this first value is a volatile keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_VOLATILE == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a while keyword.
 */
TEST(while_keyword_token)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = "while";

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

    /* this first value is a while keyword. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_KEYWORD_WHILE == f->first);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

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

/**
 * Test that we can scan an empty string token.
 */
TEST(empty_string)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a whitespace string token.
 */
TEST(whitespace_string)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("  	  
  ")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that an unterminated string sequence returns an error.
 */
TEST(unterminated_string_error)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"(")";

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
    TEST_ASSERT(
        ERROR_LIBCPARSE_COMMENT_EXPECTING_DOUBLE_QUOTE
            == abstract_parser_run(ap));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a normal string.
 */
TEST(basic_string)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("abc123")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with an escaped tick character.
 */
TEST(basic_string_with_tick_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\'")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with an escaped quote character.
 */
TEST(basic_string_with_quote_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\"")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with an escaped question character.
 */
TEST(basic_string_with_question_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\?")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with an escaped backslash character.
 */
TEST(basic_string_with_backslash_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\\")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with an escaped alert / beep character.
 */
TEST(basic_string_with_alert_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\a")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with an escaped backspace character.
 */
TEST(basic_string_with_backspace_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\b")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with an escaped formfeed character.
 */
TEST(basic_string_with_formfeed_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\f")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with an escaped newline character.
 */
TEST(basic_string_with_newline_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\n")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with an escaped cr character.
 */
TEST(basic_string_with_cr_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\r")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with an escaped tab character.
 */
TEST(basic_string_with_tab_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\t")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with an escaped vertical tab character.
 */
TEST(basic_string_with_vtab_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\v")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with a single digit octal character.
 */
TEST(basic_string_with_octal_1_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\1")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with a double digit octal character.
 */
TEST(basic_string_with_octal_2_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\12")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with a triple digit octal character.
 */
TEST(basic_string_with_octal_3_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\123")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with a multiple octal characters.
 */
TEST(basic_string_with_multiple_octal_characters)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\123\12\01\3")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with a single digit hex character.
 */
TEST(basic_string_with_hex_1_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\x1")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * The hex escape must have at least one hex digit.
 */
TEST(basic_string_with_hex_no_digit_error)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\x")";

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
    TEST_ASSERT(
        ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER
            == abstract_parser_run(ap));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a string with a multi-digit hex character.
 */
TEST(basic_string_with_hex_multi_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\xabc123")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a little u escape sequence.
 */
TEST(basic_string_with_little_u_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\u01ab")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * A zero digit universal character escape is invalid.
 */
TEST(basic_string_with_little_u_zero_digit_error)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\u")";

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
    TEST_ASSERT(
        ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER
            == abstract_parser_run(ap));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * A one digit universal character escape is invalid.
 */
TEST(basic_string_with_little_u_one_digit_error)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\u1")";

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
    TEST_ASSERT(
        ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER
            == abstract_parser_run(ap));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * A two digit universal character escape is invalid.
 */
TEST(basic_string_with_little_u_two_digit_error)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\u11")";

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
    TEST_ASSERT(
        ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER
            == abstract_parser_run(ap));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * A three digit universal character escape is invalid.
 */
TEST(basic_string_with_little_u_three_digit_error)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\u111")";

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
    TEST_ASSERT(
        ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER
            == abstract_parser_run(ap));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can scan a big u escape sequence.
 */
TEST(basic_string_with_big_u_escape_sequence)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\U0123abcd")";

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
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == f->first);
    TEST_EXPECT(INPUT_STRING == f->second);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * A zero digit big universal character escape is invalid.
 */
TEST(basic_string_with_big_u_zero_digit_error)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\U")";

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
    TEST_ASSERT(
        ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER
            == abstract_parser_run(ap));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * A one digit big universal character escape is invalid.
 */
TEST(basic_string_with_big_u_one_digit_error)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\U1")";

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
    TEST_ASSERT(
        ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER
            == abstract_parser_run(ap));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * A two digit big universal character escape is invalid.
 */
TEST(basic_string_with_big_u_two_digit_error)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\U11")";

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
    TEST_ASSERT(
        ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER
            == abstract_parser_run(ap));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * A three digit big universal character escape is invalid.
 */
TEST(basic_string_with_big_u_three_digit_error)
{
    preprocessor_scanner* scanner;
    input_stream* stream;
    event_handler eh;
    test_context t1;
    const char* INPUT_STRING = R"("\U111")";

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
    TEST_ASSERT(
        ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER
            == abstract_parser_run(ap));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}
