/**
 * \file libcparse/message/subscription.h
 *
 * \brief Messages to subscribe to parser endpoints.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event_handler.h>
#include <libcparse/function_decl.h>
#include <libcparse/message.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief the subscribe message allows a user to subscribe to an endpoint.
 */
typedef struct CPARSE_SYM(message_subscribe)
CPARSE_SYM(message_subscribe);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Initialize a \ref message_subscribe instance.
 *
 * \param msg               The message to initialize.
 * \param msg_type          The type of subscription message.
 * \param handler           The \ref event_handler to add to this endpoint.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_subscribe_init)(
    CPARSE_SYM(message_subscribe)* msg, int msg_type,
    CPARSE_SYM(event_handler)* handler);

/**
 * \brief Dispose of a \ref message_subscribe instance.
 *
 * \param msg               The message to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_subscribe_dispose)(CPARSE_SYM(message_subscribe)* msg);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the \ref event_handler associated with a \ref message_subscribe
 * instance.
 *
 * \param msg               The message to query.
 *
 * \returns the \ref event_handler associated with this message.
 */
const CPARSE_SYM(event_handler)*
CPARSE_SYM(message_subscribe_event_handler_get)(
    const CPARSE_SYM(message_subscribe)* msg);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
