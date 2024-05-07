/**
 * \file tools/import_enum/src/main.c
 *
 * \brief Main entry point for the import_enum tool.
 *
 * import_enum is a temporary tool for importing enumerations into the proof
 * assistant so we can perform proofs based on these enumerations.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int readopts(
    int* argc, char*** argv, char** input, char** output, char** enumeration,
    long* count);

/**
 * \brief Main entry point for import_enum.
 *
 * \param argc              The argument count.
 * \param argv              The argument vector.
 *
 * \returns 0 on success and non-zero on failure.
 */
int main(int argc, char* argv[])
{
    int retval, ch;
    char* input = NULL;
    char* output = NULL;
    char* enumeration = NULL;
    long count = 0;

    /* read command-line options. */
    retval = readopts(&argc, &argv, &input, &output, &enumeration, &count);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup;
    }

    fprintf(stderr, "Input file: %s\n", input);
    fprintf(stderr, "Output file: %s\n", output);
    fprintf(stderr, "Enumeration name: %s\n", enumeration);
    fprintf(stderr, "Enumeration count: %ld\n", count);
    retval = 0;
    goto cleanup;

cleanup:
    if (NULL != input)
    {
        free(input);
    }

    if (NULL != output)
    {
        free(output);
    }

    if (NULL != enumeration)
    {
        free(enumeration);
    }

    return retval;
}

/**
 * \brief Read command-line options, populating variables.
 *
 * \param argc          Pointer to argc, to be updated on success.
 * \param argv          Pointer to argv, to be updated on success.
 * \param input         Pointer to the input variable pointer.
 * \param output        Pointer to the output variable pointer.
 * \param enumeration   Pointer to the enumeration variable pointer.
 * \param count         Pointer to the count.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int readopts(
    int* argc, char*** argv, char** input, char** output, char** enumeration,
    long* count)
{
    int retval, ch;
    char* invalid_char = NULL;

    /* set these values to sane defaults. */
    *input = *output = *enumeration = NULL;
    *count = 0;

    /* read options. */
    while ((ch = getopt(*argc, *argv, "i:e:o:c:")) != -1)
    {
        switch (ch)
        {
            case 'i':
                if (NULL != *input)
                    free(*input);

                *input = strdup(optarg);
                break;

            case 'e':
                if (NULL != *enumeration)
                    free(*enumeration);

                *enumeration = strdup(optarg);
                break;

            case 'o':
                if (NULL != *output)
                    free(*output);

                *output = strdup(optarg);
                break;

            case 'c':
                *count = strtol(optarg, &invalid_char, 10);
                if (invalid_char == optarg || 0 != *invalid_char)
                {
                    fprintf(stderr, "invalid number %s\n", optarg);
                    retval = 1;
                    goto cleanup;
                }
        }
    }

    /* verify that we have an input file. */
    if (NULL == *input)
    {
        fprintf(stderr, "input file required.\n");
        retval = 1;
        goto cleanup;
    }

    /* verify that we have an output file. */
    if (NULL == *output)
    {
        fprintf(stderr, "output file required.\n");
        retval = 1;
        goto cleanup;
    }

    /* verify that we have an enumeration name. */
    if (NULL == *enumeration)
    {
        fprintf(stderr, "enumeration name required.\n");
        retval = 1;
        goto cleanup;
    }

    /* update argc / argv. */
    *argc -= optind;
    *argv += optind;

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

cleanup:
    if (NULL != *input)
    {
        free(*input);
    }

    if (NULL != *output)
    {
        free(*output);
    }

    if (NULL != *enumeration)
    {
        free(*enumeration);
    }

done:
    return retval;
}
