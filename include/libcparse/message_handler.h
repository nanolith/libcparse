/**
 * \file libcparse/message_handler.h
 *
 * \brief The \ref message_handler reacts to a message.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/message.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief A message callback function responds to a message.
 *
 * \param context               A user-supplied context pointer given to the
 *                              callback.
 * \param msg                   A message to which this callback is subscribed.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
typedef int (*CPARSE_SYM(message_callback_fn))(
    void* context, const CPARSE_SYM(message)* ev);

/**
 * \brief A message handler accepts a message.
 */
typedef struct CPARSE_SYM(message_handler) CPARSE_SYM(message_handler);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
