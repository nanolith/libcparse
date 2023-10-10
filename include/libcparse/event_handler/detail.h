/**
 * \file libcparse/event_handler/detail.h
 *
 * \brief \ref event_handler details.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/message_handler.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef int (*CPARSE_SYM(event_callback_fn))(
    void* context, const CPARSE_SYM(event)* ev);

struct CPARSE_SYM(event_handler)
{
    CPARSE_SYM(event_callback_fn) event_callback;
    void* context;
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
