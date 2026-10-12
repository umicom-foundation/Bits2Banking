/* Bits2Banking | Umicom Foundation | Sammy Hegab | MIT */
#include "device.h"
#include <stdio.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr,"FAIL line %d: %s\n",__LINE__,#x);return 1; } } while(0)
static int Lifecycle(void)
{
    BtbDevice dev={0}; uint32_t first=0U,second=0U,third=0U;
    CHECK(BtbDeviceInit(&dev,41U)==BTB_DEVICE_OK);
    CHECK(BtbDeviceSubmit(&dev,41U,100U,&first)==BTB_DEVICE_OK);
    CHECK(BtbDeviceSubmit(&dev,41U,64U,&second)==BTB_DEVICE_OK);
    CHECK(BtbDeviceRequestCancel(&dev,41U,first)==BTB_DEVICE_OK);
    CHECK(BtbDeviceOutstanding(&dev)==2U);
    CHECK(BtbDeviceComplete(&dev,41U,second,BTB_COMPLETION_SUCCESS,64U)==BTB_DEVICE_OK);
    CHECK(BtbDeviceComplete(&dev,41U,first,BTB_COMPLETION_CANCELLED,0U)==BTB_DEVICE_OK);
    CHECK(BtbDeviceQuiesce(&dev,41U)==BTB_DEVICE_OK);
    CHECK(BtbDeviceSubmit(&dev,41U,3U,&third)==BTB_DEVICE_STOPPED);
    CHECK(third==0U);
    CHECK(BtbDeviceRelease(&dev,41U)==BTB_DEVICE_BUSY);
    BtbCompletion completion={0};
    CHECK(BtbDeviceCollect(&dev,&completion)==BTB_DEVICE_OK);
    CHECK(completion.requestId==second && completion.bytesTransferred==64U);
    CHECK(BtbDeviceCollect(&dev,&completion)==BTB_DEVICE_OK);
    CHECK(completion.requestId==first && completion.result==BTB_COMPLETION_CANCELLED);
    CHECK(BtbDeviceOutstanding(&dev)==0U);
    CHECK(BtbDeviceResume(&dev,41U)==BTB_DEVICE_OK);
    CHECK(BtbDeviceSubmit(&dev,41U,7U,&third)==BTB_DEVICE_OK);
    CHECK(third>second);
    CHECK(BtbDeviceRequestCancel(&dev,41U,third)==BTB_DEVICE_OK);
    /* A device can finish successfully before it honours a cancel request. */
    CHECK(BtbDeviceComplete(&dev,41U,third,BTB_COMPLETION_SUCCESS,7U)==BTB_DEVICE_OK);
    CHECK(BtbDeviceCollect(&dev,&completion)==BTB_DEVICE_OK);
    CHECK(completion.requestId==third && completion.result==BTB_COMPLETION_SUCCESS);
    CHECK(BtbDeviceQuiesce(&dev,41U)==BTB_DEVICE_OK);
    CHECK(BtbDeviceRelease(&dev,41U)==BTB_DEVICE_OK);
    CHECK(BtbDeviceSubmit(&dev,41U,1U,&third)==BTB_DEVICE_INVALID);
    return 0;
}
static int FullCompletionQueue(void)
{
    BtbDevice device={0}; uint32_t ids[5]={0};
    CHECK(BtbDeviceInit(&device,7U)==BTB_DEVICE_OK);
    for(size_t i=0U; i<5U; ++i)
        CHECK(BtbDeviceSubmit(&device,7U,10U,&ids[i])==BTB_DEVICE_OK);
    for(size_t i=0U; i<4U; ++i)
        CHECK(BtbDeviceComplete(&device,7U,ids[i],BTB_COMPLETION_SUCCESS,10U)==BTB_DEVICE_OK);
    CHECK(BtbDeviceComplete(&device,7U,ids[4],BTB_COMPLETION_SUCCESS,10U)==BTB_DEVICE_CAPACITY);
    CHECK(BtbDeviceOutstanding(&device)==5U);
    CHECK(device.requests[4].pending && !device.requests[4].completed);
    BtbCompletion completion={0};
    CHECK(BtbDeviceCollect(&device,&completion)==BTB_DEVICE_OK);
    CHECK(completion.requestId==ids[0]);
    CHECK(BtbDeviceComplete(&device,7U,ids[4],BTB_COMPLETION_SUCCESS,10U)==BTB_DEVICE_OK);
    for(size_t i=1U; i<5U; ++i) {
        CHECK(BtbDeviceCollect(&device,&completion)==BTB_DEVICE_OK);
        CHECK(completion.requestId==ids[i]);
    }
    CHECK(BtbDeviceQuiesce(&device,7U)==BTB_DEVICE_OK);
    CHECK(BtbDeviceRelease(&device,7U)==BTB_DEVICE_OK);
    return 0;
}
int main(void)
{
    CHECK(Lifecycle()==0);
    CHECK(FullCompletionQueue()==0);
    puts("I/O request lifetime, cancellation races, FIFO completion and quiesce passed.");
    return 0;
}
