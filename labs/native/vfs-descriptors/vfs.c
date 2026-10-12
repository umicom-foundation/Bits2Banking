/*-----------------------------------------------------------------------------
 * Bits2Banking — C23 Virtual Filesystem Laboratory
 * File: labs/native/vfs-descriptors/vfs.c
 * PURPOSE: Implement checked descriptor identities, shared offsets, mount
 *          dispatch and last-reference provider release in a serial model.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "vfs.h"
#include <stdint.h>
#include <string.h>

static int BtbVfsLive(const BtbVfs *vfs)
{
    return vfs != NULL && vfs->self == vfs;
}

static size_t BtbVfsBoundedLength(const char *text, size_t capacity)
{
    size_t count = 0U;
    if (text == NULL) return capacity;
    while (count < capacity && text[count] != '\0') ++count;
    return count;
}

BtbVfsStatus BtbVfsValidateName(const char *name)
{
    const size_t length = BtbVfsBoundedLength(name, BTB_VFS_NAME_CAPACITY);
    if (length == 0U || length == BTB_VFS_NAME_CAPACITY ||
        (length == 1U && name[0] == '.') ||
        (length == 2U && name[0] == '.' && name[1] == '.'))
        return BTB_VFS_INVALID_PATH;
    if (name[0] == '.') return BTB_VFS_INVALID_PATH;
    for (size_t i = 0U; i < length; ++i) {
        const unsigned char c = (unsigned char)name[i];
        const int permitted = (c >= 'A' && c <= 'Z') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= '0' && c <= '9') || c == '-' ||
                              c == '_' || c == '.';
        if (!permitted) return BTB_VFS_INVALID_PATH;
    }
    return BTB_VFS_OK;
}

static int BtbVfsValidRights(unsigned rights)
{
    return rights != 0U && (rights & ~(BTB_VFS_READ | BTB_VFS_WRITE)) == 0U;
}

BtbVfsStatus BtbVfsInitialise(BtbVfs *vfs)
{
    if (vfs == NULL) return BTB_VFS_INVALID_ARGUMENT;
    if (vfs->self != NULL) return BTB_VFS_BAD_STATE;
    /* The caller supplied zero-initialised storage. Do not reset an existing
     * owner because that could make previously retired handles valid again. */
    vfs->self = vfs;
    for (size_t i = 0U; i < BTB_VFS_MAX_DESCRIPTORS; ++i)
        vfs->descriptors[i].generation = 1U;
    return BTB_VFS_OK;
}

/* A mount prefix is a complete /segment, never a path with trailing slash. */
static int BtbVfsPrefixValid(const char *prefix)
{
    const size_t length = BtbVfsBoundedLength(prefix, BTB_VFS_PREFIX_CAPACITY);
    if (length <= 1U || length == BTB_VFS_PREFIX_CAPACITY || prefix[0] != '/')
        return 0;
    for (size_t i = 1U; i < length; ++i) {
        const unsigned char c = (unsigned char)prefix[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
              (c >= '0' && c <= '9') || c == '-')) return 0;
    }
    return 1;
}

BtbVfsStatus BtbVfsMount(BtbVfs *vfs, const char *prefix,
                         uint64_t namespaceOwner, BtbVfsProviderOps operations,
                         void *providerContext)
{
    if (!BtbVfsLive(vfs)) return BTB_VFS_NOT_INITIALISED;
    if (!BtbVfsPrefixValid(prefix) || namespaceOwner == 0U || providerContext == NULL ||
        operations.open == NULL || operations.read == NULL || operations.release == NULL)
        return BTB_VFS_INVALID_ARGUMENT;
    size_t freeIndex = BTB_VFS_MAX_MOUNTS;
    for (size_t i = 0U; i < BTB_VFS_MAX_MOUNTS; ++i) {
        if (vfs->mounts[i].occupied && strcmp(vfs->mounts[i].prefix, prefix) == 0)
            return BTB_VFS_ALREADY_EXISTS;
        if (!vfs->mounts[i].occupied && freeIndex == BTB_VFS_MAX_MOUNTS)
            freeIndex = i;
    }
    if (freeIndex == BTB_VFS_MAX_MOUNTS) return BTB_VFS_NO_SPACE;
    BtbVfsMountRecord *const mount = &vfs->mounts[freeIndex];
    /* All checks precede publication of the new mount. */
    (void)memset(mount, 0, sizeof(*mount));
    (void)memcpy(mount->prefix, prefix, strlen(prefix) + 1U);
    mount->namespaceOwner = namespaceOwner;
    mount->operations = operations;
    mount->context = providerContext;
    mount->occupied = 1;
    return BTB_VFS_OK;
}

