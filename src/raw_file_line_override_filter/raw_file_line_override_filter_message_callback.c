/**
 * \file
 * src/raw_file_line_override_filter/raw_file_line_override_filter_message_callback.c
 *
 * \brief The \ref raw_file_line_override_filter message handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/cursor.h>
#include <libcparse/event_handler.h>
#include <libcparse/event_reactor.h>
#include <libcparse/message.h>
#include <libcparse/message/file_line_override.h>
#include <libcparse/message/subscription.h>
#include <libcparse/raw_file_line_override_filter.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "raw_file_line_override_filter_internal.h"

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_message;
CPARSE_IMPORT_message_file_line_override;
CPARSE_IMPORT_message_handler;
CPARSE_IMPORT_message_subscription;
CPARSE_IMPORT_raw_file_line_override_filter;

static int subscribe(raw_file_line_override_filter* filter, const message* msg);
static int file_line_override(
    raw_file_line_override_filter* filter, const message* msg);
static int file_set(raw_file_line_override_filter* filter, const char* file);

/**
 * \brief Message handler callback for \ref raw_file_line_override_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref raw_file_line_override_filter instance).
 * \param msg               A message for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(raw_file_line_override_filter_message_callback)(
    void* context, const CPARSE_SYM(message)* msg)
{
    raw_file_line_override_filter* filter =
        (raw_file_line_override_filter*)context;

    switch (message_get_type(msg))
    {
        case CPARSE_MESSAGE_TYPE_RFLO_SUBSCRIBE:
            return subscribe(filter, msg);

        case CPARSE_MESSAGE_TYPE_RFLO_FILE_LINE_OVERRIDE:
            return file_line_override(filter, msg);

        default:
            return message_handler_send(&filter->parent_mh, msg);
    }
}

/**
 * \brief Subscribe to the raw_file_line_override_filter.
 *
 * \param filter            The filter for this operation.
 * \param msg               The message for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int subscribe(raw_file_line_override_filter* filter, const message* msg)
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

/**
 * \brief Override the file and line for this filter.
 *
 * \param filter            The filter for this operation.
 * \param msg               The message for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int file_line_override(
    raw_file_line_override_filter* filter, const message* msg)
{
    int retval;
    message_file_line_override* m;
    cursor tmp;

    /* dynamic cast the message. */
    retval = message_downcast_to_message_file_line_override(&m, (message*)msg);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* get the line for this message. */
    unsigned int line = message_file_line_override_line_get(m);

    /* get the file for this message. */
    const char* file = message_file_line_override_file_get(m);

    /* set the new cursor values. */
    memset(&tmp, 0, sizeof(tmp));
    tmp.begin_line = tmp.end_line = line;
    tmp.begin_col = tmp.end_col = 1;

    /* set the file. */
    retval = file_set(filter, file);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* success. */
    filter->use_pos = true;
    memcpy(&filter->pos, &tmp, sizeof(filter->pos));
    filter->pos.file = filter->file;
    retval = STATUS_SUCCESS;
    goto done;

done:
    memset(&tmp, 0, sizeof(tmp));
    return retval;
}

/**
 * \brief Set the file for the override filter.
 *
 * \param filter                The filter for this operation.
 * \param file                  The file to set.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int file_set(raw_file_line_override_filter* filter, const char* file)
{
    char* tmp;

    /* duplicate the file string if set. */
    if (NULL != file)
    {
        tmp = strdup(file);
        if (NULL == tmp)
        {
            return ERROR_LIBCPARSE_OUT_OF_MEMORY;
        }
    }
    /* otherwise, the new file string is NULL. */
    else
    {
        tmp = NULL;
    }

    /* clear and free the filter file if set. */
    if (NULL != filter->file)
    {
        memset(filter->file, 0, strlen(filter->file));
        free(filter->file);
        filter->file = NULL;
    }

    /* set the filter file to our new file. */
    filter->file = tmp;

    /* success. */
    return STATUS_SUCCESS;
}
