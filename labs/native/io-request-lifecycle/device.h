/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/io-request-lifecycle/device.h
 * PURPOSE: Model an I/O service with terminal completions and explicit quiesce.
 *---------------------------------------------------------------------------*/
#ifndef BTB_IO_REQUEST_LIFECYCLE_H
#define BTB_IO_REQUEST_LIFECYCLE_H
#include "queue.h"
#include <stdint.h>
#include <stddef.h>
#define BTB_DEVICE_MAX_REQUESTS 8U
#define BTB_DEVICE_MAX_TRANSFER 4096U
typedef enum BtbDeviceStatus {
    BTB_DEVICE_OK = 0,
    BTB_DEVICE_INVALID,
    BTB_DEVICE_NOT_FOUND,
    BTB_DEVICE_CAPACITY,
    BTB_DEVICE_BUSY,
    BTB_DEVICE_STOPPED
} BtbDeviceStatus;
typedef struct BtbRequest {
    uint32_t identity;
    uint32_t bytesRequested;
    int pending;
    int completed;
    int cancelRequested;
} BtbRequest;
typedef struct BtbDevice {
    uint32_t owner;
    uint32_t nextRequest;
    int live;
    int accepting;
    BtbRequest requests[BTB_DEVICE_MAX_REQUESTS];
    BtbCompletionQueue completions;
} BtbDevice;
/* Single-threaded classroom state machine. Owner is a simulation identifier,
 * not a security token. No actual device or Kernel interface is used. */
BtbDeviceStatus BtbDeviceInit(BtbDevice *device, uint32_t owner);
BtbDeviceStatus BtbDeviceSubmit(BtbDevice *device, uint32_t owner,
                                uint32_t bytes, uint32_t *outId);
/* Cancellation records a request, NOT a terminal outcome. */
BtbDeviceStatus BtbDeviceRequestCancel(BtbDevice *device, uint32_t owner, uint32_t id);
/* Completion copies a result into the common bounded FIFO. A full completion
 * queue refuses the terminal transition, leaving this request pending. */
BtbDeviceStatus BtbDeviceComplete(BtbDevice *device, uint32_t owner, uint32_t id,
                                   BtbCompletionResult result, uint32_t transferred);
BtbDeviceStatus BtbDeviceCollect(BtbDevice *device, BtbCompletion *out);
BtbDeviceStatus BtbDeviceQuiesce(BtbDevice *device, uint32_t owner);
BtbDeviceStatus BtbDeviceResume(BtbDevice *device, uint32_t owner);
BtbDeviceStatus BtbDeviceRelease(BtbDevice *device, uint32_t owner);
size_t BtbDeviceOutstanding(const BtbDevice *device);
#endif
