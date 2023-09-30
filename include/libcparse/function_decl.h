/**
 * \file libcparse/function_decl.h
 *
 * \brief Function declaration macros for libcparse.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/config.h>
#include <libcparse/macro_tricks.h>

/*
 * With GCC 3.4 and clang, we can force a warning / error if the return value
 * of a function isn't checked.
 */
#if defined(__GNUC__) && defined(__GNUC_MINOR__)
# if (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || (__GNUC__ > 3)
#  define FN_DECL_MUST_CHECK __attribute__((warn_unused_result))
# endif
#endif

/*
 * For other compilers, skip this check.
 */
#ifndef FN_DECL_MUST_CHECK
# define FN_DECL_MUST_CHECK
#endif

/*
 * The CPARSE_UNIQUE_NAME is a UUID-based symbol.
 */
#define CPARSE_UNIQUE_NAME 97ffc0d6_5f54_11ee_9616_18c04d8c76eb

/*
 * Simple concat macro.
 */
#define CPARSE_CONCAT(x,y) x ## y

/*
 * Symbol expansion and combination macro.
 */
#define CPARSE_SYM_COMBINE(x, y, z) cparse ## _ ## x ## _ ## y ## _ ## z
#define CPARSE_SYM_COMBINE1(x, y, z) CPARSE_SYM_COMBINE(x, y, z)

/*
 * The CPARSE_SYM macro elevates a given symbol to the CPARSE namespace.
 */
#define CPARSE_SYM(sym) \
    CPARSE_SYM_COMBINE1(CPARSE_UNIQUE_NAME, CPARSE_VERSION_SYM, sym)

/**
 * Begin an export section.
 */
#define CPARSE_BEGIN_EXPORT \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wunused-function\"")

/**
 * End an export section.
 */
#define CPARSE_END_EXPORT \
    _Pragma("GCC diagnostic pop")
