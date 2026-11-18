/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/denoising-objective/trajectory.c
 *
 * PURPOSE:
 *   Trace a deterministic four-value denoising trajectory and measure error from a deliberately biased predictor.
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
#include <string.h>

static int Follow(const float *initial, const float *prediction,
    const float *clean, const char *label, double *outError)
{
    const float alpha[4]={0.0625F,0.25F,0.5625F,1.0F};
    float state[4],next[4];
    memcpy(state,initial,sizeof state);
    printf("%s\n",label);
    for(size_t step=1U;step<4U;++step) {
        /* A real network must predict from the current state and timestep.
         * This arithmetic fixture deliberately holds a known array constant. */
        UmiStatus status=UmiAiDenoisingDeterministicStep(state,prediction,4U,
            alpha[step-1U],alpha[step],next,4U);
        if(status!=UMI_STATUS_OK)return 1;
        printf("alpha %.4f -> [%.6f, %.6f, %.6f, %.6f]\n",
            alpha[step],next[0],next[1],next[2],next[3]);
        memcpy(state,next,sizeof state);
    }
    double error=0.0;
    for(size_t i=0U;i<4U;++i) {
        double difference=(double)state[i]-(double)clean[i];
        error+=difference*difference/4.0;
    }
    if(!isfinite(error))return 1;
    printf("final mean squared error %.8f\n",error);
    *outError=error;
    return 0;
}
int main(void)
{
    const float clean[4]={-0.5F,0,0.5F,1};
    const float epsilon[4]={0.2F,-0.4F,0.1F,0.8F};
    float initial[4],biased[4];
    for(size_t i=0U;i<4U;++i)biased[i]=epsilon[i]+0.05F;
    if(UmiAiDenoisingMix(clean,epsilon,4U,0.0625F,initial,4U)!=UMI_STATUS_OK)
        return 1;
    double oracleError=0.0,biasedError=0.0;
    if(Follow(initial,epsilon,clean,"Known exact noise (not a learned model)",&oracleError) ||
       Follow(initial,biased,clean,"Same noise plus a deliberate 0.05 bias",&biasedError))
        return 1;
    /* Starting at alpha=1/16 amplifies constant epsilon bias by sqrt(15).
     * Squared final error is 15 * .05^2 = .0375 for this constructed path. */
    if(oracleError>1e-10 || fabs(biasedError-0.0375)>1e-6) {
        fputs("Unexpected deterministic trajectory result.\n",stderr);
        return 1;
    }
    puts("A correct numerical step does not repair an inaccurate predictor.");
    return 0;
}
