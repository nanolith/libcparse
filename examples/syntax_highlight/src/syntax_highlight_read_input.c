/**
 * \file exmaples/syntax_highlight/src/syntax_highlight_read_input.c
 *
 * \brief Open the input file and read into an input string and source lines.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>

#include "syntax_highlight_internal.h"

static int read_input_file(syntax_highlight_config* config);
static int read_input_lines(syntax_highlight_config* config);
static void debug_output_parsed_lines(syntax_highlight_config* config);

/**
 * \brief Open input file and read input file into an input string and source
 * lines.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int syntax_highlight_read_input(syntax_highlight_config* config)
{
    int retval;

    /* read the input file. */
    retval = read_input_file(config);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* read input file lines. */
    retval = read_input_lines(config);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* if the debug flag is set, output the parsed lines. */
    if (config->debug)
    {
        debug_output_parsed_lines(config);
    }

    /* success. */
    return STATUS_SUCCESS;
}

/**
 * \brief Split the input into lines.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int read_input_lines(syntax_highlight_config* config)
{
    int retval;
    size_t start_offset = 0;
    size_t end_offset = 0;
    char* input = config->input_string;

    while (0 != *input)
    {
        end_offset = start_offset;

        /* scan to the next newline. */
        while (0 != *input && '\n' != *input)
        {
            ++input; ++end_offset;
        }

        /* compute the length of this line. */
        size_t line_length = end_offset - start_offset;

        /* insert this line. */
        retval =
            source_list_insert(
                config, config->input_string + start_offset, line_length);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        /* increment past the newline. */
        if ('\n' == *input)
        {
            ++input;
        }

        /* update the offsets. */
        start_offset = end_offset + 1;
    }

    /* reverse the list. */
    retval = source_list_reverse(config);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* success. */
    return STATUS_SUCCESS;
}

/**
 * \brief Read the input file.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int read_input_file(syntax_highlight_config* config)
{
    int retval, release_retval;
    FILE* in = NULL;

    /* open the input file for reading. */
    in = fopen(config->input, "r");
    if (NULL == in)
    {
        retval = ERROR_LIBCPARSE_FILE_OPEN_ERROR;
        goto done;
    }

    /* seek to the end of the file. */
    retval = fseek(in, 0L, SEEK_END);
    if (retval < 0)
    {
        retval = ERROR_LIBCPARSE_FILE_SEEK;
        goto cleanup_in;
    }

    /* get the offset of the file at this location. */
    long offset = ftell(in);
    if (offset < 0)
    {
        retval = ERROR_LIBCPARSE_FILE_TELL;
        goto cleanup_in;
    }

    /* allocate enough memory for the input string. */
    config->input_string = (char*)malloc(offset + 1);
    if (NULL == config->input_string)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto cleanup_in;
    }

    /* seek to the start of the file. */
    retval = fseek(in, 0L, SEEK_SET);
    if (retval < 0)
    {
        return ERROR_LIBCPARSE_FILE_SEEK;
        goto cleanup_in;
    }

    /* read the contents of the input file. */
    size_t read_size = fread(config->input_string, 1, offset, in);
    if (read_size < (size_t)offset)
    {
        retval = ERROR_LIBCPARSE_INPUT_STREAM_READ_ERROR;
        goto cleanup_in;
    }

    /* ascii-zero the input string. */
    config->input_string[offset] = 0;
    retval = STATUS_SUCCESS;
    goto done;

cleanup_in:
    release_retval = fclose(in);
    if (0 != release_retval)
    {
        retval = ERROR_LIBCPARSE_FILE_CLOSE_ERROR;
    }

done:
    return retval;
}

/**
 * \brief Output the parsed lines for debugging.
 *
 * \param config        The config instance for this operation.
 */
static void debug_output_parsed_lines(syntax_highlight_config* config)
{
    source_line* tmp = config->head;

    fprintf(stderr, "\n\nInput lines:\n");

    for (source_line* tmp = config->head; NULL != tmp; tmp = tmp->next)
    {
        fprintf(stderr, "%s\n", tmp->line);
    }
}
