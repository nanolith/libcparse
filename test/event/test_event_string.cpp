/**
 * \file test/event/test_event_string.cpp
 *
 * \brief Tests for the \ref event_string type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/event/string.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_string;

TEST_SUITE(event_string);

/**
 * Test that we can create a string value event.
 */
TEST(event_string_init)
{
    event_string ev;
    cursor c;
    const char* TEST_STRING = "test";

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_string_init(&ev, &c, TEST_STRING));

    /* get the base event type. */
    auto bev = event_string_upcast(&ev);

    /* The event type is correct. */
    TEST_EXPECT(CPARSE_EVENT_TYPE_TOKEN_VALUE_STRING == event_get_type(bev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_string_dispose(&ev));
}

/**
 * Test that we can create a system string value event.
 */
TEST(event_string_init_for_system_string)
{
    event_string ev;
    cursor c;
    const char* TEST_STRING = "test";

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_string_init_for_system_string(&ev, &c, TEST_STRING));

    /* get the base event type. */
    auto bev = event_string_upcast(&ev);

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_VALUE_SYSTEM_STRING == event_get_type(bev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_string_dispose(&ev));
}

/**
 * Test that we can get the string value of this event.
 */
TEST(event_string_get)
{
    event_string ev;
    cursor c;
    const char* TEST_STRING = "test";

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_string_init(&ev, &c, TEST_STRING));

    auto str = event_string_get(&ev);

    /* this value is not NULL. */
    TEST_ASSERT(nullptr != str);

    /* this value matches our test string. */
    TEST_EXPECT(!strcmp(str, TEST_STRING));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_string_dispose(&ev));
}

/**
 * Test that we can downcast a string event.
 */
TEST(event_downcast_to_event_string)
{
    event_string ev;
    event_string* ev2;
    cursor c;
    const char* TEST_STRING = "test";

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(STATUS_SUCCESS == event_string_init(&ev, &c, TEST_STRING));

    /* get the base event type. */
    auto bev = event_string_upcast(&ev);

    /* attempt to downcast this event. */
    TEST_ASSERT(STATUS_SUCCESS == event_downcast_to_event_string(&ev2, bev));

    /* this value should match our original event pointer. */
    TEST_EXPECT(ev2 == &ev);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_string_dispose(&ev));
}

/**
 * Test that we can downcast a system string event.
 */
TEST(event_downcast_to_event_system_string)
{
    event_string ev;
    event_string* ev2;
    cursor c;
    const char* TEST_STRING = "test";

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_string_init_for_system_string(&ev, &c, TEST_STRING));

    /* get the base event type. */
    auto bev = event_string_upcast(&ev);

    /* attempt to downcast this event. */
    TEST_ASSERT(STATUS_SUCCESS == event_downcast_to_event_string(&ev2, bev));

    /* this value should match our original event pointer. */
    TEST_EXPECT(ev2 == &ev);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_string_dispose(&ev));
}
