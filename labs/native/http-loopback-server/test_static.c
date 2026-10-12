/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/test_static.c
 * PURPOSE: Verify static MIME, byte streaming, URL guards and rooted handles.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef _WIN32
# define _POSIX_C_SOURCE 200809L
#endif
#include "http.h"
#include "static_files.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
# include <direct.h>
# define BTB_MKDIR(name) _mkdir(name)
# define BTB_GETCWD _getcwd
#else
# include <sys/stat.h>
# include <unistd.h>
# define BTB_MKDIR(name) mkdir(name, 0700)
# define BTB_GETCWD getcwd
#endif

#define BTB_TEST_BYTES 151241U
#define CHECK(condition) do { \
    if (!(condition)) { \
        fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition); \
        return 1; \
    } \
} while (0)

static int BtbRequest(const char *path, BtbHttpRequest *out, int files)
{
    char request[1800];
    const int count = snprintf(request, sizeof request,
        "GET %s HTTP/1.1\r\nHost: 127.0.0.1:8765\r\n\r\n", path);
    if (count < 0 || (size_t)count >= sizeof request) return 0;
    const BtbHttpResult outcome = files
        ? BtbHttpParseForFiles((const unsigned char *)request, (size_t)count, out)
        : BtbHttpParse((const unsigned char *)request, (size_t)count, out);
    return outcome == BTB_HTTP_OK;
}
static int BtbParserTests(void)
{
    BtbHttpRequest r = {0};
    CHECK(!BtbRequest("/index.html", &r, 0));
    CHECK(BtbRequest("/index.html", &r, 1));
    CHECK(strcmp(r.path, "/index.html") == 0);
    CHECK(BtbRequest("/guide/?page=2&lang=en", &r, 1));
    CHECK(strcmp(r.path, "/guide/") == 0);
    CHECK(BtbRequest("/assets/main%2Ecss", &r, 1));
    CHECK(!BtbRequest("/assets/main%2Ecss", &r, 0));
    CHECK(!BtbRequest("/assets/#fragment", &r, 1));
    CHECK(!BtbRequest("/assets/a b", &r, 1));
    char headers[1024];
    size_t bytes = 0U;
    CHECK(BtbHttpStaticHeaders(200U, "text/html; charset=utf-8", 151241U,
                                 headers, sizeof headers, &bytes));
    CHECK(bytes < sizeof headers);
    CHECK(strstr(headers, "Content-Length: 151241\r\n") != NULL);
    CHECK(strstr(headers, "X-Content-Type-Options: nosniff\r\n") != NULL);
    CHECK(!BtbHttpStaticHeaders(201U, "text/html", 1U, headers, sizeof headers, &bytes));
    CHECK(!BtbHttpStaticHeaders(200U, "text/html\r\nInjected: x", 1U,
                                  headers, sizeof headers, &bytes));
    CHECK(strcmp(BtbStaticMediaType("assets/main.css"), "text/css; charset=utf-8") == 0);
    CHECK(strcmp(BtbStaticMediaType("assets/unknown.ext"), "application/octet-stream") == 0);
    return 0;
}
static int BtbWrite(const char *name, size_t bytes, int generated)
{
    FILE *file = fopen(name, "wb");
    if (file == NULL) return 0;
    for (size_t i = 0U; i < bytes; ++i) {
        const int byte = generated ? (int)('A' + (int)(i % 26U)) : (int)'X';
        if (fputc(byte, file) == EOF) { fclose(file); return 0; }
    }
    return fclose(file) == 0;
}
static int BtbFileTests(void)
{
    char cwd[1024];
    if (BTB_GETCWD(cwd, sizeof cwd) == NULL) return 1;
    char rootPath[1500], nested[1600], large[1700], html[1700], css[1700], hidden[1700];
#define BTB_NAME(out, format, ...) do { \
    const int n = snprintf(out, sizeof out, format, __VA_ARGS__); \
    if (n < 0 || (size_t)n >= sizeof out) return 1; \
} while (0)
    BTB_NAME(rootPath, "%s/btb site fixture", cwd);
    BTB_NAME(nested, "%s/assets", rootPath);
    BTB_NAME(html, "%s/index.html", rootPath);
    BTB_NAME(css, "%s/main.css", nested);
    BTB_NAME(large, "%s/long.txt", nested);
    BTB_NAME(hidden, "%s/.git", rootPath);
    (void)BTB_MKDIR(rootPath);
    (void)BTB_MKDIR(nested);
    (void)BTB_MKDIR(hidden);
    CHECK(BtbWrite(html, 128U, 0));
    CHECK(BtbWrite(css, 54U, 0));
    CHECK(BtbWrite(large, BTB_TEST_BYTES, 1));
    BtbStaticRoot root = {0};
    CHECK(BtbStaticRootOpen("relative-root", &root) == BTB_STATIC_FORBIDDEN);
    CHECK(BtbStaticRootOpen(rootPath, &root) == BTB_STATIC_OK);
    CHECK(BtbStaticRootOpen(rootPath, &root) == BTB_STATIC_FORBIDDEN);
    BtbStaticFile file = {0};
    CHECK(BtbStaticFileOpen(&root, "/", &file) == BTB_STATIC_OK);
    CHECK(file.bytes == 128U);
    CHECK(strcmp(file.mediaType, "text/html; charset=utf-8") == 0);
    BtbStaticFileClose(&file);
    CHECK(BtbStaticFileOpen(&root, "/assets/main%2Ecss", &file) == BTB_STATIC_OK);
    CHECK(file.bytes == 54U);
    BtbStaticFileClose(&file);
    const char *refused[] = {
        "/../secret", "/%2e%2e/secret", "/assets/%2fconfig",
        "/assets/%5cconfig", "/assets/../../index.html", "/.git/config",
        "/CON.txt", "/assets//main.css", "/assets/main.css?x=1",
        "/assets/%252e%252e", "/assets/file:stream",
        "/assets/.secret", "/assets/..", "/assets/%00"
    };
    for (size_t i = 0U; i < sizeof refused / sizeof refused[0]; ++i)
        CHECK(BtbStaticFileOpen(&root, refused[i], &file) == BTB_STATIC_FORBIDDEN);
    CHECK(BtbStaticFileOpen(&root, "/absent.txt", &file) == BTB_STATIC_NOT_FOUND);
