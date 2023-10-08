/**
 * \file libcparse/message.h
 *
 * \brief The message type represents an individual lexer or parser message.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/message_type.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The message type abstracts individual lexer or parser messages.
 */
typedef struct CPARSE_SYM(message) CPARSE_SYM(message);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Initialize a \ref message.
 *
 * \param msg                   The message to initialize.
 * \param msg_type              The message type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_init)(CPARSE_SYM(message)* msg, int msg_type);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the message type for the given message.
 *
 * \param msg                   The message to query.
 *
 * \returns the \ref event_type for this event.
 */
int CPARSE_SYM(message_get_type)(const CPARSE_SYM(message)* msg);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_CPARSE_IMPORT_message_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(message) sym ## message; \
    static inline int sym ## message_get_type(const CPARSE_SYM(message)* x) { \
        return CPARSE_SYM(message_get_type)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_message_as(sym) \
    __INTERNAL_CPARSE_IMPORT_message_sym(sym ## _)
#define CPARSE_IMPORT_message \
    __INTERNAL_CPARSE_IMPORT_message_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
