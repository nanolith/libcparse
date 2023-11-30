/**
 * \file src/comment_filter/comment_filter_create.c
 *
 * \brief Create method for the \ref comment_filter type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/comment_filter.h>
#include <libcparse/comment_scanner.h>
#include <libcparse/event_handler.h>
#include <libcparse/event_reactor.h>
#include <libcparse/message_handler.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "comment_filter_internal.h"

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_comment_filter;
CPARSE_IMPORT_comment_filter_internal;
CPARSE_IMPORT_comment_scanner;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_file_position_cache;
CPARSE_IMPORT_message_handler;

/**
 * \brief Create a comment filter.
 *
 * This filter automatically creates a comment scanner and injects itself into
 * the message chain for the parser stack.
 *
 * \param filter            Pointer to the \ref comment_filter pointer to be
 *                          populated with the created comment filter instance
 *                          on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_filter_create)(CPARSE_SYM(comment_filter)** filter)
{
    int retval, release_retval;
    comment_filter* tmp;
    message_handler mh;
    event_handler eh;

    /* allocate memory for this instance. */
    tmp = (comment_filter*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* clear instance memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* create parent instance. */
    retval = comment_scanner_create(&tmp->parent);
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

    /* get the abstract parser instance for the parent. */
    tmp->base = comment_scanner_upcast(tmp->parent);

    /* initialize our message handler. */
    retval = message_handler_init(&mh, &comment_filter_message_callback, tmp);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* initialize our event handler. */
    retval = event_handler_init(&eh, &comment_filter_event_callback, tmp);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_mh;
    }

    /* override the comment scanner message handler with ours. */
    retval =
        abstract_parser_message_handler_override(
            &tmp->parent_mh, tmp->base, &mh);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_eh;
    }

    /* subscribe to the comment scanner. */
    retval = abstract_parser_comment_scanner_subscribe(tmp->base, &eh);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_eh;
    }

    /* we start in the initial state. */
    tmp->state = CPARSE_COMMENT_FILTER_STATE_INIT;

    /* success. */
    retval = STATUS_SUCCESS;
    *filter = tmp;
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
        release_retval = comment_filter_release(tmp);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

done:
    return retval;
}
