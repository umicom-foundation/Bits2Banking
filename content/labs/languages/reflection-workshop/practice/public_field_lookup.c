/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/languages/reflection-workshop/practice/public_field_lookup.c
 *
 * PURPOSE:
 *   Exercise present and absent results from a deliberately published C23 metadata table.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stddef.h>
#include <stdio.h>

typedef struct Reading {
    int degrees_c;
    unsigned int draft_flags;
} Reading;

enum {
    TEMPERATURE_ID = 220U,
    DRAFT_FLAGS_ID = 90U
};

typedef struct PublicField {
    unsigned int id;
    const char *label;
    size_t offset;
} PublicField;

/* Publish only the measurement. An internal member can exist in the C type
 * without appearing in the editor's public description. */
static const PublicField public_fields[] = {
    {TEMPERATURE_ID, "temperature", offsetof(Reading, degrees_c)}
};

static const PublicField *find_public_field(unsigned int id)
{
    const size_t count = sizeof public_fields / sizeof public_fields[0];
    for (size_t index = 0U; index < count; ++index) {
        if (public_fields[index].id == id) {
            return &public_fields[index];
        }
    }

    /* A distinct absence result lets callers avoid reading a different row. */
    return nullptr;
}

int main(void)
{
    const PublicField *temperature = find_public_field(TEMPERATURE_ID);
    const PublicField *draft = find_public_field(DRAFT_FLAGS_ID);
    if (temperature == nullptr ||
        temperature->offset != offsetof(Reading, degrees_c) ||
        draft != nullptr) {
        fputs("Public field lookup violated its catalogue\n", stderr);
        return 1;
    }

    printf("%u: %s\n", temperature->id, temperature->label);
    printf("%u: absent\n", (unsigned int)DRAFT_FLAGS_ID);
    return 0;
}
