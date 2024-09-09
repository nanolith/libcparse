/**
 * \file test/event/test_event_raw_character.cpp
 *
 * \brief Tests for the \ref event_raw_character type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_raw_character;

TEST_SUITE(event_raw_character);

/**
 * Test that we can create a raw character event.
 */
TEST(event_raw_character_init)
{
    event_raw_character ev;
    cursor c;
    const int ch = 'x';

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_raw_character_init(&ev, &c, ch));

    /* get the base event type. */
    auto bev = event_raw_character_upcast(&ev);

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_RAW_CHARACTER == event_get_type(bev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_character_dispose(&ev));
}

/**
 * Test that we can get the raw character value of this event.
 */
TEST(event_raw_character_get)
{
    event_raw_character ev;
    cursor c;
    const int ch = 'x';

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_raw_character_init(&ev, &c, ch));

    /* get the raw character value. */
    int gc = event_raw_character_get(&ev);

    /* this value matches our test value. */
    TEST_EXPECT(ch == gc);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_character_dispose(&ev));
}

/**
 * Test that we can downcast a raw character event.
 */
TEST(event_downcast_to_event_raw_character)
{
    event_raw_character ev;
    event_raw_character* ev2;
    cursor c;
    const int ch = 'x';

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_raw_character_init(&ev, &c, ch));

    /* get the base event type. */
    auto bev = event_raw_character_upcast(&ev);

    /* attempt to downcast this event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_downcast_to_event_raw_character(&ev2, bev));

    /* these events should match. */
    TEST_EXPECT(ev2 == &ev);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_character_dispose(&ev));
}
