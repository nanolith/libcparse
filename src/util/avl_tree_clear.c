/**
 * \file src/util/avl_tree_clear.c
 *
 * \brief Clear an \ref avl_tree instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>

#include "avl_tree_internal.h"

CPARSE_IMPORT_util_avl_tree;
CPARSE_IMPORT_util_avl_tree_internal;

/**
 * \brief Clear all elements from an \ref avl_tree instance, calling the
 * user-defined release method on each element in the tree.
 *
 * \param tree          The \ref avl_tree for this clear operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(avl_tree_clear)(CPARSE_SYM(avl_tree)* tree)
{
    int retval = STATUS_SUCCESS;

    /* delete all nodes in the tree if the tree is not empty. */
    if (NULL != tree->root)
    {
        retval = avl_tree_delete_nodes(tree, tree->root);
    }

    /* now the tree is empty. */
    tree->root = NULL;
    tree->count = 0;

    return retval;
}
