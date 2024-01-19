/**
 * \file src/preprocessor_scanner/preprocessor_scanner_message_callback.c
 *
 * \brief The \ref preprocessor_scanner message handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>

#include "preprocessor_scanner_internal.h"

/**
 * \brief Message handler callback for
 * \ref preprocessor_scanner_message_callback.
 *
 * \param context           The context for this handler (the
 *                          \ref preprocessor_scanner instance).
 * \param msg               A message for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(preprocessor_scanner_message_callback)(
    void* context, const CPARSE_SYM(message)* msg)
{
    /* TODO - fill out stub. */
    (void)context;
    (void)msg;

    return ERROR_LIBCPARSE_UNHANDLED_MESSAGE;
}
