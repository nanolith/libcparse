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

static void log_config(const import_enum_config* config);

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

    log_config(config);

    /* create the scanner and files. */
    retval = create_scanner_and_files(config);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup;
    }

    /* scan the input file and create the output file. */
    retval = scan_input_and_write_output(config);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error parsing %s.\n", config->input);
        retval = 1;
        goto cleanup;
    }

    /* TODO - fill out. */
    retval = STATUS_SUCCESS;
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

/**
 * \brief Log config values to stderr.
 *
 * \params config       The config to log.
 */
static void log_config(const import_enum_config* config)
{
    fprintf(stderr, "Input file: %s\n", config->input);
    fprintf(stderr, "Output file: %s\n", config->output);
    fprintf(stderr, "Enumeration name: %s\n", config->enumeration);
    fprintf(stderr, "Enumeration count: %ld\n", config->count);
}
