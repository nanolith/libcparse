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

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
