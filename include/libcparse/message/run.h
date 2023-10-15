/**
 * \file libcparse/message/run.h
 *
 * \brief Message to instruct the parser to run.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/function_decl.h>
#include <libcparse/message.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief the run message runs the parser.
 */
typedef struct CPARSE_SYM(message_run)
CPARSE_SYM(message_run);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
