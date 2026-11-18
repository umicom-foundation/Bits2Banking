/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/reflection-snapshot/main.c
 *
 * PURPOSE:
 *   Demonstrate self-referential metadata snapshots, explicit independent copies and bounded cleanup in C.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/reflection/registry.h"
#include "umicom/reflection/macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PreviewOptions { uint32_t width; uint32_t height; } PreviewOptions;
static const UmiReflectionFieldDescriptor fields[] = {
    UMI_REFLECTION_FIELD(PreviewOptions, width, "c.u32", UMI_REFLECTION_VALUE_UNSIGNED_INTEGER,
        UMI_REFLECTION_FIELD_REQUIRED, "Requested preview width, not an allocation permission"),
    UMI_REFLECTION_FIELD(PreviewOptions, height, "c.u32", UMI_REFLECTION_VALUE_UNSIGNED_INTEGER,
        UMI_REFLECTION_FIELD_REQUIRED, "Requested preview height, not an allocation permission")
};
static const UmiReflectionAttribute attributes[] = {{.key="purpose", .value="teaching"}};
static const UmiReflectionTypeDescriptor type = {
    .structure_size = sizeof(UmiReflectionTypeDescriptor), .schema_version = 1U,
    .type_id = "example.preview-options", .display_name = "Preview options",
    .module_id = "example.lesson", .kind = UMI_REFLECTION_TYPE_STRUCT,
    .size = sizeof(PreviewOptions), .alignment = _Alignof(PreviewOptions),
    .fields = fields, .field_count = UMI_REFLECTION_ARRAY_COUNT(fields),
    .attributes = attributes, .attribute_count = UMI_REFLECTION_ARRAY_COUNT(attributes)
};

/* Each snapshot contains bounded arrays and is deliberately allocated off the
 * thread stack. Keep three independent allocations: an array relocation or
 * assignment would not rebase the descriptor's internal pointers. */
int main(void)
{
    int result = 1;
    UmiReflectionRegistry *registry = NULL;
    UmiReflectionTypeSnapshot *original = calloc(1, sizeof *original);
    UmiReflectionTypeSnapshot *shallow = calloc(1, sizeof *shallow);
    UmiReflectionTypeSnapshot *independent = calloc(1, sizeof *independent);
    if (!original || !shallow || !independent) {
        fputs("Cannot allocate bounded teaching snapshots\n", stderr);
        goto cleanup;
    }
    UmiReflectionRegistryConfig limits = umi_reflection_registry_config_default();
    limits.type_capacity = 1U; limits.module_capacity = 1U; limits.resource_capacity = 1U;
    if (umi_reflection_registry_create(&limits, &registry) != UMI_STATUS_OK ||
        umi_reflection_registry_register_type(registry, &type) != UMI_STATUS_OK ||
        umi_reflection_registry_get_type(registry, type.type_id, original) != UMI_STATUS_OK)
        goto cleanup;

    *shallow = *original;
    if (shallow->descriptor.fields != original->fields ||
        shallow->descriptor.fields == shallow->fields) goto cleanup;
    puts("A struct assignment keeps the original array pointer.");

    /* Both allocations are still alive, so inspecting this alias is defined.
     * The copy API refuses the noncanonical source before reading its spans. */
    if (umi_reflection_type_snapshot_copy(shallow, independent) != UMI_STATUS_INVALID_ARGUMENT)
        goto cleanup;
    if (independent->descriptor.field_count != 0U) goto cleanup;
    puts("The explicit copy refuses a shallow snapshot.");
    if (umi_reflection_type_snapshot_copy(original, independent) != UMI_STATUS_OK ||
        independent->descriptor.fields != independent->fields ||
        independent->descriptor.attributes != independent->attributes)
        goto cleanup;

    umi_reflection_registry_destroy(registry); registry = NULL;
    strcpy(original->fields[0].display_name, "Changed original");
    if (strcmp(shallow->descriptor.fields[0].display_name, "Changed original") ||
        strcmp(shallow->fields[0].display_name, "width") ||
        strcmp(independent->descriptor.fields[0].display_name, "width")) goto cleanup;
    puts("A later source edit leaves the independent copy unchanged.");

    /* Discard the shallow descriptor before its referenced allocation ends.
     * No dangling pointer is dereferenced to demonstrate the ownership bug. */
    free(shallow); shallow = NULL;
    free(original); original = NULL;
    if (umi_reflection_type_descriptor_validate(&independent->descriptor) != UMI_STATUS_OK ||
        strcmp(independent->descriptor.attributes[0].value, "teaching")) goto cleanup;
    if (printf("Independent metadata: %zu fields; first field %s\n",
        independent->descriptor.field_count, independent->descriptor.fields[0].display_name) < 0)
        goto cleanup;
    puts("No live application object was copied or modified.");
    if (fflush(stdout) != 0 || ferror(stdout)) goto cleanup;
    result = 0;
cleanup:
    umi_reflection_registry_destroy(registry);
    free(shallow); free(original); free(independent);
    if (result != 0) fputs("Reflection ownership exercise failed\n", stderr);
    return result;
}
