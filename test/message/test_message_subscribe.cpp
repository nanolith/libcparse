/**
 * \file test/message/test_message_subscribe.cpp
 *
 * \brief Tests for the \ref message_subscribe type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message.h>
#include <libcparse/message/subscription.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

CPARSE_IMPORT_input_stream;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_message;
CPARSE_IMPORT_message_subscription;

TEST_SUITE(message_subscribe);

static int dummy_event_callback_fn(void* context, const CPARSE_SYM(event)* ev)
{
    (void)context;
    (void)ev;

    return STATUS_SUCCESS;
}

/**
 * Test the bascis of the message_subscribe type.
 */
TEST(basics)
{
    message_subscribe msg;
    event_handler handler;

    /* we can init the event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_handler_init(&handler, &dummy_event_callback_fn, nullptr));

    /* we can initialize the message. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == message_subscribe_init(
                    &msg, CPARSE_MESSAGE_TYPE_RSS_SUBSCRIBE, &handler));

    /* dispose the message. */
    TEST_ASSERT(STATUS_SUCCESS == message_subscribe_dispose(&msg));
}

/**
 * Get the event handler.
 */
TEST(event_handler_get)
{
    message_subscribe msg;
    event_handler handler;

    /* we can init the event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_handler_init(&handler, &dummy_event_callback_fn, nullptr));

    /* we can initialize the message. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == message_subscribe_init(
                    &msg, CPARSE_MESSAGE_TYPE_RSS_SUBSCRIBE, &handler));

    /* we can get the event handler. */
    TEST_EXPECT(nullptr != message_subscribe_event_handler_get(&msg));

    /* dispose the message. */
    TEST_ASSERT(STATUS_SUCCESS == message_subscribe_dispose(&msg));
}

/**
 *  Test that we can upcast and downcast a CPARSE_MESSAGE_TYPE_RSS_SUBSCRIBE
 *  message.
 */
TEST(upcast_downcast_CPARSE_MESSAGE_TYPE_RSS_SUBSCRIBE)
{
    message_subscribe msg;
    message* upcast_msg;
    message_subscribe* downcast_msg;
    event_handler handler;

    /* we can init the event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_handler_init(&handler, &dummy_event_callback_fn, nullptr));

    /* we can initialize the message. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == message_subscribe_init(
                    &msg, CPARSE_MESSAGE_TYPE_RSS_SUBSCRIBE, &handler));

    /* we can upcast the message. */
    upcast_msg = message_subscribe_upcast(&msg);
    TEST_ASSERT(NULL != upcast_msg);

    /* we can downcast the message. */
    TEST_ASSERT(
        STATUS_SUCCESS ==
            message_downcast_to_message_subscribe(&downcast_msg, upcast_msg));

    /* dispose the message. */
    TEST_ASSERT(STATUS_SUCCESS == message_subscribe_dispose(&msg));
}

/**
 *  Test that we can upcast and downcast a CPARSE_MESSAGE_TYPE_RFLO_SUBSCRIBE
 *  message.
 */
TEST(upcast_downcast_CPARSE_MESSAGE_TYPE_RFLO_SUBSCRIBE)
{
    message_subscribe msg;
    message* upcast_msg;
    message_subscribe* downcast_msg;
    event_handler handler;

    /* we can init the event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_handler_init(&handler, &dummy_event_callback_fn, nullptr));

    /* we can initialize the message. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == message_subscribe_init(
                    &msg, CPARSE_MESSAGE_TYPE_RFLO_SUBSCRIBE, &handler));

    /* we can upcast the message. */
    upcast_msg = message_subscribe_upcast(&msg);
    TEST_ASSERT(NULL != upcast_msg);

    /* we can downcast the message. */
    TEST_ASSERT(
        STATUS_SUCCESS ==
            message_downcast_to_message_subscribe(&downcast_msg, upcast_msg));

    /* dispose the message. */
    TEST_ASSERT(STATUS_SUCCESS == message_subscribe_dispose(&msg));
}

/**
 *  Test that we can upcast and downcast a
 *  CPARSE_MESSAGE_TYPE_COMMENT_SCANNER_SUBSCRIBE message.
 */
