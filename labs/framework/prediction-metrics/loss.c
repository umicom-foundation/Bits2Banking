/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/prediction-metrics/loss.c
 *
 * PURPOSE:
 *   Aggregate unequal evaluation batches from shared native log-loss sums without creating a training graph.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/ai/training/prediction_metrics.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
int main(void)
{
    /* Four invented two-token score rows: three uniform, one confidently
     * favoring the wrong target. No model is loaded or evaluated by this lab. */
    const float logits[8]={0,0,0,0,0,0,0,4};const size_t targets[4]={0,0,0,0};
    const uint8_t none[4]={0,0,0,0};
    UmiAiTrainingPredictionLossSummary all,first,last,empty;
    if(UmiAiTrainingPredictionLoss(logits,4,2,targets,NULL,0,&all)!=UMI_STATUS_OK ||
        UmiAiTrainingPredictionLoss(logits,3,2,targets,NULL,0,&first)!=UMI_STATUS_OK ||
        UmiAiTrainingPredictionLoss(logits+6,1,2,targets+3,NULL,0,&last)!=UMI_STATUS_OK ||
        UmiAiTrainingPredictionLoss(logits,4,2,targets,none,4,&empty)!=UMI_STATUS_OK)return 1;
    if(all.selectedRows!=4 || first.selectedRows!=3 || last.selectedRows!=1 || empty.selectedRows!=0)return 2;
    const double combinedSum=first.negativeLogLikelihoodSum+last.negativeLogLikelihoodSum;
    const size_t combinedCount=first.selectedRows+last.selectedRows;
    const double mean=combinedSum/(double)combinedCount;
    const double wrong=(first.negativeLogLikelihoodSum/(double)first.selectedRows+
        last.negativeLogLikelihoodSum/(double)last.selectedRows)/2.0;
    if(fabs(combinedSum-all.negativeLogLikelihoodSum)>1e-12 || fabs(mean-wrong)<0.5)return 3;
    if(printf("Evaluated tokens: %zu\n",combinedCount)<0 ||
        printf("Sum then divide: %.6f nats per token\n",mean)<0 ||
        printf("Mean of batch means (wrong here): %.6f\n",wrong)<0)return 4;
    /* A finite log-loss does not imply that exp(loss) is representable. This
     * fixture is modest; a production reporter must keep the overflow branch. */
    if(mean<=log(DBL_MAX)) {
        const double perplexity=exp(mean);
        if(isfinite(perplexity)) { if(printf("Fixture perplexity: %.6f\n",perplexity)<0)return 5; }
        else if(puts("Perplexity exceeds finite double range.")<0)return 5;
    } else if(puts("Perplexity exceeds finite double range.")<0)return 5;
    if(empty.selectedRows==0 && puts("No selected tokens: mean and perplexity are unavailable.")<0)return 6;
    if(puts("Invented logits only; no training graph, model or weight update.")<0)return 7;
    return 0;
}
