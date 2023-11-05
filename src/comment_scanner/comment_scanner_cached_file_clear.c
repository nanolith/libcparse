/**
 * \file src/comment_scanner/comment_scanner_cached_file_clear.c
 *
 * \brief Clear the cached file in a \ref comment_scanner.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "comment_scanner_internal.h"

/**
 * \brief Clear and free cached file.
 *
 * \param scanner           The scanner for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_scanner_cached_file_clear)(
    CPARSE_SYM(comment_scanner)* scanner)
{
    if (NULL != scanner->file)
    {
        memset(scanner->file, 0, strlen(scanner->file));
        free(scanner->file);
        scanner->file = NULL;
    }

    return STATUS_SUCCESS;
}
