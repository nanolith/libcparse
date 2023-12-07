/**
 * \file test/message/test_message.cpp
 *
 * \brief Tests for the \ref message type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message.h>
#include <libcparse/message/run.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

CPARSE_IMPORT_message;
CPARSE_IMPORT_message_run;

TEST_SUITE(message);

/**
 * Test the basics of the message type.
 */
TEST(basics)
{
    message_run msg;

    /* we can initialize the message. */
    TEST_ASSERT(STATUS_SUCCESS == message_run_init(&msg));

    /* we can upcast this to a message. */
    auto base = message_run_upcast(&msg);

    /* we can get the message type. */
    TEST_ASSERT(CPARSE_MESSAGE_TYPE_RUN == message_get_type(base));

    /* we can dispose the message. */
    TEST_ASSERT(STATUS_SUCCESS == message_run_dispose(&msg));
}
