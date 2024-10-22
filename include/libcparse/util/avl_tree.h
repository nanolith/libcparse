/**
 * \file libcparse/util/avl_tree.h
 *
 * \brief AVL tree implementation.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The avl_tree type is a container that provides O(log n) lookup and
 * O(n log n) traversal of elements stored by key.
 */
typedef struct CPARSE_SYM(avl_tree) CPARSE_SYM(avl_tree);

/**
 * \brief The avl_tree_node is an opaque structure used for traversing the tree.
 */
typedef struct CPARSE_SYM(avl_tree_node) CPARSE_SYM(avl_tree_node);

/**
 * \brief Comparison function type for comparing two avl tree elements.
 *
 * \param context       Context data to be passed to the comparison function.
 * \param lhs           The left-hand side of the comparison.
 * \param rhs           The right-hand side of the comparison.
 *
 * \returns an integer value representing the comparison result.
 *      - < 0 if \p lhs &lt; \p rhs.
 *      - 0 if \p lhs == \p rhs.
 *      - > 0 if \p lhs &gt; \p rhs.
 */
typedef int (*CPARSE_SYM(avl_tree_compare_fn))(
    void* context, const void* lhs, const void* rhs);

/**
 * \brief Given an avl tree element, return the key for this element.
 *
 * \param context       Context data to be passed to the accessor function.
 * \param elem          The element.
 *
 * \returns the key for this element.
 */
typedef const void* (*CPARSE_SYM(avl_tree_key_fn))(
    void* context, const void* elem);

/**
 * \brief Given an avl tree element, release it.
 *
 * \param context       Context data to be passed to the release function.
 * \param elem          The element to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
typedef int (*CPARSE_SYM(avl_tree_element_release_fn))(
    void* context, const void* elem);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

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
    CPARSE_SYM(avl_tree_element_release_fn) release, void* context);

/**
 * \brief Release a \ref avl_tree instance, calling the user release function on
 * any elements in the tree.
 *
 * \param tree                  The \ref avl_tree instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(avl_tree_release)(CPARSE_SYM(avl_tree)* tree);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Insert an element into the \ref avl_tree instance.
 *
 * \param tree          The \ref avl_tree instance for this insert operation.
 * \param elem          The user-defined element to insert.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(avl_tree_insert)(CPARSE_SYM(avl_tree)* tree, void* elem);

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
    void** elem, const CPARSE_SYM(avl_tree)* tree, const void* key);

/**
 * \brief Delete an element in the \ref avl_tree instance matching the given
 * user-defined key.
 *
 * \param elem          Pointer to the elem pointer to be set to the deleted
 *                      element. Set to NULL to call the user release method on
 *                      this deleted element instead.
 * \param tree          The \ref avl_tree for this delete operation.
 * \param key           The user-defined key for this delete operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - ERROR_LIBCPARSE_AVL_TREE_ELEMENT_NOT_FOUND if the element was not
 *        found.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(avl_tree_delete)(
    void** elem, CPARSE_SYM(avl_tree)* tree, const void* key);

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
int CPARSE_SYM(avl_tree_clear)(CPARSE_SYM(avl_tree)* tree);

/**
 * \brief Swap the contents of two \ref avl_tree instances.
 *
 * \param left          The left \ref avl_tree instance for the swap.
 * \param right         The right \ref avl_tree instance for the swap.
 */
void CPARSE_SYM(avl_tree_swap)(
    CPARSE_SYM(avl_tree)* left, CPARSE_SYM(avl_tree)* right);

/**
 * \brief Return the minimum node in a \ref avl_tree subtree.
 *
 * \param tree          The \ref avl_tree instance.
 * \param x             The \ref avl_tree_node from which the search should
 *                      start.
 *
 * \returns the minimum node in this subtree.
 */
CPARSE_SYM(avl_tree_node)*
CPARSE_SYM(avl_tree_minimum_node)(
    CPARSE_SYM(avl_tree)* tree, CPARSE_SYM(avl_tree_node)* x);

