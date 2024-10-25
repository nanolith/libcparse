/**
 * \file src/util/avl_tree_swap.c
 *
 * \brief Swap two \ref avl_tree instances.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <string.h>

#include "avl_tree_internal.h"

CPARSE_IMPORT_util_avl_tree;

/**
 * \brief Swap the contents of two \ref avl_tree instances.
 *
 * \param left          The left \ref avl_tree instance for the swap.
 * \param right         The right \ref avl_tree instance for the swap.
 */
void CPARSE_SYM(avl_tree_swap)(
    CPARSE_SYM(avl_tree)* left, CPARSE_SYM(avl_tree)* right)
{
    avl_tree tmp;

    memcpy(&tmp, left, sizeof(tmp));
    memcpy(left, right, sizeof(tmp));
    memcpy(right, &tmp, sizeof(tmp));
}
