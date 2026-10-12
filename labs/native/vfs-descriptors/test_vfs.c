/*-----------------------------------------------------------------------------
 * Bits2Banking — C23 Virtual Filesystem Laboratory
 * File: labs/native/vfs-descriptors/test_vfs.c
 * PURPOSE: Exercise descriptor ownership, shared offsets, namespace operations,
 *          stale-token refusal, capacity limits and failure preservation.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "vfs.h"
#include "ram_provider.h"
#include <stdio.h>
#include <string.h>

#define CHECK(expr) do { \
    if (!(expr)) { \
        (void)fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #expr); \
        return 1; \
    } \
} while (0)

static int Ownership(void)
{
    BtbVfs vfs = {0};
    BtbRamProvider ram = {0};
    CHECK(BtbVfsInitialise(&vfs) == BTB_VFS_OK);
    CHECK(BtbRamFileCreate(&ram, "NOTES.TXT", "ABCDE", 5U) == BTB_VFS_OK);
    CHECK(BtbVfsMount(&vfs, "/notes", 11U, BtbRamProviderOperations(), &ram) == BTB_VFS_OK);
    BtbVfsHandle original = 0U;
    BtbVfsHandle duplicate = 0U;
    BtbVfsHandle replacement = 0U;
    CHECK(BtbVfsOpen(&vfs, 11U, "/notes/NOTES.TXT", BTB_VFS_READ | BTB_VFS_WRITE,
                     &original) == BTB_VFS_OK);
    char buffer[8] = {0};
    size_t count = 999U;
    CHECK(BtbVfsRead(&vfs, 11U, original, buffer, 2U, &count) == BTB_VFS_OK);
    CHECK(count == 2U && memcmp(buffer, "AB", 2U) == 0);
    CHECK(BtbVfsDuplicate(&vfs, 11U, original, BTB_VFS_READ, &duplicate) == BTB_VFS_OK);
    CHECK(BtbVfsRead(&vfs, 11U, duplicate, buffer, 2U, &count) == BTB_VFS_OK);
    CHECK(count == 2U && memcmp(buffer, "CD", 2U) == 0);
    count = 12345U;
    CHECK(BtbVfsWrite(&vfs, 11U, duplicate, "X", 1U, &count) == BTB_VFS_DENIED);
    CHECK(count == 12345U);
    CHECK(BtbVfsRead(&vfs, 22U, duplicate, buffer, 2U, &count) == BTB_VFS_DENIED);
    CHECK(count == 12345U);
    CHECK(BtbVfsRead(&vfs, 11U, original, buffer, 2U, &count) == BTB_VFS_OK);
    CHECK(count == 1U && buffer[0] == 'E');
    CHECK(BtbVfsUnmount(&vfs, 11U, "/notes") == BTB_VFS_BUSY);
    CHECK(BtbVfsUnlink(&vfs, 22U, "/notes/NOTES.TXT") == BTB_VFS_DENIED);
    CHECK(BtbVfsUnlink(&vfs, 11U, "/notes/NOTES.TXT") == BTB_VFS_OK);
    BtbVfsHandle sentinel = UINT64_C(999);
    CHECK(BtbVfsOpen(&vfs, 11U, "/notes/NOTES.TXT", BTB_VFS_READ,
                     &sentinel) == BTB_VFS_NOT_FOUND);
    CHECK(sentinel == UINT64_C(999));
    CHECK(BtbRamFileCreate(&ram, "NOTES.TXT", "NEW", 3U) == BTB_VFS_OK);
    CHECK(BtbVfsOpen(&vfs, 11U, "/notes/NOTES.TXT", BTB_VFS_READ,
                     &replacement) == BTB_VFS_OK);
    CHECK(BtbVfsRead(&vfs, 11U, replacement, buffer, 4U, &count) == BTB_VFS_OK);
    CHECK(count == 3U && memcmp(buffer, "NEW", 3U) == 0);
    CHECK(BtbVfsClose(&vfs, 11U, original) == BTB_VFS_OK);
    CHECK(BtbVfsRead(&vfs, 11U, original, buffer, 1U, &count) == BTB_VFS_BAD_HANDLE);
    CHECK(BtbVfsClose(&vfs, 11U, duplicate) == BTB_VFS_OK);
    CHECK(BtbVfsClose(&vfs, 11U, replacement) == BTB_VFS_OK);
    CHECK(BtbVfsUnmount(&vfs, 22U, "/notes") == BTB_VFS_DENIED);
    CHECK(BtbVfsUnmount(&vfs, 11U, "/notes") == BTB_VFS_OK);
    CHECK(BtbVfsInitialise(&vfs) == BTB_VFS_BAD_STATE);
    return 0;
}

static int Validation(void)
{
    BtbVfs vfs = {0};
    BtbRamProvider ram = {0};
    CHECK(BtbVfsInitialise(&vfs) == BTB_VFS_OK);
    CHECK(BtbRamFileCreate(&ram, "SAVE.TXT", "data", 4U) == BTB_VFS_OK);
    CHECK(BtbVfsMount(&vfs, "/notes", 11U, BtbRamProviderOperations(), &ram) == BTB_VFS_OK);
    CHECK(BtbVfsMount(&vfs, "/notes", 11U, BtbRamProviderOperations(), &ram) == BTB_VFS_ALREADY_EXISTS);
    BtbVfsHandle token = UINT64_C(1234);
    const char *badPaths[] = {"/notes/../SAVE.TXT", "/notes/.secrets", "/notes/SUB/SAVE.TXT",
                              "/notes/", "/notes/NAME:TXT", "notes/SAVE.TXT"};
    for (size_t i = 0U; i < sizeof(badPaths) / sizeof(badPaths[0]); ++i) {
        CHECK(BtbVfsOpen(&vfs, 11U, badPaths[i], BTB_VFS_READ, &token) == BTB_VFS_INVALID_PATH);
        CHECK(token == UINT64_C(1234));
    }
    CHECK(BtbVfsOpen(&vfs, 11U, "/notes-old/SAVE.TXT", BTB_VFS_READ,
                     &token) == BTB_VFS_NOT_FOUND);
    CHECK(BtbVfsOpen(&vfs, 11U, "/notes/SAVE.TXT", BTB_VFS_READ, &token) == BTB_VFS_OK);
    size_t bytes = 55U;
    CHECK(BtbVfsWrite(&vfs, 11U, token, "!", 1U, &bytes) == BTB_VFS_DENIED);
    CHECK(bytes == 55U);
    BtbVfsHandle readOnly = token;
    BtbVfsHandle widened = UINT64_C(777);
    CHECK(BtbVfsDuplicate(&vfs, 11U, token, BTB_VFS_READ | BTB_VFS_WRITE,
                          &widened) == BTB_VFS_DENIED);
    CHECK(widened == UINT64_C(777));
    CHECK(BtbVfsClose(&vfs, 11U, token) == BTB_VFS_OK);
    CHECK(BtbVfsClose(&vfs, 11U, readOnly) == BTB_VFS_BAD_HANDLE);
    CHECK(BtbVfsOpen(&vfs, 11U, "/notes/SAVE.TXT", BTB_VFS_READ | BTB_VFS_WRITE,
                     &token) == BTB_VFS_OK);
    CHECK(token != readOnly);
    /* A failed oversized update leaves the file bytes and the shared offset
     * unchanged. Reading immediately afterwards must still start at zero. */
    unsigned char excess[BTB_RAM_FILE_CAPACITY + 1U] = {0};
    CHECK(BtbVfsWrite(&vfs, 11U, token, excess, sizeof(excess), &bytes) == BTB_VFS_NO_SPACE);
    CHECK(bytes == 55U);
    char buffer[8] = {0};
    CHECK(BtbVfsRead(&vfs, 11U, token, buffer, 4U, &bytes) == BTB_VFS_OK);
    CHECK(bytes == 4U && memcmp(buffer, "data", 4U) == 0);
    CHECK(BtbVfsClose(&vfs, 11U, token) == BTB_VFS_OK);
    /* A normal in-place write is copied into the provider. Reopening the
     * pathname obtains a fresh position and sees the updated four bytes. */
    CHECK(BtbVfsOpen(&vfs, 11U, "/notes/SAVE.TXT", BTB_VFS_READ | BTB_VFS_WRITE,
                     &token) == BTB_VFS_OK);
    CHECK(BtbVfsWrite(&vfs, 11U, token, "DONE", 4U, &bytes) == BTB_VFS_OK);
    CHECK(bytes == 4U);
    CHECK(BtbVfsClose(&vfs, 11U, token) == BTB_VFS_OK);
    CHECK(BtbVfsOpen(&vfs, 11U, "/notes/SAVE.TXT", BTB_VFS_READ, &token) == BTB_VFS_OK);
    CHECK(BtbVfsRead(&vfs, 11U, token, buffer, 4U, &bytes) == BTB_VFS_OK);
    CHECK(bytes == 4U && memcmp(buffer, "DONE", 4U) == 0);
    CHECK(BtbVfsClose(&vfs, 11U, token) == BTB_VFS_OK);
    BtbVfsHandle opened[BTB_VFS_MAX_DESCRIPTIONS];
    for (size_t i = 0U; i < BTB_VFS_MAX_DESCRIPTIONS; ++i)
        CHECK(BtbVfsOpen(&vfs, 11U, "/notes/SAVE.TXT", BTB_VFS_READ,
                         &opened[i]) == BTB_VFS_OK);
    const BtbVfsHandle last = UINT64_C(1234);
    BtbVfsHandle next = last;
    CHECK(BtbVfsOpen(&vfs, 11U, "/notes/SAVE.TXT", BTB_VFS_READ, &next) == BTB_VFS_NO_SPACE);
    CHECK(next == last);
    for (size_t i = 0U; i < BTB_VFS_MAX_DESCRIPTIONS; ++i)
        CHECK(BtbVfsClose(&vfs, 11U, opened[i]) == BTB_VFS_OK);
    /* Exercise thousands of synthetic obsolete tokens after every handle
     * has closed. None may regain authority over a reused table slot. */
    uint64_t seed = UINT64_C(0x132745ab91);
    for (size_t i = 0U; i < 4096U; ++i) {
        seed = seed * UINT64_C(6364136223846793005) + UINT64_C(1442695040888963407);
        bytes = 55U;
        CHECK(BtbVfsRead(&vfs, 11U, seed, buffer, sizeof(buffer), &bytes) == BTB_VFS_BAD_HANDLE);
        CHECK(bytes == 55U);
    }
    CHECK(BtbVfsUnmount(&vfs, 11U, "/notes") == BTB_VFS_OK);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        (void)fputs("Usage: btb-vfs-test ownership|validation\n", stderr);
        return 2;
    }
    int result = 2;
    if (strcmp(argv[1], "ownership") == 0) result = Ownership();
    else if (strcmp(argv[1], "validation") == 0) result = Validation();
    if (result == 0) (void)puts("VFS descriptor tests passed.");
    return result;
}
