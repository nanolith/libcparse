/**
 * \file libcparse/string_utils.h
 *
 * \brief Helper utilities for dealing with strings.
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

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Clear and free a string.
 *
 * \param str               The string to clear and free.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
void CPARSE_SYM(string_utils_string_release)(char* str);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
