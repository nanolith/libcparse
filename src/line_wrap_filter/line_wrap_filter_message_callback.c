/**
 * \file src/line_wrap_filter/line_wrap_filter_message_callback.c
 *
 * \brief The \ref line_wrap_filter message handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>

#include "line_wrap_filter_internal.h"

/**
 * \brief Message handler callback for \ref line_wrap_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref line_wrap_filter instance).
 * \param msg               A message for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(line_wrap_filter_message_callback)(
    void* context, const CPARSE_SYM(message)* msg)
{
    (void)context;
    (void)msg;

    return ERROR_LIBCPARSE_UNHANDLED_MESSAGE;
}
