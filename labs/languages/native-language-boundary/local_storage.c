/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/local_storage.c
 *
 * PURPOSE:
 *   Provide a native C comparison for automatic storage, retained local state and bounded owner-specific counters.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define CHECK(x) do { if(!(x)) { fprintf(stderr,"%d: %s\n",__LINE__,#x); return 1; } } while(0)
typedef struct Counter { uint32_t value; } Counter;
static int next_owned(Counter *state,uint32_t *output)
{
    if(state==NULL || output==NULL || state->value>=3U) return 0;
    uint32_t candidate=state->value+1U;
    state->value=candidate;
    *output=candidate;
    return 1;
}
static int next_automatic(uint32_t *output)
{
    Counter state={0};
    return next_owned(&state,output);
}
static int next_hidden(uint32_t *output)
{
    /* C static storage is shared across threads, unlike D's default mutable
     * thread-local static. This single-threaded lesson adds no synchronization. */
    static Counter state;
    return next_owned(&state,output);
}
int main(int argc,char **argv)
{
    CHECK(argc==2);
    uint32_t a=99U,b=99U;
    if(strcmp(argv[1],"automatic")==0) {
        CHECK(next_automatic(&a) && next_automatic(&b));
        CHECK(a==1U && b==1U);
        puts("Automatic calls: 1, 1");
    } else if(strcmp(argv[1],"static")==0) {
        CHECK(next_hidden(&a) && next_hidden(&b));
        CHECK(a==1U && b==2U);
        puts("Static calls: 1, 2");
    } else if(strcmp(argv[1],"owners")==0) {
        Counter left={0},right={0};
        CHECK(next_owned(&left,&a) && a==1U);
        CHECK(next_owned(&right,&b) && b==1U);
        CHECK(next_owned(&left,&a) && a==2U);
        CHECK(left.value==2U && right.value==1U);
        CHECK(next_owned(&left,&a) && a==3U);
        a=99U;
        CHECK(!next_owned(&left,&a));
        CHECK(a==99U && left.value==3U && right.value==1U);
        CHECK(!next_owned(NULL,&a) && a==99U);
        CHECK(!next_owned(&right,NULL) && right.value==1U);
        left.value=UINT32_MAX;
        CHECK(!next_owned(&left,&a) && left.value==UINT32_MAX && a==99U);
        puts("Owned counters: left 3, right 1; refusal preserved 99");
    } else return 2;
    return 0;
}
