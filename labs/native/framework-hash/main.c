/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/native/framework-hash/main.c
 *
 * PURPOSE:
 *   Exercise the Framework SHA-256 service through a small installed-SDK client.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <umicom/base/sha256.h>
#include <stdio.h>
#include <string.h>

#define REQUIRE(condition) do { if (!(condition)) { \
    fprintf(stderr, "Contract failed at line %d: %s\n", __LINE__, #condition); \
    return 1; } } while (0)

static const char abcDigest[] =
    "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";

static int Known(void)
{
    char hex[UMI_SHA256_HEX_CAPACITY];
    /* The array capacity includes the terminator; the input length does not. */
    REQUIRE(UmiSha256Buffer("abc", 3U, hex) == UMI_STATUS_OK);
    REQUIRE(strcmp(hex, abcDigest) == 0);
    puts(hex);
    puts("PASS known: the three input bytes match the reference digest");
    return 0;
}

static int Chunks(void)
{
    UmiSha256 context;
    unsigned char digest[UMI_SHA256_BYTES];
    char hex[UMI_SHA256_HEX_CAPACITY];
    UmiSha256Init(&context);
    REQUIRE(UmiSha256Update(&context, "a", 1U) == UMI_STATUS_OK);
    REQUIRE(UmiSha256Update(&context, "bc", 2U) == UMI_STATUS_OK);
    REQUIRE(UmiSha256Final(&context, digest) == UMI_STATUS_OK);
    UmiSha256Hex(digest, hex);
    REQUIRE(strcmp(hex, abcDigest) == 0);
    puts("PASS chunks: ordered pieces produce the same digest");
    return 0;
}

static int Changed(void)
{
    char first[UMI_SHA256_HEX_CAPACITY], second[UMI_SHA256_HEX_CAPACITY];
    REQUIRE(UmiSha256Buffer("abc", 3U, first) == UMI_STATUS_OK);
    REQUIRE(UmiSha256Buffer("abd", 3U, second) == UMI_STATUS_OK);
    REQUIRE(strcmp(first, second) != 0);
    puts("PASS changed: this changed input has a different digest");
    return 0;
}

static int Rejected(void)
{
    UmiSha256 context;
    unsigned char digest[UMI_SHA256_BYTES], before[UMI_SHA256_BYTES];
    UmiSha256Init(&context);
    REQUIRE(UmiSha256Update(&context, NULL, 1U) == UMI_STATUS_INVALID_ARGUMENT);
    /* Rejection must leave a usable context, not silently append partial data. */
    REQUIRE(UmiSha256Update(&context, "abc", 3U) == UMI_STATUS_OK);
    REQUIRE(UmiSha256Final(&context, digest) == UMI_STATUS_OK);
    char hex[UMI_SHA256_HEX_CAPACITY];
    UmiSha256Hex(digest, hex);
    REQUIRE(strcmp(hex, abcDigest) == 0);
    memset(digest, 0xA5, sizeof(digest));
    memcpy(before, digest, sizeof(before));
    REQUIRE(UmiSha256Final(&context, digest) != UMI_STATUS_OK);
    REQUIRE(memcmp(digest, before, sizeof(digest)) == 0);
    puts("PASS rejected: invalid input and repeated finish preserve their contracts");
    return 0;
}

static UmiStatus HashLink(const unsigned char previous[UMI_SHA256_BYTES],
                          const unsigned char record[8],
                          unsigned char output[UMI_SHA256_BYTES])
{
    /* This teaching record has two fixed-width fields and a format domain tag.
     * Framework owns hashing. The consumer owns serialization and field order.
     * This is an integrity demonstration, not a transaction or consensus engine. */
    static const unsigned char domain[] = "UMICOM-LEARNING-LINK";
    UmiSha256 context;
    UmiSha256Init(&context);
    UmiStatus status = UmiSha256Update(&context, domain, sizeof(domain) - 1U);
    if (status == UMI_STATUS_OK) status = UmiSha256Update(&context, previous, UMI_SHA256_BYTES);
    if (status == UMI_STATUS_OK) status = UmiSha256Update(&context, record, 8U);
    if (status == UMI_STATUS_OK) status = UmiSha256Final(&context, output);
    return status;
}

static int Chain(void)
{
    const unsigned char start[UMI_SHA256_BYTES] = {0};
    /* Sequence 1, amount 25: two unsigned little-endian 32-bit fields. */
    const unsigned char first[8] = {1, 0, 0, 0, 25, 0, 0, 0};
    const unsigned char changed[8] = {1, 0, 0, 0, 26, 0, 0, 0};
    const unsigned char second[8] = {2, 0, 0, 0, 30, 0, 0, 0};
    unsigned char firstHash[UMI_SHA256_BYTES], alteredHash[UMI_SHA256_BYTES];
    unsigned char trustedHead[UMI_SHA256_BYTES], recomputedHead[UMI_SHA256_BYTES];
    REQUIRE(HashLink(start, first, firstHash) == UMI_STATUS_OK);
    REQUIRE(HashLink(firstHash, second, trustedHead) == UMI_STATUS_OK);
    REQUIRE(HashLink(start, changed, alteredHash) == UMI_STATUS_OK);
    REQUIRE(HashLink(alteredHash, second, recomputedHead) == UMI_STATUS_OK);
    REQUIRE(memcmp(trustedHead, recomputedHead, sizeof(trustedHead)) != 0);
    REQUIRE(HashLink(firstHash, second, recomputedHead) == UMI_STATUS_OK);
    REQUIRE(memcmp(trustedHead, recomputedHead, sizeof(trustedHead)) == 0);
    puts("PASS chain: replay matches the retained head; changed history does not");
    return 0;
}

int main(int argc, char **argv)
{
    if (argc == 2) {
        if (strcmp(argv[1], "known") == 0) return Known();
        if (strcmp(argv[1], "chunks") == 0) return Chunks();
        if (strcmp(argv[1], "changed") == 0) return Changed();
        if (strcmp(argv[1], "rejected") == 0) return Rejected();
        if (strcmp(argv[1], "chain") == 0) return Chain();
    }
    fputs("Usage: btb-framework-hash known|chunks|changed|rejected|chain\n", stderr);
    return 2;
}
