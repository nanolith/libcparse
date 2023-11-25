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
#include <stdbool.h>

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
    CPARSE_MESSAGE_TYPE_RUN =                                            0x0001,
    CPARSE_MESSAGE_TYPE_RSS_ADD_INPUT_STREAM =                           0x0002,
    CPARSE_MESSAGE_TYPE_RSS_SUBSCRIBE =                                  0x0003,
    CPARSE_MESSAGE_TYPE_RFLO_SUBSCRIBE =                                 0x0004,
    CPARSE_MESSAGE_TYPE_COMMENT_SCANNER_SUBSCRIBE =                      0x0005,
    CPARSE_MESSAGE_TYPE_COMMENT_FILTER_SUBSCRIBE =                       0x0006,
    CPARSE_MESSAGE_TYPE_LINE_WRAP_FILTER_SUBSCRIBE =                     0x0007,
    CPARSE_MESSAGE_TYPE_NEWLINE_PRESERVING_WHITESPACE_FILTER_SUBSCRIBE = 0x0008,
    CPARSE_MESSAGE_TYPE_RFLO_FILE_LINE_OVERRIDE =                        0x0009,
    CPARSE_MESSAGE_TYPE_UNKNOWN =                                        0xFFFF,
};

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Verify that a message type is a valid subscription type.
 *
 * \param msg_type                  The message type to check.
 *
 * \returns true if this is a subscription message type, or false otherwise.
 */
bool CPARSE_SYM(message_type_valid_subscription_type)(int msg_type);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_CPARSE_IMPORT_message_type_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    static inline bool sym ## message_type_valid_subscription_type(int x) { \
            return CPARSE_SYM(message_type_valid_subscription_type)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_message_type_as(sym) \
    __INTERNAL_CPARSE_IMPORT_message_type_sym(sym ## _)
#define CPARSE_IMPORT_message_type \
    __INTERNAL_CPARSE_IMPORT_message_type_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
