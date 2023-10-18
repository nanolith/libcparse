/**
 * \file src/event_reactor/event_reactor_internal.h
 *
 * \brief Internal definitions for event_reactor.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event_handler.h>
#include <libcparse/event_reactor.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief An \ref event_handler entry in the \ref event_reactor.
 */
typedef struct CPARSE_SYM(event_reactor_entry) CPARSE_SYM(event_reactor_entry);

struct CPARSE_SYM(event_reactor_entry)
{
    CPARSE_SYM(event_reactor)* next;
    CPARSE_SYM(event_handler) handler;
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