/* Return an owned mount plus a borrowed relative name. The segment boundary
 * prevents /notes from matching /notes-old. A name cannot contain another /. */
static BtbVfsStatus BtbVfsRoute(BtbVfs *vfs, const char *path,
                                size_t *outMount, const char **outName)
{
    const size_t length = BtbVfsBoundedLength(path, BTB_VFS_PATH_CAPACITY);
    if (length < 4U || length >= BTB_VFS_PATH_CAPACITY || path[0] != '/')
        return BTB_VFS_INVALID_PATH;
    for (size_t i = 0U; i < BTB_VFS_MAX_MOUNTS; ++i) {
        const BtbVfsMountRecord *const mount = &vfs->mounts[i];
        if (!mount->occupied) continue;
        const size_t prefixLength = strlen(mount->prefix);
        if (length < prefixLength + 1U ||
            memcmp(path, mount->prefix, prefixLength) != 0 ||
            path[prefixLength] != '/') continue;
        if (length == prefixLength + 1U) return BTB_VFS_INVALID_PATH;
        const char *const name = path + prefixLength + 1U;
        if (BtbVfsValidateName(name) != BTB_VFS_OK) return BTB_VFS_INVALID_PATH;
        *outMount = i;
        *outName = name;
        return BTB_VFS_OK;
    }
    return BTB_VFS_NOT_FOUND;
}

static size_t BtbVfsFreeDescriptor(const BtbVfs *vfs)
{
    for (size_t i = 0U; i < BTB_VFS_MAX_DESCRIPTORS; ++i)
        if (!vfs->descriptors[i].occupied && !vfs->descriptors[i].retired)
            return i;
    return BTB_VFS_MAX_DESCRIPTORS;
}

static size_t BtbVfsFreeDescription(const BtbVfs *vfs)
{
    for (size_t i = 0U; i < BTB_VFS_MAX_DESCRIPTIONS; ++i)
        if (!vfs->descriptions[i].occupied) return i;
    return BTB_VFS_MAX_DESCRIPTIONS;
}

static BtbVfsHandle BtbVfsToken(size_t index, uint32_t generation)
{
    return ((uint64_t)generation << 32U) | (uint64_t)(index + 1U);
}

/* A token is a generation-tagged lookup key. The identity check must be made
 * using a trusted client identity; the token alone is not a secret. */
static BtbVfsStatus BtbVfsFind(BtbVfs *vfs, uint64_t client, BtbVfsHandle handle,
                               BtbVfsDescriptorRecord **outDescriptor)
{
    if (!BtbVfsLive(vfs)) return BTB_VFS_NOT_INITIALISED;
    if (client == 0U) return BTB_VFS_INVALID_ARGUMENT;
    const uint32_t low = (uint32_t)handle;
    const uint32_t generation = (uint32_t)(handle >> 32U);
    if (low == 0U || low > BTB_VFS_MAX_DESCRIPTORS || generation == 0U)
        return BTB_VFS_BAD_HANDLE;
    BtbVfsDescriptorRecord *const item = &vfs->descriptors[low - 1U];
    if (!item->occupied || item->generation != generation)
        return BTB_VFS_BAD_HANDLE;
    if (item->client != client) return BTB_VFS_DENIED;
    if (item->descriptionIndex >= BTB_VFS_MAX_DESCRIPTIONS ||
        !vfs->descriptions[item->descriptionIndex].occupied)
        return BTB_VFS_BAD_STATE;
    *outDescriptor = item;
    return BTB_VFS_OK;
}

BtbVfsStatus BtbVfsOpen(BtbVfs *vfs, uint64_t client, const char *path,
                        unsigned rights, BtbVfsHandle *outHandle)
{
    if (!BtbVfsLive(vfs)) return BTB_VFS_NOT_INITIALISED;
    if (client == 0U || outHandle == NULL || !BtbVfsValidRights(rights))
        return BTB_VFS_INVALID_ARGUMENT;
    size_t mountIndex = 0U;
    const char *name = NULL;
    BtbVfsStatus status = BtbVfsRoute(vfs, path, &mountIndex, &name);
    if (status != BTB_VFS_OK) return status;
    const size_t descriptorIndex = BtbVfsFreeDescriptor(vfs);
    const size_t descriptionIndex = BtbVfsFreeDescription(vfs);
    if (descriptorIndex == BTB_VFS_MAX_DESCRIPTORS ||
        descriptionIndex == BTB_VFS_MAX_DESCRIPTIONS) return BTB_VFS_NO_SPACE;
    BtbVfsMountRecord *const mount = &vfs->mounts[mountIndex];
    if ((rights & BTB_VFS_WRITE) != 0U && mount->operations.write == NULL)
        return BTB_VFS_READ_ONLY;
    uint32_t node = 0U;
    status = mount->operations.open(mount->context, name, rights, &node);
    if (status != BTB_VFS_OK) return status;
    /* A successful provider Open must return a nonzero node. A broken
     * provider cannot be silently converted into a valid VFS descriptor. */
    if (node == 0U) return BTB_VFS_BAD_STATE;
    BtbVfsDescriptionRecord *const description = &vfs->descriptions[descriptionIndex];
    *description = (BtbVfsDescriptionRecord){.occupied = 1, .mountIndex = mountIndex,
                .node = node, .position = 0U, .references = 1U};
    BtbVfsDescriptorRecord *const descriptor = &vfs->descriptors[descriptorIndex];
    descriptor->occupied = 1;
    descriptor->client = client;
    descriptor->descriptionIndex = descriptionIndex;
    descriptor->rights = rights;
    *outHandle = BtbVfsToken(descriptorIndex, descriptor->generation);
    return BTB_VFS_OK;
}

