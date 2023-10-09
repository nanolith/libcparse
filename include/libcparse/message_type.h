/**
 * \file libcparse/message_type.h
 *
 * \brief The message_type enumeration describes the type of message.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The message type abstracts individual lexer or parser messages.
 */
enum CPARSE_SYM(message_type)
{
    /* Messages supported by \ref raw_stack_scanner. */
    CPARSE_MESSAGE_TYPE_RSS_ADD_INPUT_STREAM =                          0x0001,
    CPARSE_MESSAGE_TYPE_RSS_SUBSCRIBE =                                 0x0002,
    CPARSE_MESSAGE_TYPE_UNKNOWN =                                       0xFFFF,
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
