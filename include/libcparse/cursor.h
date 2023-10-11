/**
 * \file libcparse/cursor.h
 *
 * \brief The cursor type describes location data for an event.
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
 * \brief The cursor type describes location data for an event.
 */
typedef struct CPARSE_SYM(cursor) CPARSE_SYM(cursor);

struct CPARSE_SYM(cursor)
{
    const char* file;
    int begin_line;
    int begin_col;
    int end_line;
    int end_col;
};

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_CPARSE_IMPORT_cursor_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(cursor) sym ## cursor; \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_cursor_as(sym) \
    __INTERNAL_CPARSE_IMPORT_cursor_sym(sym ## _)
#define CPARSE_IMPORT_cursor \
    __INTERNAL_CPARSE_IMPORT_cursor_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
