/**
 * \file
 * src/newline_preserving_whitespace_filter/newline_preserving_whitespace_filter_message_callback.c
 *
 * \brief The \ref newline_preserving_whitespace_filter message handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>

#include "newline_preserving_whitespace_filter_internal.h"

/**
 * \brief Message handler callback for
 * \ref newline_preserving_whitespace_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref newline_preserving_whitespace_filter instance).
 * \param msg               A message for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(newline_preserving_whitespace_filter_message_callback)(
    void* context, const CPARSE_SYM(message)* msg)
{
    (void)context;
    (void)msg;

    return ERROR_LIBCPARSE_UNHANDLED_MESSAGE;
}
