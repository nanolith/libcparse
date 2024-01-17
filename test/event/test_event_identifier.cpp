/**
 * \file test/event/test_event_identifier.cpp
 *
 * \brief Tests for the \ref event_identifier type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/event/identifier.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_identifier;

TEST_SUITE(event_identifier);

/**
 * Test that we can create an identifier event.
 */
TEST(event_identifier_init)
{
    event_identifier ev;
    cursor c;
    const char* TEST_ID = "test";

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_identifier_init(&ev, &c, TEST_ID));

    /* get the base event type. */
    auto bev = event_identifier_upcast(&ev);

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == event_get_type(bev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_identifier_dispose(&ev));
}
