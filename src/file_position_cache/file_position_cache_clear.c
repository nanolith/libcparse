/**
 * \file file_position_cache/file_position_cache_clear.c
 *
 * \brief Clear the \ref file_position_cache.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/string_utils.h>
#include <stdlib.h>
#include <string.h>

#include "file_position_cache_internal.h"

CPARSE_IMPORT_string_utils;

/**
 * \brief Clear the \ref file_position_cache.
 *
 * \param cache             The \ref file_position_cache instance for this
 *                          operation.
 */
void CPARSE_SYM(file_position_cache_clear)(
    CPARSE_SYM(file_position_cache)* cache)
{
    if (NULL != cache->file)
    {
        string_utils_string_release(cache->file);
        cache->file = NULL;
    }

    memset(&cache->pos, 0, sizeof(cache->pos));
}
