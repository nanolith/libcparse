/**
 * \file test/comment_scanner/test_comment_scanner.cpp
 *
 * \brief Tests for the \ref comment_scanner type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/comment_scanner.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_comment_scanner;

TEST_SUITE(comment_scanner);

/**
 * Test that we can create and release a comment scanner.
 */
TEST(create_release)
{
    comment_scanner* scanner;

    /* we can create the comment_scanner. */
    TEST_ASSERT(
        STATUS_SUCCESS == comment_scanner_create(&scanner));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == comment_scanner_release(scanner));
}
