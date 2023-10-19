/**
 * \file src/raw_stack_scanner/raw_stack_scanner_message_callback.c
 *
 * \brief The \ref raw_stack_scanner message handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>

#include "raw_stack_scanner_internal.h"

/**
 * \brief Message handler callback for \ref raw_stack_scanner.
 *
 * \param context           The context for this handler (the
 *                          \ref raw_stack_scanner instance).
 * \param msg               A message for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(raw_stack_scanner_message_callback)(
    void* context, const CPARSE_SYM(message)* msg)
{
    /* TODO - currently stubbed. */
    (void)context;
    (void)msg;

    return ERROR_LIBCPARSE_UNHANDLED_MESSAGE;
}
