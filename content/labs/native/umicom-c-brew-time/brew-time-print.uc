/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/umicom-c-brew-time/brew-time-print.uc
 *
 * PURPOSE:
 * Publish typed output independently of the brew calculation's return value.
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
    /* Give the two display lines different types so the host's formatting is visible. */
    int seconds = 4 * 60 + 15;
    bool includes_pour = true;
    print(seconds);
    print(includes_pour);
    return seconds;
}
