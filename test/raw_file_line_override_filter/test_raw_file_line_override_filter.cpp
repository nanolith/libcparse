/**
 * \file
 * test/raw_file_line_override_filter/test_raw_file_line_override_filter.cpp
 *
 * \brief Tests for the \ref raw_file_line_override_filter type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/raw_file_line_override_filter.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_raw_file_line_override_filter;

TEST_SUITE(raw_file_line_override_filter);

/**
 * Test that we can create and release a raw file line override filter.
 */
TEST(create_release)
{
    raw_file_line_override_filter* filter;

    /* we can create the raw_file_line_override_filter. */
    TEST_ASSERT(
        STATUS_SUCCESS == raw_file_line_override_filter_create(&filter));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == raw_file_line_override_filter_release(filter));
}
