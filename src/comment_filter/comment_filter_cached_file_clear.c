/**
 * \file src/comment_filter/comment_filter_cached_file_clear.c
 *
 * \brief Clear the cached file in a \ref comment_filter.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "comment_filter_internal.h"

/**
 * \brief Clear and free cached file.
 *
 * \param filter            The filter for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_filter_cached_file_clear)(
    CPARSE_SYM(comment_filter)* filter)
{
    if (NULL != filter->file)
    {
        memset(filter->file, 0, strlen(filter->file));
        free(filter->file);
        filter->file = NULL;
    }

    return STATUS_SUCCESS;
}
