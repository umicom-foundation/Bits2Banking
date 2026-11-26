/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/fastcgi-head-review/head_review.h
 *
 * PURPOSE:
 *   Describe an offline fixture for HEAD length and header-only output.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef BITS_FASTCGI_HEAD_REVIEW_H
#define BITS_FASTCGI_HEAD_REVIEW_H
#include <stdbool.h>
#include <stddef.h>

/* Keep the classroom range small enough to inspect manually. The Framework
 * gateway has its own separately configured representation limits. */
enum { BITS_HEAD_REVIEW_LENGTH_LIMIT = 4096 };

typedef struct BitsHeadMetadata {
    bool reported;
    size_t representation_length;
} BitsHeadMetadata;

typedef enum BitsHeadResult {
    BITS_HEAD_OK,
    BITS_HEAD_INVALID,
    BITS_HEAD_RANGE,
    BITS_HEAD_OUTPUT
} BitsHeadResult;

/* Write a complete header-only fixture or leave the destination unchanged.
 * Length records the representation selected for GET when known. */
BitsHeadResult BitsHeadReviewFormat(BitsHeadMetadata metadata, char *output, size_t capacity);

#endif /* BITS_FASTCGI_HEAD_REVIEW_H */

