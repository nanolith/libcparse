/**
 * \file libcparse/event/raw_character.h
 *
 * \brief The \ref event_raw_character type indicates the scan of a raw
 * character.
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
 * \brief The raw character event type indicates the scan of a single raw
 * character.
 */
typedef struct CPARSE_SYM(event_raw_character) CPARSE_SYM(event_raw_character);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
