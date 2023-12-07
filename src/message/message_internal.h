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

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
