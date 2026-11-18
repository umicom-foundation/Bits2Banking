/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/tagged_number.c
 *
 * PURPOSE:
 *   Compare a native C union protocol with the BASIC and D teaching examples.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
typedef enum NumberKind { NUMBER_INVALID=0, NUMBER_WHOLE=1, NUMBER_FRACTIONAL=2 } NumberKind;
typedef union NumberPayload { int64_t whole; double fractional; } NumberPayload;
typedef struct TaggedNumber { NumberKind kind; NumberPayload payload; } TaggedNumber;

/* Layout checks describe storage, not the active semantic alternative. */
static_assert(offsetof(NumberPayload,whole)==offsetof(NumberPayload,fractional));
static_assert(sizeof(NumberPayload)>=sizeof(int64_t) && sizeof(NumberPayload)>=sizeof(double));
static TaggedNumber Whole(int64_t value)
{
    return (TaggedNumber){.kind=NUMBER_WHOLE,.payload={.whole=value}};
}
static TaggedNumber Fractional(double value)
{
    return (TaggedNumber){.kind=NUMBER_FRACTIONAL,.payload={.fractional=value}};
}
static bool TryWhole(const TaggedNumber *value,int64_t *out)
{
    if(value==NULL || out==NULL || value->kind!=NUMBER_WHOLE) return false;
    *out=value->payload.whole; return true;
}
static bool TryFractional(const TaggedNumber *value,double *out)
{
    if(value==NULL || out==NULL || value->kind!=NUMBER_FRACTIONAL) return false;
    *out=value->payload.fractional; return true;
}
int main(void)
{
    TaggedNumber value=Whole(42);
    int64_t whole=-7; double fractional=-8.5;
    if(!TryWhole(&value,&whole) || whole!=42) return 1;
    if(TryFractional(&value,&fractional) || fractional!=-8.5) return 2;
    value=Fractional(12.5);
    if(!TryFractional(&value,&fractional) || fractional!=12.5) return 3;
    if(TryWhole(&value,&whole) || whole!=42) return 4;
    /* Test a malformed tag without reading the union through either view. */
    value.kind=(NumberKind)99;
    if(TryWhole(&value,&whole) || TryFractional(&value,&fractional)) return 5;
    if(whole!=42 || fractional!=12.5) return 6;
    const TaggedNumber unselected={0};
    if(TryWhole(&unselected,&whole) || TryFractional(&unselected,&fractional)) return 7;
    if(TryWhole(NULL,&whole) || TryFractional(NULL,&fractional) ||
        TryWhole(&value,NULL) || TryFractional(&value,NULL)) return 8;
    puts("Umicom tagged-number checks passed.");
    puts("Wrong and unknown tags preserved both output values.");
    return 0;
}
