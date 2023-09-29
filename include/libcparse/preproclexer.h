/**
 * \file libcparse/preproclexer.h
 *
 * \brief The preprocessor lexer interface returns tokens associated with the
 * C preprocessor.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The preproclexer type returns tokens read from an input buffer.
 */
typedef struct preproclexer preproclexer;

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
