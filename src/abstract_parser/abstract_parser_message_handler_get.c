/**
 * \file src/abstract_parser/abstract_parser_message_handler_get.c
 *
 * \brief Get the message handler associated with the given abstract parser.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>

/**
 * \brief Get the message handler for this abstract parser.
 *
 * \param ap                    The abstract parser instance to query.
 *
 * \returns the \ref message_handler instance for this abstract parser instance.
 */
CPARSE_SYM(message_handler)*
CPARSE_SYM(abstract_parser_message_handler_get)(
    CPARSE_SYM(abstract_parser)* ap)
{
    return &ap->mh;
}
