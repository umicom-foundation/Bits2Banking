/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-http-contracts/check.h
 *
 * PURPOSE:
 *   Report failed educational expectations without depending on assert build options.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef BTB_HTTP_CHECK_H
#define BTB_HTTP_CHECK_H
#include <stdio.h>
#define REQUIRE(condition) do { \
    if (!(condition)) { \
        fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition); \
        return 1; \
    } \
} while (0)
#endif
