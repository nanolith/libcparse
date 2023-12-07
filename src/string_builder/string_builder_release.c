/**
 * \file src/string_builder/string_builder_release.c
 *
 * \brief Release method for the \ref string_builder type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <libcparse/string_builder.h>
#include <stdlib.h>

CPARSE_IMPORT_string_builder;

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
    /* clear the structure. */
    string_builder_clear(builder);

    /* free structure. */
    free(builder);

    return STATUS_SUCCESS;
}
