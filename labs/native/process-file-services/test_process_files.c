/* Bits2Banking | Sammy Hegab, Umicom Foundation | MIT */
#include "process_files.h"
#include "ram_provider.h"
#include <stdio.h>
#include <string.h>
#define CHECK(q) do {if (!(q)) {fprintf(stderr,"%s:%d: %s\n",__FILE__,__LINE__,#q);return 1;}} while(0)

static int Setup(BtbVfs *vfs, BtbRamProvider *ram, BtbProcessFiles *owner)
{
    CHECK(BtbVfsInitialise(vfs) == BTB_VFS_OK);
    CHECK(BtbRamFileCreate(ram, "LESSON.TXT", "Original", 8U) == BTB_VFS_OK);
    CHECK(BtbVfsMount(vfs, "/notes", 11U, BtbRamProviderOperations(), ram) == BTB_VFS_OK);
    CHECK(BtbProcessFilesInitialise(owner, vfs, 11U) == BTB_VFS_OK);
    const char path[] = "/notes/LESSON.TXT";
    CHECK(BtbProcessFilesPut(owner, 0U, path, sizeof path - 1U) == BTB_VFS_OK);
    return 0;
}
static int Access(void)
{
    BtbVfs vfs = {0}; BtbRamProvider ram = {0}; BtbProcessFiles owner = {0};
    CHECK(Setup(&vfs, &ram, &owner) == 0);
    BtbProcessFileRequest call = {.operation = BTB_PROCESS_FILE_OPEN,
        .rights = BTB_VFS_READ | BTB_VFS_WRITE, .offset = 0U, .length = 17U};
    BtbProcessFileReply reply = {.descriptor = UINT64_C(555), .bytesTransferred = 777U};
    CHECK(BtbProcessFilesCall(&owner, &call, &reply) == BTB_VFS_OK);
    BtbVfsHandle handle = reply.descriptor;
    CHECK(handle != 0U);
    call = (BtbProcessFileRequest){.operation = BTB_PROCESS_FILE_READ, .descriptor = handle,
        .offset = 480U, .length = 8U};
    CHECK(BtbProcessFilesCall(&owner, &call, &reply) == BTB_VFS_OK);
    CHECK(reply.bytesTransferred == 8U);
    char bytes[10] = {0};
    CHECK(BtbProcessFilesGet(&owner, 480U, bytes, 8U) == BTB_VFS_OK);
    CHECK(memcmp(bytes,"Original",8U) == 0);
    CHECK(BtbProcessFilesPut(&owner, 510U, "XX", 2U) == BTB_VFS_OK);
    call.offset = 510U; call.length = 3U;
    const BtbProcessFileReply before = reply;
    CHECK(BtbProcessFilesCall(&owner, &call, &reply) == BTB_VFS_INVALID_ARGUMENT);
    CHECK(memcmp(&reply, &before, sizeof reply) == 0);
    CHECK(BtbProcessFilesGet(&owner, 510U, bytes, 2U) == BTB_VFS_OK);
    CHECK(memcmp(bytes,"XX",2U) == 0);
    call = (BtbProcessFileRequest){.operation = BTB_PROCESS_FILE_OPEN,
        .rights = BTB_VFS_READ, .offset = 0U, .length = 18U};
    CHECK(BtbProcessFilesCall(&owner, &call, &reply) == BTB_VFS_INVALID_PATH);
    CHECK(memcmp(&reply, &before, sizeof reply) == 0);
    call.length = 17U;
    CHECK(BtbProcessFilesPut(&owner, 4U, "\0", 1U) == BTB_VFS_OK);
    CHECK(BtbProcessFilesCall(&owner, &call, &reply) == BTB_VFS_INVALID_PATH);
    CHECK(BtbProcessFilesShutdown(&owner) == BTB_VFS_OK);
    CHECK(BtbVfsUnmount(&vfs, 11U, "/notes") == BTB_VFS_OK);
    return 0;
}
static int Lifetime(void)
{
    BtbVfs vfs = {0}; BtbRamProvider ram = {0}; BtbProcessFiles owner = {0};
    CHECK(Setup(&vfs, &ram, &owner) == 0);
    BtbProcessFileRequest open = {.operation = BTB_PROCESS_FILE_OPEN,
        .rights = BTB_VFS_READ, .offset = 0U, .length = 17U};
    BtbProcessFileReply reply = {0};
    CHECK(BtbProcessFilesCall(&owner, &open, &reply) == BTB_VFS_OK);
    const BtbVfsHandle handle = reply.descriptor;
    CHECK(BtbVfsUnmount(&vfs, 11U, "/notes") == BTB_VFS_BUSY);
    BtbProcessFileRequest read = {.operation = BTB_PROCESS_FILE_READ,
        .descriptor = handle, .offset = 128U, .length = 8U};
    CHECK(BtbProcessFilesCall(&owner, &read, &reply) == BTB_VFS_OK);
    CHECK(reply.bytesTransferred == 8U);
    BtbProcessFileRequest close = {.operation = BTB_PROCESS_FILE_CLOSE, .descriptor = handle};
    CHECK(BtbProcessFilesCall(&owner, &close, &reply) == BTB_VFS_OK);
    CHECK(BtbProcessFilesCall(&owner, &read, &reply) == BTB_VFS_BAD_HANDLE);
    CHECK(BtbProcessFilesShutdown(&owner) == BTB_VFS_OK);
    CHECK(BtbProcessFilesCall(&owner, &open, &reply) == BTB_VFS_BAD_STATE);
    CHECK(BtbProcessFilesGet(&owner, 128U, &close, 1U) == BTB_VFS_BAD_STATE);
    CHECK(BtbVfsUnmount(&vfs, 11U, "/notes") == BTB_VFS_OK);
    return 0;
}
int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    if (strcmp(argv[1],"access") == 0) return Access();
    if (strcmp(argv[1],"lifetime") == 0) return Lifetime();
    return 2;
}
