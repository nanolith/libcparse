/**
 * \file
 * test/newline_preserving_whitespace_filter/test_newline_preserving_whitespace_filter.cpp
 *
 * \brief Tests for the \ref newline_preserving_whitespace_filter type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/newline_preserving_whitespace_filter.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_newline_preserving_whitespace_filter;

TEST_SUITE(newline_preserving_whitespace_filter);

/**
 * Test that we can create and release a newline preserving whitespace filter.
 */
TEST(create_release)
{
    newline_preserving_whitespace_filter* filter;

    /* we can create the filter. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_create(&filter));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == newline_preserving_whitespace_filter_release(filter));
}
