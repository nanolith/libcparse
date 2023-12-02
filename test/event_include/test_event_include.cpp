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
