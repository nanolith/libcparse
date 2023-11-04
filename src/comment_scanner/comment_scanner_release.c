/**
 * \file src/comment_scanner/comment_scanner_release.c
 *
 * \brief Release method for the \ref comment_scanner type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_reactor.h>
#include <libcparse/message_handler.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "comment_scanner_internal.h"

CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_message_handler;
CPARSE_IMPORT_raw_file_line_override_filter;

/**
 * \brief Release a comment scanner instance, releasing any internal resources
 * it may own.
 *
 * \param scanner           The \ref comment_scanner instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_scanner_release)(CPARSE_SYM(comment_scanner)* scanner)
{
    int parent_release_retval = STATUS_SUCCESS;
    int reactor_release_retval = STATUS_SUCCESS;
    int mh_dispose_retval = STATUS_SUCCESS;

    /* release the parent if valid. */
    if (NULL != scanner->parent)
    {
        parent_release_retval =
            raw_file_line_override_filter_release(scanner->parent);
    }

    /* release the event reactor if valid. */
    if (NULL != scanner->reactor)
    {
        reactor_release_retval = event_reactor_release(scanner->reactor);
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
    else
    {
        return mh_dispose_retval;
    }
}
