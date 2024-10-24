/**
 * \file src/util/avl_tree_root_node.c
 *
 * \brief Get the root node of the given tree.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "avl_tree_internal.h"

CPARSE_IMPORT_util_avl_tree;

/**
 * \brief Return the root node pointer for this tree.
 *
 * \param tree          The \ref avl_tree instance.
 *
 * \returns the root pointer for this tree, or NULL if the tree is empty.
 */
CPARSE_SYM(avl_tree_node)*
CPARSE_SYM(avl_tree_root_node)(CPARSE_SYM(avl_tree)* tree)
{
    return tree->root;
}
