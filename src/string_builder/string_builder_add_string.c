/**
 * \file src/string_builder/string_builder_add_string.c
 *
 * \brief Add a string to the \ref string_builder.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <libcparse/string_builder.h>

CPARSE_IMPORT_string_builder;

/**
 * \brief Add a string to the string builder.
 *
 * \param builder           The string builder instance for this operation.
 * \param str               The string to add.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(string_builder_add_string)(
    CPARSE_SYM(string_builder)* builder, const char* ch)
{
    int retval;

    /* interate through the string. */
    for (const char* tmp = ch; 0 != *tmp; ++tmp)
    {
        /* attempt to add this character to the builder. */
        retval = string_builder_add_character(builder, *tmp);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }
    }

    /* success. */
    return STATUS_SUCCESS;
}
