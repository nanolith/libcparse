/**
 * \file libcparse/message_handler/detail.h
 *
 * \brief \ref message_handler details.
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

typedef int (*CPARSE_SYM(message_callback_fn))(
    void* context, const CPARSE_SYM(message)* msg);

struct CPARSE_SYM(message_handler)
{
    CPARSE_SYM(message_callback_fn) message_callback;
    void* context;
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
