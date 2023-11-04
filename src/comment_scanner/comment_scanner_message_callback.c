/**
 * \file src/comment_scanner/comment_scanner_message_callback.c
 *
 * \brief The \ref comment_scanner message handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/comment_scanner.h>
#include <libcparse/status_codes.h>

#include "comment_scanner_internal.h"

CPARSE_IMPORT_comment_scanner;
CPARSE_IMPORT_message_handler;

/**
 * \brief Message handler callback for \ref comment_scanner.
 *
 * \param context           The context for this handler (the
 *                          \ref comment_scanner instance).
 * \param msg               A message for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_scanner_message_callback)(
    void* context, const CPARSE_SYM(message)* msg)
{
    comment_scanner* scanner = (comment_scanner*)context;

    /* call the parent handler. */
    return message_handler_send(&scanner->parent_mh, msg);
}
