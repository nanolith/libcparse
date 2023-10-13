/**
 * \file libcparse/input_stream_fwd.h
 *
 * \brief Forward decl for \ref input_stream.
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
