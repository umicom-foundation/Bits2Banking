/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/web/shell-practice/shell.h
 *
 * PURPOSE:
 *   Define the shared shell-practice boundary for desktop and browser clients.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_SHELL_PRACTICE_H
#define BTB_SHELL_PRACTICE_H

#include <stddef.h>

/* Clients fill the bounded input view. Mode zero is Bash and mode one is
 * PowerShell. Read the output view before submitting or resetting again. */
unsigned char *BtbShellInput(void);
size_t BtbShellCapacity(void);
const char *BtbShellOutput(void);
size_t BtbShellOutputLength(void);
unsigned BtbShellSubmit(unsigned requestedMode, size_t length);
void BtbShellReset(unsigned requestedMode);

#endif