TEST(upcast_downcast_CPARSE_MESSAGE_TYPE_COMMENT_SCANNER_SUBSCRIBE)
{
    message_subscribe msg;
    message* upcast_msg;
    message_subscribe* downcast_msg;
    event_handler handler;

    /* we can init the event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_handler_init(&handler, &dummy_event_callback_fn, nullptr));

    /* we can initialize the message. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == message_subscribe_init_for_comment_scanner(&msg, &handler));

    /* we can upcast the message. */
    upcast_msg = message_subscribe_upcast(&msg);
    TEST_ASSERT(NULL != upcast_msg);

    /* we can downcast the message. */
    TEST_ASSERT(
        STATUS_SUCCESS ==
            message_downcast_to_message_subscribe(&downcast_msg, upcast_msg));

    /* dispose the message. */
    TEST_ASSERT(STATUS_SUCCESS == message_subscribe_dispose(&msg));
}

/**
 *  Test that we can upcast and downcast a
 *  CPARSE_MESSAGE_TYPE_COMMENT_FILTER_SUBSCRIBE message.
 */
TEST(upcast_downcast_CPARSE_MESSAGE_TYPE_COMMENT_FILTER_SUBSCRIBE)
{
    message_subscribe msg;
    message* upcast_msg;
    message_subscribe* downcast_msg;
    event_handler handler;

    /* we can init the event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_handler_init(&handler, &dummy_event_callback_fn, nullptr));

    /* we can initialize the message. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == message_subscribe_init_for_comment_filter(&msg, &handler));

    /* we can upcast the message. */
    upcast_msg = message_subscribe_upcast(&msg);
    TEST_ASSERT(NULL != upcast_msg);

    /* we can downcast the message. */
    TEST_ASSERT(
        STATUS_SUCCESS ==
            message_downcast_to_message_subscribe(&downcast_msg, upcast_msg));

    /* dispose the message. */
    TEST_ASSERT(STATUS_SUCCESS == message_subscribe_dispose(&msg));
}

/**
 *  Test that we can upcast and downcast a
 *  CPARSE_MESSAGE_TYPE_LINE_WRAP_FILTER_SUBSCRIBE message.
 */
TEST(upcast_downcast_CPARSE_MESSAGE_TYPE_LINE_WRAP_FILTER_SUBSCRIBE)
{
    message_subscribe msg;
    message* upcast_msg;
    message_subscribe* downcast_msg;
    event_handler handler;

    /* we can init the event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_handler_init(&handler, &dummy_event_callback_fn, nullptr));

    /* we can initialize the message. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == message_subscribe_init(
                    &msg, CPARSE_MESSAGE_TYPE_LINE_WRAP_FILTER_SUBSCRIBE,
                    &handler));

    /* we can upcast the message. */
    upcast_msg = message_subscribe_upcast(&msg);
    TEST_ASSERT(NULL != upcast_msg);

    /* we can downcast the message. */
    TEST_ASSERT(
        STATUS_SUCCESS ==
            message_downcast_to_message_subscribe(&downcast_msg, upcast_msg));

    /* dispose the message. */
    TEST_ASSERT(STATUS_SUCCESS == message_subscribe_dispose(&msg));
}

/**
 *  Test that we can upcast and downcast a
 *  CPARSE_MESSAGE_TYPE_NEWLINE_PRESERVING_WHITESPACE_FILTER_SUBSCRIBE message.
 */
TEST(upcast_downcast_CPARSE_MESSAGE_TYPE_NEWLINE_PRESERVING_WS_FILTER_SUB)
{
    message_subscribe msg;
    message* upcast_msg;
    message_subscribe* downcast_msg;
    event_handler handler;

    /* we can init the event handler. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_handler_init(&handler, &dummy_event_callback_fn, nullptr));

    /* we can initialize the message. */
    TEST_ASSERT(
      STATUS_SUCCESS
      == message_subscribe_init(
            &msg,
            CPARSE_MESSAGE_TYPE_NEWLINE_PRESERVING_WHITESPACE_FILTER_SUBSCRIBE,
            &handler));

    /* we can upcast the message. */
    upcast_msg = message_subscribe_upcast(&msg);
    TEST_ASSERT(NULL != upcast_msg);

    /* we can downcast the message. */
    TEST_ASSERT(
        STATUS_SUCCESS ==
            message_downcast_to_message_subscribe(&downcast_msg, upcast_msg));

    /* dispose the message. */
    TEST_ASSERT(STATUS_SUCCESS == message_subscribe_dispose(&msg));
}
