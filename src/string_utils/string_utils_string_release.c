/**
 * \file src/string_utils/string_utils_string_release.c
 *
 * \brief Clear and release a string.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/string_utils.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief Clear and free a string.
 *
 * \param str               The string to clear and free.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
void CPARSE_SYM(string_utils_string_release)(char* str)
{
    memset(str, 0, strlen(str));
    free(str);
}
