/*-----------------------------------------------------------------------------
 * Bits2Banking — Read-only VFS Provider Laboratory
 * File: labs/native/vfs-provider-composition/reference_provider.c
 * PURPOSE: Expose copied text from immutable assets without implementing
 *          writes, unlinking or a second descriptor/dispatch layer.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "reference_provider.h"
#include <string.h>

static const struct {
    const char *name;
    const char *text;
} REFERENCE_FILES[BTB_REFERENCE_FILES] = {
    {"MISSION.TXT", "Service to Many Leads to Greatness.\n"},
    {"COURSES.TXT", "Computing, C23, Assembly, Umicom Kernel.\n"}
};

static BtbVfsStatus ReferenceOpen(void *context, const char *name,
                                  unsigned rights, uint32_t *outNode)
{
    BtbReferenceProvider *provider = context;
    if (provider == NULL || name == NULL || outNode == NULL || rights == 0U)
        return BTB_VFS_INVALID_ARGUMENT;
    if ((rights & BTB_VFS_WRITE) != 0U) return BTB_VFS_READ_ONLY;
    if (rights != BTB_VFS_READ) return BTB_VFS_INVALID_ARGUMENT;
    for (size_t i = 0U; i < BTB_REFERENCE_FILES; ++i) {
        if (strcmp(name, REFERENCE_FILES[i].name) == 0) {
            if (provider->openCount[i] >= BTB_VFS_MAX_DESCRIPTIONS)
                return BTB_VFS_NO_SPACE;
            ++provider->openCount[i];
            *outNode = (uint32_t)(i + 1U);
            return BTB_VFS_OK;
        }
    }
    return BTB_VFS_NOT_FOUND;
}

static BtbVfsStatus ReferenceRead(void *context, uint32_t node, size_t position,
                                  void *destination, size_t capacity, size_t *outRead)
{
    BtbReferenceProvider *provider = context;
    if (provider == NULL || outRead == NULL || node == 0U || node > BTB_REFERENCE_FILES ||
        provider->openCount[node - 1U] == 0U || (capacity != 0U && destination == NULL))
        return BTB_VFS_INVALID_ARGUMENT;
    const char *const content = REFERENCE_FILES[node - 1U].text;
    const size_t length = strlen(content);
    size_t count = position < length ? length - position : 0U;
    if (count > capacity) count = capacity;
    if (count != 0U) (void)memcpy(destination, content + position, count);
    *outRead = count;
    return BTB_VFS_OK;
}

static BtbVfsStatus ReferenceRelease(void *context, uint32_t node)
{
    BtbReferenceProvider *provider = context;
    if (provider == NULL || node == 0U || node > BTB_REFERENCE_FILES ||
        provider->openCount[node - 1U] == 0U) return BTB_VFS_BAD_STATE;
    --provider->openCount[node - 1U];
    return BTB_VFS_OK;
}

BtbVfsProviderOps BtbReferenceProviderOperations(void)
{
    /* Missing operations are deliberate capability restrictions. Open-file
     * descriptions are owned by the same VFS as the writable Notes provider. */
    return (BtbVfsProviderOps){.open = ReferenceOpen, .read = ReferenceRead,
        .write = NULL, .unlink = NULL, .release = ReferenceRelease};
}
