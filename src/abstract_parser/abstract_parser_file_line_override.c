/**
 * \file src/abstract_parser/abstract_parser_file_line_override.c
 *
 * \brief Send a file/line override request to the
 * \ref raw_file_line_override_filter.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/message/file_line_override.h>
#include <libcparse/message_type.h>
#include <libcparse/status_codes.h>

CPARSE_IMPORT_message_handler;
CPARSE_IMPORT_message_file_line_override;

/**
 * \brief Override the line number and file name in the file / line override
 * filter.
 *
 * \note This operation also overrides the column number, setting it to 1.
 *
 * \param ap                The \ref abstract_parser for this operation.
 * \param line              The new line number.
 * \param file              The new file name, or NULL to keep it the same.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int
CPARSE_SYM(abstract_parser_file_line_override)(
    CPARSE_SYM(abstract_parser)* ap, unsigned int line, const char* file)
{
    int retval, release_retval;
    message_file_line_override msg;

    /* initialize the message. */
    retval =
        message_file_line_override_init(
            &msg, CPARSE_MESSAGE_TYPE_RFLO_FILE_LINE_OVERRIDE, file, line);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* send the message. */
    retval =
        message_handler_send(&ap->mh, message_file_line_override_upcast(&msg));
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_msg;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_msg;

cleanup_msg:
    release_retval = message_file_line_override_dispose(&msg);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
