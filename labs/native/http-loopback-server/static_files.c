/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/static_files.c
 * PURPOSE: Root-relative file streaming, with native no-follow handle checks.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef _WIN32
# define _POSIX_C_SOURCE 200809L
#endif
#include "static_files.h"
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <wchar.h>
#else
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
#endif

#define BTB_STATIC_NATIVE_PATH 4096U

typedef struct BtbRootOwner {
#ifdef _WIN32
    HANDLE directory;
    wchar_t diskPath[BTB_STATIC_NATIVE_PATH];
    wchar_t canonicalPath[BTB_STATIC_NATIVE_PATH];
#else
    int descriptor;
#endif
} BtbRootOwner;
typedef struct BtbFileOwner {
#ifdef _WIN32
    HANDLE handle;
#else
    int descriptor;
#endif
} BtbFileOwner;

static int BtbHexDigit(unsigned char value)
{
    if (value >= '0' && value <= '9') return (int)(value - '0');
    if (value >= 'A' && value <= 'F') return (int)(value - 'A') + 10;
    if (value >= 'a' && value <= 'f') return (int)(value - 'a') + 10;
    return -1;
}
static int BtbAsciiNameByte(unsigned char value)
{
    return (value >= 'A' && value <= 'Z') ||
           (value >= 'a' && value <= 'z') ||
           (value >= '0' && value <= '9') ||
           value == '_' || value == '-' || value == '.';
}
static int BtbComponentAllowed(const char *name, size_t length)
{
    if (length == 0U || length > 240U) return 0;
    if ((length == 1U && name[0] == '.') ||
        (length == 2U && name[0] == '.' && name[1] == '.')) return 0;
    /* Prevent exposing metadata such as .git and Windows trailing-dot aliases.
     * A static web root has no reason to serve hidden metadata. */
    if (name[0] == '.' || name[length - 1U] == '.') return 0;
    for (size_t i = 0U; i < length; ++i)
        if (!BtbAsciiNameByte((unsigned char)name[i])) return 0;
    /* Reject Windows device names on every OS to keep the exercises portable.
     * The device-name restriction applies even with a file extension. */
    size_t base = 0U;
    while (base < length && name[base] != '.') ++base;
    char word[8];
    if (base < 3U || base >= sizeof word) return 1;
    for (size_t i = 0U; i < base; ++i)
        word[i] = (char)toupper((unsigned char)name[i]);
    word[base] = '\0';
    if (!strcmp(word, "CON") || !strcmp(word, "PRN") ||
        !strcmp(word, "AUX") || !strcmp(word, "NUL")) return 0;
    if (base == 4U && ((memcmp(word, "COM", 3U) == 0) ||
                        (memcmp(word, "LPT", 3U) == 0)) &&
        word[3] >= '1' && word[3] <= '9') return 0;
    return 1;
}

/* The input is an ASCII URL path with no query. It is decoded exactly once
 * without broadening an encoded slash or backslash into a directory boundary.
 * The result is a canonical, relative, forward-slash-separated portable name. */
static BtbStaticResult BtbPortableRelative(const char *url,
                                           char output[BTB_STATIC_MAX_PATH])
{
    if (url == NULL || url[0] != '/') return BTB_STATIC_FORBIDDEN;
    const size_t size = strlen(url);
    if (size >= BTB_STATIC_MAX_PATH) return BTB_STATIC_TOO_LARGE;
    size_t used = 0U;
    for (size_t i = 1U; i < size; ++i) {
        unsigned char c = (unsigned char)url[i];
        if (c == '%') {
            if (size - i < 3U) return BTB_STATIC_FORBIDDEN;
            const int a = BtbHexDigit((unsigned char)url[i + 1U]);
            const int b = BtbHexDigit((unsigned char)url[i + 2U]);
            if (a < 0 || b < 0) return BTB_STATIC_FORBIDDEN;
            c = (unsigned char)((unsigned)a * 16U + (unsigned)b);
            i += 2U;
            /* No double decoding, separator rewriting, or encoded NUL. */
            if (c == '%' || c == '/' || c == '\\') return BTB_STATIC_FORBIDDEN;
        }
        if (c != '/' && !BtbAsciiNameByte(c)) return BTB_STATIC_FORBIDDEN;
        if (used + 1U >= BTB_STATIC_MAX_PATH) return BTB_STATIC_TOO_LARGE;
        output[used++] = (char)c;
    }
    /* '/' and '/guide/' serve their index page. Double slashes remain invalid. */
    if (used == 0U || output[used - 1U] == '/') {
        const char suffix[] = "index.html";
        if (sizeof suffix > BTB_STATIC_MAX_PATH - used) return BTB_STATIC_TOO_LARGE;
        memcpy(output + used, suffix, sizeof suffix);
        used += sizeof suffix - 1U;
    }
    output[used] = '\0';
    size_t beginning = 0U;
    for (size_t i = 0U; i <= used; ++i) {
        if (output[i] == '/' || output[i] == '\0') {
            if (!BtbComponentAllowed(output + beginning, i - beginning))
                return BTB_STATIC_FORBIDDEN;
            beginning = i + 1U;
        }
    }
    return BTB_STATIC_OK;
}

