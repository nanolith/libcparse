/**
 * \file src/comment_filter/comment_filter_release.c
 *
 * \brief Release method for the \ref comment_filter type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_reactor.h>
#include <libcparse/message_handler.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "comment_filter_internal.h"

CPARSE_IMPORT_comment_filter_internal;
CPARSE_IMPORT_comment_scanner;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_message_handler;

/**
 * \brief Release a comment filter instance, releasing any internal resources
 * it may own.
 *
 * \param filter            The \ref comment_filter instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_filter_release)(CPARSE_SYM(comment_filter)* filter)
{
    int parent_release_retval = STATUS_SUCCESS;
    int reactor_release_retval = STATUS_SUCCESS;
    int cached_file_clear = STATUS_SUCCESS;
    int mh_dispose_retval = STATUS_SUCCESS;

    /* release the parent if valid. */
    if (NULL != filter->parent)
    {
        parent_release_retval = comment_scanner_release(filter->parent);
    }

    /* release the event reactor if valid. */
    if (NULL != filter->reactor)
    {
        reactor_release_retval = event_reactor_release(filter->reactor);
    }

    /* clear the cached file name if set. */
    cached_file_clear = comment_filter_cached_file_clear(filter);

    /* dispose the parent message handler. */
    mh_dispose_retval = message_handler_dispose(&filter->parent_mh);

    /* clear the filter. */
    memset(filter, 0, sizeof(*filter));

    /* free filter memory. */
    free(filter);

    /* decode return value. */
    if (STATUS_SUCCESS != parent_release_retval)
    {
        return parent_release_retval;
    }
    else if (STATUS_SUCCESS != reactor_release_retval)
    {
        return reactor_release_retval;
    }
    else if (STATUS_SUCCESS != cached_file_clear)
    {
        return cached_file_clear;
    }
    else
    {
        return mh_dispose_retval;
    }
}
