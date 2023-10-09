/**
 * \file libcparse/message/subscription.h
 *
 * \brief Messages to subscribe to parser endpoints.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

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

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
