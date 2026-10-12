/*-----------------------------------------------------------------------------
 * Bits2Banking — Read-only VFS Provider Laboratory
 * File: labs/native/vfs-provider-composition/main.c
 * PURPOSE: Read the same VFS API from writable Notes and read-only Library.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "reference_provider.h"
#include "ram_provider.h"
#include "vfs.h"
#include <stdio.h>

int main(void)
{
    BtbVfs vfs = {0};
    BtbRamProvider notes = {0};
    BtbReferenceProvider library = {0};
    BtbVfsHandle handle = 0U;
    char buffer[96] = {0};
    size_t readBytes = 0U;
    if (BtbVfsInitialise(&vfs) != BTB_VFS_OK ||
        BtbRamFileCreate(&notes, "PLAN.TXT", "Umicom learning plan", 20U) != BTB_VFS_OK ||
        BtbVfsMount(&vfs, "/notes", 101U, BtbRamProviderOperations(), &notes) != BTB_VFS_OK ||
        BtbVfsMount(&vfs, "/library", 101U, BtbReferenceProviderOperations(), &library) != BTB_VFS_OK ||
        BtbVfsOpen(&vfs, 101U, "/library/COURSES.TXT", BTB_VFS_READ, &handle) != BTB_VFS_OK ||
        BtbVfsRead(&vfs, 101U, handle, buffer, sizeof(buffer) - 1U, &readBytes) != BTB_VFS_OK ||
        BtbVfsClose(&vfs, 101U, handle) != BTB_VFS_OK ||
        BtbVfsUnmount(&vfs, 101U, "/library") != BTB_VFS_OK ||
        BtbVfsUnmount(&vfs, 101U, "/notes") != BTB_VFS_OK)
        return 1;
    buffer[readBytes] = '\0';
    (void)printf("Library: %s", buffer);
    return 0;
}
