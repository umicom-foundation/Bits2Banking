/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/process-file-services/process_files.c
 * PURPOSE: Checked user-byte copy, identity binding and terminal file cleanup.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "process_files.h"
#include <string.h>

static int BtbProcessLive(const BtbProcessFiles *owner)
{
    return owner != NULL && owner->self == owner && !owner->ended &&
           owner->vfs != NULL && owner->identity != 0U;
}
static int BtbProcessSpan(size_t offset, size_t bytes)
{
    /* Subtract first. Checking offset + bytes could overflow size_t. */
    return offset <= BTB_PROCESS_USER_BYTES &&
           bytes <= BTB_PROCESS_USER_BYTES - offset;
}
static size_t BtbProcessFreeSlot(const BtbProcessFiles *owner)
{
    for (size_t i = 0U; i < BTB_PROCESS_MAX_OPEN; ++i)
        if (owner->owned[i] == 0U) return i;
    return BTB_PROCESS_MAX_OPEN;
}
static size_t BtbProcessFindSlot(const BtbProcessFiles *owner, BtbVfsHandle handle)
{
    for (size_t i = 0U; i < BTB_PROCESS_MAX_OPEN; ++i)
        if (handle != 0U && owner->owned[i] == handle) return i;
    return BTB_PROCESS_MAX_OPEN;
}

BtbVfsStatus BtbProcessFilesInitialise(BtbProcessFiles *owner, BtbVfs *vfs,
                                      uint64_t trustedIdentity)
{
    if (owner == NULL || vfs == NULL || trustedIdentity == 0U)
        return BTB_VFS_INVALID_ARGUMENT;
    if (owner->self != NULL || vfs->self != vfs)
        return BTB_VFS_BAD_STATE;
    /* trustedIdentity is chosen by the harness. A real kernel derives it from
     * the running task, rather than an unchecked syscall argument. */
    owner->vfs = vfs;
    owner->identity = trustedIdentity;
    owner->self = owner;
    return BTB_VFS_OK;
}
BtbVfsStatus BtbProcessFilesPut(BtbProcessFiles *owner, size_t offset,
                                const void *source, size_t bytes)
{
    if (!BtbProcessLive(owner)) return BTB_VFS_BAD_STATE;
    if (!BtbProcessSpan(offset, bytes) || (bytes != 0U && source == NULL))
        return BTB_VFS_INVALID_ARGUMENT;
    if (bytes != 0U) (void)memmove(owner->userBytes + offset, source, bytes);
    return BTB_VFS_OK;
}
BtbVfsStatus BtbProcessFilesGet(const BtbProcessFiles *owner, size_t offset,
                                void *destination, size_t bytes)
{
    if (!BtbProcessLive(owner)) return BTB_VFS_BAD_STATE;
    if (!BtbProcessSpan(offset, bytes) || (bytes != 0U && destination == NULL))
        return BTB_VFS_INVALID_ARGUMENT;
    if (bytes != 0U) (void)memmove(destination, owner->userBytes + offset, bytes);
    return BTB_VFS_OK;
}

BtbVfsStatus BtbProcessFilesCall(BtbProcessFiles *owner,
                                 const BtbProcessFileRequest *request,
                                 BtbProcessFileReply *outReply)
{
    if (!BtbProcessLive(owner)) return BTB_VFS_BAD_STATE;
    if (request == NULL || outReply == NULL) return BTB_VFS_INVALID_ARGUMENT;
    BtbProcessFileReply candidate = {0};
    BtbVfsStatus status = BTB_VFS_INVALID_ARGUMENT;
    if (request->operation == BTB_PROCESS_FILE_OPEN) {
        const size_t slot = BtbProcessFreeSlot(owner);
        if (slot == BTB_PROCESS_MAX_OPEN) return BTB_VFS_NO_SPACE;
        if (request->length == 0U || request->length >= BTB_VFS_PATH_CAPACITY ||
            !BtbProcessSpan(request->offset, request->length))
            return BTB_VFS_INVALID_PATH;
        char path[BTB_VFS_PATH_CAPACITY];
        /* A path is a length-delimited user byte span; an embedded terminator
         * is never allowed to conceal a malicious trailing suffix. */
        if (memchr(owner->userBytes + request->offset, '\0', request->length))
            return BTB_VFS_INVALID_PATH;
        (void)memcpy(path, owner->userBytes + request->offset, request->length);
        path[request->length] = '\0';
        status = BtbVfsOpen(owner->vfs, owner->identity, path,
                            request->rights, &candidate.descriptor);
        if (status != BTB_VFS_OK) return status;
        owner->owned[slot] = candidate.descriptor;
    } else if (request->operation == BTB_PROCESS_FILE_CLOSE) {
        const size_t slot = BtbProcessFindSlot(owner, request->descriptor);
        if (slot == BTB_PROCESS_MAX_OPEN) return BTB_VFS_BAD_HANDLE;
        status = BtbVfsClose(owner->vfs, owner->identity, request->descriptor);
        if (status != BTB_VFS_OK) return status;
        owner->owned[slot] = 0U;
    } else if (request->operation == BTB_PROCESS_FILE_READ ||
               request->operation == BTB_PROCESS_FILE_WRITE) {
        if (BtbProcessFindSlot(owner, request->descriptor) == BTB_PROCESS_MAX_OPEN)
            return BTB_VFS_BAD_HANDLE;
        if (request->length > BTB_PROCESS_MAX_TRANSFER ||
            !BtbProcessSpan(request->offset, request->length))
            return BTB_VFS_INVALID_ARGUMENT;
        /* Always transfer through short, owned staging storage. In the real
         * Kernel, virtual pages and rights are checked across the entire span
         * before copying and must remain stable until publication. */
        unsigned char staged[BTB_PROCESS_MAX_TRANSFER] = {0};
        if (request->operation == BTB_PROCESS_FILE_WRITE) {
            if (request->length != 0U)
                (void)memcpy(staged, owner->userBytes + request->offset, request->length);
            status = BtbVfsWrite(owner->vfs, owner->identity, request->descriptor,
                                 staged, request->length, &candidate.bytesTransferred);
        } else {
            status = BtbVfsRead(owner->vfs, owner->identity, request->descriptor,
                                staged, request->length, &candidate.bytesTransferred);
            if (status == BTB_VFS_OK && candidate.bytesTransferred <= request->length &&
                candidate.bytesTransferred != 0U)
                (void)memcpy(owner->userBytes + request->offset, staged,
                             candidate.bytesTransferred);
        }
        if (status != BTB_VFS_OK) return status;
        if (candidate.bytesTransferred > request->length) return BTB_VFS_BAD_STATE;
    } else {
        return BTB_VFS_INVALID_ARGUMENT;
    }
    /* Only accepted requests publish the completed reply. */
    *outReply = candidate;
    return BTB_VFS_OK;
}

BtbVfsStatus BtbProcessFilesShutdown(BtbProcessFiles *owner)
{
    if (!BtbProcessLive(owner)) return BTB_VFS_BAD_STATE;
    for (size_t i = 0U; i < BTB_PROCESS_MAX_OPEN; ++i) {
        if (owner->owned[i] == 0U) continue;
        const BtbVfsStatus status =
            BtbVfsClose(owner->vfs, owner->identity, owner->owned[i]);
        if (status != BTB_VFS_OK) return status;
        owner->owned[i] = 0U;
    }
    /* A terminated owner cannot reopen files or lend stale copied memory. */
    (void)memset(owner->userBytes, 0, sizeof(owner->userBytes));
    owner->ended = 1;
    return BTB_VFS_OK;
}