#ifndef _WIN32
    char linkPath[1700];
    BTB_NAME(linkPath, "%s/link.txt", rootPath);
    (void)unlink(linkPath);
    if (symlink(html, linkPath) == 0) {
        CHECK(BtbStaticFileOpen(&root, "/link.txt", &file) == BTB_STATIC_FORBIDDEN);
        (void)unlink(linkPath);
    }
#endif
    CHECK(BtbStaticFileOpen(&root, "/assets/long.txt", &file) == BTB_STATIC_OK);
    CHECK(file.bytes == BTB_TEST_BYTES);
    unsigned char buffer[BTB_STATIC_STREAM_BYTES];
    uint64_t seen = 0U;
    while (seen < file.bytes) {
        size_t got = 0U;
        CHECK(BtbStaticFileRead(&file, buffer, sizeof buffer, &got) == BTB_STATIC_OK);
        CHECK(got != 0U);
        for (size_t j = 0U; j < got; ++j)
            CHECK(buffer[j] == (unsigned char)('A' + (int)((seen + j) % 26U)));
        seen += got;
    }
    size_t eof = 9U;
    CHECK(BtbStaticFileRead(&file, buffer, sizeof buffer, &eof) == BTB_STATIC_OK);
    CHECK(eof == 0U);
    BtbStaticFileClose(&file);
    CHECK(seen == BTB_TEST_BYTES);
    BtbStaticRootClose(&root);
    BtbStaticRootClose(&root);
    return 0;
}
int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    if (strcmp(argv[1], "parsing") == 0) return BtbParserTests();
    if (strcmp(argv[1], "files") == 0) return BtbFileTests();
    return 2;
}
