/**
 * \file file_position_cache/file_position_cache_release.c
 *
 * \brief Release method for \ref file_position_cache.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "file_position_cache_internal.h"

/**
 * \brief Release a file position cache instance, releasing any internal
 * resources it may own.
 *
 * \param cache             The \ref line_wrap_filter instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_release)(
    CPARSE_SYM(file_position_cache)* cache)
{
    if (NULL != cache->file)
    {
        memset(cache->file, 0, strlen(cache->file));
        free(cache->file);
    }

    memset(cache, 0, sizeof(*cache));
    free(cache);

    return STATUS_SUCCESS;
}
