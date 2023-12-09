/**
 * \file src/string_builder/string_builder_build.c
 *
 * \brief Build a string using the current state of the string builder.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "string_builder_internal.h"

CPARSE_IMPORT_string_builder_internal;

/**
 * \brief Build a string from the current string builder.
 *
 * \param str               Pointer to the string pointer to receive the string
 *                          on success. On success, this string is owned by the
 *                          caller and must be freed when no longer needed.
 * \param builder           The string builder for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(string_builder_build)(
    char** str, CPARSE_SYM(string_builder)* builder)
{
    size_t string_size = builder->offset + 1;
    size_t count;
    char* tmp;
    char* out;
    string_builder_chunk* curr = builder->head;

    /* allocate memory for the string. */
    tmp = (char*)malloc(string_size);
    if (NULL == tmp)
    {
        return ERROR_LIBCPARSE_OUT_OF_MEMORY;
    }

    /* clear the string. */
    memset(tmp, 0, string_size);

    /* set the output pointer. */
    out = tmp;

    /* iterate over all of the builder chunks. */
    while (NULL != curr)
    {
        /* decode the copy count. */
        if (curr == builder->tail)
        {
            count = builder->offset % CPARSE_STRING_BUILDER_CHUNK_ARRAY_SIZE;
        }
        else
        {
            count = CPARSE_STRING_BUILDER_CHUNK_ARRAY_SIZE;
        }

        /* copy string data. */
        memcpy(out, curr->arr, count);

        /* update the output pointer. */
        out += count;

        /* skip to the next chunk. */
        curr = curr->next;
    }

    /* success. */
    *str = tmp;
    return STATUS_SUCCESS;
}
