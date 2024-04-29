/**
 * \file src/preprocessor_scanner/preprocessor_scanner_create.c
 *
 * \brief Create method for the \ref preprocessor_scanner type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_reactor.h>
#include <libcparse/preprocessor_scanner.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "preprocessor_scanner_internal.h"

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_file_position_cache;
CPARSE_IMPORT_message_handler;
CPARSE_IMPORT_newline_preserving_whitespace_filter;
CPARSE_IMPORT_preprocessor_scanner;
CPARSE_IMPORT_preprocessor_scanner_internal;
CPARSE_IMPORT_string_builder;

/**
 * \brief Create a preprocessor scanner.
 *
 * This scanner automatically creates a newline preserving whitespace filter and
 * injects itself into the message chain for the parser stack.
 *
 * \param scanner           Pointer to the \ref preprocessor_scanner pointer to
 *                          be populated with the created preprocessor scanner
 *                          instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(preprocessor_scanner_create)(
    CPARSE_SYM(preprocessor_scanner)** scanner)
{
    int retval, release_retval;
    preprocessor_scanner* tmp;
    message_handler mh;
    event_handler eh;

    /* allocate memory for this instance. */
    tmp = (preprocessor_scanner*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* clear instance memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* create parent instance. */
    retval = newline_preserving_whitespace_filter_create(&tmp->parent);
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

    /* create the cache. */
    retval = file_position_cache_create(&tmp->cache);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* create the string builder. */
    retval = string_builder_create(&tmp->builder);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* get the abstract parser instance for the parent. */
    tmp->base = newline_preserving_whitespace_filter_upcast(tmp->parent);

    /* initialize our message handler. */
    retval =
        message_handler_init(
            &mh, &preprocessor_scanner_message_callback, tmp);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* initialize our event handler. */
    retval =
        event_handler_init(
            &eh, &preprocessor_scanner_event_callback, tmp);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_mh;
    }

    /* override the newline preserving whitespace filter message handler with
     * ours. */
    retval =
        abstract_parser_message_handler_override(
            &tmp->parent_mh, tmp->base, &mh);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_eh;
    }

    /* subscribe to the newline preserving whitespace filter. */
    retval =
        abstract_parser_newline_preserving_whitespace_filter_subscribe(
            tmp->base, &eh);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_eh;
    }

    /* we start in the initial state. */
    tmp->state = CPARSE_PREPROCESSOR_SCANNER_STATE_INIT;
    /* we set the state_reset flag to true, forcing us into the begin line state
     * after the first event. */
    tmp->state_reset = true;

    /* success. */
    retval = STATUS_SUCCESS;
    *scanner = tmp;
    tmp = NULL;
    goto cleanup_eh;

cleanup_eh:
    release_retval = event_handler_dispose(&eh);
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

cleanup_tmp:
    if (NULL != tmp)
    {
        release_retval = preprocessor_scanner_release(tmp);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

done:
    return retval;
}
