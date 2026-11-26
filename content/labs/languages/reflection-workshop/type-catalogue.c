/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/languages/reflection-workshop/type-catalogue.c
 *
 * PURPOSE:
 *   Create a named C23 field catalogue and demonstrate a compile-time type observation.
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

/* One reviewed field list supplies both the declaration and the public labels.
 * Changes to a name flow to both places during preprocessing. */
#define READING_FIELDS(X) \
    X(unsigned int, station_id, "station number") \
    X(int, degrees_c, "degrees Celsius")

#define DECLARE_FIELD(type, name, label) type name;
typedef struct Reading {
    READING_FIELDS(DECLARE_FIELD)
} Reading;
#undef DECLARE_FIELD

typedef struct FieldDescription {
    const char *name;
    const char *description;
    size_t offset;
} FieldDescription;

#define DESCRIBE_FIELD(type, name, label) {#name, label, offsetof(Reading, name)},
static const FieldDescription reading_fields[] = {
    READING_FIELDS(DESCRIBE_FIELD)
};
#undef DESCRIBE_FIELD

#define TYPE_LABEL(value) _Generic((value), int: "int", unsigned int: "unsigned int", default: "other")

int main(void)
{
    const Reading saved = {.station_id = 3U, .degrees_c = 68};

    /* This query copies the member's type without the const qualifier. The
     * initializer and subsequent assignment choose the separate local value. */
    typeof_unqual(saved.degrees_c) editable = saved.degrees_c;
    editable = 70;

    const size_t count = sizeof reading_fields / sizeof reading_fields[0];
    for (size_t index = 0; index < count; ++index) {
        printf("%s - %s\n", reading_fields[index].name,
               reading_fields[index].description);
    }

    /* Confirm that both offsets were produced for different members of this
     * exact type. The report avoids printing ABI-dependent numeric offsets. */
    if (reading_fields[0].offset >= reading_fields[1].offset) {
        fputs("Unexpected field layout\n", stderr);
        return 1;
    }

    printf("editable local type: %s\n", TYPE_LABEL(editable));
    printf("editable local value: %d\n", editable);
    printf("stored measurement: %d\n", saved.degrees_c);
    return 0;
}
