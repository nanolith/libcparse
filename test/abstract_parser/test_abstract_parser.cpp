/**
 * \file test/abstract_parser/test_abstract_parser.cpp
 *
 * \brief Tests for the \ref abstract_parser type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/input_stream.h>
#include <libcparse/message/raw_stack_scanner.h>
#include <libcparse/message_handler.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_input_stream;
CPARSE_IMPORT_message;
CPARSE_IMPORT_message_handler;
CPARSE_IMPORT_message_raw_stack_scanner;

TEST_SUITE(abstract_parser);

namespace
{
    struct test_context_override
    {
        bool override_called;
        message_handler mh;

        test_context_override()
            : override_called(false)
        {
        }
    };

    struct test_context
    {
        bool run_called;
        bool push_input_stream_called;
        bool rss_subscribe_called;
        bool rflo_subscribe_called;
        bool error;

        test_context()
            : run_called(false)
            , push_input_stream_called(false)
            , rss_subscribe_called(false)
            , rflo_subscribe_called(false)
            , error(false)
        {
        }
    };
}

static int dummy_event_callback(void* context, const CPARSE_SYM(event)* ev)
{
    (void)context;
    (void)ev;
    return STATUS_SUCCESS;
}

static int dummy_callback_override(
    void* context, const CPARSE_SYM(message)* msg)
{
    test_context_override* over = (test_context_override*)context;

    over->override_called = true;

    return message_handler_send(&over->mh, msg);
}

static int dummy_callback(void* context, const CPARSE_SYM(message)* msg)
{
    int retval;
    test_context* ctx = (test_context*)context;
    input_stream* stream;
    message_rss_add_input_stream* rimsg;

    switch (message_get_type(msg))
    {
        case CPARSE_MESSAGE_TYPE_RUN:
            ctx->run_called = true;
            break;

        case CPARSE_MESSAGE_TYPE_RSS_SUBSCRIBE:
            ctx->rss_subscribe_called = true;
            break;

        case CPARSE_MESSAGE_TYPE_RFLO_SUBSCRIBE:
            ctx->rflo_subscribe_called = true;
            break;

        case CPARSE_MESSAGE_TYPE_RSS_ADD_INPUT_STREAM:
            ctx->push_input_stream_called = true;
            retval =
                message_downcast_to_message_rss_add_input_stream(
                    &rimsg, (message*)msg);
            if (STATUS_SUCCESS != retval)
            {
                ctx->error = true;
                break;
            }
            retval = message_rss_add_input_stream_xfer(&stream, rimsg);
            if (STATUS_SUCCESS != retval)
            {
                ctx->error = true;
                break;
            }
            retval = input_stream_release(stream);
            if (STATUS_SUCCESS != retval)
            {
                ctx->error = true;
                break;
            }
            break;

        default:
            break;
    }

    return STATUS_SUCCESS;
}

/**
 * Test that we can init and dispose an abstract parser.
 */
TEST(init_dispose)
{
    abstract_parser ap;
    message_handler mh;

    /* initialize the message handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == message_handler_init(&mh, &dummy_callback, nullptr));

    /* initialize the abstract parser. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_init(&ap, &mh));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_dispose(&ap));
    TEST_ASSERT(STATUS_SUCCESS == message_handler_dispose(&mh));
}

/**
 * Test that run sends a run message to the message handler.
 */
TEST(run)
{
    abstract_parser ap;
    test_context ctx;
    message_handler mh;

    /* initialize the message handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == message_handler_init(&mh, &dummy_callback, &ctx));

    /* initialize the abstract parser. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_init(&ap, &mh));

    /* precondition: no errors encountered. */
    TEST_EXPECT(!ctx.error);

    /* precondition: run_called is false. */
    TEST_ASSERT(!ctx.run_called);

    /* call run. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(&ap));

    /* postcondition: no errors encountered. */
    TEST_EXPECT(!ctx.error);

    /* postcondition: run_called is true. */
    TEST_EXPECT(ctx.run_called);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_dispose(&ap));
    TEST_ASSERT(STATUS_SUCCESS == message_handler_dispose(&mh));
}

/**
 * Test that we can send an input stream to the parser.
 */
