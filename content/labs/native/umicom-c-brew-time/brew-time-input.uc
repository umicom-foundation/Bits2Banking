/*
 * Umicom Bits2Banking
 * File: brew-time-input.uc
 *
 * PURPOSE:
 * Reuse a single signed input entry for different brew times.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 */

int umicom_run(int minutes)
{
    /* Keep a distinct recipe refusal unless the signed input is in range. */
    int seconds = -1;
    if (minutes >= 1 && minutes <= 60) {
        seconds = minutes * 60 + 15;
    }
    return seconds;
}
