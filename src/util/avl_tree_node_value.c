/**
 * \file src/util/avl_tree_node_value.c
 *
 * \brief Get the value of a \ref avl_tree_node instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "avl_tree_internal.h"

CPARSE_IMPORT_util_avl_tree;

/**
 * \brief Return the value associated with a given \ref avl_tree_node.
 *
 * \param tree          The \ref avl_tree instance.
 * \param node          The \ref avl_tree_node accessed.
 *
 * \returns the value associated with this node.
 */
void*
CPARSE_SYM(avl_tree_node_value)(
    CPARSE_SYM(avl_tree)* tree, CPARSE_SYM(avl_tree_node)* node)
{
    (void)tree;

    return node->element;
}
