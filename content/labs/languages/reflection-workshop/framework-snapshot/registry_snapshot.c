/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/languages/reflection-workshop/framework-snapshot/registry_snapshot.c
 *
 * PURPOSE:
 *   Demonstrate registry registration and independent Framework metadata snapshots.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "umicom/reflection/macros.h"
#include "umicom/reflection/registry.h"

typedef struct Reading {
    unsigned int station_id;
    int degrees_c;
} Reading;

/* Publish only this pair of fields. Framework derives the C size and offset
 * from the actual declaration and keeps the display policy in the descriptor. */
static const UmiReflectionFieldDescriptor reading_fields[] = {
    UMI_REFLECTION_FIELD(Reading, station_id, "unsigned-int",
        UMI_REFLECTION_VALUE_UNSIGNED_INTEGER, UMI_REFLECTION_FIELD_READ_ONLY,
        "Station number"),
    UMI_REFLECTION_FIELD(Reading, degrees_c, "int",
        UMI_REFLECTION_VALUE_SIGNED_INTEGER, UMI_REFLECTION_FIELD_NONE,
        "Degrees Celsius")
};

static const UmiReflectionTypeDescriptor reading_type = {
    .structure_size = (uint32_t)sizeof(UmiReflectionTypeDescriptor),
    .schema_version = 1U,
    .type_id = "workshop.reading",
    .display_name = "Workbench reading",
    .module_id = "workshop",
    .description = "Published metadata for a temperature reading",
    .kind = UMI_REFLECTION_TYPE_STRUCT,
    .size = sizeof(Reading),
    .alignment = alignof(Reading),
    .fields = reading_fields,
    .field_count = UMI_REFLECTION_ARRAY_COUNT(reading_fields)
};

int main(void)
{
    UmiReflectionRegistryConfig limits = umi_reflection_registry_config_default();
    limits.type_capacity = 2U;
    limits.module_capacity = 1U;
    limits.resource_capacity = 1U;

    UmiReflectionRegistry *registry = NULL;
    if (umi_reflection_registry_create(&limits, &registry) != UMI_STATUS_OK) {
        fputs("Could not create reflection registry\n", stderr);
        return 1;
    }

    UmiReflectionTypeSnapshot original = {0};
    UmiReflectionTypeSnapshot retained = {0};
    UmiStatus status = umi_reflection_registry_register_type(registry, &reading_type);
    if (status == UMI_STATUS_OK) {
        status = umi_reflection_registry_get_type(registry, reading_type.type_id, &original);
    }
    if (status == UMI_STATUS_OK) {
        /* Rebase the internal field pointer into the independent destination. */
        status = umi_reflection_type_snapshot_copy(&original, &retained);
    }
    if (status != UMI_STATUS_OK) {
        fputs("Could not retain the registered descriptor\n", stderr);
        umi_reflection_registry_destroy(registry);
        return 1;
    }

    printf("Registered type: %s (%zu fields)\n",
           original.descriptor.type_id, original.descriptor.field_count);

    status = umi_reflection_registry_unregister_type(registry, reading_type.type_id);
    const size_t remaining = umi_reflection_registry_type_count(registry);
    umi_reflection_registry_destroy(registry);
    if (status != UMI_STATUS_OK || remaining != 0U) {
        fputs("Could not remove the registered type\n", stderr);
        return 1;
    }

    /* Discard both earlier owners before consulting the retained metadata.
     * The copy must point into its own array even after registry destruction. */
    memset(&original, 0, sizeof original);
    if (retained.descriptor.fields != retained.fields ||
        retained.descriptor.field_count != UMI_REFLECTION_ARRAY_COUNT(reading_fields)) {
        fputs("Snapshot did not retain independent field storage\n", stderr);
        return 1;
    }

    printf("Registry count after removal: %zu\n", remaining);
    printf("Retained fields: %zu\n", retained.descriptor.field_count);
    for (size_t index = 0U; index < retained.descriptor.field_count; ++index) {
        const UmiReflectionFieldDescriptor *field = &retained.descriptor.fields[index];
        const char *flag = (field->flags & UMI_REFLECTION_FIELD_READ_ONLY) != 0U
            ? "set" : "clear";
        printf("%s: read-only flag %s\n", field->field_id, flag);
    }
    return 0;
}
