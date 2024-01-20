/**
 * \file src/preprocessor_scanner/preprocessor_scanner_message_callback.c
 *
 * \brief The \ref preprocessor_scanner message handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message.h>
#include <libcparse/message_handler.h>
#include <libcparse/preprocessor_scanner.h>
#include <libcparse/status_codes.h>

#include "preprocessor_scanner_internal.h"

CPARSE_IMPORT_message;
CPARSE_IMPORT_message_handler;
CPARSE_IMPORT_preprocessor_scanner;

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
    preprocessor_scanner* scanner = (preprocessor_scanner*)context;

    switch (message_get_type(msg))
    {
        default:
            return message_handler_send(&scanner->parent_mh, msg);
    }
}
