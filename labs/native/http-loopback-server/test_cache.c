/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/test_cache.c
 * PURPOSE: Validate conditional GET/HEAD, safe tags and metadata from opened files.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "cache_validator.h"
#include "http.h"
#include "static_files.h"
#include <stdio.h>
#include <string.h>
#define CHECK(condition) do { if (!(condition)) { \
    fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition); return 1; \
} } while (0)

static BtbHttpResult Parse(const char *header, BtbHttpRequest *out, const char *method)
{
    char request[800];
    const int length = snprintf(request, sizeof request,
        "%s /index.html HTTP/1.1\r\nHost: 127.0.0.1:8765\r\n%s\r\n",
        method, header);
    if (length <= 0 || (size_t)length >= sizeof request) return BTB_HTTP_INVALID;
    return BtbHttpParseForFiles((const unsigned char *)request, (size_t)length, out);
}
static int Validators(void)
{
    char tag[BTB_CACHE_TAG_CAPACITY] = {0};
    CHECK(BtbCacheTagFromMetadata(123U, 987U, tag));
    CHECK(strcmp(tag, "W/\"000000000000007b-00000000000003db\"") == 0);
    CHECK(BtbCacheCompareIfNoneMatch(tag, tag) == BTB_CACHE_MATCH);
    CHECK(BtbCacheCompareIfNoneMatch("\"000000000000007b-00000000000003db\"", tag)
           == BTB_CACHE_MATCH);
    CHECK(BtbCacheCompareIfNoneMatch("  \"other\" , W/\"000000000000007b-00000000000003db\" ", tag)
           == BTB_CACHE_MATCH);
    CHECK(BtbCacheCompareIfNoneMatch("*", tag) == BTB_CACHE_MATCH);
    CHECK(BtbCacheCompareIfNoneMatch("\"other\"", tag) == BTB_CACHE_MISS);
    CHECK(BtbCacheCompareIfNoneMatch("\"other\", \"again\"", tag) == BTB_CACHE_MISS);
    const char *invalid[] = {"", " ", "W/", "W/\"open", "\"x\",", "*, \"x\"",
        "\"x\" \"y\"", "\"x\"\r\n", "W/\"x\"junk", "\"x\",,\"y\"", "bad"};
    for (size_t i = 0U; i < sizeof invalid / sizeof invalid[0]; ++i)
        CHECK(BtbCacheCompareIfNoneMatch(invalid[i], tag) == BTB_CACHE_INVALID);
    BtbHttpRequest request = {0};
    CHECK(Parse("If-None-Match: W/\"123\"\r\n", &request, "GET") == BTB_HTTP_OK);
    CHECK(request.ifNoneMatchPresent == 1U);
    CHECK(strcmp(request.ifNoneMatch, "W/\"123\"") == 0);
    CHECK(Parse("If-None-Match: *\r\n", &request, "HEAD") == BTB_HTTP_OK);
    CHECK(strcmp(request.ifNoneMatch, "*") == 0);
    CHECK(Parse("If-None-Match: \"x\"\r\nIf-None-Match: \"y\"\r\n", &request, "GET")
           == BTB_HTTP_INVALID);
    CHECK(Parse("If-None-Match: W/\"unfinished\r\n", &request, "GET")
           == BTB_HTTP_INVALID);
    CHECK(Parse("If-None-Match: \"x\",,\"y\"\r\n", &request, "GET")
           == BTB_HTTP_INVALID);
    char headers[1024];
    size_t bytes = 0U;
    CHECK(BtbCacheStaticHeaders(200U, "text/plain; charset=utf-8", 123U,
                                tag, headers, sizeof headers, &bytes));
    CHECK(bytes > 0U && strstr(headers, "Content-Length: 123\r\n") != NULL);
    CHECK(strstr(headers, "Cache-Control: private, no-cache") != NULL);
    CHECK(strstr(headers, "ETag: W/\"") != NULL);
    CHECK(BtbCacheStaticHeaders(304U, "text/plain", 123U,
                                tag, headers, sizeof headers, &bytes));
    CHECK(strncmp(headers, "HTTP/1.1 304 Not Modified\r\n", 27U) == 0);
    CHECK(strstr(headers, "Content-Length:") == NULL);
    CHECK(strstr(headers, "Content-Type:") == NULL);
    CHECK(headers[bytes - 1U] == '\n');
    CHECK(!BtbCacheStaticHeaders(302U, "text/plain", 1U, tag, headers, sizeof headers, &bytes));
    CHECK(!BtbCacheStaticHeaders(200U, "text/plain\r\nInjected: yes", 1U,
                                 tag, headers, sizeof headers, &bytes));
    return 0;
}
static int FileTags(const char *rootPath)
{
    BtbStaticRoot root = {0};
    CHECK(BtbStaticRootOpen(rootPath, &root) == BTB_STATIC_OK);
    BtbStaticFile file = {0}, other = {0};
    CHECK(BtbStaticFileOpen(&root, "/index.html", &file) == BTB_STATIC_OK);
    CHECK(file.bytes > 0U && file.cacheTag[0] == 'W');
    CHECK(BtbCacheCompareIfNoneMatch(file.cacheTag, file.cacheTag) == BTB_CACHE_MATCH);
    CHECK(BtbStaticFileOpen(&root, "/assets/site.css", &other) == BTB_STATIC_OK);
    CHECK(BtbCacheCompareIfNoneMatch(file.cacheTag, other.cacheTag) == BTB_CACHE_MISS);
    BtbStaticFileClose(&other);
    BtbStaticFileClose(&file);
    CHECK(file.owner == NULL && file.cacheTag[0] == '\0');
    BtbStaticRootClose(&root);
    return 0;
}
int main(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "validators") == 0) return Validators();
    if (argc == 3 && strcmp(argv[1], "files") == 0) return FileTags(argv[2]);
    return 2;
}
