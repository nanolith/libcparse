/**
 * \file src/raw_stack_scanner/raw_stack_scanner_message_callback.c
 *
 * \brief The \ref raw_stack_scanner message handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/raw_character.h>
#include <libcparse/event_handler.h>
#include <libcparse/event_reactor.h>
#include <libcparse/input_stream.h>
#include <libcparse/message.h>
#include <libcparse/message/raw_stack_scanner.h>
#include <libcparse/message/subscription.h>
#include <libcparse/raw_stack_scanner.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "raw_stack_scanner_internal.h"

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_raw_character;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_input_stream;
CPARSE_IMPORT_message;
CPARSE_IMPORT_message_raw_stack_scanner;
CPARSE_IMPORT_message_subscription;
CPARSE_IMPORT_raw_stack_scanner;
CPARSE_IMPORT_raw_stack_scanner_internal;

static int add_input_stream(raw_stack_scanner* scanner, message* msg);
static int subscribe(raw_stack_scanner* scanner, const message* msg);
static int run(raw_stack_scanner* scanner, const message* msg);
static void update_cursor(cursor* pos, int ch);
static int broadcast_raw_character_event(
    raw_stack_scanner* scanner, const cursor* pos, int ch);
static int broadcast_eof_event(raw_stack_scanner* scanner, const cursor* pos);
static int pop_stack(raw_stack_scanner* scanner);

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

        case CPARSE_MESSAGE_TYPE_RUN:
            return run(scanner, msg);

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

/**
 * \brief Run the raw_stack_scanner, kicking off the parser.
 *
 * \param scanner           The scanner for this operation.
 * \param msg               The message for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int run(raw_stack_scanner* scanner, const message* msg)
{
    (void)msg;
    int retval;
    cursor running_pos;
    raw_stack_entry* ent;
    int ch;
    char name_cache[256];

    /* initialize the running cursor. */
    memset(&running_pos, 0, sizeof(running_pos));
    running_pos.begin_line = running_pos.end_line = 1;
    running_pos.begin_col = running_pos.end_col = 1;
    running_pos.file = "(null)";

    /* iterate over all input sources. */
    while (NULL != scanner->head)
    {
        ent = scanner->head;

        /* copy the running cursor. */
        memcpy(&running_pos, &ent->pos, sizeof(running_pos));

        /* read a character from the input stream. */
        retval = input_stream_read(ent->stream, &ch);

        /* if we've reached EOF... */
        if (ERROR_LIBCPARSE_INPUT_STREAM_EOF == retval)
        {
            /* cache the current name. */
            strlcpy(name_cache, ent->pos.file, sizeof(name_cache));
            running_pos.file = name_cache;

            /* pop this entry off of the stack. */
            retval = pop_stack(scanner);
            if (STATUS_SUCCESS != retval)
            {
                goto done;
            }

            /* skip to the next entry. */
            continue;
        }
        /* any other error is fatal. */
        else if (STATUS_SUCCESS != retval)
        {
            goto done;
        }

        /* update the position in the stream for the next character. */
        update_cursor(&ent->pos, ch);

        /* broadcast this raw character event. */
        retval = broadcast_raw_character_event(scanner, &running_pos, ch);
        if (STATUS_SUCCESS != retval)
        {
            goto done;
        }
    }

    /* broadcast EOF. */
    retval = broadcast_eof_event(scanner, &running_pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    memset(&running_pos, 0, sizeof(running_pos));
    memset(name_cache, 0, sizeof(name_cache));

    return retval;
}

/**
 * \brief Update a cursor with the given character.
 *
 * \param pos               The cursor to update.
 * \param ch                The character to use to update this cursor.
 */
static void update_cursor(cursor* pos, int ch)
{
    switch (ch)
    {
        case '\n':
            pos->begin_line += 1;
            pos->end_line = pos->begin_line;
            pos->begin_col = pos->end_col = 1;
            break;

        default:
            pos->begin_col += 1;
            pos->end_col = pos->begin_col;
            break;
    }
}

/**
 * \brief Broadcast a raw character event to the event reactor.
 *
 * \param scanner           The scanner instance for this operation.
 * \param pos               The cursor position for this event.
 * \param ch                The character to broadcast.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_raw_character_event(
    raw_stack_scanner* scanner, const cursor* pos, int ch)
{
    int retval, release_retval;
    event_raw_character rev;

    /* create an event for this character. */
    retval = event_raw_character_init(&rev, pos, ch);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this event. */
    retval =
        event_reactor_broadcast(
            scanner->reactor, event_raw_character_upcast(&rev));
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_rev;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_rev;

cleanup_rev:
    release_retval = event_raw_character_dispose(&rev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Broadcast an EOF event to the event reactor.
 *
 * \param scanner           The scanner instance for this operation.
 * \param pos               The cursor position for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int broadcast_eof_event(raw_stack_scanner* scanner, const cursor* pos)
{
    int retval, release_retval;
    event ev;

    /* Create an EOF event. */
    retval = event_init(&ev, CPARSE_EVENT_TYPE_EOF, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast the EOF event. */
    retval = event_reactor_broadcast(scanner->reactor, &ev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_ev;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_ev;

cleanup_ev:
    release_retval = event_dispose(&ev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Pop the top input stream stack entry.
 *
 * \param scanner           The scanner for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int pop_stack(raw_stack_scanner* scanner)
{
    int retval;

    /* get the top entry on the stack. */
    raw_stack_entry* ent = scanner->head;

    /* if it is NULL, we are done. */
    if (NULL == ent)
    {
        retval = STATUS_SUCCESS;
        goto done;
    }

    /* pop this entry off of the stack. */
    scanner->head = ent->next;

    /* release this entry. */
    retval = raw_stack_entry_release(ent);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

done:
    return retval;
}
