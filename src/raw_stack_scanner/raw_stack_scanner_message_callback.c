/**
 * \file src/raw_stack_scanner/raw_stack_scanner_message_callback.c
 *
 * \brief The \ref raw_stack_scanner message handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_handler.h>
#include <libcparse/event_reactor.h>
#include <libcparse/input_stream.h>
#include <libcparse/message.h>
#include <libcparse/message/raw_stack_scanner.h>
#include <libcparse/message/subscription.h>
#include <libcparse/raw_stack_scanner.h>
#include <libcparse/status_codes.h>

#include "raw_stack_scanner_internal.h"

CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_input_stream;
CPARSE_IMPORT_message;
CPARSE_IMPORT_message_raw_stack_scanner;
CPARSE_IMPORT_message_subscription;
CPARSE_IMPORT_raw_stack_scanner;
CPARSE_IMPORT_raw_stack_scanner_internal;

static int add_input_stream(raw_stack_scanner* scanner, message* msg);
static int subscribe(raw_stack_scanner* scanner, const message* msg);

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
    raw_stack_scanner* scanner = (raw_stack_scanner*)context;

    switch (message_get_type(msg))
    {
    case CPARSE_MESSAGE_TYPE_RSS_ADD_INPUT_STREAM:
        return add_input_stream(scanner, (message*)msg);

    case CPARSE_MESSAGE_TYPE_RSS_SUBSCRIBE:
        return subscribe(scanner, msg);

    default:
        return ERROR_LIBCPARSE_UNHANDLED_MESSAGE;
    }
}

/**
 * \brief Add an input stream to the scanner.
 *
 * \param scanner           The scanner for this operation.
 * \param msg               The message for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int add_input_stream(raw_stack_scanner* scanner, message* msg)
{
    int retval, release_retval;
    message_rss_add_input_stream* m;
    const char* name;
    input_stream* stream;
    raw_stack_entry* ent;

    /* dynamic cast the message. */
    retval = message_downcast_to_message_rss_add_input_stream(&m, msg);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* get the name of this stream. */
    name = message_rss_add_input_stream_filename_get(m);

    /* transfer the input stream ownership to the caller. */
    retval = message_rss_add_input_stream_xfer(&stream, m);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* create a raw stack entry. */
    retval = raw_stack_entry_create(&ent, stream, name);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_stream;
    }

    /* append this raw stack entry onto the stack. */
    ent->next = scanner->head;
    scanner->head = ent;
    retval = STATUS_SUCCESS;
    goto done;

cleanup_stream:
    release_retval = input_stream_release(stream);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Subscribe to the raw_stack_scanner.
 *
 * \param scanner           The scanner for this operation.
 * \param msg               The message for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int subscribe(raw_stack_scanner* scanner, const message* msg)
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
    retval = event_reactor_add(scanner->reactor, eh);
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
