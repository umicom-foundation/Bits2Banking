/*-----------------------------------------------------------------------------
 * Bits2Banking — Read-only VFS Provider Laboratory
 * File: labs/native/vfs-provider-composition/test_composition.c
 * PURPOSE: Test two providers, separate namespaces, descriptor access rights
 *          and last-reference release after a transient provider error.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "reference_provider.h"
#include "ram_provider.h"
#include "vfs.h"
#include <stdio.h>
#include <string.h>

#define REQUIRE(expr) do { if (!(expr)) { \
    (void)fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #expr); \
    return 1; } } while (0)

typedef struct FlakyReference {
    BtbReferenceProvider base;
    int failNextRelease;
} FlakyReference;

static BtbVfsStatus FlakyOpen(void *context, const char *name, unsigned rights,
                              uint32_t *outNode)
{
    FlakyReference *const flaky = context;
    const BtbVfsProviderOps ops = BtbReferenceProviderOperations();
    return ops.open(&flaky->base, name, rights, outNode);
}

static BtbVfsStatus FlakyRead(void *context, uint32_t node, size_t position,
                              void *destination, size_t capacity, size_t *outRead)
{
    FlakyReference *const flaky = context;
    const BtbVfsProviderOps ops = BtbReferenceProviderOperations();
    return ops.read(&flaky->base, node, position, destination, capacity, outRead);
}

static BtbVfsStatus FlakyRelease(void *context, uint32_t node)
{
    FlakyReference *const flaky = context;
    if (flaky->failNextRelease) {
        flaky->failNextRelease = 0;
        return BTB_VFS_BUSY;
    }
    const BtbVfsProviderOps ops = BtbReferenceProviderOperations();
    return ops.release(&flaky->base, node);
}

static int ComposeProviders(void)
{
    BtbVfs vfs = {0};
    BtbRamProvider notes = {0};
    BtbReferenceProvider library = {0};
    REQUIRE(BtbVfsInitialise(&vfs) == BTB_VFS_OK);
    REQUIRE(BtbRamFileCreate(&notes, "LESSON.TXT", "C23 Notes", 9U) == BTB_VFS_OK);
    REQUIRE(BtbVfsMount(&vfs, "/notes", 7U, BtbRamProviderOperations(), &notes) == BTB_VFS_OK);
    REQUIRE(BtbVfsMount(&vfs, "/library", 7U, BtbReferenceProviderOperations(), &library) == BTB_VFS_OK);
    BtbVfsHandle notesHandle = 0U;
    BtbVfsHandle bookHandle = 0U;
    REQUIRE(BtbVfsOpen(&vfs, 7U, "/notes/LESSON.TXT", BTB_VFS_READ | BTB_VFS_WRITE,
                       &notesHandle) == BTB_VFS_OK);
    REQUIRE(BtbVfsOpen(&vfs, 9U, "/library/MISSION.TXT", BTB_VFS_READ,
                       &bookHandle) == BTB_VFS_OK);
    char text[80] = {0};
    size_t count = 0U;
    REQUIRE(BtbVfsRead(&vfs, 9U, bookHandle, text, sizeof(text), &count) == BTB_VFS_OK);
    REQUIRE(count == strlen("Service to Many Leads to Greatness.\n"));
    REQUIRE(memcmp(text, "Service to Many Leads to Greatness.\n", count) == 0);
    BtbVfsHandle invalid = UINT64_C(77);
    REQUIRE(BtbVfsOpen(&vfs, 9U, "/library/MISSION.TXT", BTB_VFS_WRITE,
                       &invalid) == BTB_VFS_READ_ONLY);
    REQUIRE(invalid == UINT64_C(77));
    REQUIRE(BtbVfsUnlink(&vfs, 7U, "/library/MISSION.TXT") == BTB_VFS_READ_ONLY);
    REQUIRE(BtbVfsUnlink(&vfs, 9U, "/notes/LESSON.TXT") == BTB_VFS_DENIED);
    REQUIRE(BtbVfsUnmount(&vfs, 7U, "/library") == BTB_VFS_BUSY);
    REQUIRE(BtbVfsClose(&vfs, 9U, bookHandle) == BTB_VFS_OK);
    REQUIRE(library.openCount[0] == 0U);
    REQUIRE(BtbVfsUnmount(&vfs, 7U, "/library") == BTB_VFS_OK);
    REQUIRE(BtbVfsClose(&vfs, 7U, notesHandle) == BTB_VFS_OK);
    REQUIRE(BtbVfsUnmount(&vfs, 7U, "/notes") == BTB_VFS_OK);
    return 0;
}

static int FailedReleaseCanRetry(void)
{
    BtbVfs vfs = {0};
    FlakyReference fixture = {0};
    REQUIRE(BtbVfsInitialise(&vfs) == BTB_VFS_OK);
    BtbVfsProviderOps operations = {.open = FlakyOpen,
        .read = FlakyRead, .release = FlakyRelease};
    REQUIRE(BtbVfsMount(&vfs, "/library", 7U, operations, &fixture) == BTB_VFS_OK);
    BtbVfsHandle token = 0U;
    REQUIRE(BtbVfsOpen(&vfs, 7U, "/library/COURSES.TXT", BTB_VFS_READ,
                       &token) == BTB_VFS_OK);
    fixture.failNextRelease = 1;
    REQUIRE(BtbVfsClose(&vfs, 7U, token) == BTB_VFS_BUSY);
    REQUIRE(BtbVfsUnmount(&vfs, 7U, "/library") == BTB_VFS_BUSY);
    REQUIRE(fixture.base.openCount[1] == 1U);
    REQUIRE(BtbVfsClose(&vfs, 7U, token) == BTB_VFS_OK);
    REQUIRE(BtbVfsClose(&vfs, 7U, token) == BTB_VFS_BAD_HANDLE);
    REQUIRE(fixture.base.openCount[1] == 0U);
    REQUIRE(BtbVfsUnmount(&vfs, 7U, "/library") == BTB_VFS_OK);
    return 0;
}

int main(void)
{
    if (ComposeProviders() != 0 || FailedReleaseCanRetry() != 0) return 1;
    (void)puts("VFS provider composition and release-retry checks passed.");
    return 0;
}
