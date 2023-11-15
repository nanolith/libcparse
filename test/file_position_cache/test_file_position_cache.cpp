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
#include <string.h>

using namespace std;

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_file_position_cache;

TEST_SUITE(file_position_cache);

/**
 * Test that we can create and release a file position cache.
 */
TEST(create_release)
{
    file_position_cache* cache;

    /* we can create the file_position_cache. */
    TEST_ASSERT(
        STATUS_SUCCESS == file_position_cache_create(&cache));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == file_position_cache_release(cache));
}

/**
 * Test that if the cache is not set, then we get an error trying to retrieve
 * the file and position.
 */
TEST(cache_not_set_error)
{
    file_position_cache* cache;
    const char* file = nullptr;
    const cursor* pos = nullptr;

    /* we can create the file_position_cache. */
    TEST_ASSERT(
        STATUS_SUCCESS == file_position_cache_create(&cache));

    /* getting the file fails because the cache is not set. */
    TEST_EXPECT(
        ERROR_LIBCPARSE_FILE_POSITION_CACHE_NOT_SET
            == file_position_cache_file_get(cache, &file));

    /* getting the position fails because the cache is not set. */
    TEST_EXPECT(
        ERROR_LIBCPARSE_FILE_POSITION_CACHE_NOT_SET
            == file_position_cache_position_get(cache, &pos));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == file_position_cache_release(cache));
}

/**
 * Test that if we set the cache, we can retrieve the file and position.
 */
TEST(cache_set)
{
    const char* EXPECTED_FILE = "testfile";
    cursor EXPECTED_CURSOR;
    file_position_cache* cache;
    const char* file = nullptr;
    const cursor* pos = nullptr;

    /* initialize the expected cursor. */
    EXPECTED_CURSOR.file = EXPECTED_FILE;
    EXPECTED_CURSOR.begin_line = 10;
    EXPECTED_CURSOR.begin_col = 2;
    EXPECTED_CURSOR.end_line = 12;
    EXPECTED_CURSOR.end_col = 16;

    /* we can create the file_position_cache. */
    TEST_ASSERT(
        STATUS_SUCCESS == file_position_cache_create(&cache));

    /* Setting the cache should succeed. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == file_position_cache_set(cache, EXPECTED_FILE, &EXPECTED_CURSOR));

    /* getting the file succeeds. */
    TEST_ASSERT(STATUS_SUCCESS == file_position_cache_file_get(cache, &file));

    /* the file is not NULL. */
    TEST_ASSERT(nullptr != file);

    /* the file matches our expected file. */
    TEST_EXPECT(!strcmp(file, EXPECTED_FILE));

    /* getting the position succeeds. */
    TEST_ASSERT(
        STATUS_SUCCESS == file_position_cache_position_get(cache, &pos));

    /* the position is not NULL. */
    TEST_ASSERT(nullptr != pos);

    /* the position matches our expected position. */
    TEST_ASSERT(nullptr != pos->file);
    TEST_EXPECT(!strcmp(pos->file, EXPECTED_CURSOR.file));
    TEST_EXPECT(pos->begin_line == EXPECTED_CURSOR.begin_line);
    TEST_EXPECT(pos->begin_col == EXPECTED_CURSOR.begin_col);
    TEST_EXPECT(pos->end_line == EXPECTED_CURSOR.end_line);
    TEST_EXPECT(pos->end_col == EXPECTED_CURSOR.end_col);

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == file_position_cache_release(cache));
}

/**
 * Test that setting the cache twice results in an error.
 */
TEST(cache_set_twice_error)
{
    const char* EXPECTED_FILE = "testfile";
    cursor EXPECTED_CURSOR;
    file_position_cache* cache;

    /* initialize the expected cursor. */
    EXPECTED_CURSOR.file = EXPECTED_FILE;
    EXPECTED_CURSOR.begin_line = 10;
    EXPECTED_CURSOR.begin_col = 2;
    EXPECTED_CURSOR.end_line = 12;
    EXPECTED_CURSOR.end_col = 16;

    /* we can create the file_position_cache. */
    TEST_ASSERT(
        STATUS_SUCCESS == file_position_cache_create(&cache));

    /* Setting the cache should succeed. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == file_position_cache_set(cache, EXPECTED_FILE, &EXPECTED_CURSOR));

    /* Setting the cache a second time should fail. */
    TEST_ASSERT(
        ERROR_LIBCPARSE_FILE_POSITION_CACHE_ALREADY_SET
            == file_position_cache_set(cache, EXPECTED_FILE, &EXPECTED_CURSOR));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == file_position_cache_release(cache));
}

/**
 * Test that if we set the cache and clear it, retrieving the file and position
 * will fail.
 */
TEST(cache_set_clear)
{
    const char* EXPECTED_FILE = "testfile";
    cursor EXPECTED_CURSOR;
    file_position_cache* cache;
    const char* file = nullptr;
    const cursor* pos = nullptr;

    /* initialize the expected cursor. */
    EXPECTED_CURSOR.file = EXPECTED_FILE;
    EXPECTED_CURSOR.begin_line = 10;
    EXPECTED_CURSOR.begin_col = 2;
    EXPECTED_CURSOR.end_line = 12;
    EXPECTED_CURSOR.end_col = 16;

    /* we can create the file_position_cache. */
    TEST_ASSERT(
        STATUS_SUCCESS == file_position_cache_create(&cache));

    /* Setting the cache should succeed. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == file_position_cache_set(cache, EXPECTED_FILE, &EXPECTED_CURSOR));

    /* Clear the cache. */
    file_position_cache_clear(cache);

    /* getting the file fails because the cache is not set. */
    TEST_EXPECT(
        ERROR_LIBCPARSE_FILE_POSITION_CACHE_NOT_SET
            == file_position_cache_file_get(cache, &file));

    /* getting the position fails because the cache is not set. */
    TEST_EXPECT(
        ERROR_LIBCPARSE_FILE_POSITION_CACHE_NOT_SET
            == file_position_cache_position_get(cache, &pos));

    /* clean up. */
    TEST_ASSERT(
        STATUS_SUCCESS == file_position_cache_release(cache));
}
