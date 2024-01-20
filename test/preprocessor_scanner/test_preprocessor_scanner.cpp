/**
 * \file test/preprocessor_scanner/test_preprocessor_scanner.cpp
 *
 * \brief Tests for the \ref preprocessor_scanner type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/preprocessor_scanner.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_preprocessor_scanner;

TEST_SUITE(preprocessor_scanner);

/**
 * Test that we can create and release a preprocessor scanner.
 */
TEST(create_release)
{
    preprocessor_scanner* scanner;

    /* we can create the scanner. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_create(&scanner));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == preprocessor_scanner_release(scanner));
}