const char *BtbStaticResultText(BtbStaticResult result)
{
    switch (result) {
        case BTB_STATIC_OK: return "ok";
        case BTB_STATIC_NOT_FOUND: return "not found";
        case BTB_STATIC_FORBIDDEN: return "forbidden";
        case BTB_STATIC_TOO_LARGE: return "too large";
        case BTB_STATIC_IO_ERROR: return "I/O failure";
    }
    return "unknown";
}

const char *BtbStaticMediaType(const char *relative)
{
    if (relative == NULL) return "application/octet-stream";
    const char *name = strrchr(relative, '/');
    name = name == NULL ? relative : name + 1;
    const char *dot = strrchr(name, '.');
    if (dot == NULL) return "application/octet-stream";
    /* The static suffix catalogue describes supported educational assets;
     * it does not call into a system MIME database or execute file contents. */
    if (!strcmp(dot, ".html") || !strcmp(dot, ".htm")) return "text/html; charset=utf-8";
    if (!strcmp(dot, ".css")) return "text/css; charset=utf-8";
    if (!strcmp(dot, ".js") || !strcmp(dot, ".mjs")) return "text/javascript; charset=utf-8";
    if (!strcmp(dot, ".json") || !strcmp(dot, ".map")) return "application/json";
    if (!strcmp(dot, ".svg")) return "image/svg+xml";
    if (!strcmp(dot, ".png")) return "image/png";
    if (!strcmp(dot, ".jpg") || !strcmp(dot, ".jpeg")) return "image/jpeg";
    if (!strcmp(dot, ".gif")) return "image/gif";
    if (!strcmp(dot, ".webp")) return "image/webp";
    if (!strcmp(dot, ".ico")) return "image/x-icon";
    if (!strcmp(dot, ".woff")) return "font/woff";
    if (!strcmp(dot, ".woff2")) return "font/woff2";
    if (!strcmp(dot, ".ttf")) return "font/ttf";
    if (!strcmp(dot, ".otf")) return "font/otf";
    if (!strcmp(dot, ".wasm")) return "application/wasm";
    if (!strcmp(dot, ".pdf")) return "application/pdf";
    if (!strcmp(dot, ".epub")) return "application/epub+zip";
    if (!strcmp(dot, ".xml")) return "application/xml";
    if (!strcmp(dot, ".txt") || !strcmp(dot, ".md")) return "text/plain; charset=utf-8";
    return "application/octet-stream";
}

#ifdef _WIN32
static int BtbToWide(const char *utf8, wchar_t output[BTB_STATIC_NATIVE_PATH])
{
    if (utf8 == NULL) return 0;
    size_t n = strlen(utf8);
    if (n == 0U || n > 3U * BTB_STATIC_MAX_PATH) return 0;
    const int units = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, utf8, -1,
                                         output, (int)BTB_STATIC_NATIVE_PATH);
    return units > 0;
}
/* Use the stable handle's final resolved path; a Windows directory component
 * cannot redirect the file outside the root by substituting a reparse point. */
static int BtbFinalPath(HANDLE handle, wchar_t result[BTB_STATIC_NATIVE_PATH])
{
    const DWORD chars = GetFinalPathNameByHandleW(handle, result,
                                                   BTB_STATIC_NATIVE_PATH,
                                                   FILE_NAME_NORMALIZED);
    return chars != 0U && chars < BTB_STATIC_NATIVE_PATH;
}
static int BtbInside(const wchar_t *root, const wchar_t *candidate)
{
    size_t prefix = wcslen(root);
    if (_wcsnicmp(root, candidate, prefix) != 0) return 0;
    return candidate[prefix] == L'\\';
}
#endif

