/**
 * \file test/message/test_message.cpp
 *
 * \brief Tests for the \ref message type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

CPARSE_IMPORT_message;

TEST_SUITE(message);

/**
 * Test the basics of the message type.
 */
TEST(basics)
{
    message msg;
    const int MESSAGE_TYPE = 27;

    /* we can initialize the message. */
    TEST_ASSERT(STATUS_SUCCESS == message_init(&msg, MESSAGE_TYPE));

    /* we can get the message type. */
    TEST_ASSERT(MESSAGE_TYPE == message_get_type(&msg));

    /* we can dispose the message. */
    TEST_ASSERT(STATUS_SUCCESS == message_dispose(&msg));
}
