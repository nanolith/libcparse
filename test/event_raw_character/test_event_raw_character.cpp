/**
 * \file test/event_raw_character/test_event_raw_character.cpp
 *
 * \brief Tests for the \ref event_raw_character type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <cstring>
#include <libcparse/event/raw_character.h>
#include <libcparse/event_type.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event_raw_character;

TEST_SUITE(event_raw_character);

/**
 * Test that we can init and dispose an event_raw_character type.
 */
TEST(init_dispose)
{
    cursor pos;
    event_raw_character ev;
    const int TEST_CHAR = 'A';

    /* set up the position. */
    memset(&pos, 0, sizeof(pos));
    pos.file = "stdin";
    pos.begin_line = pos.end_line = 1;
    pos.begin_col = pos.end_col = 1;

    /* we can initialize the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_raw_character_init(
                    &ev, CPARSE_EVENT_TYPE_RAW_CHARACTER, &pos, TEST_CHAR));

    /* we can dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_character_dispose(&ev));
}

/**
 * Test that we can get the raw character value.
 */
TEST(get)
{
    cursor pos;
    event_raw_character ev;
    const int TEST_CHAR = 'A';

    /* set up the position. */
    memset(&pos, 0, sizeof(pos));
    pos.file = "stdin";
    pos.begin_line = pos.end_line = 1;
    pos.begin_col = pos.end_col = 1;

    /* init the event. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == event_raw_character_init(
                    &ev, CPARSE_EVENT_TYPE_RAW_CHARACTER, &pos, TEST_CHAR));

    /* the character value should match our constructor value. */
    TEST_EXPECT(TEST_CHAR == event_raw_character_get(&ev));

    /* dispose the event. */
    TEST_ASSERT(STATUS_SUCCESS == event_raw_character_dispose(&ev));
}
