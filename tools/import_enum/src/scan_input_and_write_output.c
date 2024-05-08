/**
 * \file tools/import_enum/src/scan_input_and_write_output.c
 *
 * \brief Scan the input file and write the output file.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/abstract_parser.h>
#include <libcparse/event.h>
#include <libcparse/event_handler.h>
#include <libcparse/status_codes.h>

#include "import_enum_internal.h"

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_handler;

static int scanner_event_callback(import_enum_config* config, const event* ev);

/**
 * \brief Scan the input file, writing enumeration details to the output file.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int scan_input_and_write_output(import_enum_config* config)
{
    int retval, release_retval;
    event_handler eh;

    /* create an event handler for preprocessor scanner events. */
    retval =
        event_handler_init(
            &eh, (event_callback_fn)&scanner_event_callback, config);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* subscribe to preprocessor scanner events. */
    retval = abstract_parser_preprocessor_scanner_subscribe(config->ap, &eh);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_eh;
    }

    /* run the scanner. */
    retval = abstract_parser_run(config->ap);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_eh;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_eh;

cleanup_eh:
    release_retval = event_handler_dispose(&eh);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Callback to receive events from the preprocessor scanner.
 *
 * \param config        The config for this instance.
 * \param ev            The event for this callback.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int scanner_event_callback(import_enum_config* config, const event* ev)
{
    /* TODO - fill out stub. */
    return STATUS_SUCCESS;
}