BtbStaticResult BtbStaticRootOpen(const char *absolutePath, BtbStaticRoot *outRoot)
{
    if (absolutePath == NULL || outRoot == NULL || outRoot->owner != NULL)
        return BTB_STATIC_FORBIDDEN;
    BtbRootOwner *owner = calloc(1U, sizeof(*owner));
    if (owner == NULL) return BTB_STATIC_IO_ERROR;
#ifdef _WIN32
    wchar_t wanted[BTB_STATIC_NATIVE_PATH];
    /* Explicit local drive path. Network shares and relative roots are not
     * admitted by the teaching server. They can be added with separate tests. */
    if (!BtbToWide(absolutePath, wanted) ||
        !((wanted[0] >= L'A' && wanted[0] <= L'Z') ||
          (wanted[0] >= L'a' && wanted[0] <= L'z')) ||
        wanted[1] != L':' || (wanted[2] != L'\\' && wanted[2] != L'/')) {
        free(owner);
        return BTB_STATIC_FORBIDDEN;
    }
    DWORD used = GetFullPathNameW(wanted, BTB_STATIC_NATIVE_PATH,
                                  owner->diskPath, NULL);
    if (used == 0U || used >= BTB_STATIC_NATIVE_PATH) {
        free(owner);
        return BTB_STATIC_TOO_LARGE;
    }
    owner->directory = CreateFileW(owner->diskPath, FILE_LIST_DIRECTORY,
                                   FILE_SHARE_READ, NULL, OPEN_EXISTING,
                                   FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT, NULL);
    if (owner->directory == INVALID_HANDLE_VALUE) {
        free(owner);
        return BTB_STATIC_NOT_FOUND;
    }
    BY_HANDLE_FILE_INFORMATION info;
    if (!GetFileInformationByHandle(owner->directory, &info) ||
        (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0U ||
        (info.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) != 0U ||
        !BtbFinalPath(owner->directory, owner->canonicalPath)) {
        CloseHandle(owner->directory);
        free(owner);
        return BTB_STATIC_FORBIDDEN;
    }
    size_t end = wcslen(owner->canonicalPath);
    while (end > 4U && owner->canonicalPath[end - 1U] == L'\\')
        owner->canonicalPath[--end] = L'\0';
    end = wcslen(owner->diskPath);
    while (end > 3U && (owner->diskPath[end - 1U] == L'\\' ||
                         owner->diskPath[end - 1U] == L'/'))
        owner->diskPath[--end] = L'\0';
#else
    if (absolutePath[0] != '/' || strlen(absolutePath) >= BTB_STATIC_NATIVE_PATH) {
        free(owner);
        return BTB_STATIC_FORBIDDEN;
    }
    owner->descriptor = open(absolutePath, O_RDONLY | O_DIRECTORY | O_NOFOLLOW | O_CLOEXEC);
    if (owner->descriptor < 0) {
        const int problem = errno;
        free(owner);
        return problem == ENOENT ? BTB_STATIC_NOT_FOUND : BTB_STATIC_FORBIDDEN;
    }
#endif
    outRoot->owner = owner;
    return BTB_STATIC_OK;
}
void BtbStaticRootClose(BtbStaticRoot *root)
{
    if (root == NULL || root->owner == NULL) return;
    BtbRootOwner *owner = root->owner;
#ifdef _WIN32
    (void)CloseHandle(owner->directory);
#else
    (void)close(owner->descriptor);
#endif
    free(owner);
    root->owner = NULL;
}

BtbStaticResult BtbStaticFileOpen(const BtbStaticRoot *root, const char *urlPath,
                                   BtbStaticFile *outFile)
{
    if (root == NULL || root->owner == NULL || outFile == NULL ||
        outFile->owner != NULL) return BTB_STATIC_FORBIDDEN;
    char relative[BTB_STATIC_MAX_PATH];
    BtbStaticResult status = BtbPortableRelative(urlPath, relative);
    if (status != BTB_STATIC_OK) return status;
    const BtbRootOwner *parent = root->owner;
    BtbFileOwner *owner = calloc(1U, sizeof(*owner));
    if (owner == NULL) return BTB_STATIC_IO_ERROR;
    uint64_t length = 0U;
    uint64_t changedStamp = 0U;
#ifdef _WIN32
    wchar_t name[BTB_STATIC_NATIVE_PATH];
    wchar_t full[BTB_STATIC_NATIVE_PATH];
    if (!BtbToWide(relative, name)) { free(owner); return BTB_STATIC_TOO_LARGE; }
    size_t baseLength = wcslen(parent->diskPath), nameLength = wcslen(name);
    if (baseLength + nameLength + 2U >= BTB_STATIC_NATIVE_PATH) {
        free(owner);
        return BTB_STATIC_TOO_LARGE;
    }
    (void)wcscpy(full, parent->diskPath);
    full[baseLength++] = L'\\';
    for (size_t i = 0U; i < nameLength; ++i)
        full[baseLength + i] = name[i] == L'/' ? L'\\' : name[i];
    full[baseLength + nameLength] = L'\0';
    owner->handle = CreateFileW(full, GENERIC_READ, FILE_SHARE_READ, NULL,
                                OPEN_EXISTING, FILE_FLAG_OPEN_REPARSE_POINT, NULL);
    if (owner->handle == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        free(owner);
        return error == ERROR_FILE_NOT_FOUND || error == ERROR_PATH_NOT_FOUND
            ? BTB_STATIC_NOT_FOUND : BTB_STATIC_FORBIDDEN;
    }
    BY_HANDLE_FILE_INFORMATION info;
    wchar_t canonical[BTB_STATIC_NATIVE_PATH];
    LARGE_INTEGER size;
    if (!GetFileInformationByHandle(owner->handle, &info) ||
        (info.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_REPARSE_POINT)) != 0U ||
        !BtbFinalPath(owner->handle, canonical) ||
        !BtbInside(parent->canonicalPath, canonical) ||
        !GetFileSizeEx(owner->handle, &size) || size.QuadPart < 0) {
        CloseHandle(owner->handle);
        free(owner);
        return BTB_STATIC_FORBIDDEN;
    }
    length = (uint64_t)size.QuadPart;
    changedStamp = ((uint64_t)info.ftLastWriteTime.dwHighDateTime << 32U) |
                    (uint64_t)info.ftLastWriteTime.dwLowDateTime;
#else
    int previous = dup(parent->descriptor);
    if (previous < 0) { free(owner); return BTB_STATIC_IO_ERROR; }
    char components[BTB_STATIC_MAX_PATH];
    memcpy(components, relative, strlen(relative) + 1U);
    char *current = components;
    int finalDescriptor = -1;
    for (;;) {
        char *slash = strchr(current, '/');
        if (slash != NULL) *slash = '\0';
        const int last = slash == NULL;
        int opened = openat(previous, current,
                            O_RDONLY | O_CLOEXEC | O_NOFOLLOW | (last ? 0 : O_DIRECTORY));
        const int savedError = errno;
        (void)close(previous);
        if (opened < 0) {
            free(owner);
            return savedError == ENOENT ? BTB_STATIC_NOT_FOUND : BTB_STATIC_FORBIDDEN;
        }
        if (last) { finalDescriptor = opened; break; }
        previous = opened;
        current = slash + 1;
    }
    struct stat info;
    if (fstat(finalDescriptor, &info) != 0 || !S_ISREG(info.st_mode) || info.st_size < 0) {
        (void)close(finalDescriptor);
        free(owner);
        return BTB_STATIC_FORBIDDEN;
    }
    length = (uint64_t)info.st_size;
    /* Keep nanoseconds distinct where the host filesystem reports them.
     * The result is a metadata stamp, not a cryptographic content hash. */
    changedStamp = ((uint64_t)info.st_mtim.tv_sec << 32U) ^
                    (uint64_t)(uint32_t)info.st_mtim.tv_nsec;
    owner->descriptor = finalDescriptor;
#endif
    if (length > BTB_STATIC_MAX_FILE_BYTES) {
#ifdef _WIN32
        CloseHandle(owner->handle);
#else
        (void)close(owner->descriptor);
#endif
        free(owner);
        return BTB_STATIC_TOO_LARGE;
    }
    char tag[BTB_CACHE_TAG_CAPACITY];
    if (!BtbCacheTagFromMetadata(length, changedStamp, tag)) {
#ifdef _WIN32
        CloseHandle(owner->handle);
#else
        (void)close(owner->descriptor);
#endif
        free(owner);
        return BTB_STATIC_IO_ERROR;
    }
    outFile->owner = owner;
    outFile->bytes = length;
    memset(outFile->cacheTag, 0, sizeof outFile->cacheTag);
    memcpy(outFile->cacheTag, tag, strlen(tag) + 1U);
    outFile->mediaType = BtbStaticMediaType(relative);
    return BTB_STATIC_OK;
}
BtbStaticResult BtbStaticFileRead(BtbStaticFile *file, void *buffer, size_t capacity,
                                   size_t *outRead)
{
    if (file == NULL || file->owner == NULL || buffer == NULL ||
        outRead == NULL || capacity == 0U || capacity > BTB_STATIC_STREAM_BYTES)
        return BTB_STATIC_FORBIDDEN;
    BtbFileOwner *owner = file->owner;
#ifdef _WIN32
    DWORD got = 0U;
    if (!ReadFile(owner->handle, buffer, (DWORD)capacity, &got, NULL))
        return BTB_STATIC_IO_ERROR;
    *outRead = (size_t)got;
#else
    ssize_t got = -1;
    do { got = read(owner->descriptor, buffer, capacity); }
    while (got < 0 && errno == EINTR);
    if (got < 0) return BTB_STATIC_IO_ERROR;
    *outRead = (size_t)got;
#endif
    return BTB_STATIC_OK;
}
void BtbStaticFileClose(BtbStaticFile *file)
{
    if (file == NULL || file->owner == NULL) return;
    BtbFileOwner *owner = file->owner;
#ifdef _WIN32
    CloseHandle(owner->handle);
#else
    (void)close(owner->descriptor);
#endif
    free(owner);
    *file = (BtbStaticFile){0};
}
