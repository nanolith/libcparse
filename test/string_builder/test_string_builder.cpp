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
#include <stdlib.h>
#include <string.h>

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

/**
 * Test that an empty string builder builds an empty string.
 */
TEST(empty_string_builder)
{
    string_builder* builder;
    char* str = nullptr;

    /* we can create the string_builder. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_create(&builder));

    /* we can build an empty string. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_build(&str, builder));

    /* This string is not NULL. */
    TEST_ASSERT(nullptr != str);

    /* This string is empty. */
    TEST_EXPECT(!strcmp(str, ""));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_release(builder));
    free(str);
}
