/**
 * \file tools/import_enum/src/create_scanner_and_files.c
 *
 * \brief Create the input / output files and the scanner.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fcntl.h>
#include <libcparse/status_codes.h>
#include <unistd.h>

#include "import_enum_internal.h"

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_input_stream;
CPARSE_IMPORT_preprocessor_scanner;

/**
 * \brief Open input file and output file, creating the preprocessor scanner.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int create_scanner_and_files(import_enum_config* config)
{
    int retval, release_retval;
    int fd = -1;
    input_stream* stream = NULL;

    /* open the input file for reading. */
    fd = open(config->input, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Could not open %s for reading.\n", config->input);
        retval = ERROR_LIBCPARSE_FILE_OPEN_ERROR;
        goto done;
    }

    /* open the output file for writing. */
    config->out = fopen(config->output, "wx");
    if (NULL == config->out)
    {
        fprintf(stderr, "Could not open %s for writing.\n", config->output);
        retval = ERROR_LIBCPARSE_FILE_OPEN_ERROR;
        goto close_fd;
    }

    /* create an input stream from this descriptor. */
    retval = input_stream_create_from_descriptor(&stream, fd);
    if (STATUS_SUCCESS != retval)
    {
        goto close_fd;
    }

    /* the descriptor is now owned by the stream. */
    fd = -1;

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
        /* scanner cleanup is handled by the config release method. */
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

close_fd:
    if (fd >= 0)
    {
        close(fd);
    }

done:
    return retval;
}
