/**
 * \file src/util/avl_tree_find.c
 *
 * \brief Find an element in the \ref avl_tree instance matching the given key.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>

#include "avl_tree_internal.h"

CPARSE_IMPORT_util_avl_tree;
CPARSE_IMPORT_util_avl_tree_internal;

/**
 * \brief Find an element in the \ref avl_tree instance matching the given
 * user-defined key.
 *
 * \param elem          Pointer to the elem pointer to set to the found element.
 * \param tree          The \ref avl_tree for this find operation.
 * \param key           The user-defined key for this find operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - ERROR_LIBCPARSE_AVL_TREE_ELEMENT_NOT_FOUND if the element was not
 *        found.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(avl_tree_find)(
    void** elem, const CPARSE_SYM(avl_tree)* tree, const void* key)
{
    avl_tree_node* node;

    /* attempt to find the matching node. */
    int retval = avl_tree_find_node(&node, tree, key);
    if (STATUS_SUCCESS != retval)
    {
        *elem = NULL;
        return retval;
    }

    /* success. */
    *elem = node->element;
    return STATUS_SUCCESS;
}
