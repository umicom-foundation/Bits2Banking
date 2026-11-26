/*
 * Umicom Bits2Banking
 * File: brew-time-zero-divisor.uc
 *
 * PURPOSE:
 * Observe a valid expression that cannot finish executing.
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
    /* This deliberately incomplete runtime rule reaches a zero divisor. */
    int seconds = 4 * 60 + 15;
    return seconds / 0;
}
