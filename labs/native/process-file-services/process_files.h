/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/process-file-services/process_files.h
 * PURPOSE: Classroom process-file service with owned bytes, checked offsets,
 *          copied requests and VFS-owned file descriptions.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_PROCESS_FILES_H
#define BTB_PROCESS_FILES_H
#include "vfs.h"
#include <stddef.h>
#include <stdint.h>

#define BTB_PROCESS_USER_BYTES 512U
#define BTB_PROCESS_MAX_OPEN 8U
#define BTB_PROCESS_MAX_TRANSFER 64U

typedef enum BtbProcessFileOperation {
    BTB_PROCESS_FILE_OPEN = 1,
    BTB_PROCESS_FILE_READ = 2,
    BTB_PROCESS_FILE_WRITE = 3,
    BTB_PROCESS_FILE_CLOSE = 4
} BtbProcessFileOperation;

/* All offsets refer to the classroom process's byte array. They are not host
 * pointers. Never accept a client identity from this request structure. */
typedef struct BtbProcessFileRequest {
    BtbProcessFileOperation operation;
    BtbVfsHandle descriptor;
    unsigned rights;
    size_t offset;
    size_t length;
} BtbProcessFileRequest;

typedef struct BtbProcessFileReply {
    BtbVfsHandle descriptor;
    size_t bytesTransferred;
} BtbProcessFileReply;

/* Caller supplies zero-filled storage at a stable address. VFS and providers
 * outlive this owner; one synchronous caller serialises every operation. */
typedef struct BtbProcessFiles {
    const struct BtbProcessFiles *self;
    BtbVfs *vfs;
    uint64_t identity;
    int ended;
    unsigned char userBytes[BTB_PROCESS_USER_BYTES];
    BtbVfsHandle owned[BTB_PROCESS_MAX_OPEN];
} BtbProcessFiles;

BtbVfsStatus BtbProcessFilesInitialise(BtbProcessFiles *owner, BtbVfs *vfs,
                                      uint64_t trustedIdentity);
/* A fixture/user-memory staging operation. No real machine process or memory
 * mapping is accessed. Both operations preserve output on refusal. */
BtbVfsStatus BtbProcessFilesPut(BtbProcessFiles *owner, size_t offset,
                                const void *source, size_t bytes);
BtbVfsStatus BtbProcessFilesGet(const BtbProcessFiles *owner, size_t offset,
                                void *destination, size_t bytes);
/* A failed call never publishes a partial reply; refused reads do not publish
 * any bytes to the process buffer. OPEN requires an unterminated path byte span;
 * READ/WRITE copy up to 64 bytes. */
BtbVfsStatus BtbProcessFilesCall(BtbProcessFiles *owner,
                                 const BtbProcessFileRequest *request,
                                 BtbProcessFileReply *outReply);
/* Close all owned descriptors. On provider refusal retain the owner and the
 * not-yet-closed handles so the trusted caller can retry; no silent leak. */
BtbVfsStatus BtbProcessFilesShutdown(BtbProcessFiles *owner);

#endif
