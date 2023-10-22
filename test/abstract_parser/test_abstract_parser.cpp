/**
 * \file test/abstract_parser/test_abstract_parser.cpp
 *
 * \brief Tests for the \ref abstract_parser type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/message_handler.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_message_handler;

TEST_SUITE(abstract_parser);

struct test_context
{
    bool run_called;
    bool push_input_stream_called;
    bool subscribe_called;
};

static int dummy_callback(void* context, const CPARSE_SYM(message)* ev)
{
    (void)context;
    (void)ev;

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
