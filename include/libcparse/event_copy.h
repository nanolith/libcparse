/**
 * \file libcparse/event_copy.h
 *
 * \brief The event copy type allows an event to be cloned so that its lifetime
 * exceeds the lifetime of the original event on which it was based.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The event copy type abstracts cloned events.
 */
typedef struct CPARSE_SYM(event_copy) CPARSE_SYM(event_copy);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
