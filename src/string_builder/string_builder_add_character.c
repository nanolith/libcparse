/**
 * \file src/string_builder/string_builder_add_character.c
 *
 * \brief Add a character to the \ref string_builder.
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
 * \brief Add a character to the string builder.
 *
 * \param builder           The string builder instance for this operation.
 * \param ch                The character to add.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(string_builder_add_character)(
    CPARSE_SYM(string_builder)* builder, int ch)
{
    string_builder_chunk* tmp;
    size_t chunk_offset =
        builder->offset % CPARSE_STRING_BUILDER_CHUNK_ARRAY_SIZE;

    /* There are three possible states:
     * 1. There are no chunks, so allocate one.
     * 2. The current chunks are full, so allocate one.
     * 3. There is room for this character in an existing chunk, so add it.
     *
     * This function progressively shifts toward state 3.
     */

    /* 3. There is room for the character in an existing chunk, so set tmp to
     * this chunk. */
    if (builder->offset > 0 && 0 != chunk_offset)
    {
        tmp = builder->tail;
    }

    /* 2. We need to allocate memory for the chunk, so save it to tmp. */
    if (0 == chunk_offset)
    {
        /* allocate memory for this chunk. */
        tmp = (string_builder_chunk*)malloc(sizeof(*tmp));
        if (NULL == tmp)
        {
            return ERROR_LIBCPARSE_OUT_OF_MEMORY;
        }

        /* clear the new chunk. */
        memset(tmp, 0, sizeof(*tmp));

        /* this is our new tail. */
        builder->tail->next = tmp;
        builder->tail = tmp;
    }

    /* 1. Is this the first chunk? If so, set head to tmp. */
    if (0 == builder->offset)
    {
        builder->head = tmp;
    }

    /* 3. Add the character to the builder. */
    tmp->arr[chunk_offset] = ch;
    builder->offset += 1;

    /* success. */
    return STATUS_SUCCESS;
}
