/**
 * \file libcparse/event/raw_character_literal.h
 *
 * \brief The \ref event_raw_character_literal type represents a raw character
 * literal token that hasn't yet been fully interpreted.
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
 * \brief The raw string event type represents a partially interpreted string
 * constant token.
 */
typedef struct CPARSE_SYM(event_raw_character_literal)
CPARSE_SYM(event_raw_character_literal);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
