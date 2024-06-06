/**
 * \file libcparse/event/raw_float.h
 *
 * \brief The \ref event_raw_float type represents a raw floating point literal
 * token event before it has been differentiated into a numerical value.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/function_decl.h>
#include <libcparse/event/integer.h>
#include <stdint.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The raw float event type represents a partially interpreted floating
 * point constant token.
 */
typedef struct CPARSE_SYM(event_raw_float_token)
CPARSE_SYM(event_raw_float_token);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
