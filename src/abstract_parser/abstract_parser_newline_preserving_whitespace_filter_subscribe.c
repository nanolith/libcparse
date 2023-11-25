/**
 * \file
 * src/abstract_parser/abstract_parser_newline_preserving_whitespace_filter_subscribe.c
 *
 * \brief Send a subscription request to the \ref
 * newline_preserving_whitespace_filter.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/message/subscription.h>
#include <libcparse/message_type.h>
#include <libcparse/status_codes.h>

CPARSE_IMPORT_message_handler;
CPARSE_IMPORT_message_subscription;

/**
 * \brief Subscribe to \ref newline_preserving_whitespace_filter events.
 *
 * \param ap                The \ref abstract_parser for this operation.
 * \param eh                The event handler to add to the subscription list.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int
CPARSE_SYM(abstract_parser_newline_preserving_whitespace_filter_subscribe)(
    CPARSE_SYM(abstract_parser)* ap, CPARSE_SYM(event_handler)* eh)
{
    int retval, release_retval;
    message_subscribe msg;

    /* initialize the message. */
    retval =
        message_subscribe_init(
            &msg,
            CPARSE_MESSAGE_TYPE_NEWLINE_PRESERVING_WHITESPACE_FILTER_SUBSCRIBE,
            eh);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* send the message. */
    retval = message_handler_send(&ap->mh, message_subscribe_upcast(&msg));
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_msg;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_msg;

cleanup_msg:
    release_retval = message_subscribe_dispose(&msg);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
