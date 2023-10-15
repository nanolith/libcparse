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

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Initialize a \ref message_run instance.
 *
 * \param msg               The message to initialize.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_run_init)(CPARSE_SYM(message_run)* msg);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
