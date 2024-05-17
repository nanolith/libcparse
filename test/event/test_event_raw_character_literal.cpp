/**
 * \file test/event/test_event_raw_character_literal.cpp
 *
 * \brief Tests for the \ref event_raw_character_literal type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/event/raw_character_literal.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_raw_character_literal;

TEST_SUITE(event_raw_character_literal);

/**
 * Test that we can create a raw character literal value event.
 */
TEST(event_raw_character_literal_init)
{
    event_raw_character_literal ev;
    cursor c;
    const char* TEST_STRING = "'x'";

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_raw_character_literal_init(&ev, &c, TEST_STRING));

    /* get the base event type. */
    auto bev = event_raw_character_literal_upcast(&ev);

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_CHARACTER == event_get_type(bev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_character_literal_dispose(&ev));
}

/**
 * Test that we can get the raw character value of this event.
 */
TEST(event_raw_character_literal_get)
{
    event_raw_character_literal ev;
    cursor c;
    const char* TEST_STRING = "'x'";

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_raw_character_literal_init(&ev, &c, TEST_STRING));

    auto str = event_raw_character_literal_get(&ev);

    /* this value is not NULL. */
    TEST_ASSERT(nullptr != str);

    /* this value matches our test string. */
    TEST_EXPECT(!strcmp(str, TEST_STRING));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_character_literal_dispose(&ev));
}
