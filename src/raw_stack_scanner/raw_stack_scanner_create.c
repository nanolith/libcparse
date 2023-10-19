/**
 * \file src/raw_stack_scanner/raw_stack_scanner_create.c
 *
 * \brief Create a \ref raw_stack_scanner instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/event_reactor.h>
#include <libcparse/raw_stack_scanner.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "raw_stack_scanner_internal.h"

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_message_handler;
CPARSE_IMPORT_raw_stack_scanner;
CPARSE_IMPORT_raw_stack_scanner_internal;

/**
 * \brief Create a raw stack scanner.
 *
 * \param scanner           Pointer to the \ref raw_stack_scanner pointer to be
 *                          populated with the created raw stack scanner on
 *                          success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(raw_stack_scanner_create)(
    CPARSE_SYM(raw_stack_scanner)** scanner)
{
    int retval, release_retval;
    raw_stack_scanner* tmp;
    message_handler mh;

    /* allocate instance memory. */
    tmp = malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* clear instance memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* initialize message handler. */
    retval =
        message_handler_init(&mh, &raw_stack_scanner_message_callback, tmp);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* initialize abstract parser. */
    retval = abstract_parser_init(&tmp->hdr, &mh);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* create event reactor. */
    retval = event_reactor_create(&tmp->reactor);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    *scanner = tmp;
    goto cleanup_mh;

cleanup_tmp:
    release_retval = raw_stack_scanner_release(tmp);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

cleanup_mh:
    release_retval = message_handler_dispose(&mh);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
