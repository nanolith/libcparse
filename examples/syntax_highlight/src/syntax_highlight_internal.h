/**
 * \file examples/syntaxn_highlight/src/syntax_highlight_internal.h
 *
 * \brief Internal data structures and functions for the syntax_highlight
 * utility.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/abstract_parser.h>
#include <libcparse/cursor.h>
#include <libcparse/preprocessor_scanner.h>
#include <libcparse/preprocessor_scanner.h>
#include <stdio.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct syntax_highlight_config syntax_highlight_config;
typedef struct source_line source_line;

struct syntax_highlight_config
{
    char* input;
    char* output;
    int state;
    CPARSE_SYM(preprocessor_scanner)* scanner;
    CPARSE_SYM(abstract_parser)* ap;
    char* input_string;
    FILE* out;
    long count;
    source_line* head;
    long snip_begin;
    long snip_end;
};

struct source_line
{
    source_line* next;
    size_t length;
    char* line;
    int* highlight_line;
};

enum highlight_type
{
    HIGHLIGHT_TYPE_NORMAL = 0,
    HIGHLIGHT_TYPE_COMMENT = 1,
    HIGHLIGHT_TYPE_PREPROCESSOR = 2,
    HIGHLIGHT_TYPE_TYPE = 3,
    HIGHLIGHT_TYPE_CHAR_LITERAL = 4,
    HIGHLIGHT_TYPE_STRING = 5,
    HIGHLIGHT_TYPE_NUMBER = 6,
};

/**
 * \brief Read command-line options, creating a syntax_highlight_config instance
 * on success.
 *
 * \param config        Pointer to the config pointer to populate with the
 *                      created config on success.
 * \param argc          Pointer to argc, to be updated on success.
 * \param argv          Pointer to argv, to be updated on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int syntax_highlight_config_create(
    syntax_highlight_config** config, int* argc, char*** argv);

/**
 * \brief Release a syntax_highlight_config instance.
 *
 * \param config        The instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int syntax_highlight_config_release(syntax_highlight_config* config);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
