/**
 * \file tools/import_enum/src/import_enum_config_create.c
 *
 * \brief Create an \ref import_enum_config instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "import_enum_internal.h"

/**
 * \brief Read command-line options, creating an import_enum_config instance on
 * success.
 *
 * \param config        Pointer to the config pointer to populate with the
 *                      created config on success.
 * \param argc          Pointer to argc, to be updated on success.
 * \param argv          Pointer to argv, to be updated on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int import_enum_config_create(
    import_enum_config** config, int* argc, char*** argv)
{
    int retval, release_retval, ch;
    import_enum_config* tmp = NULL;
    char* invalid_char = NULL;

    /* allocate memory for this instance. */
    tmp = (import_enum_config*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* clear this memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* read options. */
    while ((ch = getopt(*argc, *argv, "i:e:o:c:")) != -1)
    {
        switch (ch)
        {
            case 'i':
                if (NULL != tmp->input)
                    free(tmp->input);

                tmp->input = strdup(optarg);
                break;

            case 'e':
                if (NULL != tmp->enumeration)
                    free(tmp->enumeration);

                tmp->enumeration = strdup(optarg);
                break;

            case 'o':
                if (NULL != tmp->output)
                    free(tmp->output);

                tmp->output = strdup(optarg);
                break;

            case 'c':
                tmp->count = strtol(optarg, &invalid_char, 10);
                if (invalid_char == optarg || 0 != *invalid_char)
                {
                    fprintf(stderr, "invalid number %s\n", optarg);
                    retval = 1;
                    goto cleanup;
                }
        }
    }

    /* verify that we have an input file. */
    if (NULL == tmp->input)
    {
        fprintf(stderr, "input file required.\n");
        retval = 1;
        goto cleanup;
    }

    /* verify that we have an output file. */
    if (NULL == tmp->output)
    {
        fprintf(stderr, "output file required.\n");
        retval = 1;
        goto cleanup;
    }

    /* verify that we have an enumeration name. */
    if (NULL == tmp->enumeration)
    {
        fprintf(stderr, "enumeration name required.\n");
        retval = 1;
        goto cleanup;
    }

    /* update argc / argv. */
    *argc -= optind;
    *argv += optind;

    /* success. */
    *config = tmp;
    retval = STATUS_SUCCESS;
    goto done;

cleanup:
    release_retval = import_enum_config_release(tmp);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
