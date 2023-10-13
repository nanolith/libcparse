/**
 * \file libcparse/abstract_parser.h
 *
 * \brief The \ref abstract_parser provides a unified interface for scanners and
 * parsers.
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
 * \brief The abstract parser is a unified interface for parsers and scanners.
 */
typedef struct CPARSE_SYM(abstract_parser) CPARSE_SYM(abstract_parser);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
