/**
 * \file libcparse/event_reactor.h
 *
 * \brief The \ref event_reactor registers event handlers and broadcasts events
 * to them.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The event reactor provides event management support for a parser.
 */
typedef struct CPARSE_SYM(event_reactor) CPARSE_SYM(event_reactor);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
