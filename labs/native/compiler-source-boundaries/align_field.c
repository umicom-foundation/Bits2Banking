/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/compiler-source-boundaries/align_field.c
 *
 * PURPOSE:
 *   Find a small field offset using the selected C integer alignment.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

int main(void)
{
    /* Leave one byte for a practice kind field before the first int. */
    int alignment = alignof(int);
    int offset = 1;
    int remainder = offset % alignment;
    /* Move only when the present offset violates the type's requirement. */
    if (remainder != 0) {
        offset = offset + alignment - remainder;
    }
    return offset;
}
