/**
 * \file src/raw_stack_scanner/raw_stack_scanner_release.c
 *
 * \brief Release a \ref raw_stack_scanner instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/raw_stack_scanner.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "raw_stack_scanner_internal.h"

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_raw_stack_scanner;
CPARSE_IMPORT_raw_stack_scanner_internal;

/**
 * \brief Release a raw stack scanner instance, releasing any internal resources
 * it may own.
 *
 * \param scanner           The \ref raw_stack_scanner instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(raw_stack_scanner_release)(
    CPARSE_SYM(raw_stack_scanner)* scanner)
{
    int retval = STATUS_SUCCESS, release_retval = STATUS_SUCCESS;

    /* release entries. */
    while (NULL != scanner->head)
    {
        raw_stack_entry* tmp = scanner->head;
        scanner->head = scanner->head->next;

        /* release entry. */
        release_retval = raw_stack_entry_release(tmp);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

    /* dispose abstract parser. */
    release_retval = abstract_parser_dispose(&scanner->hdr);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

    /* clear instance memory. */
    memset(scanner, 0, sizeof(*scanner));

    /* free instance memory. */
    free(scanner);

    /* decode return code. */
    return retval;
}
