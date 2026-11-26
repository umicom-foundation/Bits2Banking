/*
 * Umicom Bits2Banking
 * File: brew-time-adjust.uc
 *
 * PURPOSE:
 * Watch a local change before the final return.
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
    /* Keep assignment and adjustment on separate lines for the source debugger. */
    int seconds = 4 * 60;
    seconds += 15;
    return seconds;
}
