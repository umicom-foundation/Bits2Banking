/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/denoising-objective/velocity.c
 *
 * PURPOSE:
 *   Demonstrate why diffusion prediction conventions must be converted explicitly.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/denoising.h"
#include <math.h>
#include <stdio.h>
#define CHECK(call) do { UmiStatus status=(call); if(status!=UMI_STATUS_OK) { \
    fprintf(stderr,"%s refused: %d\n",#call,(int)status); return 1; } } while(0)
int main(void)
{
    enum { COUNT=3 };
    const float clean[COUNT]={.2F,-.8F,1.2F},epsilon[COUNT]={1,-.5F,.25F};
    const float points[3]={0,.25F,1};
    puts("Umicom diffusion prediction convention exercise (no model loaded)");
    puts("alphaBar  maximum clean error  maximum epsilon error");
    for(size_t point=0U;point<3U;++point) {
        float alpha=points[point],noisy[COUNT],velocity[COUNT];
        float estimatedClean[COUNT],estimatedNoise[COUNT];
        double signal=sqrt((double)alpha),noise=sqrt(1.0-(double)alpha);
        CHECK(UmiAiDenoisingMix(clean,epsilon,COUNT,alpha,noisy,COUNT));
        /* We know clean and epsilon only because this is a synthetic fixture.
         * A trained model would predict velocity from noisy input, timestep
         * and conditioning; the conversion below does not train that model. */
        for(size_t i=0U;i<COUNT;++i)
            velocity[i]=(float)(signal*epsilon[i]-noise*clean[i]);
        CHECK(UmiAiDenoisingVelocityToClean(noisy,velocity,COUNT,alpha,estimatedClean,COUNT));
        CHECK(UmiAiDenoisingVelocityToNoise(noisy,velocity,COUNT,alpha,estimatedNoise,COUNT));
        float cleanError=0,noiseError=0;
        for(size_t i=0U;i<COUNT;++i) {
            cleanError=fmaxf(cleanError,fabsf(estimatedClean[i]-clean[i]));
            noiseError=fmaxf(noiseError,fabsf(estimatedNoise[i]-epsilon[i]));
        }
        printf("%8.2f  %19.8f  %21.8f\n",(double)alpha,(double)cleanError,(double)noiseError);
        if(cleanError>2e-6F || noiseError>2e-6F)return 1;
        if(alpha==.25F) {
            float wrongClean[COUNT],wrongError=0;
            /* Intentional misuse for comparison: every float is finite, but
             * the array has the wrong meaning for epsilon reconstruction. */
            CHECK(UmiAiDenoisingRecover(noisy,velocity,COUNT,alpha,wrongClean,COUNT));
            for(size_t i=0U;i<COUNT;++i)
                wrongError=fmaxf(wrongError,fabsf(wrongClean[i]-clean[i]));
            printf("Treating velocity as epsilon gives maximum error %.6f\n",(double)wrongError);
            if(wrongError<1.0F)return 1;
        }
    }
    puts("The conversion fixes a convention mismatch; it does not improve an inaccurate predictor.");
    return 0;
}
