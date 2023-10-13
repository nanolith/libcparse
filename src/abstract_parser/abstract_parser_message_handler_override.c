/**
 * \file src/abstract_parser/abstract_parser_message_handler_override.c
 *
 * \brief Override the message handler for this \ref abstract_parser instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/status_codes.h>

CPARSE_IMPORT_message_handler;

/**
 * \brief Override the message handler for the given message handler instance
 * with the given message handler.
 *
 * \note When a message event is sent to \p new_handler, it is up to this
 * handler to publish this message event to \p old_handler if it does not
 * override the message, so that the message chain is maintained.
 *
 * \param old_handler       Pointer to a \ref message handler to be set to the
 *                          old handler.
 * \param ap                The \ref abstract_parser instance for this
 *                          operation.
 * \param new_handler       The \ref message_handler instance to install.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int
CPARSE_SYM(abstract_parser_message_handler_override)(
    CPARSE_SYM(message_handler)* old_handler,
    CPARSE_SYM(abstract_parser)* ap,
    CPARSE_SYM(message_handler)* new_handler)
{
    int retval;

    /* copy the current handler to the old handler. */
    retval = message_handler_init_copy(old_handler, &ap->mh);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* copy the new handler to the abstract parser's handler. */
    retval = message_handler_init_copy(&ap->mh, new_handler);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
