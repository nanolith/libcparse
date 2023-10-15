/**
 * \file src/abstract_parser/abstract_parser_run.c
 *
 * \brief Send the run message to the \ref abstract_parser, starting the parse.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/message/run.h>
#include <libcparse/status_codes.h>

CPARSE_IMPORT_message_handler;
CPARSE_IMPORT_message_run;

/**
 * \brief Run an abstract parser instance.
 *
 * \param ap                    The abstract parser instance to run.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(abstract_parser_run)(CPARSE_SYM(abstract_parser)* ap)
{
    int retval, release_retval;
    message_run msg;

    /* initialize the message. */
    retval = message_run_init(&msg);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* send the message. */
    retval = message_handler_send(&ap->mh, message_run_upcast(&msg));
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_msg;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_msg;

cleanup_msg:
    release_retval = message_run_dispose(&msg);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