BtbVfsStatus BtbVfsDuplicate(BtbVfs *vfs, uint64_t client,
                             BtbVfsHandle existing, unsigned narrowedRights,
                             BtbVfsHandle *outHandle)
{
    if (outHandle == NULL || !BtbVfsValidRights(narrowedRights))
        return BTB_VFS_INVALID_ARGUMENT;
    BtbVfsDescriptorRecord *source = NULL;
    const BtbVfsStatus status = BtbVfsFind(vfs, client, existing, &source);
    if (status != BTB_VFS_OK) return status;
    if ((narrowedRights & source->rights) != narrowedRights)
        return BTB_VFS_DENIED;
    const size_t index = BtbVfsFreeDescriptor(vfs);
    if (index == BTB_VFS_MAX_DESCRIPTORS) return BTB_VFS_NO_SPACE;
    BtbVfsDescriptionRecord *const description = &vfs->descriptions[source->descriptionIndex];
    if (description->references >= BTB_VFS_MAX_DESCRIPTORS) return BTB_VFS_BAD_STATE;
    ++description->references;
    BtbVfsDescriptorRecord *const result = &vfs->descriptors[index];
    result->occupied = 1;
    result->client = client;
    result->descriptionIndex = source->descriptionIndex;
    result->rights = narrowedRights;
    *outHandle = BtbVfsToken(index, result->generation);
    return BTB_VFS_OK;
}

BtbVfsStatus BtbVfsRead(BtbVfs *vfs, uint64_t client, BtbVfsHandle handle,
                        void *destination, size_t capacity, size_t *outRead)
{
    if (outRead == NULL || (capacity != 0U && destination == NULL))
        return BTB_VFS_INVALID_ARGUMENT;
    BtbVfsDescriptorRecord *descriptor = NULL;
    BtbVfsStatus status = BtbVfsFind(vfs, client, handle, &descriptor);
    if (status != BTB_VFS_OK) return status;
    if ((descriptor->rights & BTB_VFS_READ) == 0U) return BTB_VFS_DENIED;
    BtbVfsDescriptionRecord *description = &vfs->descriptions[descriptor->descriptionIndex];
    BtbVfsMountRecord *mount = &vfs->mounts[description->mountIndex];
    size_t readCount = 0U;
    status = mount->operations.read(mount->context, description->node,
                                    description->position, destination, capacity, &readCount);
    if (status != BTB_VFS_OK) return status;
    if (readCount > capacity || readCount > SIZE_MAX - description->position)
        return BTB_VFS_BAD_STATE;
    description->position += readCount;
    *outRead = readCount;
    return BTB_VFS_OK;
}

BtbVfsStatus BtbVfsWrite(BtbVfs *vfs, uint64_t client, BtbVfsHandle handle,
                         const void *source, size_t bytes, size_t *outWritten)
{
    if (outWritten == NULL || (bytes != 0U && source == NULL))
        return BTB_VFS_INVALID_ARGUMENT;
    BtbVfsDescriptorRecord *descriptor = NULL;
    BtbVfsStatus status = BtbVfsFind(vfs, client, handle, &descriptor);
    if (status != BTB_VFS_OK) return status;
    if ((descriptor->rights & BTB_VFS_WRITE) == 0U) return BTB_VFS_DENIED;
    BtbVfsDescriptionRecord *description = &vfs->descriptions[descriptor->descriptionIndex];
    BtbVfsMountRecord *mount = &vfs->mounts[description->mountIndex];
    if (mount->operations.write == NULL) return BTB_VFS_READ_ONLY;
    size_t written = 0U;
    status = mount->operations.write(mount->context, description->node,
                                     description->position, source, bytes, &written);
    if (status != BTB_VFS_OK) return status;
    if (written > bytes || written > SIZE_MAX - description->position)
        return BTB_VFS_BAD_STATE;
    description->position += written;
    *outWritten = written;
    return BTB_VFS_OK;
}

