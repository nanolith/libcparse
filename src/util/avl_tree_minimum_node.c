/**
 * \file src/util/avl_tree_minimum_node.c
 *
 * \brief Get the minimum node of the given tree.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "avl_tree_internal.h"

CPARSE_IMPORT_util_avl_tree;

/**
 * \brief Return the minimum node in a \ref avl_tree subtree.
 *
 * \param tree          The \ref avl_tree instance.
 * \param x             The \ref avl_tree_node from which the search should
 *                      start.
 *
 * \returns the minimum node in this subtree.
 */
CPARSE_SYM(avl_tree_node)*
CPARSE_SYM(avl_tree_minimum_node)(
    CPARSE_SYM(avl_tree)* tree, CPARSE_SYM(avl_tree_node)* x)
{
    (void)tree;

    while (x->left != NULL)
    {
        x = x->left;
    }

    return x;
}
