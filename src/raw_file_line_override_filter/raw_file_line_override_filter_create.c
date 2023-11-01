/**
 * \file
 * src/raw_file_line_override_filter/raw_file_line_override_filter_create.c
 *
 * \brief Create method for the \ref raw_file_line_override_filter type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/event_reactor.h>
#include <libcparse/message_handler.h>
#include <libcparse/raw_file_line_override_filter.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "raw_file_line_override_filter_internal.h"

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_message_handler;
CPARSE_IMPORT_raw_file_line_override_filter;
CPARSE_IMPORT_raw_file_line_override_filter_internal;
CPARSE_IMPORT_raw_stack_scanner;

/**
 * \brief Create a raw file/line override filter.
 *
 * This filter automatically creates a raw stack scanner and injects itself into
 * the message chain for that scanner.
 *
 * \param filter            Pointer to the \ref raw_file_line_override_filter
 *                          pointer to be populated with the created raw
 *                          file/line override filter instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(raw_file_line_override_filter_create)(
    CPARSE_SYM(raw_file_line_override_filter)** filter)
{
    int retval, release_retval;
    raw_file_line_override_filter* tmp;
    message_handler mh;

    /* allocate memory for this instance. */
    tmp = (raw_file_line_override_filter*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* clear instance memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* create parent instance. */
    retval = raw_stack_scanner_create(&tmp->parent);
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

    /* Get the abstract parser instance for the parent. */
    abstract_parser* ap = raw_stack_scanner_upcast(tmp->parent);

    /* initialize our message handler. */
    retval =
        message_handler_init(
            &mh, &raw_file_line_override_filter_message_callback, tmp);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* override the raw stack scanner's message handler with our own. */
    retval = abstract_parser_message_handler_override(&tmp->parent_mh, ap, &mh);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_mh;
    }

    /* by default, we do not override the position. */
    tmp->use_pos = false;

    /* success. */
    retval = STATUS_SUCCESS;
    *filter = tmp;
    tmp = NULL;
    goto cleanup_mh;

cleanup_mh:
    release_retval = message_handler_dispose(&mh);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

cleanup_tmp:
    if (NULL != tmp)
    {
        release_retval = raw_file_line_override_filter_release(tmp);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

done:
    return retval;
}
