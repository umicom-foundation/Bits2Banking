/*-----------------------------------------------------------------------------
 * Bits2Banking — C23 Virtual Filesystem Laboratory
 * File: labs/native/vfs-descriptors/ram_provider.c
 * PURPOSE: Store Notes in bounded RAM and retain unlinked open nodes until
 *          their final description releases them.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "ram_provider.h"
#include <string.h>

static BtbRamFile *BtbRamNode(BtbRamProvider *provider, uint32_t node)
{
    if (provider == NULL || node == 0U || node > BTB_RAM_MAX_FILES)
        return NULL;
    BtbRamFile *const file = &provider->files[node - 1U];
    return (file->linked || file->references != 0U) ? file : NULL;
}

BtbVfsStatus BtbRamFileCreate(BtbRamProvider *provider, const char *name,
                              const void *initial, size_t initialBytes)
{
    if (provider == NULL || (initialBytes > 0U && initial == NULL))
        return BTB_VFS_INVALID_ARGUMENT;
    if (BtbVfsValidateName(name) != BTB_VFS_OK) return BTB_VFS_INVALID_PATH;
    if (initialBytes > BTB_RAM_FILE_CAPACITY) return BTB_VFS_NO_SPACE;
    size_t freeIndex = BTB_RAM_MAX_FILES;
    for (size_t i = 0U; i < BTB_RAM_MAX_FILES; ++i) {
        BtbRamFile *const file = &provider->files[i];
        if (file->linked && strcmp(file->name, name) == 0)
            return BTB_VFS_ALREADY_EXISTS;
        if (!file->linked && file->references == 0U && freeIndex == BTB_RAM_MAX_FILES)
            freeIndex = i;
    }
    if (freeIndex == BTB_RAM_MAX_FILES) return BTB_VFS_NO_SPACE;
    /* Stage input before changing a slot. This also protects a caller who
     * passed bytes currently located inside a reusable provider slot. */
    unsigned char copied[BTB_RAM_FILE_CAPACITY];
    if (initialBytes != 0U) (void)memmove(copied, initial, initialBytes);
    char copiedName[BTB_VFS_NAME_CAPACITY];
    (void)memmove(copiedName, name, strlen(name) + 1U);
    BtbRamFile *const file = &provider->files[freeIndex];
    *file = (BtbRamFile){0};
    (void)memcpy(file->name, copiedName, strlen(copiedName) + 1U);
    if (initialBytes != 0U) (void)memcpy(file->bytes, copied, initialBytes);
    file->size = initialBytes;
    file->linked = 1;
    return BTB_VFS_OK;
}

static BtbVfsStatus BtbRamOpen(void *context, const char *name, unsigned rights,
                               uint32_t *outNode)
{
    BtbRamProvider *provider = context;
    if (provider == NULL || outNode == NULL || name == NULL ||
        (rights & ~(BTB_VFS_READ | BTB_VFS_WRITE)) != 0U || rights == 0U)
        return BTB_VFS_INVALID_ARGUMENT;
    for (size_t i = 0U; i < BTB_RAM_MAX_FILES; ++i) {
        BtbRamFile *const file = &provider->files[i];
        if (file->linked && strcmp(file->name, name) == 0) {
            if (file->references >= BTB_VFS_MAX_DESCRIPTIONS) return BTB_VFS_NO_SPACE;
            ++file->references;
            *outNode = (uint32_t)(i + 1U);
            return BTB_VFS_OK;
        }
    }
    return BTB_VFS_NOT_FOUND;
}

static BtbVfsStatus BtbRamRead(void *context, uint32_t node, size_t position,
                               void *destination, size_t capacity, size_t *outRead)
{
    BtbRamFile *file = BtbRamNode(context, node);
    if (file == NULL || file->references == 0U || outRead == NULL ||
        (capacity > 0U && destination == NULL)) return BTB_VFS_INVALID_ARGUMENT;
    size_t available = position < file->size ? file->size - position : 0U;
    if (available > capacity) available = capacity;
    if (available != 0U) (void)memcpy(destination, file->bytes + position, available);
    *outRead = available;
    return BTB_VFS_OK;
}

static BtbVfsStatus BtbRamWrite(void *context, uint32_t node, size_t position,
                                const void *source, size_t bytes, size_t *outWritten)
{
    BtbRamFile *file = BtbRamNode(context, node);
    if (file == NULL || file->references == 0U || outWritten == NULL ||
        (bytes > 0U && source == NULL)) return BTB_VFS_INVALID_ARGUMENT;
    if (position > file->size || bytes > BTB_RAM_FILE_CAPACITY - position)
        return BTB_VFS_NO_SPACE;
    if (bytes != 0U) (void)memmove(file->bytes + position, source, bytes);
    if (position + bytes > file->size) file->size = position + bytes;
    *outWritten = bytes;
    return BTB_VFS_OK;
}

static BtbVfsStatus BtbRamUnlink(void *context, const char *name)
{
    BtbRamProvider *provider = context;
    if (provider == NULL || BtbVfsValidateName(name) != BTB_VFS_OK)
        return BTB_VFS_INVALID_ARGUMENT;
    for (size_t i = 0U; i < BTB_RAM_MAX_FILES; ++i) {
        BtbRamFile *const file = &provider->files[i];
        if (file->linked && strcmp(file->name, name) == 0) {
            file->linked = 0;
            if (file->references == 0U) *file = (BtbRamFile){0};
            return BTB_VFS_OK;
        }
    }
    return BTB_VFS_NOT_FOUND;
}

static BtbVfsStatus BtbRamRelease(void *context, uint32_t node)
{
    BtbRamFile *file = BtbRamNode(context, node);
    if (file == NULL || file->references == 0U) return BTB_VFS_BAD_STATE;
    --file->references;
    if (file->references == 0U && !file->linked) *file = (BtbRamFile){0};
    return BTB_VFS_OK;
}

BtbVfsProviderOps BtbRamProviderOperations(void)
{
    return (BtbVfsProviderOps){.open = BtbRamOpen, .read = BtbRamRead,
        .write = BtbRamWrite, .unlink = BtbRamUnlink, .release = BtbRamRelease};
}
