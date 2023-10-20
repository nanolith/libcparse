/**
 * \file test/raw_stack_scanner/test_raw_stack_scanner.cpp
 *
 * \brief Tests for the \ref raw_stack_scanner type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/raw_stack_scanner.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>

CPARSE_IMPORT_raw_stack_scanner;

TEST_SUITE(raw_stack_scanner);

/**
 * Test that we can create and release a raw stack scanner.
 */
TEST(create_release)
{
    raw_stack_scanner* scanner;

    /* we can create the raw_stack_scanner. */
    TEST_ASSERT(STATUS_SUCCESS == raw_stack_scanner_create(&scanner));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == raw_stack_scanner_release(scanner));
}
