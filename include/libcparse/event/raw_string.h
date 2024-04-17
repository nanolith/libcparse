/**
 * \file libcparse/event/raw_string.h
 *
 * \brief The \ref event_raw_string_token type represents a raw string token
 * that hasn't yet been fully interpreted.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/function_decl.h>
#include <stdint.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The raw string event type represents a partially interpreted string
 * constant token.
 */
typedef struct CPARSE_SYM(event_raw_string_token)
CPARSE_SYM(event_raw_string_token);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
