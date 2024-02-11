/**
 * \file libcparse/event/integer.h
 *
 * \brief The \ref event_integer_token type represents integer token events.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/function_decl.h>
#include <libcparse/integer_type.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The integer event type represents an integer constant token.
 */
typedef struct CPARSE_SYM(event_integer_token) CPARSE_SYM(event_integer_token);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
