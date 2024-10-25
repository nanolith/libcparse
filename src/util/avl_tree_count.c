/**
 * \file src/util/avl_tree_count.c
 *
 * \brief Get the count of elements in this \ref avl_tree instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "avl_tree_internal.h"

CPARSE_IMPORT_util_avl_tree;

/**
 * \brief Return the count of elements currently in this \ref avl_tree instance.
 *
 * \param tree          The \ref avl_tree instance.
 *
 * \returns the count of elements in the \ref avl_tree instance.
 */
size_t
CPARSE_SYM(avl_tree_count)(CPARSE_SYM(avl_tree)* tree)
{
    return tree->count;
}
