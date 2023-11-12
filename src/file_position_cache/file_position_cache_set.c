/**
 * \file file_position_cache/file_position_cache_set.c
 *
 * \brief Set the \ref file_position_cache.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "file_position_cache_internal.h"

/**
 * \brief Set the \ref file_position_cache file and position.
 *
 * \param cache             The \ref file_position_cache instance for this
 *                          operation.
 * \param file              The file to cache.
 * \param position          The position to cache.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_set)(
    CPARSE_SYM(file_position_cache)* cache, const char* file,
    const CPARSE_SYM(cursor)* position)
{
    char* tmp;

    /* if the file is already set, then return an error. */
    if (NULL != cache->file)
    {
        return ERROR_LIBCPARSE_FILE_POSITION_CACHE_ALREADY_SET;
    }

    /* copy the file. */
    tmp = strdup(file);
    if (NULL == tmp)
    {
        return ERROR_LIBCPARSE_OUT_OF_MEMORY;
    }

    /* set the cache. */
    memcpy(&cache->pos, position, sizeof(cache->pos));

    /* set the file. */
    cache->file = tmp;
    tmp = NULL;

    /* success. */
    return STATUS_SUCCESS;
}
