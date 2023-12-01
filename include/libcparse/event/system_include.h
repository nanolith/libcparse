/**
 * \file libcparse/event/system_include.h
 *
 * \brief The \ref event_system_include type indicates the scan of a system
 * include preprocessor control line.
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
 * \brief The raw line event type indicates the scan of a single raw
 * preprocessor control line.
 */
typedef struct CPARSE_SYM(event_system_include)
CPARSE_SYM(event_system_include);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
