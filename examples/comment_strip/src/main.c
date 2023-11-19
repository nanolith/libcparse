/**
 * \file examples/comment_strip/src/main.c
 *
 * \brief Main entry point for the comment_strip example command.
 *
 * comment_strip strips all C comments from input files.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fcntl.h>
#include <libcparse/abstract_parser.h>
#include <libcparse/comment_filter.h>
#include <libcparse/event.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/event_handler.h>
#include <libcparse/input_stream.h>
#include <libcparse/status_codes.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

CPARSE_IMPORT_abstract_parser;
CPARSE_IMPORT_comment_filter;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_raw_character;
CPARSE_IMPORT_input_stream;

/* context structure. */
typedef struct comment_strip_context comment_strip_context;

struct comment_strip_context
{
};

/* forward decls. */
static int setup_parser(
    abstract_parser* ap, comment_strip_context* context, int argc,
    char* argv[]);
static int comment_strip_event_callback(void* context, const event* ev);

/**
 * \brief Main entry point for comment_strip.
 *
 * \param argc              The argument count.
 * \param argv              The argument vector.
 *
 * \returns 0 on success and non-zero on failure.
 */
int main(int argc, char* argv[])
{
    comment_filter* filter = NULL;
    abstract_parser* ap = NULL;
    event_handler eh;
    int return_code = 0;
    int retval;
    int desc = -1;
    comment_strip_context context;

    /* clear context. */
    memset(&context, 0, sizeof(context));

    /* create the comment filter. */
    retval = comment_filter_create(&filter);
    if (STATUS_SUCCESS != retval)
    {
        return_code = 1;
        goto done;
    }

    /* get the abstract parser for this filter. */
    ap = comment_filter_upcast(filter);

    /* set up the parser with the input arguments. */
    retval = setup_parser(ap, &context, argc, argv);
    if (STATUS_SUCCESS != retval)
    {
        return_code = 1;
        goto cleanup_filter;
    }

    /* initialize our event_handler for reading events from the filter. */
    retval = event_handler_init(&eh, &comment_strip_event_callback, &context);
    if (STATUS_SUCCESS != retval)
    {
        return_code = 1;
        goto cleanup_filter;
    }

    /* subscribe to events from the filter. */
    retval = abstract_parser_comment_filter_subscribe(ap, &eh);
    if (STATUS_SUCCESS != retval)
    {
        return_code = 1;
        goto cleanup_filter;
    }

    /* run the filter. */
    retval = abstract_parser_run(ap);
    if (STATUS_SUCCESS != retval)
    {
        return_code = 1;
        goto cleanup_filter;
    }

    /* flush standard output. */
    fflush(stdout);

    /* success. */
    return_code = 0;
    goto cleanup_filter;

cleanup_filter:
    if (NULL != filter)
    {
        retval = comment_filter_release(filter);
        if (STATUS_SUCCESS != retval)
        {
            return_code = 1;
        }
    }

done:
    return return_code;
}

/**
 * \brief Set up the parser using the arguments.
 *
 * \param ap                The parser to set up.
 * \param context           The slowcat context.
 * \param argc              The number of arguments.
 * \param argv              The argument vector.
 */
static int setup_parser(
    abstract_parser* ap, comment_strip_context* context, int argc, char* argv[])
{
    int ch, retval, release_retval;
    input_stream* stream = NULL;
    int desc = -1;

    const char* progname = argv[0];

    /* parse flags. */
    while ((ch = getopt(argc, argv, "")) != -1)
    {
        switch (ch)
        {
            default:
                fprintf(stderr, "usage: %s [file ...]\n", progname);
                retval = 1;
                goto done;
        }
    }

    /* skip past flags. */
    argc -= optind;
    argv += optind;

    /* should we write stdin to stdout? */
    if (0 == argc)
    {
        /* turn stdin into a stream. */
        retval = input_stream_create_from_descriptor(&stream, 0);
        if (STATUS_SUCCESS != retval)
        {
            goto done;
        }

        /* push this stream to the scanner. */
        retval = abstract_parser_push_input_stream(ap, "stdin", stream);
        if (STATUS_SUCCESS != retval)
        {
            goto cleanup_stream;
        }

        /* the scanner now owns this stream. */
        stream = NULL;
    }
    else
    {
        /* iterate backward through all remaining arguments. */
        for (int i = argc; i > 0; --i)
        {
            const char* filename = argv[i - 1];

            if (!strcmp(filename, "-"))
            {
                desc = 0;
            }
            else
            {
                /* attempt to open the filename. */
                desc = open(filename, O_RDONLY);
                if (desc < 0)
                {
                    fprintf(stderr, "Could not open %s\n", filename);
                    retval = 1;
                    goto done;
                }
            }

            /* turn this descriptor into a stream. */
            retval = input_stream_create_from_descriptor(&stream, desc);
            if (STATUS_SUCCESS != retval)
            {
                goto close_desc;
            }

            /* the descriptor is now owned by the stream. */
            desc = -1;

            /* push this stream to the scanner. */
            retval = abstract_parser_push_input_stream(ap, filename, stream);
            if (STATUS_SUCCESS != retval)
            {
                goto cleanup_stream;
            }

            /* the scanner now owns this stream. */
            stream = NULL;
        }
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

close_desc:
    if (desc >= 0)
    {
        close(desc);
    }

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

/**
 * \brief filter event callback.
 *
 * \param context           Not used by this callback.
 * \param ev                The event to process.
 */
static int comment_strip_event_callback(void* context, const event* ev)
{
    int retval;
    event_raw_character* rev;

    switch (event_get_type(ev))
    {
        case CPARSE_EVENT_TYPE_RAW_CHARACTER:
            retval = event_downcast_to_event_raw_character(&rev, (event*)ev);
            if (STATUS_SUCCESS != retval)
            {
                return retval;
            }

            /* output the raw character. */
            fputc(event_raw_character_get(rev), stdout);
            break;

        /* ignore all other events. */
        default:
            break;
    }

    return STATUS_SUCCESS;
}
