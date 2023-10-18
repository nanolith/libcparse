/**
 * \file test/event_event_reactor/test_event_reactor.cpp
 *
 * \brief Tests for the \ref event_reactor type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_reactor.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

CPARSE_IMPORT_event_reactor;

TEST_SUITE(event_reactor);

/**
 * Test the basics of the event_reactor type.
 */
TEST(basics)
{
    event_reactor* er;

    /* we can create the event_reactor. */
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_create(&er));

    /* we can release the event_reactor. */
    TEST_ASSERT(STATUS_SUCCESS == event_reactor_release(er));
}
