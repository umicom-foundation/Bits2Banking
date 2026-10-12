/* Bits2Banking | Umicom Foundation | Sammy Hegab | MIT */
#include "device.h"
#include <stdio.h>
int main(void)
{
    BtbDevice device={0}; uint32_t request=0U;
    if(BtbDeviceInit(&device,1U)!=BTB_DEVICE_OK ||
       BtbDeviceSubmit(&device,1U,256U,&request)!=BTB_DEVICE_OK ||
       BtbDeviceComplete(&device,1U,request,BTB_COMPLETION_SUCCESS,256U)!=BTB_DEVICE_OK)
        return 1;
    BtbCompletion result={0};
    if(BtbDeviceCollect(&device,&result)!=BTB_DEVICE_OK)return 1;
    printf("I/O request %u completed: %u of 256 bytes.\n",
        (unsigned)result.requestId,(unsigned)result.bytesTransferred);
    return BtbDeviceQuiesce(&device,1U)==BTB_DEVICE_OK &&
           BtbDeviceRelease(&device,1U)==BTB_DEVICE_OK ? 0 : 1;
}
