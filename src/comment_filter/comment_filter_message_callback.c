/**
 * \file src/comment_filter/comment_filter_message_callback.c
 *
 * \brief The \ref comment_filter message handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>

#include "comment_filter_internal.h"

/**
 * \brief Message handler callback for \ref comment_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref comment_filter instance).
 * \param msg               A message for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_filter_message_callback)(
    void* context, const CPARSE_SYM(message)* msg)
{
    (void)context;
    (void)msg;

    return ERROR_LIBCPARSE_UNHANDLED_MESSAGE;
}
