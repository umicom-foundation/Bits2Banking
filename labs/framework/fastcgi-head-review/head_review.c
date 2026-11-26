/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/fastcgi-head-review/head_review.c
 *
 * PURPOSE:
 *   Format a bounded classroom HEAD response with no document bytes.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "head_review.h"
#include <stdio.h>
#include <string.h>

BitsHeadResult BitsHeadReviewFormat(BitsHeadMetadata metadata, char *output, size_t capacity)
{
    if (output == NULL) return BITS_HEAD_INVALID;
    if (metadata.reported && metadata.representation_length > BITS_HEAD_REVIEW_LENGTH_LIMIT)
        return BITS_HEAD_RANGE;

    /* The boolean decides whether the header exists. An explicit zero must
     * travel through the same path as every other reported value. */
    char staged[96];
    const int used = metadata.reported
        ? snprintf(staged, sizeof staged, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %zu\r\n\r\n",
            metadata.representation_length)
        : snprintf(staged, sizeof staged, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
    if (used < 0 || (size_t)used >= sizeof staged || (size_t)used >= capacity)
        return BITS_HEAD_OUTPUT;

    /* Copy only after the complete response and C terminator fit.
     * No worker document is part of this formatting contract. */
    memcpy(output, staged, (size_t)used + 1U);
    return BITS_HEAD_OK;
}

