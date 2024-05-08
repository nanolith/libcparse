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

#include "import_enum_internal.h"

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
    int retval, release_retval;
    import_enum_config* config = NULL;

    /* read command-line options. */
    retval = import_enum_config_create(&config, &argc, &argv);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    fprintf(stderr, "Input file: %s\n", config->input);
    fprintf(stderr, "Output file: %s\n", config->output);
    fprintf(stderr, "Enumeration name: %s\n", config->enumeration);
    fprintf(stderr, "Enumeration count: %ld\n", config->count);
    retval = 0;
    goto cleanup;

cleanup:
    release_retval = import_enum_config_release(config);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
