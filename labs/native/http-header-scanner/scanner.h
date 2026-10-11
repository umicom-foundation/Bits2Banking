/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/http-header-scanner/scanner.h
 * PURPOSE: Compare C with architecture-specific Assembly for bounded CRLF detection.
 *---------------------------------------------------------------------------*/
#ifndef BITS_HTTP_HEADER_SCANNER_H
#define BITS_HTTP_HEADER_SCANNER_H
#include <stddef.h>
#include <stdint.h>
/* Borrowed bytes may contain NUL. No terminator is required.
 * If count is zero, bytes may be NULL. No I/O, no allocations. */
int BitsHttpContainsCrlfC(const unsigned char *bytes, size_t count);
#if defined(BITS_HTTP_HAVE_ASSEMBLY)
int BitsHttpContainsCrlfAsm(const unsigned char *bytes, size_t count);
#endif
#endif
