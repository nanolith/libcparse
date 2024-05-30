/**
 * \file examples/syntax_highlight/src/source_line_release.c
 *
 * \brief Release a \ref source_line instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "syntax_highlight_internal.h"

/**
 * \brief Release a source line.
 *
 * \param line          The source line to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int source_line_release(source_line* line)
{
    /* clear and free line if set. */
    if (NULL != line->line)
    {
        memset(line->line, 0, line->length);
        free(line->line);
    }

    /* clear and free highlight_line if set. */
    if (NULL != line->highlight_line)
    {
        memset(
            line->highlight_line, 0,
            line->length * sizeof(*line->highlight_line));
        free(line->highlight_line);
    }

    /* clear this line. */
    memset(line, 0, sizeof(*line));

    /* free this line. */
    free(line);

    /* success. */
    return STATUS_SUCCESS;
}
