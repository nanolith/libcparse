/**
 * \file src/util/avl_tree_maximum_node.c
 *
 * \brief Get the maximum node of the given tree.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "avl_tree_internal.h"

CPARSE_IMPORT_util_avl_tree;

/**
 * \brief Return the maximum node in a \ref avl_tree subtree.
 *
 * \param tree          The \ref avl_tree instance.
 * \param x             The \ref avl_tree_node from which the search should
 *                      start.
 *
 * \returns the maximum node in this subtree.
 */
CPARSE_SYM(avl_tree_node)*
CPARSE_SYM(avl_tree_maximum_node)(
    CPARSE_SYM(avl_tree)* tree, CPARSE_SYM(avl_tree_node)* x)
{
    (void)tree;

    while (x->right != NULL)
    {
        x = x->right;
    }

    return x;
}
