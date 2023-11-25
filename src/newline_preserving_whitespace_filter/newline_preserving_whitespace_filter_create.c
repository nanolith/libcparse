/**
 * \file
 * src/newline_preserving_whitespace_filter/newline_preserving_whitespace_filter_create.c
 *
 * \brief Create method for the \ref newline_preserving_whitespace_filter type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/comment_filter.h>
#include <libcparse/event_handler.h>
#include <libcparse/event_reactor.h>
#include <libcparse/file_position_cache.h>
#include <libcparse/message_handler.h>
#include <libcparse/newline_preserving_whitespace_filter.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "newline_preserving_whitespace_filter_internal.h"

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_comment_filter;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_file_position_cache;
CPARSE_IMPORT_message_handler;
CPARSE_IMPORT_newline_preserving_whitespace_filter;
CPARSE_IMPORT_newline_preserving_whitespace_filter_internal;

/**
 * \brief Create a newline preserving whitespace filter.
 *
 * This filter automatically creates a comment filter and injects itself into
 * the message chain for the parser stack.
 *
 * \param filter            Pointer to the
 *                          \ref newline_preserving_whitespace_filter pointer to
 *                          be populated with the filter instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(newline_preserving_whitespace_filter_create)(
    CPARSE_SYM(newline_preserving_whitespace_filter)** filter)
{
    int retval, release_retval;
    newline_preserving_whitespace_filter* tmp;
    message_handler mh;
    event_handler eh;

    /* allocate memory for this instance. */
    tmp = (newline_preserving_whitespace_filter*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* clear instance memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* create parent instance. */
    retval = comment_filter_create(&tmp->parent);
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
    abstract_parser* ap = comment_filter_upcast(tmp->parent);

    /* initialize our message handler. */
    retval =
        message_handler_init(
            &mh, &newline_preserving_whitespace_filter_message_callback, tmp);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* initialize our event handler. */
    retval =
        event_handler_init(
            &eh, &newline_preserving_whitespace_filter_event_callback, tmp);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_mh;
    }

    /* override the comment filter message handler with ours. */
    retval = abstract_parser_message_handler_override(&tmp->parent_mh, ap, &mh);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_eh;
    }

    /* subscribe to the comment filter. */
    retval = abstract_parser_comment_filter_subscribe(ap, &eh);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_eh;
    }

    /* we start in the initial state. */
    tmp->state = CPARSE_NL_WHITESPACE_FILTER_STATE_INIT;

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
        release_retval = newline_preserving_whitespace_filter_release(tmp);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

done:
    return retval;
}
