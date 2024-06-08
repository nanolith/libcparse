/**
 * \file test/preprocessor_scanner/test_preprocessor_scanner_helper.cpp
 *
 * \brief Helpers for \ref preprocessor_scanner unit tests.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/identifier.h>
#include <libcparse/event/raw_character_literal.h>
#include <libcparse/event/raw_integer.h>
#include <libcparse/event/raw_string.h>
#include <libcparse/event_type.h>
#include <libcparse/status_codes.h>

#include "test_preprocessor_scanner_helper.h"

using namespace std;
using namespace test_preprocessor_scanner_helper;

CPARSE_IMPORT_event;
CPARSE_IMPORT_event_identifier;
CPARSE_IMPORT_event_raw_character_literal;
CPARSE_IMPORT_event_raw_integer;
CPARSE_IMPORT_event_raw_string;

int test_preprocessor_scanner_helper::dummy_callback(
    void* context, const CPARSE_SYM(event)* ev)
{
    int retval;
    test_context* ctx = (test_context*)context;

    auto token_type = event_get_type(ev);

    if (CPARSE_EVENT_TYPE_EOF == token_type)
    {
        ctx->eof = true;
    }
    else if (CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER == token_type)
    {
        event_identifier* iev;
        retval = event_downcast_to_event_identifier(&iev, (event*)ev);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        auto str = event_identifier_get(iev);

        ctx->vals.push_back(make_pair(CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER, str));
    }
    else if (CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_CHARACTER == token_type)
    {
        event_raw_character_literal* cev;
        retval =
            event_downcast_to_event_raw_character_literal(&cev, (event*)ev);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        auto str = event_raw_character_literal_get(cev);

        ctx->vals.push_back(
            make_pair(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_CHARACTER, str));
    }
    else if (CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING == token_type)
    {
        event_raw_string_token* sev;
        retval = event_downcast_to_event_raw_string_token(&sev, (event*)ev);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        auto str = event_raw_string_token_get(sev);

        ctx->vals.push_back(
            make_pair(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_STRING, str));
    }
    else if (CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_SYSTEM_STRING == token_type)
    {
        event_raw_string_token* sev;
        retval = event_downcast_to_event_raw_string_token(&sev, (event*)ev);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        auto str = event_raw_string_token_get(sev);

        ctx->vals.push_back(
            make_pair(CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_SYSTEM_STRING, str));
    }
    else if (CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_INTEGER == token_type)
    {
        event_raw_integer_token* iev;
        retval = event_downcast_to_event_raw_integer_token(&iev, (event*)ev);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        auto str = event_raw_integer_token_string_get(iev);

        ctx->vals.push_back(make_pair(token_type, str));
    }
    else
    {
        switch (token_type)
        {
        case CPARSE_EVENT_TYPE_TOKEN_LEFT_PAREN:
            ctx->vals.push_back(make_pair(token_type, "("));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_RIGHT_PAREN:
            ctx->vals.push_back(make_pair(token_type, ")"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACE:
            ctx->vals.push_back(make_pair(token_type, "{"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACE:
            ctx->vals.push_back(make_pair(token_type, "}"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_LEFT_BRACKET:
            ctx->vals.push_back(make_pair(token_type, "["));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_RIGHT_BRACKET:
            ctx->vals.push_back(make_pair(token_type, "]"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_COMMA:
            ctx->vals.push_back(make_pair(token_type, ","));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_COLON:
            ctx->vals.push_back(make_pair(token_type, ":"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_SEMICOLON:
            ctx->vals.push_back(make_pair(token_type, ";"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_DOT:
            ctx->vals.push_back(make_pair(token_type, "."));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_ARROW:
            ctx->vals.push_back(make_pair(token_type, "->"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PLUS:
            ctx->vals.push_back(make_pair(token_type, "+"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_MINUS:
            ctx->vals.push_back(make_pair(token_type, "-"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_STAR:
            ctx->vals.push_back(make_pair(token_type, "*"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_FORWARD_SLASH:
            ctx->vals.push_back(make_pair(token_type, "/"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PERCENT:
            ctx->vals.push_back(make_pair(token_type, "%"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_LOGICAL_AND:
            ctx->vals.push_back(make_pair(token_type, "&&"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_LOGICAL_OR:
            ctx->vals.push_back(make_pair(token_type, "||"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_AMPERSAND:
            ctx->vals.push_back(make_pair(token_type, "&"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PIPE:
            ctx->vals.push_back(make_pair(token_type, "|"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_CARET:
            ctx->vals.push_back(make_pair(token_type, "^"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_TILDE:
            ctx->vals.push_back(make_pair(token_type, "~"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_QUESTION:
            ctx->vals.push_back(make_pair(token_type, "?"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_EQUAL_COMPARE:
            ctx->vals.push_back(make_pair(token_type, "=="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_NOT_EQUAL_COMPARE:
            ctx->vals.push_back(make_pair(token_type, "!="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_EQUAL_ASSIGN:
            ctx->vals.push_back(make_pair(token_type, "="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PLUS_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "+="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_MINUS_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "-="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_TIMES_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "*="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_DIV_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "/="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_MOD_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "%="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_AND_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "&="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_OR_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "|="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_XOR_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "^="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_COMPL_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "~="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_LEFT_SHIFT_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "<<="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_RIGHT_SHIFT_EQUAL:
            ctx->vals.push_back(make_pair(token_type, ">>="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_BITSHIFT_LEFT:
            ctx->vals.push_back(make_pair(token_type, "<<"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_BITSHIFT_RIGHT:
            ctx->vals.push_back(make_pair(token_type, ">>"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_LESS_THAN:
            ctx->vals.push_back(make_pair(token_type, "<"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_GREATER_THAN:
            ctx->vals.push_back(make_pair(token_type, ">"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_LESS_THAN_EQUAL:
            ctx->vals.push_back(make_pair(token_type, "<="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_GREATER_THAN_EQUAL:
            ctx->vals.push_back(make_pair(token_type, ">="));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_INCREMENT:
            ctx->vals.push_back(make_pair(token_type, "++"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_DECREMENT:
            ctx->vals.push_back(make_pair(token_type, "--"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_NOT:
            ctx->vals.push_back(make_pair(token_type, "!"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_ELLIPSIS:
            ctx->vals.push_back(make_pair(token_type, "..."));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ALIGNAS:
            ctx->vals.push_back(make_pair(token_type, "_Alignas"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ALIGNOF:
            ctx->vals.push_back(make_pair(token_type, "_Alignof"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__ATOMIC:
            ctx->vals.push_back(make_pair(token_type, "_Atomic"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__BOOL:
            ctx->vals.push_back(make_pair(token_type, "_Bool"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__COMPLEX:
            ctx->vals.push_back(make_pair(token_type, "_Complex"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__GENERIC:
            ctx->vals.push_back(make_pair(token_type, "_Generic"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__IMAGINARY:
            ctx->vals.push_back(make_pair(token_type, "_Imaginary"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__NORETURN:
            ctx->vals.push_back(make_pair(token_type, "_Noreturn"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__STATIC_ASSERT:
            ctx->vals.push_back(make_pair(token_type, "_Static_assert"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD__THREAD_LOCAL:
            ctx->vals.push_back(make_pair(token_type, "_Thread_local"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_AUTO:
            ctx->vals.push_back(make_pair(token_type, "auto"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_BREAK:
            ctx->vals.push_back(make_pair(token_type, "break"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CASE:
            ctx->vals.push_back(make_pair(token_type, "case"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CHAR:
            ctx->vals.push_back(make_pair(token_type, "char"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CONST:
            ctx->vals.push_back(make_pair(token_type, "const"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_CONTINUE:
            ctx->vals.push_back(make_pair(token_type, "continue"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DEFAULT:
            ctx->vals.push_back(make_pair(token_type, "default"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DO:
            ctx->vals.push_back(make_pair(token_type, "do"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_DOUBLE:
            ctx->vals.push_back(make_pair(token_type, "double"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ELSE:
            ctx->vals.push_back(make_pair(token_type, "else"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_ENUM:
            ctx->vals.push_back(make_pair(token_type, "enum"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_EXTERN:
            ctx->vals.push_back(make_pair(token_type, "extern"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FLOAT:
            ctx->vals.push_back(make_pair(token_type, "float"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_FOR:
            ctx->vals.push_back(make_pair(token_type, "for"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_GOTO:
            ctx->vals.push_back(make_pair(token_type, "goto"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_IF:
            ctx->vals.push_back(make_pair(token_type, "if"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_INLINE:
            ctx->vals.push_back(make_pair(token_type, "inline"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_INT:
            ctx->vals.push_back(make_pair(token_type, "int"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_LONG:
            ctx->vals.push_back(make_pair(token_type, "long"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_REGISTER:
            ctx->vals.push_back(make_pair(token_type, "register"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_RESTRICT:
            ctx->vals.push_back(make_pair(token_type, "restrict"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_RETURN:
            ctx->vals.push_back(make_pair(token_type, "return"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SHORT:
            ctx->vals.push_back(make_pair(token_type, "short"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SIGNED:
            ctx->vals.push_back(make_pair(token_type, "signed"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SIZEOF:
            ctx->vals.push_back(make_pair(token_type, "sizeof"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_STATIC:
            ctx->vals.push_back(make_pair(token_type, "static"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_STRUCT:
            ctx->vals.push_back(make_pair(token_type, "struct"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_SWITCH:
            ctx->vals.push_back(make_pair(token_type, "switch"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_TYPEDEF:
            ctx->vals.push_back(make_pair(token_type, "typedef"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_UNION:
            ctx->vals.push_back(make_pair(token_type, "union"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_UNSIGNED:
            ctx->vals.push_back(make_pair(token_type, "unsigned"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_VOID:
            ctx->vals.push_back(make_pair(token_type, "void"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_VOLATILE:
            ctx->vals.push_back(make_pair(token_type, "volatile"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_KEYWORD_WHILE:
            ctx->vals.push_back(make_pair(token_type, "while"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PP_HASH:
            ctx->vals.push_back(make_pair(token_type, "#"));
            break;
        case CPARSE_EVENT_TYPE_PP_END:
            ctx->vals.push_back(make_pair(token_type, ""));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_IF:
            ctx->vals.push_back(make_pair(token_type, "#if"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_IFDEF:
            ctx->vals.push_back(make_pair(token_type, "#ifdef"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_IFNDEF:
            ctx->vals.push_back(make_pair(token_type, "#ifndef"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_INCLUDE:
            ctx->vals.push_back(make_pair(token_type, "#include"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_DEFINE:
            ctx->vals.push_back(make_pair(token_type, "#define"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_ELIF:
            ctx->vals.push_back(make_pair(token_type, "#elif"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_ELSE:
            ctx->vals.push_back(make_pair(token_type, "#else"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_ERROR:
            ctx->vals.push_back(make_pair(token_type, "#error"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_LINE:
            ctx->vals.push_back(make_pair(token_type, "#line"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_ENDIF:
            ctx->vals.push_back(make_pair(token_type, "#endif"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_PRAGMA:
            ctx->vals.push_back(make_pair(token_type, "#pragma"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PP_ID_UNDEF:
            ctx->vals.push_back(make_pair(token_type, "#undef"));
            break;
        case CPARSE_EVENT_TYPE_TOKEN_PP_STRING_CONCAT:
            ctx->vals.push_back(make_pair(token_type, "##"));
            break;

        default:
            return -1;
        }
    }

    return STATUS_SUCCESS;
}
