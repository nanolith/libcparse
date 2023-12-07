/**
 * \file src/message/message_internal.h
 *
 * \brief Internal declarations for the message type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/message.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/******************************************************************************/
/* Start of private constructors.                                             */
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

/**
 * \brief Dispose a \ref message.
 *
 * \param msg                   The message to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_dispose)(CPARSE_SYM(message)* msg);

/******************************************************************************/
/* Start of private exports.                                                  */
/******************************************************************************/
#define __INTERNAL_CPARSE_IMPORT_message_internal_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    static inline int sym ## message_init( \
        CPARSE_SYM(message)* x, int y) { \
            return CPARSE_SYM(message_init)(x,y); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_message_internal_as(sym) \
    __INTERNAL_CPARSE_IMPORT_message_internal_sym(sym ## _)
#define CPARSE_IMPORT_message_internal \
    __INTERNAL_CPARSE_IMPORT_message_internal_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
