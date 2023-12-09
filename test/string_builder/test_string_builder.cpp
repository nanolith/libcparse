/**
 * \file * test/string_builder/test_string_builder.cpp
 *
 * \brief Tests for the \ref string_builder type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <libcparse/string_builder.h>
#include <minunit/minunit.h>

using namespace std;

CPARSE_IMPORT_string_builder;

TEST_SUITE(string_builder);

/**
 * Test that we can create and release a string builder.
 */
TEST(create_release)
{
    string_builder* builder;

    /* we can create the string_builder. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_create(&builder));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_release(builder));
}
