/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/boolean_wire.c
 *
 * PURPOSE:
 *   Demonstrate strict 0/1 byte flags without treating arbitrary bytes as C Boolean objects.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static uint8_t encode_flag(bool value)
{
    return value ? UINT8_C(1) : UINT8_C(0);
}
static bool decode_flag(uint8_t raw, bool *value)
{
    /* A successful decode can produce false. Status and value are separate;
     * refusal preserves the caller's previous value. No representation punning. */
    if (value == NULL || raw > UINT8_C(1)) return false;
    *value = raw == UINT8_C(1);
    return true;
}
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr,"line %d: %s\n",__LINE__,#x); return 1; } } while(0)
int main(void)
{
    REQUIRE(encode_flag(false)==0 && encode_flag(true)==1);
    REQUIRE((bool)2); /* Conversion is truth testing, not strict wire validation. */
    REQUIRE(!decode_flag(0,NULL));
    REQUIRE(!decode_flag(1,NULL));
    for(unsigned raw=0;raw<=255;++raw){
        bool destination=true;
        bool accepted=decode_flag((uint8_t)raw,&destination);
        if(raw<=1){
            REQUIRE(accepted && destination==(raw==1));
            REQUIRE(encode_flag(destination)==raw);
        }else{
            REQUIRE(!accepted && destination);
            destination=false;
            accepted=decode_flag((uint8_t)raw,&destination);
            REQUIRE(!accepted && !destination);
        }
    }
    puts("Umicom Boolean wire: all 256 bytes checked.");
    puts("Explicit encoding: false=0, true=1.");
    return 0;
}
