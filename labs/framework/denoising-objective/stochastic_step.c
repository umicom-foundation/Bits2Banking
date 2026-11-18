/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/denoising-objective/stochastic_step.c
 *
 * PURPOSE:
 *   Compare a single stochastic denoising transition with deterministic replay and explicit noise ownership.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/denoising.h"
#include "umicom/ai/training/initialisation.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
static void Show(const char *label,const float values[4])
{
    printf("%s: [%.6f, %.6f, %.6f, %.6f]\n",label,values[0],values[1],values[2],values[3]);
}
int main(void)
{
    const float clean[4]={-.5F,0,.5F,1},prediction[4]={.2F,-.4F,.1F,.8F};
    float noisy[4],noise[4],replayedNoise[4],advancedNoise[4];
    float sampled[4],replayed[4],deterministic[4],other[4];
    UmiAiTrainingRandomState random;
    if(UmiAiDenoisingMix(clean,prediction,4,.25F,noisy,4)!=UMI_STATUS_OK ||
       UmiAiTrainingRandomSeed(&random,42U)!=UMI_STATUS_OK ||
       UmiAiTrainingRandomFillNormal(&random,0,1,noise,4)!=UMI_STATUS_OK ||
       UmiAiTrainingRandomFillNormal(&random,0,1,advancedNoise,4)!=UMI_STATUS_OK ||
       UmiAiTrainingRandomSeed(&random,42U)!=UMI_STATUS_OK ||
       UmiAiTrainingRandomFillNormal(&random,0,1,replayedNoise,4)!=UMI_STATUS_OK)return 1;
    if(memcmp(noise,replayedNoise,sizeof noise))return 1;
    if(UmiAiDenoisingStochasticStep(noisy,prediction,noise,4,.25F,.5F,.75F,sampled,4)!=UMI_STATUS_OK ||
       UmiAiDenoisingStochasticStep(noisy,prediction,replayedNoise,4,.25F,.5F,.75F,replayed,4)!=UMI_STATUS_OK ||
       memcmp(sampled,replayed,sizeof sampled))return 1;
    if(UmiAiDenoisingDeterministicStep(noisy,prediction,4,.25F,.5F,deterministic,4)!=UMI_STATUS_OK ||
       UmiAiDenoisingStochasticStep(noisy,prediction,advancedNoise,4,.25F,.5F,0,other,4)!=UMI_STATUS_OK ||
       memcmp(deterministic,other,sizeof other))return 1;
    Show("Current noisy values",noisy);
    Show("Fresh step noise",noise);
    Show("eta 0.75",sampled);
    Show("eta 0",deterministic);
    puts("Replay: same supplied noise and coefficients gave the same output on this build.");
    puts("A real predictor must run again on the next noisy state; this is one model-free transition.");
    /* Even unused noise is admitted: a nonfinite tail cannot hide behind eta=0. */
    advancedNoise[3]=NAN;memcpy(other,deterministic,sizeof other);
    if(UmiAiDenoisingStochasticStep(noisy,prediction,advancedNoise,4,.25F,.5F,0,other,4)!=UMI_STATUS_INVALID_ARGUMENT ||
       memcmp(other,deterministic,sizeof other))return 1;
    puts("Nonfinite noise refused without changing the previous output.");
    return 0;
}
