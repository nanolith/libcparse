/**
 * \file
 * exmaples/syntax_highlight/src/syntax_highlight_create_scanner_and_output.c
 *
 * \brief Create the scanner and output file.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/input_stream.h>
#include <libcparse/preprocessor_scanner.h>
#include <libcparse/status_codes.h>

#include "syntax_highlight_internal.h"

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_input_stream;
CPARSE_IMPORT_preprocessor_scanner;

/**
 * \brief Create scanner and output file.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int syntax_highlight_create_scanner_and_output(syntax_highlight_config* config)
{
    int retval, release_retval;
    input_stream* stream;

    /* open the output file for writing. */
    config->out = fopen(config->output, "w");
    if (NULL == config->out)
    {
        fprintf(stderr, "Could not open %s for writing.\n", config->output);
        retval = ERROR_LIBCPARSE_FILE_OPEN_ERROR;
        goto done;
    }

    /* create an input stream from the input string. */
    retval = input_stream_create_from_string(&stream, config->input_string);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error creating input stream.\n");
        goto done;
    }

    /* create a preprocessor scanner instance. */
    retval = preprocessor_scanner_create(&config->scanner);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_stream;
    }

    /* get the abstract parser for this scanner. */
    config->ap = preprocessor_scanner_upcast(config->scanner);

    /* add the input stream to the parser. */
    retval =
        abstract_parser_push_input_stream(config->ap, config->input, stream);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_stream;
    }

    /* the stream is now owned by the scanner. */
    stream = NULL;

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

cleanup_stream:
    if (NULL != stream)
    {
        release_retval = input_stream_release(stream);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

done:
    return retval;
}