BtbVfsStatus BtbVfsClose(BtbVfs *vfs, uint64_t client, BtbVfsHandle handle)
{
    BtbVfsDescriptorRecord *descriptor = NULL;
    BtbVfsStatus status = BtbVfsFind(vfs, client, handle, &descriptor);
    if (status != BTB_VFS_OK) return status;
    BtbVfsDescriptionRecord *description = &vfs->descriptions[descriptor->descriptionIndex];
    if (description->references == 0U || description->mountIndex >= BTB_VFS_MAX_MOUNTS)
        return BTB_VFS_BAD_STATE;
    if (description->references == 1U) {
        BtbVfsMountRecord *mount = &vfs->mounts[description->mountIndex];
        if (!mount->occupied) return BTB_VFS_BAD_STATE;
        /* Never invalidate the last descriptor when the provider still owns
         * the opened node. The same Close can be retried later. */
        status = mount->operations.release(mount->context, description->node);
        if (status != BTB_VFS_OK) return status;
        *description = (BtbVfsDescriptionRecord){0};
    } else {
        --description->references;
    }
    descriptor->occupied = 0;
    descriptor->client = 0U;
    descriptor->rights = 0U;
    descriptor->descriptionIndex = 0U;
    if (descriptor->generation == UINT32_MAX) descriptor->retired = 1;
    else ++descriptor->generation;
    return BTB_VFS_OK;
}

BtbVfsStatus BtbVfsUnlink(BtbVfs *vfs, uint64_t client, const char *path)
{
    if (!BtbVfsLive(vfs)) return BTB_VFS_NOT_INITIALISED;
    if (client == 0U) return BTB_VFS_INVALID_ARGUMENT;
    size_t index = 0U;
    const char *name = NULL;
    BtbVfsStatus status = BtbVfsRoute(vfs, path, &index, &name);
    if (status != BTB_VFS_OK) return status;
    BtbVfsMountRecord *mount = &vfs->mounts[index];
    if (mount->namespaceOwner != client) return BTB_VFS_DENIED;
    if (mount->operations.unlink == NULL) return BTB_VFS_READ_ONLY;
    return mount->operations.unlink(mount->context, name);
}

BtbVfsStatus BtbVfsUnmount(BtbVfs *vfs, uint64_t client, const char *prefix)
{
    if (!BtbVfsLive(vfs)) return BTB_VFS_NOT_INITIALISED;
    if (client == 0U || !BtbVfsPrefixValid(prefix)) return BTB_VFS_INVALID_ARGUMENT;
    for (size_t i = 0U; i < BTB_VFS_MAX_MOUNTS; ++i) {
        BtbVfsMountRecord *mount = &vfs->mounts[i];
        if (!mount->occupied || strcmp(mount->prefix, prefix) != 0) continue;
        if (mount->namespaceOwner != client) return BTB_VFS_DENIED;
        for (size_t j = 0U; j < BTB_VFS_MAX_DESCRIPTIONS; ++j)
            if (vfs->descriptions[j].occupied &&
                vfs->descriptions[j].mountIndex == i)
                return BTB_VFS_BUSY;
        *mount = (BtbVfsMountRecord){0};
        return BTB_VFS_OK;
    }
    return BTB_VFS_NOT_FOUND;
}

const char *BtbVfsStatusText(BtbVfsStatus status)
{
    switch (status) {
        case BTB_VFS_OK: return "OK";
        case BTB_VFS_INVALID_ARGUMENT: return "INVALID_ARGUMENT";
        case BTB_VFS_INVALID_PATH: return "INVALID_PATH";
        case BTB_VFS_NOT_INITIALISED: return "NOT_INITIALISED";
        case BTB_VFS_NOT_FOUND: return "NOT_FOUND";
        case BTB_VFS_ALREADY_EXISTS: return "ALREADY_EXISTS";
        case BTB_VFS_DENIED: return "DENIED";
        case BTB_VFS_READ_ONLY: return "READ_ONLY";
        case BTB_VFS_NO_SPACE: return "NO_SPACE";
        case BTB_VFS_BAD_HANDLE: return "BAD_HANDLE";
        case BTB_VFS_BUSY: return "BUSY";
        case BTB_VFS_BAD_STATE: return "BAD_STATE";
        default: return "UNKNOWN";
    }
}
