/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: read_window.h
 *
 * PURPOSE:
 *   Define and check the original bounded read-window teaching contract.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#ifndef UMICOM_LEARNING_READ_WINDOW_H
#define UMICOM_LEARNING_READ_WINDOW_H
#include <stddef.h>
#include <stdint.h>
/* Output storage is distinct and unchanged on invalid arguments. */
int umi_learning_read_window(uint64_t position, size_t requested, size_t length,
    size_t *offset, size_t *count);
#endif
