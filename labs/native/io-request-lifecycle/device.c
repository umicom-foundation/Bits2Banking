/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/io-request-lifecycle/device.c
 * PURPOSE: Compose the prior copied completion queue instead of duplicating it.
 *---------------------------------------------------------------------------*/
#include "device.h"
#include <string.h>
static int Ready(const BtbDevice *device, uint32_t owner)
{
    return device != NULL && device->live && owner != 0U && device->owner == owner;
}
static BtbRequest *Find(BtbDevice *device, uint32_t id)
{
    if (device == NULL || id == 0U) return NULL;
    for(size_t i=0U; i<BTB_DEVICE_MAX_REQUESTS; ++i)
        if(device->requests[i].identity == id) return &device->requests[i];
    return NULL;
}
static BtbRequest *Free(BtbDevice *device)
{
    for(size_t i=0U; i<BTB_DEVICE_MAX_REQUESTS; ++i)
        if(device->requests[i].identity == 0U) return &device->requests[i];
    return NULL;
}
BtbDeviceStatus BtbDeviceInit(BtbDevice *device, uint32_t owner)
{
    if (device == NULL || owner == 0U) return BTB_DEVICE_INVALID;
    *device = (BtbDevice){.owner=owner,.nextRequest=1U,.live=1,.accepting=1};
    return BtbCompletionQueueInit(&device->completions)==BTB_QUEUE_OK
        ? BTB_DEVICE_OK : BTB_DEVICE_INVALID;
}
BtbDeviceStatus BtbDeviceSubmit(BtbDevice *device, uint32_t owner,
                                uint32_t bytes, uint32_t *outId)
{
    if(!Ready(device,owner) || outId == NULL || bytes == 0U ||
       bytes > BTB_DEVICE_MAX_TRANSFER) return BTB_DEVICE_INVALID;
    if(!device->accepting) return BTB_DEVICE_STOPPED;
    if(device->nextRequest == 0U) return BTB_DEVICE_CAPACITY;
    BtbRequest *request = Free(device);
    if(request == NULL) return BTB_DEVICE_CAPACITY;
    const uint32_t id = device->nextRequest++;
    *request = (BtbRequest){.identity=id,.bytesRequested=bytes,.pending=1};
    *outId = id;
    return BTB_DEVICE_OK;
}
BtbDeviceStatus BtbDeviceRequestCancel(BtbDevice *device, uint32_t owner, uint32_t id)
{
    if(!Ready(device,owner)) return BTB_DEVICE_INVALID;
    BtbRequest *request=Find(device,id);
    if(request == NULL) return BTB_DEVICE_NOT_FOUND;
    if(!request->pending || request->completed || request->cancelRequested)
        return BTB_DEVICE_BUSY;
    request->cancelRequested = 1;
    return BTB_DEVICE_OK;
}
BtbDeviceStatus BtbDeviceComplete(BtbDevice *device, uint32_t owner, uint32_t id,
                                   BtbCompletionResult result, uint32_t transferred)
{
    if(!Ready(device,owner) || result > BTB_COMPLETION_CANCELLED)
        return BTB_DEVICE_INVALID;
    BtbRequest *request=Find(device,id);
    if(request == NULL) return BTB_DEVICE_NOT_FOUND;
    if(!request->pending || request->completed) return BTB_DEVICE_BUSY;
    if(transferred > request->bytesRequested ||
       (result != BTB_COMPLETION_SUCCESS && transferred != 0U) ||
       (result == BTB_COMPLETION_CANCELLED && !request->cancelRequested))
        return BTB_DEVICE_INVALID;
    BtbCompletion value={.requestId=id,.bytesTransferred=transferred,.result=result};
    const BtbQueueStatus status=BtbCompletionQueuePush(&device->completions,value);
    if(status == BTB_QUEUE_FULL) return BTB_DEVICE_CAPACITY;
    if(status != BTB_QUEUE_OK) return BTB_DEVICE_INVALID;
    request->pending = 0;
    request->completed = 1;
    return BTB_DEVICE_OK;
}
BtbDeviceStatus BtbDeviceCollect(BtbDevice *device, BtbCompletion *out)
{
    if(device == NULL || !device->live || out == NULL) return BTB_DEVICE_INVALID;
    /* Invariant: a published completion names a still-retained request.
     * If this internal invariant breaks, do not pop and lose the completion. */
    if(BtbCompletionQueueCount(&device->completions)==0U) return BTB_DEVICE_NOT_FOUND;
    const BtbCompletion first=device->completions.entries[device->completions.head];
    BtbRequest *request=Find(device,first.requestId);
    if(request == NULL || !request->completed) return BTB_DEVICE_INVALID;
    BtbCompletion copied={0};
    if(BtbCompletionQueuePop(&device->completions,&copied)!=BTB_QUEUE_OK)
        return BTB_DEVICE_INVALID;
    *request = (BtbRequest){0};
    *out = copied;
    return BTB_DEVICE_OK;
}
BtbDeviceStatus BtbDeviceQuiesce(BtbDevice *device, uint32_t owner)
{
    if(!Ready(device,owner)) return BTB_DEVICE_INVALID;
    if(!device->accepting) return BTB_DEVICE_BUSY;
    device->accepting=0;
    return BTB_DEVICE_OK;
}
BtbDeviceStatus BtbDeviceResume(BtbDevice *device, uint32_t owner)
{
    if(!Ready(device,owner)) return BTB_DEVICE_INVALID;
    if(device->accepting) return BTB_DEVICE_BUSY;
    device->accepting=1;
    return BTB_DEVICE_OK;
}
size_t BtbDeviceOutstanding(const BtbDevice *device)
{
    if(device == NULL || !device->live) return 0U;
    size_t count=0U;
    for(size_t i=0U; i<BTB_DEVICE_MAX_REQUESTS; ++i)
        if(device->requests[i].identity != 0U) ++count;
    return count;
}
BtbDeviceStatus BtbDeviceRelease(BtbDevice *device, uint32_t owner)
{
    if(!Ready(device,owner)) return BTB_DEVICE_INVALID;
    if(device->accepting || BtbDeviceOutstanding(device)!=0U ||
       BtbCompletionQueueCount(&device->completions)!=0U) return BTB_DEVICE_BUSY;
    /* Never reuse this object's old request identities after release. Its
     * owner must allocate a fresh object for a new service lifetime. */
    device->live=0;
    device->owner=0U;
    return BTB_DEVICE_OK;
}
