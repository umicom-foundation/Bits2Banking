/*-----------------------------------------------------------------------------
 * Bits2Banking — C23 Virtual Filesystem Laboratory
 * File: labs/native/vfs-descriptors/ram_provider.h
 * PURPOSE: Provide copied, bounded Notes files behind the VFS callback ABI.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_RAM_PROVIDER_H
#define BTB_RAM_PROVIDER_H
#include "vfs.h"

#define BTB_RAM_MAX_FILES 8U
#define BTB_RAM_FILE_CAPACITY 256U

typedef struct BtbRamFile {
    int linked;
    char name[BTB_VFS_NAME_CAPACITY];
    unsigned char bytes[BTB_RAM_FILE_CAPACITY];
    size_t size;
    size_t references;
} BtbRamFile;

typedef struct BtbRamProvider {
    BtbRamFile files[BTB_RAM_MAX_FILES];
} BtbRamProvider;

/* Create files outside the VFS for the lab's initial fixture. The provider
 * copies the entire buffer and never retains a caller's pointer. */
BtbVfsStatus BtbRamFileCreate(BtbRamProvider *provider, const char *name,
                              const void *initial, size_t initialBytes);
BtbVfsProviderOps BtbRamProviderOperations(void);

#endif /* BTB_RAM_PROVIDER_H */
