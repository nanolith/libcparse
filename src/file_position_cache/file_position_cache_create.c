/**
 * \file file_position_cache/file_position_cache_create.c
 *
 * \brief Create method for \ref file_position_cache.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/file_position_cache.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "file_position_cache_internal.h"

CPARSE_IMPORT_file_position_cache;

/**
 * \brief Create a file position cache instance.
 *
 * \param cache             Pointer to the \ref file_position_cache pointer to
 *                          be populated with the created file position cache
 *                          instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_create)(
    CPARSE_SYM(file_position_cache)** cache)
{
    int retval;
    file_position_cache* tmp;

    /* allocate memory for instance. */
    tmp = (file_position_cache*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* clear instance memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* success. */
    retval = STATUS_SUCCESS;
    *cache = tmp;
    tmp = NULL;
    goto done;

done:
    return retval;
}
