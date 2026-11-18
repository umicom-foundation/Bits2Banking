/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/prediction-metrics/aggregate.c
 *
 * PURPOSE:
 *   Stream checked token-loss summaries through shared Framework reporting without retaining batch tensors.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/prediction_metrics.h"
#include <math.h>
#include <stdio.h>

int main(void)
{
    /* Four invented two-token rows. Real callers may release each borrowed
     * batch after scoring it; the total retains only two counts and a sum. */
    const float logits[8]={0,0,0,0,0,0,0,4};
    const size_t targets[4]={0,0,0,0};
    UmiAiTrainingPredictionLossSummary total={0}, batch;
    for(size_t row=0U;row<4U;++row){
        if(UmiAiTrainingPredictionLoss(logits+2U*row,1U,2U,targets+row,NULL,0U,&batch)!=UMI_STATUS_OK)
            return 1;
        if(UmiAiTrainingPredictionLossMerge(&total,&batch,&total)!=UMI_STATUS_OK)
            return 2;
    }
    double mean=-1.0, perplexity=-1.0;
    if(UmiAiTrainingPredictionLossMean(&total,&mean)!=UMI_STATUS_OK ||
        UmiAiTrainingPredictionLossPerplexity(&total,&perplexity)!=UMI_STATUS_OK)
        return 3;
    const double expected=(3.0*log(2.0)+log(1.0+exp(4.0)))/4.0;
    if(total.rows!=4U || total.selectedRows!=4U || fabs(mean-expected)>1e-12)return 4;
    if(printf("Selected tokens: %zu\nMean: %.6f nats\nPerplexity: %.6f\n",
        total.selectedRows,mean,perplexity)<0)return 5;

    const UmiAiTrainingPredictionLossSummary empty={6U,0U,0.0};
    double untouched=77.0;
    if(UmiAiTrainingPredictionLossMean(&empty,&untouched)!=UMI_STATUS_UNAVAILABLE ||
        untouched!=77.0)return 6;
    if(puts("Zero selected tokens: unavailable; previous result unchanged.")<0)return 7;
    const UmiAiTrainingPredictionLossSummary large={1U,1U,1000.0};
    if(UmiAiTrainingPredictionLossMean(&large,&mean)!=UMI_STATUS_OK || mean!=1000.0 ||
        UmiAiTrainingPredictionLossPerplexity(&large,&untouched)!=UMI_STATUS_CAPACITY_EXCEEDED ||
        untouched!=77.0)return 8;
    if(puts("Mean 1000 nats remains reportable; its exponential exceeds range.")<0)return 9;
    if(puts("Invented scores only; no model, training, download or retained tensor.")<0)return 10;
    return 0;
}
