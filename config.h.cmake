/**
 * \file libcparse/config.h
 *
 * \brief Generated configuration file for libcparse.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#define MAKE_C_VERSION(X,Y) V ## X ## _ ## Y
#define CPARSE_VERSION_SYM \
    MAKE_C_VERSION(@CPARSE_VERSION_MAJOR@, @CPARSE_VERSION_MINOR@)

#define CPARSE_VERSION_STRING \
    "@CPARSE_VERSION_MAJOR@.@CPARSE_VERSION_MINOR@.@CPARSE_VERSION_REL@"
