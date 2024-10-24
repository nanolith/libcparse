/**
 * \file src/util/avl_tree_find_node.c
 *
 * \brief Find a node matching the given key.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>

#include "avl_tree_internal.h"

CPARSE_IMPORT_util_avl_tree;

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
    const void* key)
{
    avl_tree_node* x = tree->root;

    while (x != NULL)
    {
        const void* x_key = tree->key_fn(tree->context, x->element);

        int compare_result = tree->compare_fn(tree->context, key, x_key);
        if (compare_result == 0)
        {
            *node = x;
            return STATUS_SUCCESS;
        }
        else if (compare_result < 0)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    return ERROR_LIBCPARSE_AVL_TREE_ELEMENT_NOT_FOUND;
}
