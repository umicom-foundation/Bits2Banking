/* Bits2Banking | Sammy Hegab, Umicom Foundation | MIT */
#include "process_files.h"
#include "ram_provider.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    BtbVfs vfs = {0};
    BtbRamProvider notes = {0};
    BtbProcessFiles process = {0};
    const char path[] = "/notes/LESSON.TXT";
    const char contents[] = "Umicom Notes";
    BtbProcessFileReply reply = {0};
    if (BtbVfsInitialise(&vfs) != BTB_VFS_OK ||
        BtbRamFileCreate(&notes, "LESSON.TXT", contents, sizeof contents - 1U) != BTB_VFS_OK ||
        BtbVfsMount(&vfs, "/notes", 11U, BtbRamProviderOperations(), &notes) != BTB_VFS_OK ||
        BtbProcessFilesInitialise(&process, &vfs, 11U) != BTB_VFS_OK ||
        BtbProcessFilesPut(&process, 0U, path, sizeof path - 1U) != BTB_VFS_OK)
        return 1;
    const BtbProcessFileRequest open = {
        .operation = BTB_PROCESS_FILE_OPEN, .rights = BTB_VFS_READ,
        .offset = 0U, .length = sizeof path - 1U};
    if (BtbProcessFilesCall(&process, &open, &reply) != BTB_VFS_OK) return 1;
    const BtbVfsHandle handle = reply.descriptor;
    const BtbProcessFileRequest read = {.operation = BTB_PROCESS_FILE_READ,
        .descriptor = handle, .offset = 128U, .length = 24U};
    if (BtbProcessFilesCall(&process, &read, &reply) != BTB_VFS_OK) return 1;
    char copied[25] = {0};
    if (reply.bytesTransferred >= sizeof copied ||
        BtbProcessFilesGet(&process, 128U, copied, reply.bytesTransferred) != BTB_VFS_OK)
        return 1;
    printf("Process 11 read: %s\n", copied);
    if (BtbProcessFilesShutdown(&process) != BTB_VFS_OK ||
        BtbVfsUnmount(&vfs, 11U, "/notes") != BTB_VFS_OK) return 1;
    return 0;
}
