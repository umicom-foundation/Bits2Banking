/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/prediction-metrics/main.c
 *
 * PURPOSE:
 *   Explain selected-token counts and unequal-batch aggregation through the canonical Framework scorer.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/prediction_metrics.h"
#include <stdio.h>

int main(void)
{
    /* Four invented score rows keep the arithmetic visible. They are not
     * predictions from a trained model and do not establish model quality. */
    const float logits[16]={4,3,2,1, 3,4,2,1, 2,3,4,1, 1,2,3,4};
    const size_t targets[4]={0U,0U,0U,0U};
    const uint8_t answerOnly[4]={1U,1U,1U,0U};
    const uint8_t none[4]={0U,0U,0U,0U};
    UmiAiTrainingPredictionCounts whole,first,tail,selected,empty;
    if (UmiAiTrainingPredictionScore(logits,4U,4U,targets,NULL,0U,2U,&whole)!=UMI_STATUS_OK ||
        UmiAiTrainingPredictionScore(logits,1U,4U,targets,NULL,0U,2U,&first)!=UMI_STATUS_OK ||
        UmiAiTrainingPredictionScore(logits+4,3U,4U,targets+1,NULL,0U,2U,&tail)!=UMI_STATUS_OK ||
        UmiAiTrainingPredictionScore(logits,4U,4U,targets,answerOnly,4U,2U,&selected)!=UMI_STATUS_OK ||
        UmiAiTrainingPredictionScore(logits,4U,4U,targets,none,4U,2U,&empty)!=UMI_STATUS_OK)
        return 1;
    if (whole.selectedRows!=4U || whole.topOneCorrect!=1U || whole.topKCorrect!=2U ||
        first.selectedRows!=1U || first.topOneCorrect!=1U || tail.selectedRows!=3U ||
        tail.topOneCorrect!=0U || first.topOneCorrect+tail.topOneCorrect!=whole.topOneCorrect ||
        first.selectedRows+tail.selectedRows!=whole.selectedRows ||
        selected.selectedRows!=3U || selected.topOneCorrect!=1U || selected.topKCorrect!=2U ||
        empty.selectedRows!=0U || empty.topOneCorrect!=0U || empty.topKCorrect!=0U)
        return 2;
    printf("all rows: top-one=%zu/%zu top-two=%zu/%zu\n",
        whole.topOneCorrect,whole.selectedRows,whole.topKCorrect,whole.selectedRows);
    printf("unequal batches: %zu/%zu and %zu/%zu; combined %zu/%zu\n",
        first.topOneCorrect,first.selectedRows,tail.topOneCorrect,tail.selectedRows,
        first.topOneCorrect+tail.topOneCorrect,first.selectedRows+tail.selectedRows);
    printf("selected answers: top-one=%zu/%zu top-two=%zu/%zu\n",
        selected.topOneCorrect,selected.selectedRows,selected.topKCorrect,selected.selectedRows);
    if (empty.selectedRows==0U) puts("no selected rows: accuracy unavailable");
    return 0;
}
