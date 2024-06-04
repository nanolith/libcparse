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
#include <stdbool.h>
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
    size_t count;
    source_line* head;
    source_line** lines;
    long snip_begin;
    long snip_end;
    bool debug;
    CPARSE_SYM(cursor) comment_scanner_pos;
    CPARSE_SYM(cursor) preprocessor_scanner_pos;
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
    HIGHLIGHT_TYPE_KEYWORD = 7,
    HIGHLIGHT_TYPE_MODIFIER = 8,
    HIGHLIGHT_TYPE_LABEL = 9,
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

/**
 * \brief Open input file and read input file into an input string and source
 * lines.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int syntax_highlight_read_input(syntax_highlight_config* config);

/**
 * \brief Create scanner and output file.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int syntax_highlight_create_scanner_and_output(syntax_highlight_config* config);

/**
 * \brief Scan the input file, writing HTML markup to the output file.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int scan_input_and_write_output(syntax_highlight_config* config);

/**
 * \brief Insert a line into the source list.
 *
 * \param config        The config instance for this operation.
 * \param line          The line to insert. It is copied.
 * \param size          The size of the line in bytes.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int source_list_insert(
    syntax_highlight_config* config, const char* line, size_t size);

/**
 * \brief Reverse the source list.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int source_list_reverse(syntax_highlight_config* config);

/**
 * \brief Release a source line.
 *
 * \param line          The source line to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int source_line_release(source_line* line);

/**
 * \brief Release a source list.
 *
 * \param list          The source list to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int source_list_release(source_line* list);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
