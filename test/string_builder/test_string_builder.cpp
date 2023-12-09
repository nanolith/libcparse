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

/**
 * Test that we can add characters to a string.
 */
TEST(add_character)
{
    string_builder* builder;
    char* str = nullptr;

    /* we can create the string_builder. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_create(&builder));

    /* add characters to the string. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_add_character(builder, 'A'));
    TEST_ASSERT(STATUS_SUCCESS == string_builder_add_character(builder, 'B'));
    TEST_ASSERT(STATUS_SUCCESS == string_builder_add_character(builder, 'C'));
    TEST_ASSERT(STATUS_SUCCESS == string_builder_add_character(builder, 'D'));
    TEST_ASSERT(STATUS_SUCCESS == string_builder_add_character(builder, 'E'));
    TEST_ASSERT(STATUS_SUCCESS == string_builder_add_character(builder, 'F'));
    TEST_ASSERT(STATUS_SUCCESS == string_builder_add_character(builder, 'G'));

    /* we can build a string. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_build(&str, builder));

    /* This string is not NULL. */
    TEST_ASSERT(nullptr != str);

    /* This string matches our characters. */
    TEST_EXPECT(!strcmp(str, "ABCDEFG"));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_release(builder));
    free(str);
}

/**
 * Test that we can add strings to a string.
 */
TEST(add_strings)
{
    string_builder* builder;
    char* str = nullptr;

    /* we can create the string_builder. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_create(&builder));

    /* add characters to the string. */
    TEST_ASSERT(
        STATUS_SUCCESS == string_builder_add_string(builder, "Hello, "));
    TEST_ASSERT(
        STATUS_SUCCESS == string_builder_add_string(builder, "World!"));

    /* we can build a string. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_build(&str, builder));

    /* This string is not NULL. */
    TEST_ASSERT(nullptr != str);

    /* This string matches our characters. */
    TEST_EXPECT(!strcmp(str, "Hello, World!"));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_release(builder));
    free(str);
}

/**
 * Test that we can add 1024 As to the builder.
 */
TEST(A1024)
{
    string_builder* builder;
    char* str = nullptr;

    /* we can create the string_builder. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_create(&builder));

    for (int i = 0; i < 1024; ++i)
    {
        TEST_ASSERT(
            STATUS_SUCCESS == string_builder_add_character(builder, 'A'));
    }

    /* we can build a string. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_build(&str, builder));

    /* This string is not NULL. */
    TEST_ASSERT(nullptr != str);

    /* This string matches our characters. */
    char* tmp = str;
    for (int i = 0; i < 1024; ++i)
    {
        TEST_EXPECT('A' == *tmp);
        ++tmp;
    }

    /* the string is terminated with an ASCII zero. */
    TEST_EXPECT(0 == *tmp);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_release(builder));
    free(str);
}

/**
 * Test that we can clear a builder to reset its state.
*/
TEST(clear)
{
    string_builder* builder;
    char* str = nullptr;

    /* we can create the string_builder. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_create(&builder));

    /* add a dummy string. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_add_string(builder, "Dummy"));

    /* clear the builder. */
    string_builder_clear(builder);

    /* Build a string. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_build(&str, builder));

    /* The string is not NULL. */
    TEST_ASSERT(nullptr != str);

    /* The string is empty. */
    TEST_EXPECT(!strcmp(str, ""));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == string_builder_release(builder));
    free(str);
}
