/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/static_files.h
 * PURPOSE: Open and stream read-only regular files beneath one selected root.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_STATIC_FILES_H
#define BTB_STATIC_FILES_H
#include <stddef.h>
#include <stdint.h>

/* Teaching limits. Each file is streamed; it is never allocated as one buffer.
 * An explicit absolute directory is required. No directory listing, uploads,
 * symlink traversal, CGI, PHP execution or public-network binding is provided. */
#define BTB_STATIC_MAX_PATH 1024U
#define BTB_STATIC_MAX_FILE_BYTES (64ULL * 1024ULL * 1024ULL)
#define BTB_STATIC_STREAM_BYTES 8192U

typedef enum BtbStaticResult {
    BTB_STATIC_OK = 0,
    BTB_STATIC_NOT_FOUND,
    BTB_STATIC_FORBIDDEN,
    BTB_STATIC_TOO_LARGE,
    BTB_STATIC_IO_ERROR
} BtbStaticResult;

typedef struct BtbStaticRoot {
    void *owner; /* Private native directory owner; not an encoded path. */
} BtbStaticRoot;
typedef struct BtbStaticFile {
    void *owner; /* Private stable file handle, closed by StaticFileClose. */
    uint64_t bytes;
    const char *mediaType; /* Static constant borrowed for the file lifetime. */
} BtbStaticFile;

/* On success, the object must eventually be closed once. A refusal leaves the
 * caller's zero-initialised output unchanged. This laboratory is single-threaded. */
BtbStaticResult BtbStaticRootOpen(const char *absolutePath, BtbStaticRoot *outRoot);
void BtbStaticRootClose(BtbStaticRoot *root);

/* URL path must have been parsed by the HTTP layer (no query). Decode at most
 * once. Reject dot segments, portable reserved names, hidden components,
 * encoded separators, paths outside root, and filesystem symlinks/reparse
 * points. '/' and a trailing '/' select index.html. No arbitrary user path is
 * ever passed to a shell. The file is opened in read-only mode. */
BtbStaticResult BtbStaticFileOpen(const BtbStaticRoot *root, const char *urlPath,
                                   BtbStaticFile *outFile);
BtbStaticResult BtbStaticFileRead(BtbStaticFile *file, void *buffer, size_t capacity,
                                   size_t *outRead);
void BtbStaticFileClose(BtbStaticFile *file);

/* MIME names are a small, intentionally explicit teaching allow-list. Unknown
 * suffixes are served as application/octet-stream and marked nosniff. */
const char *BtbStaticMediaType(const char *portableRelativePath);
const char *BtbStaticResultText(BtbStaticResult result);
#endif
