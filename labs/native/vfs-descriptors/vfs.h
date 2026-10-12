/*-----------------------------------------------------------------------------
 * Bits2Banking — C23 Virtual Filesystem Laboratory
 * File: labs/native/vfs-descriptors/vfs.h
 * PURPOSE: Teach mount dispatch, per-client descriptors and shared open-file
 *          descriptions using a bounded, serial, hosted-C model.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_VFS_H
#define BTB_VFS_H

#include <stddef.h>
#include <stdint.h>

#define BTB_VFS_MAX_MOUNTS 4U
#define BTB_VFS_MAX_DESCRIPTIONS 8U
#define BTB_VFS_MAX_DESCRIPTORS 12U
#define BTB_VFS_PREFIX_CAPACITY 32U
#define BTB_VFS_PATH_CAPACITY 128U
#define BTB_VFS_NAME_CAPACITY 32U

#define BTB_VFS_READ  1U
#define BTB_VFS_WRITE 2U

typedef uint64_t BtbVfsHandle;

typedef enum BtbVfsStatus {
    BTB_VFS_OK = 0,
    BTB_VFS_INVALID_ARGUMENT,
    BTB_VFS_INVALID_PATH,
    BTB_VFS_NOT_INITIALISED,
    BTB_VFS_NOT_FOUND,
    BTB_VFS_ALREADY_EXISTS,
    BTB_VFS_DENIED,
    BTB_VFS_READ_ONLY,
    BTB_VFS_NO_SPACE,
    BTB_VFS_BAD_HANDLE,
    BTB_VFS_BUSY,
    BTB_VFS_BAD_STATE
} BtbVfsStatus;

/* Provider identifiers are provider-local. They are not memory addresses or
 * VFS descriptor tokens. Providers must preserve outputs on failure. */
typedef struct BtbVfsProviderOps {
    BtbVfsStatus (*open)(void *context, const char *name, unsigned rights,
                         uint32_t *outNode);
    BtbVfsStatus (*read)(void *context, uint32_t node, size_t position,
                         void *destination, size_t capacity, size_t *outRead);
    BtbVfsStatus (*write)(void *context, uint32_t node, size_t position,
                          const void *source, size_t bytes, size_t *outWritten);
    BtbVfsStatus (*unlink)(void *context, const char *name);
    BtbVfsStatus (*release)(void *context, uint32_t node);
} BtbVfsProviderOps;

/* These records are public only to allow fixed stack allocation and to make
 * the classroom lifetime visible. Clients must not mutate a live record. */
typedef struct BtbVfsMountRecord {
    int occupied;
    char prefix[BTB_VFS_PREFIX_CAPACITY];
    uint64_t namespaceOwner;
    BtbVfsProviderOps operations;
    void *context;
} BtbVfsMountRecord;

typedef struct BtbVfsDescriptionRecord {
    int occupied;
    size_t mountIndex;
    uint32_t node;
    size_t position;
    size_t references;
} BtbVfsDescriptionRecord;

typedef struct BtbVfsDescriptorRecord {
    int occupied;
    int retired;
    uint32_t generation;
    uint64_t client;
    size_t descriptionIndex;
    unsigned rights;
} BtbVfsDescriptorRecord;

typedef struct BtbVfs {
    const struct BtbVfs *self;
    BtbVfsMountRecord mounts[BTB_VFS_MAX_MOUNTS];
    BtbVfsDescriptionRecord descriptions[BTB_VFS_MAX_DESCRIPTIONS];
    BtbVfsDescriptorRecord descriptors[BTB_VFS_MAX_DESCRIPTORS];
} BtbVfs;

/* Pass zero-initialised caller storage. The object and every mounted provider
 * must remain at stable addresses while a descriptor is alive. Not thread-safe. */
BtbVfsStatus BtbVfsInitialise(BtbVfs *vfs);
BtbVfsStatus BtbVfsMount(BtbVfs *vfs, const char *prefix,
                         uint64_t namespaceOwner, BtbVfsProviderOps operations,
                         void *providerContext);
BtbVfsStatus BtbVfsUnmount(BtbVfs *vfs, uint64_t client, const char *prefix);

/* client is supplied by the trusted classroom harness. In a real kernel the
 * identity must be derived from the current process, not an untrusted arg. */
BtbVfsStatus BtbVfsOpen(BtbVfs *vfs, uint64_t client, const char *path,
                        unsigned rights, BtbVfsHandle *outHandle);
BtbVfsStatus BtbVfsDuplicate(BtbVfs *vfs, uint64_t client,
                             BtbVfsHandle existing, unsigned narrowedRights,
                             BtbVfsHandle *outHandle);
BtbVfsStatus BtbVfsRead(BtbVfs *vfs, uint64_t client, BtbVfsHandle handle,
                        void *destination, size_t capacity, size_t *outRead);
BtbVfsStatus BtbVfsWrite(BtbVfs *vfs, uint64_t client, BtbVfsHandle handle,
                         const void *source, size_t bytes, size_t *outWritten);
BtbVfsStatus BtbVfsClose(BtbVfs *vfs, uint64_t client, BtbVfsHandle handle);
/* Removing a name is namespace authority, not a descriptor's WRITE right. */
BtbVfsStatus BtbVfsUnlink(BtbVfs *vfs, uint64_t client, const char *path);
/* No directory traversal or creation is offered by this deliberately bounded
 * exercise. In particular, /mount/filename has exactly one filename part. */
BtbVfsStatus BtbVfsValidateName(const char *name);
const char *BtbVfsStatusText(BtbVfsStatus status);

#endif /* BTB_VFS_H */
