/**
 * \file test/comment_filter/test_comment_filter.cpp
 *
 * \brief Tests for the \ref comment_filter type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/comment_filter.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

using namespace std;

TEST_SUITE(comment_filter);

CPARSE_IMPORT_comment_filter;

/**
 * Test that we can create and release a comment filter.
 */
TEST(create_release)
{
    comment_filter* filter;

    /* we can create the comment_filter. */
    TEST_ASSERT(
        STATUS_SUCCESS == comment_filter_create(&filter));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == comment_filter_release(filter));
}
