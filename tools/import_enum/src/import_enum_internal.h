/**
 * \file tools/import_enum/src/import_enum_internal.h
 *
 * \brief Internal data structures and functions for the import_enum utility.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct import_enum_config import_enum_config;

struct import_enum_config
{
    char* input;
    char* output;
    char* enumeration;
    long count;
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

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
