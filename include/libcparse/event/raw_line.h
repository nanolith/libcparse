/**
 * \file libcparse/event/raw_line.h
 *
 * \brief The \ref event_raw_line type indicates the scan of a raw preprocessor
 * control line.
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
typedef struct CPARSE_SYM(event_raw_line) CPARSE_SYM(event_raw_line);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
