/**
 * \file test/event/test_event_include.cpp
 *
 * \brief Tests for the \ref event_include type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/event/include.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

#include "../../src/event/event_internal.h"

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_internal;
CPARSE_IMPORT_event_include;

TEST_SUITE(event_include);

/**
 * Test that we can create a system include event.
 */
TEST(event_system_include_init)
{
    event_include ev;
    cursor c;
    const char* file = "stdio.h";

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_include_init_for_system_include(&ev, &c, file));

    /* get the base event type. */
    auto bev = event_include_upcast(&ev);

    /* the event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_PREPROCESSOR_SYSTEM_INCLUDE == event_get_type(bev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_include_dispose(&ev));
}

/**
 * Test that we can create a local include event.
 */
TEST(event_local_include_init)
{
    event_include ev;
    cursor c;
    const char* file = "localheader.h";

    /* clear the cursor. */
    memset(&c, 0, sizeof(c));

    /* initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_include_init_for_local_include(&ev, &c, file));

    /* get the base event type. */
    auto bev = event_include_upcast(&ev);

    /* the event type is correct. */
    TEST_EXPECT(
        CPARSE_EVENT_TYPE_PREPROCESSOR_LOCAL_INCLUDE == event_get_type(bev));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == event_include_dispose(&ev));
}
