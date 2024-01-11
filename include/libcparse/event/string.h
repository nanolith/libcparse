/**
 * \file libcparse/event/string.h
 *
 * \brief The \ref event_string type represents string token events.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The raw line event type indicates the scan of a single raw
 * preprocessor control line.
 */
typedef struct CPARSE_SYM(event_string) CPARSE_SYM(event_string);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
