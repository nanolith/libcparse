/**
 * \file src/comment_scanner/comment_scanner_create.c
 *
 * \brief Create method for the \ref comment_scanner type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/comment_scanner.h>
#include <libcparse/event_handler.h>
#include <libcparse/event_reactor.h>
#include <libcparse/line_wrap_filter.h>
#include <libcparse/message_handler.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "comment_scanner_internal.h"

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_comment_scanner;
CPARSE_IMPORT_comment_scanner_internal;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_file_position_cache;
CPARSE_IMPORT_line_wrap_filter;
CPARSE_IMPORT_message_handler;

/**
 * \brief Create a comment scanner.
 *
 * This filter automatically creates a file / line override filter and injects
 * itself into the message chain for the parser stack.
 *
 * \param scanner           Pointer to the \ref comment_scanner pointer to be
 *                          populated with the created comment scanner instance
 *                          on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_scanner_create)(CPARSE_SYM(comment_scanner)** scanner)
{
    int retval, release_retval;
    comment_scanner* tmp;
    message_handler mh;
    event_handler eh;

    /* allocate memory for this instance. */
    tmp = (comment_scanner*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* clear instance memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* create parent instance. */
    retval = line_wrap_filter_create(&tmp->parent);
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

    /* create the file/position cache. */
    retval = file_position_cache_create(&tmp->cache);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* get the abstract parser instance for the parent. */
    abstract_parser* ap = line_wrap_filter_upcast(tmp->parent);

    /* initialize our message handler. */
    retval = message_handler_init(&mh, &comment_scanner_message_callback, tmp);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* initialize our event handler. */
    retval = event_handler_init(&eh, &comment_scanner_event_callback, tmp);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_mh;
    }

    /* override the raw file line override filter message handler with ours. */
    retval = abstract_parser_message_handler_override(&tmp->parent_mh, ap, &mh);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_eh;
    }

    /* subscribe to the line wrap filter. */
    retval = abstract_parser_line_wrap_filter_subscribe(ap, &eh);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_eh;
    }

    /* we start in the initial state. */
    tmp->state = CPARSE_COMMENT_SCANNER_STATE_INIT;

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
        release_retval = comment_scanner_release(tmp);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

done:
    return retval;
}
