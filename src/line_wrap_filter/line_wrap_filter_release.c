/**
 * \file src/line_wrap_filter/line_wrap_filter_release.c
 *
 * \brief Release method for the \ref line_wrap_filter type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_reactor.h>
#include <libcparse/message_handler.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "line_wrap_filter_internal.h"

CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_file_position_cache;
CPARSE_IMPORT_message_handler;
CPARSE_IMPORT_raw_file_line_override_filter;

/**
 * \brief Release a line wrap filter instance, releasing any internal resources
 * it may own.
 *
 * \param filter            The \ref line_wrap_filter instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(line_wrap_filter_release)(CPARSE_SYM(line_wrap_filter)* filter)
{
    int parent_release_retval = STATUS_SUCCESS;
    int reactor_release_retval = STATUS_SUCCESS;
    int cache_release_retval = STATUS_SUCCESS;
    int mh_dispose_retval = STATUS_SUCCESS;

    /* release the parent if valid. */
    if (NULL != filter->parent)
    {
        parent_release_retval =
            raw_file_line_override_filter_release(filter->parent);
    }

    /* release the event reactor if valid. */
    if (NULL != filter->reactor)
    {
        reactor_release_retval = event_reactor_release(filter->reactor);
    }

    /* release the cache if valid. */
    if (NULL != filter->cache)
    {
        cache_release_retval = file_position_cache_release(filter->cache);
    }

    /* dispose the parent message handler. */
    mh_dispose_retval = message_handler_dispose(&filter->parent_mh);

    /* clear the filter. */
    memset(filter, 0, sizeof(*filter));

    /* free filter memory. */
    free(filter);

    /* decode return values. */
    if (STATUS_SUCCESS != parent_release_retval)
    {
        return parent_release_retval;
    }
    else if (STATUS_SUCCESS != reactor_release_retval)
    {
        return reactor_release_retval;
    }
    else if (STATUS_SUCCESS != cache_release_retval)
    {
        return cache_release_retval;
    }
    else
    {
        return mh_dispose_retval;
    }
}
