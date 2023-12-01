/**
 * \file libcparse/event/include.h
 *
 * \brief The \ref event_include type indicates the scan of a system
 * or local include preprocessor control line.
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
 * \brief The include event type indicates the scan of a single include
 * preprocessor control line.
 */
typedef struct CPARSE_SYM(event_include)
CPARSE_SYM(event_include);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
