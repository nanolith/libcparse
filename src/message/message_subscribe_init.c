/**
 * \file src/message/message_subscribe_init.c
 *
 * \brief Init method for the \ref message_subscribe type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/subscription.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "message_internal.h"

CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_message_internal;

/**
 * \brief Initialize a \ref message_subscribe instance.
 *
 * \param msg               The message to initialize.
 * \param msg_type          The type of subscription message.
 * \param handler           The \ref event_handler to add to this endpoint.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_subscribe_init)(
    CPARSE_SYM(message_subscribe)* msg, int msg_type,
    CPARSE_SYM(event_handler)* handler)
{
    int retval;

    /* clear the message buffer. */
    memset(msg, 0, sizeof(*msg));

    /* initialize the base message. */
    retval = message_init(&msg->hdr, msg_type);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* copy the handler. */
    retval = event_handler_init_copy(&msg->handler, handler);
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
