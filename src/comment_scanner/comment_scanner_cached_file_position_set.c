/**
 * \file src/comment_scanner/comment_scanner_cached_file_position_set.c
 *
 * \brief Set the cached file and position in a \ref comment_scanner.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "comment_scanner_internal.h"

CPARSE_IMPORT_comment_scanner_internal;

/**
 * \brief Set the cached file and position, clearing the previous cached file if
 * necessary.
 *
 * \param scanner           The scanner for this operation.
 * \param pos               The position to use for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_scanner_cached_file_position_set)(
    CPARSE_SYM(comment_scanner)* scanner, const CPARSE_SYM(cursor)* pos)
{
    int retval;
    char* tmp;

    /* duplicate the file to our cached file. */
    tmp = strdup(pos->file);
    if (NULL == scanner->file)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* Clear the old cached file position. */
    retval = comment_scanner_cached_file_clear(scanner);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* set the file on success. */
    scanner->file = tmp;

    /* cache this position. */
    memcpy(&scanner->pos1, pos, sizeof(scanner->pos1));

    /* override the file with our cached file. */
    scanner->pos1.file = scanner->file;

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

cleanup_tmp:
    memset(tmp, 0, strlen(tmp));
    free(tmp);

done:
    return retval;
}
