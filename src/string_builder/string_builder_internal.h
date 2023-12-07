/**
 * \file src/string_builder/string_builder_internal.h
 *
 * \brief Internal declarations for \ref string_builder.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/string_builder.h>
#include <stdint.h>
#include <stddef.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

#define CPARSE_STRING_BUILDER_CHUNK_ARRAY_SIZE 100

typedef struct CPARSE_SYM(string_builder_chunk)
CPARSE_SYM(string_builder_chunk);

struct CPARSE_SYM(string_builder_chunk)
{
    CPARSE_SYM(string_builder_chunk)* next;
    char arr[CPARSE_STRING_BUILDER_CHUNK_ARRAY_SIZE];
};

struct CPARSE_SYM(string_builder)
{
    CPARSE_SYM(string_builder_chunk)* head;
    CPARSE_SYM(string_builder_chunk)* tail;
    size_t offset;
};

/******************************************************************************/
/* Start of private exports.                                                  */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_string_builder_internal_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(string_builder_chunk) sym ## string_builder_chunk; \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_string_builder_internal_as(sym) \
    __INTERNAL_CPARSE_IMPORT_string_builder_internal_sym(sym ## _)
#define CPARSE_IMPORT_string_builder_internal \
    __INTERNAL_CPARSE_IMPORT_string_builder_internal_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
