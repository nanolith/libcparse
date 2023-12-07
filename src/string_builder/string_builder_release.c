/**
 * \file src/string_builder/string_builder_release.c
 *
 * \brief Release method for the \ref string_builder type.
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
 * \brief Release a string builder instance, releasing any internal resources it
 * may own.
 *
 * \param builder           The \ref string_builder instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(string_builder_release)(CPARSE_SYM(string_builder)* builder)
{
    /* clear all chunks. */
    string_builder_chunk* tmp = builder->head;
    while (NULL != tmp)
    {
        string_builder_chunk* next = tmp->next;

        memset(tmp, 0, sizeof(*tmp));
        free(tmp);
        tmp = next;
    }

    /* clear structure. */
    memset(builder, 0, sizeof(*builder));

    /* free structure. */
    free(builder);

    return STATUS_SUCCESS;
}
