/**
 * \file libcparse/event_handler_fwd.h
 *
 * \brief Forward decls for \ref event_handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief An event callback function responds to an event.
 *
 * \param context               A user-supplied context pointer given to the
 *                              callback.
 * \param ev                    An event to which this callback is subscribed.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
typedef int (*CPARSE_SYM(event_callback_fn))(
    void* context, const CPARSE_SYM(event)* ev);

/**
 * \brief An event handler accepts an event.
 */
typedef struct CPARSE_SYM(event_handler) CPARSE_SYM(event_handler);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
