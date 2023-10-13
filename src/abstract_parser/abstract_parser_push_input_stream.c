/**
 * \file src/abstract_parser/abstract_parser_push_input_stream.c
 *
 * \brief Push the given \ref input_stream to a \ref abstract_parser instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/message/raw_stack_scanner.h>
#include <libcparse/status_codes.h>

CPARSE_IMPORT_message_handler;
CPARSE_IMPORT_message_raw_stack_scanner;

/**
 * \brief Push an \ref input_stream onto the \ref raw_stack_scanner stream.
 *
 * \note Ownership of this \ref input_stream is passed to the \ref
 * abstract_parser.
 *
 * \param ap                The \ref abstract_parser to add this stream to.
 * \param name              The name of this stream.
 * \param stream            The stream to push onto the stack.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int
CPARSE_SYM(abstract_parser_push_input_stream)(
    CPARSE_SYM(abstract_parser)* ap, const char* name,
    CPARSE_SYM(input_stream)* input_stream)
{
    int retval, release_retval;
    message_rss_add_input_stream msg;

    /* initialize the message. */
    retval = message_rss_add_input_stream_init(&msg, name, input_stream);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* send the message. */
    retval =
        message_handler_send(
            &ap->mh, message_rss_add_input_stream_upcast(&msg));
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_msg;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_msg;

cleanup_msg:
    release_retval = message_rss_add_input_stream_dispose(&msg);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
