/**
 * \file src/comment_filter/comment_filter_message_callback.c
 *
 * \brief The \ref comment_filter message handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/comment_filter.h>
#include <libcparse/event_handler.h>
#include <libcparse/event_reactor.h>
#include <libcparse/message.h>
#include <libcparse/message/subscription.h>
#include <libcparse/message_handler.h>
#include <libcparse/status_codes.h>

#include "comment_filter_internal.h"

CPARSE_IMPORT_comment_filter;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_message;
CPARSE_IMPORT_message_handler;
CPARSE_IMPORT_message_subscription;

static int subscribe(comment_filter* filter, const message* msg);

/**
 * \brief Message handler callback for \ref comment_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref comment_filter instance).
 * \param msg               A message for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_filter_message_callback)(
    void* context, const CPARSE_SYM(message)* msg)
{
    comment_filter* filter = (comment_filter*)context;

    switch (message_get_type(msg))
    {
        case CPARSE_MESSAGE_TYPE_COMMENT_FILTER_SUBSCRIBE:
            return subscribe(filter, msg);

        default:
            return message_handler_send(&filter->parent_mh, msg);
    }
}

/**
 * \brief Subscribe to the comment_filter.
 *
 * \param filter            The filter for this operation.
 * \param msg               The message for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int subscribe(comment_filter* filter, const message* msg)
{
    int retval;
    message_subscribe* m;
    const event_handler* eh;

    /* dynamic cast the message. */
    retval = message_downcast_to_message_subscribe(&m, (message*)msg);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* get the event handler for this message. */
    eh = message_subscribe_event_handler_get(m);

    /* add this handler to our reactor. */
    retval = event_reactor_add(filter->reactor, eh);
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
