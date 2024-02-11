/**
 * \file libcparse/integer_type.h
 *
 * \brief The integer_type enumeration describes the type of an integer.
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
 * \brief The integer type describes the type of an integer constant.
 */
enum CPARSE_SYM(integer_type)
{
    CPARSE_INTEGER_TYPE_SIGNED_INT =                                    0x0000,
    CPARSE_INTEGER_TYPE_UNSIGNED_INT =                                  0x0001,
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
