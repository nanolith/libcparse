/**
 * \file exmaples/syntax_highlight/src/source_list_insert.c
 *
 * \brief Insert an item into the source list.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "syntax_highlight_internal.h"

/**
 * \brief Insert a line into the source list.
 *
 * \param config        The config instance for this operation.
 * \param line          The line to insert. It is copied.
 * \param size          The size of the line in bytes.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int source_list_insert(
    syntax_highlight_config* config, const char* line, size_t size)
{
    int retval;
    char* tmpline = NULL;
    int* tmphighlight = NULL;
    source_line* tmp = NULL;

    /* allocate memory for the line. */
    tmpline = (char*)malloc(size + 1);
    if (NULL == tmpline)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* clear the line. */
    memset(tmpline, 0, size + 1);

    /* copy the line. */
    memcpy(tmpline, line, size);

    /* create a blank highlight line. */
    tmphighlight = (int*)malloc(size * sizeof(*tmphighlight));
    if (NULL == tmphighlight)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto cleanup_tmpline;
    }

    /* clear tmphighlight. */
    memset(tmphighlight, 0, size * sizeof(*tmphighlight));

    /* allocate memory for the item. */
    tmp = (source_line*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto cleanup_tmphighlight;
    }

    /* clear the item. */
    memset(tmp, 0, sizeof(*tmp));

    /* assign variables to this item. */
    tmp->line = tmpline;
    tmp->highlight_line = tmphighlight;
    tmp->length = size;

    /* these values are now owned by the item. */
    tmpline = NULL;
    tmphighlight = NULL;

    /* push this onto the list. */
    tmp->next = config->head;
    config->head = tmp;

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

cleanup_tmphighlight:
    if (NULL != tmphighlight)
    {
        free(tmphighlight);
    }

cleanup_tmpline:
    if (NULL != tmpline)
    {
        memset(tmpline, 0, size);
        free(tmpline);
    }

done:
    return retval;
}
