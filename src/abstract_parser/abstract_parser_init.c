/**
 * \file src/abstract_parser/abstract_parser_init.c
 *
 * \brief Init method for the \ref abstract_parser type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/status_codes.h>
#include <string.h>

CPARSE_IMPORT_message_handler;

/**
 * \brief Initialize an \ref abstract_parser from a root \ref message_handler.
 *
 * \param ap                    The abstract parser instance to initialize.
 * \param mh                    The root \ref message_handler for this parser.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(abstract_parser_init)(
    CPARSE_SYM(abstract_parser)* ap, const CPARSE_SYM(message_handler)* mh)
{
    int retval;

    /* clear the instance. */
    memset(ap, 0, sizeof(*ap));

    /* copy the message handler. */
    retval = message_handler_init_copy(&ap->mh, mh);
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
