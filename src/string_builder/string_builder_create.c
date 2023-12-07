/**
 * \file src/string_builder/string_builder_create.c
 *
 * \brief Create method for the \ref string_builder type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "string_builder_internal.h"

CPARSE_IMPORT_string_builder;

/**
 * \brief Create a string builder instance.
 *
 * \param builder           Pointer to the string builder pointer to receive
 *                          this instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(string_builder_create)(CPARSE_SYM(string_builder)** builder)
{
    int retval;
    string_builder* tmp;

    /* allocate memory for this instance. */
    tmp = (string_builder*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* clear instance memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* success. */
    *builder = tmp;
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
