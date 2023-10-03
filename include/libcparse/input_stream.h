/**
 * \file libcparse/input_stream.h
 *
 * \brief The input stream abstracts input, which can be from a file, a memory
 * buffer, or from a mock.
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
 * \brief The input stream abstracts input for the parser.
 */
typedef struct CPARSE_SYM(input_stream) CPARSE_SYM(input_stream);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
