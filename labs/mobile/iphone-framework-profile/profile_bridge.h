/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/mobile/iphone-framework-profile/profile_bridge.h
 *
 * PURPOSE:
 *   Expose the shared Framework name policy through a small C boundary that Swift can import.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef BTB_IPHONE_PROFILE_BRIDGE_H
#define BTB_IPHONE_PROFILE_BRIDGE_H
#include <stddef.h>
#include "umicom/security/profile_name.h"
#ifdef __cplusplus
extern "C" {
#endif
/* Success returns 1 and publishes a canonical name in capacity bytes. Refusal
 * returns 0 and leaves output unchanged. Both buffers belong to the caller;
 * neither address survives this synchronous call. Input is an exact byte span,
 * not a C string, so embedded NUL cannot silently shorten a name. */
int BtbProfileCanonical(const unsigned char *input, size_t length,
    char output[UMI_LOCAL_PROFILE_NAME_CAPACITY]);
#ifdef __cplusplus
}
#endif
#endif
