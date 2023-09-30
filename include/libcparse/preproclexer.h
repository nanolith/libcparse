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

#include <libcparse/event.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The preproclexer type returns tokens read from an input buffer.
 */
typedef struct CPARSE_SYM(preproclexer) CPARSE_SYM(preproclexer);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_CPARSE_IMPORT_preproclexer_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(preproclexer) sym ## preproclexer; \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_preproclexer_as(sym) \
    __INTERNAL_CPARSE_IMPORT_preproclexer_sym(sym ## _)
#define CPARSE_IMPORT_preproclexer \
    __INTERNAL_CPARSE_IMPORT_preproclexer_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
