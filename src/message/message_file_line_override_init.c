/**
 * \file src/message/message_file_line_override_init.c
 *
 * \brief Init method for the \ref message_file_line_override type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/file_line_override.h>
#include <libcparse/status_codes.h>
#include <string.h>

CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_message;

/**
 * \brief Initialize a \ref message_file_line_override instance.
 *
 * \param msg               The message to initialize.
 * \param msg_type          The type of file/line override message.
 * \param file              The new name of the file, which is optional and can
 *                          be NULL if unchanged.
 * \param line              The line to override.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_file_line_override_init)(
    CPARSE_SYM(message_file_line_override)* msg, int msg_type,
    const char* file, unsigned int line)
{
    int retval, release_retval;

    /* clear the message buffer. */
    memset(msg, 0, sizeof(*msg));

    /* initialize the base message. */
    retval = message_init(&msg->hdr, msg_type);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* copy the file. */
    msg->file = strdup(file);
    if (NULL == msg->file)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto cleanup_msg;
    }

    /* copy the other fields. */
    msg->line = line;

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

cleanup_msg:
    release_retval = message_dispose(&msg->hdr);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
