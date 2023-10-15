/**
 * \file src/message/message_run_upcast.c
 *
 * \brief Upcast this \ref message_run instance to the base \ref message
 * instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/run.h>

/**
 * \brief Upcast a \ref message_run to a \ref message.
 *
 * \param msg               The \ref message_run to upcast.
 *
 * \returns the \ref message instance for this message.
 */
CPARSE_SYM(message)* CPARSE_SYM(message_run_upcast)(
    CPARSE_SYM(message_run)* msg)
{
    return &msg->hdr;
}
