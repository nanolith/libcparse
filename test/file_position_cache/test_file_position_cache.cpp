/**
 * \file test/file_position_cache/test_file_position_cache.cpp
 *
 * \brief Tests for the \ref file_position_cache type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/file_position_cache.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_file_position_cache;

TEST_SUITE(file_position_cache);

/**
 * Test that we can create and release a file position cache.
 */
TEST(create_release)
{
    file_position_cache* cache;

    /* we can create the comment_filter. */
    TEST_ASSERT(
        STATUS_SUCCESS == file_position_cache_create(&cache));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == file_position_cache_release(cache));
}
