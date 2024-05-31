/**
 * \file exmaples/syntax_highlight/src/source_list_release.c
 *
 * \brief Release a source list.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>

#include "syntax_highlight_internal.h"

/**
 * \brief Release a source list.
 *
 * \param list          The source list to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int source_list_release(source_line* list)
{
    int retval = STATUS_SUCCESS;
    int release_retval;
    source_line* tmp = list;

    while (NULL != list)
    {
        list = list->next;

        release_retval = source_line_release(tmp);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }

        tmp = list;
    }

    return retval;
}
