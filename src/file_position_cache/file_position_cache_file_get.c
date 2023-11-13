/**
 * \file file_position_cache/file_position_cache_file_get.c
 *
 * \brief Get the cached file.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stddef.h>

#include "file_position_cache_internal.h"

/**
 * \brief Get the cached file.
 *
 * \param cache             The \ref file_position_cache instance for this
 *                          operation.
 * \param file              The file pointer pointer to receive this file on
 *                          success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_file_get)(
    CPARSE_SYM(file_position_cache)* cache, const char** file)
{
    if (NULL == cache->file)
    {
        return ERROR_LIBCPARSE_FILE_POSITION_CACHE_NOT_SET;
    }

    /* set the file return parameter. */
    *file = cache->file;

    /* success. */
    return STATUS_SUCCESS;
}
