/**
 * \file tools/import_enum/src/import_enum_internal.h
 *
 * \brief Internal data structures and functions for the import_enum utility.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/abstract_parser.h>
#include <libcparse/preprocessor_scanner.h>
#include <libcparse/preprocessor_scanner.h>
#include <stdio.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct import_enum_config import_enum_config;
typedef struct enum_item enum_item;

struct import_enum_config
{
    char* input;
    char* output;
    char* enumeration;
    long count;
    CPARSE_SYM(preprocessor_scanner)* scanner;
    CPARSE_SYM(abstract_parser)* ap;
    FILE* out;
    enum_item* head;
    char* enum_name;
};

struct enum_item
{
    enum_item* next;
    char* enum_name;
    long enum_value;
};

/**
 * \brief Read command-line options, creating an import_enum_config instance on
 * success.
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
int import_enum_config_create(
    import_enum_config** config, int* argc, char*** argv);

/**
 * \brief Release an import_enum_config instance.
 *
 * \param config        The instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int import_enum_config_release(import_enum_config* config);

/**
 * \brief Open input file and output file, creating the preprocessor scanner.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int create_scanner_and_files(import_enum_config* config);

/**
 * \brief Scan the input file, writing enumeration details to the output file.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int scan_input_and_write_output(import_enum_config* config);

/**
 * \brief Insert an enum item onto the enum list.
 *
 * \param config        The config instance for this operation.
 * \param name          The name of this enum item.
 * \param value         The value of this enum item.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int enum_item_list_insert(
    import_enum_config* config, const char* name, long value);

/**
 * \brief Reverse the enum item list, so it is ready for output.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int enum_item_list_reverse(import_enum_config* config);

/**
 * \brief Release an enum item.
 *
 * \param item          The enum item to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int enum_item_release(enum_item* item);

/**
 * \brief Release an enum item list.
 *
 * \param list          The enum item list to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int enum_item_list_release(enum_item* list);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
