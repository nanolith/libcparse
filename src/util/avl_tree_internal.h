/**
 * \file src/util/avl_tree.h
 *
 * \brief Private details for the AVL tree implementation.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/util/avl_tree.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

struct CPARSE_SYM(avl_tree_node)
{
    CPARSE_SYM(avl_tree_node)* parent;
    CPARSE_SYM(avl_tree_node)* left;
    CPARSE_SYM(avl_tree_node)* right;
    int height;
    void* element;
};

struct CPARSE_SYM(avl_tree)
{
    CPARSE_SYM(avl_tree_compare_fn) compare_fn;
    CPARSE_SYM(avl_tree_key_fn) key_fn;
    CPARSE_SYM(avl_tree_element_release_fn) release_fn;
    void* context;
    CPARSE_SYM(avl_tree_node)* root;
    size_t count;
};

/******************************************************************************/
/* Start of private methods.                                                  */
/******************************************************************************/

/**
 * \brief Find an \ref avl_tree_node matching the given key in a \ref avl_tree
 * instance.
 *
 * \param node          Pointer to the node pointer to receive the
 *                      \ref avl_tree_node on success.
 * \param tree          The \ref avl_tree for this find operation.
 * \param key           The user-defined key for this find operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - ERROR_LIBCPARSE_AVL_TREE_ELEMENT_NOT_FOUND if the element was not
 *        found.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(avl_tree_find_node)(
    CPARSE_SYM(avl_tree_node)** node, const CPARSE_SYM(avl_tree)* tree,
    const void* key);

/******************************************************************************/
/* Start of private exports.                                                  */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_util_avl_tree_internal_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    static inline int sym ## avl_tree_find_node( \
        CPARSE_SYM(avl_tree_node)** x, const CPARSE_SYM(avl_tree)* y, \
        const void* z) { \
            return CPARSE_SYM(avl_tree_find_node)(x,y,z); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_util_avl_tree_internal_as(sym) \
    __INTERNAL_CPARSE_IMPORT_util_avl_tree_internal_sym(sym ## _)
#define CPARSE_IMPORT_util_avl_tree_internal \
    __INTERNAL_CPARSE_IMPORT_util_avl_tree_internal_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
