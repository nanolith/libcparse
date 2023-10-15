/**
 * \file libcparse/event_fwd.h
 *
 * \brief Forward declaration of \ref event type.
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

typedef struct CPARSE_SYM(event) CPARSE_SYM(event);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
