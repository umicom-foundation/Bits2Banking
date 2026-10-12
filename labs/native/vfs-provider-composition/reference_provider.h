/*-----------------------------------------------------------------------------
 * Bits2Banking — Read-only VFS Provider Laboratory
 * File: labs/native/vfs-provider-composition/reference_provider.h
 * PURPOSE: Demonstrate an independent provider behind the common VFS API.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_REFERENCE_PROVIDER_H
#define BTB_REFERENCE_PROVIDER_H
#include "vfs.h"

#define BTB_REFERENCE_FILES 2U

typedef struct BtbReferenceProvider {
    size_t openCount[BTB_REFERENCE_FILES];
} BtbReferenceProvider;

BtbVfsProviderOps BtbReferenceProviderOperations(void);
#endif /* BTB_REFERENCE_PROVIDER_H */
