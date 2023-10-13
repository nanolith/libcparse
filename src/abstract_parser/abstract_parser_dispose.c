/**
 * \file src/abstract_parser/abstract_parser_dispose.c
 *
 * \brief Dispose method for the \ref abstract_parser type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/status_codes.h>
#include <string.h>

CPARSE_IMPORT_message_handler;

/**
 * \brief Dispose a \ref abstract_parser instance.
 *
 * \param ap                    The abstract parser instance to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(abstract_parser_dispose)(CPARSE_SYM(abstract_parser)* ap)
{
    int mh_dispose_retval = STATUS_SUCCESS;

    /* dispose the message handler. */
    mh_dispose_retval = message_handler_dispose(&ap->mh);

    /* clear the structure. */
    memset(ap, 0, sizeof(*ap));

    return mh_dispose_retval;
}
