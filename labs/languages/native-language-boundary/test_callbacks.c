/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/test_callbacks.c
 *
 * PURPOSE:
 *   Verify callback admission, early stopping and synchronous context ownership.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "boundary.h"
#include <stddef.h>
#include <stdio.h>
#define CHECK(c) do { if (!(c)) { fprintf(stderr,"%d: %s\n",__LINE__,#c); return 1; } } while (0)
typedef struct Observations { int32_t calls,stopAt,values[64]; } Observations;
static int32_t Collect(int32_t index,int32_t percent,void *opaque)
{
    Observations *state=opaque;
    if(state==NULL||index!=state->calls||index<0||index>=64)return 99;
    state->values[index]=percent;
    ++state->calls;
    return index==state->stopAt?17:0;
}
int main(void)
{
    int32_t done[64],total[64],accepted=-1;
    for(int32_t i=0;i<64;++i){done[i]=i;total[i]=64;}
    Observations state={.stopAt=-1};
    CHECK(bounded_progress_visit(done,total,64,Collect,&state,&accepted)==0);
    CHECK(accepted==64&&state.calls==64&&state.values[0]==0&&state.values[63]==98);
    state=(Observations){.stopAt=1};
    CHECK(bounded_progress_visit(done,total,64,Collect,&state,&accepted)==2);
    CHECK(accepted==1&&state.calls==2&&state.values[1]==1);
    /* The stopping callback was attempted and changed state; it was not
     * accepted. Consumers must distinguish those two facts. */
    state=(Observations){.stopAt=-1};total[63]=0;
    CHECK(bounded_progress_visit(done,total,64,Collect,&state,&accepted)==1);
    CHECK(accepted==0&&state.calls==0);total[63]=64;
    CHECK(bounded_progress_visit(NULL,NULL,0,NULL,NULL,&accepted)==0&&accepted==0);
    CHECK(bounded_progress_visit(done,total,-1,Collect,&state,&accepted)==1&&accepted==0);
    CHECK(bounded_progress_visit(done,total,65,Collect,&state,&accepted)==1&&accepted==0);
    CHECK(bounded_progress_visit(NULL,total,1,Collect,&state,&accepted)==1);
    CHECK(bounded_progress_visit(done,NULL,1,Collect,&state,&accepted)==1);
    CHECK(bounded_progress_visit(done,total,1,NULL,&state,&accepted)==1);
    CHECK(bounded_progress_visit(done,total,1,Collect,&state,NULL)==1);
    CHECK(state.calls==0);
    puts("C callback ownership checks passed");return 0;
}
