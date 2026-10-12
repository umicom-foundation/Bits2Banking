/*-----------------------------------------------------------------------------
 * Bits2Banking — C23 Virtual Filesystem Laboratory
 * File: labs/native/vfs-descriptors/main.c
 * PURPOSE: Trace a Notes file through a mount, descriptor and shared position.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "vfs.h"
#include "ram_provider.h"
#include <stdio.h>

int main(void)
{
    BtbVfs vfs = {0};
    BtbRamProvider notes = {0};
    BtbVfsHandle handle = 0U;
    char text[16] = {0};
    size_t bytes = 0U;
    if (BtbVfsInitialise(&vfs) != BTB_VFS_OK ||
        BtbRamFileCreate(&notes, "PROJECT.TXT", "Umicom Studio", 13U) != BTB_VFS_OK ||
        BtbVfsMount(&vfs, "/notes", 101U, BtbRamProviderOperations(), &notes) != BTB_VFS_OK ||
        BtbVfsOpen(&vfs, 101U, "/notes/PROJECT.TXT", BTB_VFS_READ, &handle) != BTB_VFS_OK ||
        BtbVfsRead(&vfs, 101U, handle, text, sizeof(text) - 1U, &bytes) != BTB_VFS_OK ||
        BtbVfsClose(&vfs, 101U, handle) != BTB_VFS_OK ||
        BtbVfsUnmount(&vfs, 101U, "/notes") != BTB_VFS_OK) {
        (void)fputs("VFS Notes demonstration failed.\n", stderr);
        return 1;
    }
    text[bytes] = '\0';
    (void)printf("Mounted /notes: %s (%zu bytes)\n", text, bytes);
    return 0;
}
