/**
 * \file src/util/avl_tree_delete_nodes.c
 *
 * \brief Recursively delete the given node and all nodes underneath. 
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>

#include "avl_tree_internal.h"

CPARSE_IMPORT_util_avl_tree;
CPARSE_IMPORT_util_avl_tree_internal;

/**
 * \brief Recursively delete all nodes under the given node and the given node
 * in a tree.
 *
 * \param tree          The \ref avl_tree for this delete operation.
 * \param n             The node to recursively delete.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(avl_tree_delete_nodes)(
    CPARSE_SYM(avl_tree)* tree, CPARSE_SYM(avl_tree_node)* n)
{
    int retval_left = STATUS_SUCCESS;
    int retval_right = STATUS_SUCCESS;

    /* recursively delete the left branch. */
    if (NULL != n->left)
    {
        retval_left = avl_tree_delete_nodes(tree, n->left);
    }

    /* recursively delete the right branch. */
    if (NULL != n->right)
    {
        retval_right = avl_tree_delete_nodes(tree, n->right);
    }

    /* release this node. */
    int node_release_retval = tree->release_fn(tree->context, n->element);
    free(n);

    /* decode return value. */
    if (STATUS_SUCCESS != retval_left)
        return retval_left;
    if (STATUS_SUCCESS != retval_right)
        return retval_right;
    return node_release_retval;
}
