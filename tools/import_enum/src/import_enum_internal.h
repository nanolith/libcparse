/**
 * \file tools/import_enum/src/import_enum_internal.h
 *
 * \brief Internal data structures and functions for the import_enum utility.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

typedef struct import_enum_config import_enum_config;

struct import_enum_config
{
    char* input;
    char* output;
    char* enumeration;
    long count;
};
