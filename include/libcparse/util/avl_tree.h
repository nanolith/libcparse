/**
 * \file libcparse/util/avl_tree.h
 *
 * \brief AVL tree implementation.
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
 * \brief The avl_tree type is a container that provides O(log n) lookup and
 * O(n log n) traversal of elements stored by key.
 */
typedef struct CPARSE_SYM(avl_tree) CPARSE_SYM(avl_tree);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_util_avl_tree_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(avl_tree) sym ## avl_tree; \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_util_avl_tree_as(sym) \
    __INTERNAL_CPARSE_IMPORT_util_avl_tree_sym(sym ## _)
#define CPARSE_IMPORT_util_avl_tree \
    __INTERNAL_CPARSE_IMPORT_util_avl_tree_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
