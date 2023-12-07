/**
 * \file libcparse/string_builder.h
 *
 * \brief The \ref string_builder type builds a string in a more efficient and
 * generic way by using internal chunks that can be bucket allocated.
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
 * \brief The string builder type builds strings.
 */
typedef struct CPARSE_SYM(string_builder) CPARSE_SYM(string_builder);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
