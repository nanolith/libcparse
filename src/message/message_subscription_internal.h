/**
 * \file src/message/message_subscription_internal.h
 *
 * \brief Internal declarations for the subscription message type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/message/subscription.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/******************************************************************************/
/* Start of private constructors.                                             */
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

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
