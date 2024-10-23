/**
 * \file src/util/avl_tree_create.c
 *
 * \brief Create an \ref avl_tree instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>

#include "avl_tree_internal.h"

CPARSE_IMPORT_util_avl_tree;

/**
 * \brief Create a new \ref avl_tree instance.
 *
 * \param tree                  Pointer to the \ref avl_tree pointer to set to
 *                              the created instance on success.
 * \param compare               The comparison function to use for this tree.
 * \param key                   The key function to use for this tree.
 * \param release               The element release function to use for this
 *                              tree.
 * \param context               The user context to use for this tree.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(avl_tree_create)(
    CPARSE_SYM(avl_tree)** tree, CPARSE_SYM(avl_tree_compare_fn) compare,
    CPARSE_SYM(avl_tree_key_fn) key,
    CPARSE_SYM(avl_tree_element_release_fn) release, void* context)
{
    int retval;
    avl_tree* tmp;

    /* allocate memory for the tree. */
    tmp = (avl_tree*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* set up tree. */
    tmp->compare_fn = compare;
    tmp->key_fn = key;
    tmp->release_fn = release;
    tmp->context = context;
    tmp->root = NULL;
    tmp->count = 0;

    /* success. */
    *tree = tmp;
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
