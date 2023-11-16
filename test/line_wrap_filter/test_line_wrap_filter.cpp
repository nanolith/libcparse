/**
 * \file test/line_wrap_filter/test_line_wrap_filter.cpp
 *
 * \brief Tests for the \ref line_wrap_filter type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/line_wrap_filter.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_line_wrap_filter;

TEST_SUITE(line_wrap_filter);

/**
 * Test that we can create and release a line wrap filter.
 */
TEST(create_release)
{
    line_wrap_filter* filter;

    /* we can create a line_wrap_filter. */
    TEST_ASSERT(STATUS_SUCCESS == line_wrap_filter_create(&filter));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == line_wrap_filter_release(filter));
}
