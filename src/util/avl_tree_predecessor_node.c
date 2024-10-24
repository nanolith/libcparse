/**
 * \file src/util/avl_tree_predecessor_node.c
 *
 * \brief Get the predecessor node of the given node.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "avl_tree_internal.h"

CPARSE_IMPORT_util_avl_tree;

/**
 * \brief Return the in-order predecessor node of the given node.
 *
 * \param tree          The \ref avl_tree instance.
 * \param x             The \ref avl_tree_node from which the predecessor is
 *                      found.
 *
 * \returns the predecessor node of this node, or NULL if none is found.
 */
CPARSE_SYM(avl_tree_node)*
CPARSE_SYM(avl_tree_predecessor_node)(
    CPARSE_SYM(avl_tree)* tree, CPARSE_SYM(avl_tree_node)* x)
{
    (void)tree;

    if (x->left != NULL)
    {
        return avl_tree_maximum_node(tree, x->left);
    }

    avl_tree_node* y = x->parent;

    while (y != NULL && x == y->left)
    {
        x = y;
        y = y->parent;
    }

    return y;
}
