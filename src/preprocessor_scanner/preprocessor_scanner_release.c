/**
 * \file src/preprocessor_scanner/preprocessor_scanner_release.c
 *
 * \brief Release method for the \ref preprocessor_scanner type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_reactor.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "preprocessor_scanner_internal.h"

CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_file_position_cache;
CPARSE_IMPORT_message_handler;
CPARSE_IMPORT_newline_preserving_whitespace_filter;
CPARSE_IMPORT_string_builder;

/**
 * \brief Release a preprocessor scanner instance, releasing any internal
 * resources it may own.
 *
 * \param scanner           The \ref preprocessor_scanner instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(preprocessor_scanner_release)(
    CPARSE_SYM(preprocessor_scanner)* scanner)
{
    int parent_release_retval = STATUS_SUCCESS;
    int reactor_release_retval = STATUS_SUCCESS;
    int cache_release_retval = STATUS_SUCCESS;
    int newline_cache_release_retval = STATUS_SUCCESS;
    int hash_cache_release_retval = STATUS_SUCCESS;
    int mh_dispose_retval = STATUS_SUCCESS;
    int builder_release_retval = STATUS_SUCCESS;

    /* release the parent if valid. */
    if (NULL != scanner->parent)
    {
        parent_release_retval =
            newline_preserving_whitespace_filter_release(scanner->parent);
    }

    /* release the event reactor if valid. */
    if (NULL != scanner->reactor)
    {
        reactor_release_retval = event_reactor_release(scanner->reactor);
    }

    /* release the cache if valid. */
    if (NULL != scanner->cache)
    {
        cache_release_retval = file_position_cache_release(scanner->cache);
    }

    /* release the newline cache if valid. */
    if (NULL != scanner->newline_cache)
    {
        newline_cache_release_retval =
            file_position_cache_release(scanner->newline_cache);
    }

    /* release the hash cache if valid. */
    if (NULL != scanner->hash_cache)
    {
        hash_cache_release_retval =
            file_position_cache_release(scanner->hash_cache);
    }

    /* release the builder if valid. */
    if (NULL != scanner->builder)
    {
        builder_release_retval = string_builder_release(scanner->builder);
    }

    /* dispose the parent message handler. */
    mh_dispose_retval = message_handler_dispose(&scanner->parent_mh);

    /* clear the scanner. */
    memset(scanner, 0, sizeof(*scanner));

    /* free scanner memory. */
    free(scanner);

    /* decode return value. */
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
    else if (STATUS_SUCCESS != newline_cache_release_retval)
    {
        return newline_cache_release_retval;
    }
    else if (STATUS_SUCCESS != hash_cache_release_retval)
    {
        return hash_cache_release_retval;
    }
    else if (STATUS_SUCCESS != builder_release_retval)
    {
        return builder_release_retval;
    }
    else
    {
        return mh_dispose_retval;
    }
}
