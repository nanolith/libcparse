/**
 * \file file_position_cache/file_position_cache_position_get.c
 *
 * \brief Get the cached position.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stddef.h>

#include "file_position_cache_internal.h"

/**
 * \brief Get the cached position.
 *
 * \param cache             The \ref file_position_cache instance for this
 *                          operation.
 * \param pos               The cursor pointer pointer to receive this position
 *                          on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_position_get)(
    CPARSE_SYM(file_position_cache)* cache,
    const CPARSE_SYM(cursor)** position)
{
    if (NULL == cache->file)
    {
        return ERROR_LIBCPARSE_FILE_POSITION_CACHE_NOT_SET;
    }

    /* set the position return parameter. */
    *position = &cache->pos;

    /* success. */
    return STATUS_SUCCESS;
}
