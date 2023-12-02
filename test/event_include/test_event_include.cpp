/**
 * \file test/event_include/test_event_include.cpp
 *
 * \brief Tests for the \ref event_include type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <cstring>
#include <libcparse/event/include.h>
#include <libcparse/event_type.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event_include;

TEST_SUITE(event_include);

/**
 * Test that we can init and dispose an event_include type.
 */
TEST(init_dispose)
{
    cursor pos;
    event_include ev;
    const char* TEST_FILE = "stdio.h";

    /* set up the position. */
    memset(&pos, 0, sizeof(pos));
    pos.file = "stdin";
    pos.begin_line = pos.end_line = 1;
    pos.begin_col = pos.end_col = 1;

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_include_init(
                    &ev, CPARSE_EVENT_TYPE_PREPROCESSOR_SYSTEM_INCLUDE, &pos,
                    TEST_FILE));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_include_dispose(&ev));
}

/**
 * Test that we can get the file value.
 */
TEST(get)
{
    cursor pos;
    event_include ev;
    const char* TEST_FILE = "stdio.h";

    /* set up the position. */
    memset(&pos, 0, sizeof(pos));
    pos.file = "stdin";
    pos.begin_line = pos.end_line = 1;
    pos.begin_col = pos.end_col = 1;

    /* init the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_include_init(
                    &ev, CPARSE_EVENT_TYPE_PREPROCESSOR_SYSTEM_INCLUDE, &pos,
                    TEST_FILE));

    /* the file should match our constructor value. */
    TEST_EXPECT(!strcmp(TEST_FILE, event_include_file_get(&ev)));

    /* dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_include_dispose(&ev));
}

/**
 * Test that we can upcast and downcast a system include event.
 */
TEST(upcast_downcast_system_include)
{
    cursor pos;
    event_include ev;
    event_include* iev;
    const char* TEST_FILE = "stdio.h";

    /* set up the position. */
    memset(&pos, 0, sizeof(pos));
    pos.file = "stdin";
    pos.begin_line = pos.end_line = 1;
    pos.begin_col = pos.end_col = 1;

    /* init the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_include_init(
                    &ev, CPARSE_EVENT_TYPE_PREPROCESSOR_SYSTEM_INCLUDE, &pos,
                    TEST_FILE));

    /* upcast the event. */
    auto oev = event_include_upcast(&ev);

    /* this value is not NULL. */
    TEST_ASSERT(nullptr != oev);

    /* we can downcast this event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_downcast_to_event_include(&iev, oev));

    /* dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_include_dispose(&ev));
}

/**
 * Test that we can upcast and downcast a local include event.
 */
TEST(upcast_downcast_local_include)
{
    cursor pos;
    event_include ev;
    event_include* iev;
    const char* TEST_FILE = "stdio.h";

    /* set up the position. */
    memset(&pos, 0, sizeof(pos));
    pos.file = "stdin";
    pos.begin_line = pos.end_line = 1;
    pos.begin_col = pos.end_col = 1;

    /* init the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_include_init(
                    &ev, CPARSE_EVENT_TYPE_PREPROCESSOR_LOCAL_INCLUDE, &pos,
                    TEST_FILE));

    /* upcast the event. */
    auto oev = event_include_upcast(&ev);

    /* this value is not NULL. */
    TEST_ASSERT(nullptr != oev);

    /* we can downcast this event. */
    TEST_ASSERT(
        STATUS_SUCCESS == event_downcast_to_event_include(&iev, oev));

    /* dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_include_dispose(&ev));
}
