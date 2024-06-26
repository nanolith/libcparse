/**
 * \file test/event/test_event_raw_string_token.cpp
 *
 * \brief Tests for the \ref event_raw_string_token type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/event/raw_string.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_raw_string;

TEST_SUITE(event_raw_string_token);

/**
 * Test that we can create a raw string token value event.
 */
TEST(event_raw_string_token_init)
{
    event_raw_string_token ev;
    cursor c;
    const char* TEST_STRING = "test";

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_raw_string_token_init(&ev, &c, TEST_STRING));

    /* get the base event type. */
    auto bev = event_raw_string_token_upcast(&ev);

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == event_get_type(bev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_string_token_dispose(&ev));
}

/**
 * Test that we can create a raw system string token value event.
 */
TEST(event_raw_string_token_init_for_system_string)
{
    event_raw_string_token ev;
    cursor c;
    const char* TEST_STRING = "test";

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_raw_string_token_init_for_system_string(
                    &ev, &c, TEST_STRING));

    /* get the base event type. */
    auto bev = event_raw_string_token_upcast(&ev);

    /* The event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_SYSTEM_STRING == event_get_type(bev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_string_token_dispose(&ev));
}

/**
 * Test that we can get the string value of this event.
 */
TEST(event_raw_string_token_get)
{
    event_raw_string_token ev;
    cursor c;
    const char* TEST_STRING = "test";

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_raw_string_token_init(&ev, &c, TEST_STRING));

    auto str = event_raw_string_token_get(&ev);

    /* this value is not NULL. */
    TEST_ASSERT(nullptr != str);

    /* this value matches our test string. */
    TEST_EXPECT(!strcmp(str, TEST_STRING));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_string_token_dispose(&ev));
}

/**
 * Test that we can downcast a raw string event.
 */
TEST(event_downcast_to_event_raw_string_token)
{
    event_raw_string_token ev;
    event_raw_string_token* ev2;
    cursor c;
    const char* TEST_STRING = "test";

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_raw_string_token_init(&ev, &c, TEST_STRING));

    /* get the base event type. */
    auto bev = event_raw_string_token_upcast(&ev);

    /* attempt to downcast this event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_downcast_to_event_raw_string_token(&ev2, bev));

    /* this value should match our original event pointer. */
    TEST_EXPECT(ev2 == &ev);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_string_token_dispose(&ev));
}

/**
 * Test that we can downcast a raw system string event.
 */
TEST(event_downcast_to_event_raw_system_string_token)
{
    event_raw_string_token ev;
    event_raw_string_token* ev2;
    cursor c;
    const char* TEST_STRING = "test";

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* Initialize an event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_raw_string_token_init_for_system_string(
            &ev, &c, TEST_STRING));

    /* get the base event type. */
    auto bev = event_raw_string_token_upcast(&ev);

    /* attempt to downcast this event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_downcast_to_event_raw_string_token(&ev2, bev));

    /* this value should match our original event pointer. */
    TEST_EXPECT(ev2 == &ev);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_string_token_dispose(&ev));
}
