/**
 * \file test/preprocessor_scanner/test_preprocessor_scanner_helper.h
 *
 * \brief Helpers for \ref preprocessor_scanner unit tests.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event.h>
#include <list>
#include <string>

namespace test_preprocessor_scanner_helper
{
    typedef std::pair<int, std::string> test_token;

    struct test_context
    {
        std::list<test_token> vals;
        bool eof;

        test_context()
            : eof(false)
        {
        }
    };

    int dummy_callback(void* context, const CPARSE_SYM(event)* ev);
}
