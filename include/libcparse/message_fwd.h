/**
 * \file libcparse/message_fwd.h
 *
 * \brief Forward decls for message.
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
 * \brief The message type abstracts individual lexer or parser messages.
 */
typedef struct CPARSE_SYM(message) CPARSE_SYM(message);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
