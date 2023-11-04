/**
 * \file test/comment_scanner/test_comment_scanner.cpp
 *
 * \brief Tests for the \ref comment_scanner type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/comment_scanner.h>
#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/event_handler.h>
#include <libcparse/status_codes.h>
#include <list>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_comment_scanner;
CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_raw_character;

TEST_SUITE(comment_scanner);

struct test_context
{
    list<int> vals;
    bool eof;
    cursor pos;

    test_context()
        : eof(false)
    {
    }
};

static int dummy_callback(void* context, const CPARSE_SYM(event)* ev)
{
    int retval;
    test_context* ctx = (test_context*)context;

    if (CPARSE_EVENT_TYPE_EOF == event_get_type(ev))
    {
        ctx->eof = true;
    }
    else if (CPARSE_EVENT_TYPE_RAW_CHARACTER == event_get_type(ev))
    {
        event_raw_character* rev;
        retval = event_downcast_to_event_raw_character(&rev, (event*)ev);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        ctx->vals.push_back(event_raw_character_get(rev));
        memcpy(&ctx->pos, event_get_cursor(ev), sizeof(ctx->pos));
    }
    else
    {
        return -1;
    }

    return STATUS_SUCCESS;
}

/**
 * Test that we can create and release a comment scanner.
 */
TEST(create_release)
{
    comment_scanner* scanner;

    /* we can create the comment_scanner. */
    TEST_ASSERT(
        STATUS_SUCCESS == comment_scanner_create(&scanner));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == comment_scanner_release(scanner));
}

/**
 * Test that we can subscribe to a comment_scanner.
 */
TEST(subscribe)
{
    comment_scanner* scanner;
    event_handler eh;
    test_context t1;

    /* create the scanner instance. */
    TEST_ASSERT(
        STATUS_SUCCESS == comment_scanner_create(&scanner));

    /* create our event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_handler_init(&eh, &dummy_callback, &t1));

    /* get the abstract parser. */
    auto ap = comment_scanner_upcast(scanner);

    /* subscribe to the scanner. */
    TEST_ASSERT(
        STATUS_SUCCESS == abstract_parser_comment_scanner_subscribe(ap, &eh));

    /* precondition: eof is false. */
    TEST_ASSERT(!t1.eof);

    /* run the filter. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(ap));

    /* postcondition: eof is true. */
    TEST_EXPECT(t1.eof);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == comment_scanner_release(scanner));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}