TEST(push_input_stream)
{
    abstract_parser ap;
    test_context ctx;
    message_handler mh;
    input_stream* stream;

    /* create an input stream. */
    TEST_ASSERT(
        STATUS_SUCCESS == input_stream_create_from_string(&stream, "test"));

    /* initialize the message handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == message_handler_init(&mh, &dummy_callback, &ctx));

    /* initialize the abstract parser. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_init(&ap, &mh));

    /* precondition: no errors encountered. */
    TEST_EXPECT(!ctx.error);

    /* precondition: push_input_stream_called is false. */
    TEST_ASSERT(!ctx.push_input_stream_called);

    /* call push_input_stream. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_push_input_stream(&ap, "test", stream));

    /* postcondition: no errors encountered. */
    TEST_EXPECT(!ctx.error);

    /* postcondition: push_input_stream_called is true. */
    TEST_EXPECT(ctx.push_input_stream_called);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_dispose(&ap));
    TEST_ASSERT(STATUS_SUCCESS == message_handler_dispose(&mh));
}

/**
 * Test that we can subscribe to raw stack scanner events.
 */
TEST(raw_stack_scanner_subscribe)
{
    abstract_parser ap;
    test_context ctx;
    message_handler mh;
    event_handler eh;

    /* initialize the event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_handler_init(&eh, &dummy_event_callback, nullptr));

    /* initialize the message handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == message_handler_init(&mh, &dummy_callback, &ctx));

    /* initialize the abstract parser. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_init(&ap, &mh));

    /* precondition: no errors encountered. */
    TEST_EXPECT(!ctx.error);

    /* precondition: rss_subscribe_called is false. */
    TEST_ASSERT(!ctx.rss_subscribe_called);

    /* call subscribe. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_raw_stack_scanner_subscribe(&ap, &eh));

    /* postcondition: no errors encountered. */
    TEST_EXPECT(!ctx.error);

    /* postcondition: rss_subscribe_called is true. */
    TEST_EXPECT(ctx.rss_subscribe_called);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_dispose(&ap));
    TEST_ASSERT(STATUS_SUCCESS == message_handler_dispose(&mh));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can subscribe to raw file/line override filter events.
 */
TEST(raw_file_line_override_filter_subscribe)
{
    abstract_parser ap;
    test_context ctx;
    message_handler mh;
    event_handler eh;

    /* initialize the event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_handler_init(&eh, &dummy_event_callback, nullptr));

    /* initialize the message handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == message_handler_init(&mh, &dummy_callback, &ctx));

    /* initialize the abstract parser. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_init(&ap, &mh));

    /* precondition: no errors encountered. */
    TEST_EXPECT(!ctx.error);

    /* precondition: rflo_subscribe_called is false. */
    TEST_ASSERT(!ctx.rflo_subscribe_called);

    /* call subscribe. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_raw_file_line_override_filter_subscribe(
                    &ap, &eh));

    /* postcondition: no errors encountered. */
    TEST_EXPECT(!ctx.error);

    /* postcondition: rflo_subscribe_called is true. */
    TEST_EXPECT(ctx.rflo_subscribe_called);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_dispose(&ap));
    TEST_ASSERT(STATUS_SUCCESS == message_handler_dispose(&mh));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}

/**
 * Test that we can override the message handler.
 */
TEST(message_handler_override)
{
    abstract_parser ap;
    test_context ctx;
    test_context_override octx;
    message_handler mh, omh;
    event_handler eh;

    /* initialize the event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_handler_init(&eh, &dummy_event_callback, nullptr));

    /* initialize the message handler. */
    TEST_ASSERT(
        STATUS_SUCCESS == message_handler_init(&mh, &dummy_callback, &ctx));

    /* initialize the override message handler. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == message_handler_init(&omh, &dummy_callback_override, &octx));

    /* initialize the abstract parser. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_init(&ap, &mh));

    /* override the message handler. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == abstract_parser_message_handler_override(&octx.mh, &ap, &omh));

    /* precondition: no errors encountered. */
    TEST_EXPECT(!ctx.error);

    /* precondition: override_called is false. */
    TEST_ASSERT(!octx.override_called);

    /* precondition: run_called is false. */
    TEST_ASSERT(!ctx.run_called);

    /* call run. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_run(&ap));

    /* postcondition: no errors encountered. */
    TEST_EXPECT(!ctx.error);

    /* postcondition: override_called is true. */
    TEST_EXPECT(octx.override_called);

    /* postcondition: run_called is true. */
    TEST_EXPECT(ctx.run_called);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == abstract_parser_dispose(&ap));
    TEST_ASSERT(STATUS_SUCCESS == message_handler_dispose(&mh));
    TEST_ASSERT(STATUS_SUCCESS == message_handler_dispose(&omh));
    TEST_ASSERT(STATUS_SUCCESS == event_handler_dispose(&eh));
}