/**
 * \brief Return the maximum node in a \ref avl_tree subtree.
 *
 * \param tree          The \ref avl_tree instance.
 * \param x             The \ref avl_tree_node from which the search should
 *                      start.
 *
 * \returns the maximum node in this subtree.
 */
CPARSE_SYM(avl_tree_node)*
CPARSE_SYM(avl_tree_maximum_node)(
    CPARSE_SYM(avl_tree)* tree, CPARSE_SYM(avl_tree_node)* x);

/**
 * \brief Return the in-order successor node of the given node.
 *
 * \param tree          The \ref avl_tree instance.
 * \param x             The \ref avl_tree_node from which the successor is
 *                      found.
 *
 * \returns the successor node of this node, or NULL if none is found.
 */
CPARSE_SYM(avl_tree_node)*
CPARSE_SYM(avl_tree_successor_node)(
    CPARSE_SYM(avl_tree)* tree, CPARSE_SYM(avl_tree_node)* x);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_util_avl_tree_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(avl_tree) sym ## avl_tree; \
    typedef CPARSE_SYM(avl_tree_node) sym ## avl_tree_node; \
    typedef CPARSE_SYM(avl_tree_compare_fn) sym ## avl_tree_compare_fn; \
    typedef CPARSE_SYM(avl_tree_key_fn) sym ## avl_tree_key_fn; \
    typedef CPARSE_SYM(avl_tree_element_release_fn) \
    sym ## avl_tree_element_release_fn; \
    static inline int sym ## avl_tree_create( \
        CPARSE_SYM(avl_tree)** v, CPARSE_SYM(avl_tree_compare_fn) w, \
        CPARSE_SYM(avl_tree_key_fn) x, \
        CPARSE_SYM(avl_tree_element_release_fn) y, void* z) { \
            return CPARSE_SYM(avl_tree_create)(v,w,x,y,z); } \
    static inline int sym ## avl_tree_release( \
        CPARSE_SYM(avl_tree)* x) { \
            return CPARSE_SYM(avl_tree_release)(x); } \
    static inline int sym ## avl_tree_insert( \
        CPARSE_SYM(avl_tree)* x, void* y) { \
            return CPARSE_SYM(avl_tree_insert)(x,y); } \
    static inline int sym ## avl_tree_find( \
        void** x, const CPARSE_SYM(avl_tree)* y, const void* z) { \
            return CPARSE_SYM(avl_tree_find)(x,y,z); } \
    static inline int sym ## avl_tree_delete( \
        void** x, CPARSE_SYM(avl_tree)* y, const void* z) { \
            return CPARSE_SYM(avl_tree_delete)(x,y,z); } \
    static inline int sym ## avl_tree_clear( \
        CPARSE_SYM(avl_tree)* x) { \
            return CPARSE_SYM(avl_tree_clear)(x); } \
    static inline void sym ## avl_tree_swap( \
        CPARSE_SYM(avl_tree)* x, CPARSE_SYM(avl_tree)* y) { \
            CPARSE_SYM(avl_tree_swap)(x,y); } \
    static inline CPARSE_SYM(avl_tree_node)* \
    sym ## avl_tree_minimum_node( \
        CPARSE_SYM(avl_tree)* x, CPARSE_SYM(avl_tree_node)* y) { \
            return CPARSE_SYM(avl_tree_minimum_node)(x,y); } \
    static inline CPARSE_SYM(avl_tree_node)* \
    sym ## avl_tree_maximum_node( \
        CPARSE_SYM(avl_tree)* x, CPARSE_SYM(avl_tree_node)* y) { \
            return CPARSE_SYM(avl_tree_maximum_node)(x,y); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_util_avl_tree_as(sym) \
    __INTERNAL_CPARSE_IMPORT_util_avl_tree_sym(sym ## _)
#define CPARSE_IMPORT_util_avl_tree \
    __INTERNAL_CPARSE_IMPORT_util_avl_tree_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
