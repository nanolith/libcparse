/**
 * \file test/event_copy/test_event_copy.cpp
 *
 * \brief Tests for the \ref event_copy type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event_copy.h>
#include <libcparse/status_codes.h>
#include <minunit/minunit.h>
#include <string.h>

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_copy;

TEST_SUITE(event_copy);

static const char* TESTFILE = "test.c";

#define EVENT_BASE_COPY_TEST(ctor) \
    TEST(ctor) \
    { \
        event ev; \
        cursor c; \
        event_copy* cpy; \
        const event* clone; \
        const cursor* clone_c; \
        \
        memset(&c, 0, sizeof(c)); \
        c.begin_line = 23; \
        c.end_line = 24; \
        c.begin_col = 1; \
        c.end_col = 5; \
        c.file = TESTFILE; \
        \
        TEST_ASSERT(STATUS_SUCCESS == ctor(&ev, &c)); \
        TEST_ASSERT(STATUS_SUCCESS == event_copy_create(&cpy, &ev)); \
        \
        clone = event_copy_get_event(cpy); \
        TEST_ASSERT(NULL != clone); \
        \
        TEST_EXPECT(event_get_type(&ev) == event_get_type(clone)); \
        \
        clone_c = event_get_cursor(clone); \
        TEST_ASSERT(NULL != clone_c); \
        TEST_EXPECT(clone_c->begin_line == c.begin_line); \
        TEST_EXPECT(clone_c->end_line == c.end_line); \
        TEST_EXPECT(clone_c->begin_col == c.begin_col); \
        TEST_EXPECT(clone_c->end_col == c.end_col); \
        TEST_ASSERT(NULL != clone_c->file); \
        TEST_EXPECT(!strcmp(c.file, clone_c->file)); \
        \
        TEST_ASSERT(STATUS_SUCCESS == event_copy_release(cpy)); \
        TEST_ASSERT(STATUS_SUCCESS == event_dispose(&ev)); \
    }

EVENT_BASE_COPY_TEST(event_init_for_eof);
EVENT_BASE_COPY_TEST(event_init_for_whitespace_token);
EVENT_BASE_COPY_TEST(event_init_for_newline_token);
EVENT_BASE_COPY_TEST(event_init_for_comment_block_begin);
EVENT_BASE_COPY_TEST(event_init_for_comment_block_end);
EVENT_BASE_COPY_TEST(event_init_for_comment_line_begin);
EVENT_BASE_COPY_TEST(event_init_for_comment_line_end);
EVENT_BASE_COPY_TEST(event_init_for_token_left_paren);
EVENT_BASE_COPY_TEST(event_init_for_token_right_paren);
EVENT_BASE_COPY_TEST(event_init_for_token_left_brace);
EVENT_BASE_COPY_TEST(event_init_for_token_right_brace);
