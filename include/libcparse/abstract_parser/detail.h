/**
 * \file libcparse/abstract_parser/detail.h
 *
 * \brief Internal details for \ref abstract_parser.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/message_handler/detail.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

struct CPARSE_SYM(abstract_parser)
{
    CPARSE_SYM(message_handler) mh;
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
