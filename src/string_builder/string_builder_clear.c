/**
 * \file src/string_builder/string_builder_clear.c
 *
 * \brief Clear method for the \ref string_builder type.
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
 * \brief Clear the current string builder instance, returning its internal
 * state to empty.
 *
 * \param builder           The string builder for this operation.
 */
void CPARSE_SYM(string_builder_clear)(CPARSE_SYM(string_builder)* builder)
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
}
