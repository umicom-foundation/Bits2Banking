/*
 * Umicom Bits2Banking
 * File: brew-time-spelling.uc
 *
 * PURPOSE:
 * Change spelling and layout while preserving the emitted operations.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 */

int main(void)
{
    /* A hexadecimal literal and a binary literal spell the same inputs. */
    return 0x4 * 0b111100 + 0xf;
}
