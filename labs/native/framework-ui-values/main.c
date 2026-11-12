/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-ui-values/main.c
 *
 * PURPOSE:
 *   Demonstrate owned UI values and refused publication through the installed Framework SDK.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ui/value.h"
#include "umicom/ui/property.h"
#include "umicom/ui/reactive/observable_store.h"
#include "umicom/ui/reactive/command_parameter.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQUIRE(c) do { if (!(c)) { fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #c); goto done; } } while (0)

static int ShowAlias(void)
{
    int result = EXIT_FAILURE;
    UmiUiValue value;
    REQUIRE(umi_ui_value_set_string(&value, "prefix/Umicom") == UMI_STATUS_OK);
    REQUIRE(umi_ui_value_set_string(&value, value.string_value + 7U) == UMI_STATUS_OK);
    REQUIRE(value.kind == UMI_UI_VALUE_STRING && strcmp(value.string_value, "Umicom") == 0);
    printf("Title: %s\n", value.string_value);
    result = EXIT_SUCCESS;
done:
    return result;
}
static int ShowRefusal(void)
{
    int result = EXIT_FAILURE;
    UmiUiValue value, retained;
    char oversized[UMI_UI_VALUE_STRING_CAPACITY + 1U];
    REQUIRE(umi_ui_value_set_integer(&value, 42) == UMI_STATUS_OK);
    memcpy(&retained, &value, sizeof(retained));
    memset(oversized, 'x', sizeof(oversized));
    oversized[sizeof(oversized) - 1U] = '\0';
    REQUIRE(umi_ui_value_set_string(&value, oversized) == UMI_STATUS_CAPACITY_EXCEEDED);
    REQUIRE(memcmp(&value, &retained, sizeof(value)) == 0);
    printf("Status: CAPACITY_EXCEEDED\nPrevious integer: %" PRId64 "\n", value.integer_value);
    result = EXIT_SUCCESS;
done:
    return result;
}
static int ShowProperty(int malformed)
{
    int result = EXIT_FAILURE;
    UmiUiPropertyBag *properties = NULL;
    UmiUiValue source, observed;
    REQUIRE(umi_ui_property_bag_create(&properties) == UMI_STATUS_OK);
    REQUIRE(umi_ui_value_set_string(&source, "Accepted title") == UMI_STATUS_OK);
    REQUIRE(umi_ui_property_bag_set(properties, "title", &source) == UMI_STATUS_OK);
    const uint64_t revision = umi_ui_property_bag_revision(properties);
    if (malformed) {
        /* Deliberate component-boundary fixture, never a valid UI payload. */
        source.kind = (UmiUiValueKind)99;
        REQUIRE(!umi_ui_value_valid(&source));
        REQUIRE(umi_ui_property_bag_set(properties, "title", &source) == UMI_STATUS_INVALID_ARGUMENT);
        REQUIRE(umi_ui_property_bag_revision(properties) == revision);
        puts("Status: INVALID_ARGUMENT");
    } else {
        REQUIRE(umi_ui_value_set_string(&source, "Caller changed") == UMI_STATUS_OK);
        puts("Caller title: Caller changed");
    }
    REQUIRE(umi_ui_property_bag_get(properties, "title", &observed) == UMI_STATUS_OK);
    REQUIRE(observed.kind == UMI_UI_VALUE_STRING && strcmp(observed.string_value, "Accepted title") == 0);
    REQUIRE(umi_ui_property_bag_count(properties) == 1U);
    printf("Stored title: %s\nProperties: %zu\n", observed.string_value, umi_ui_property_bag_count(properties));
    result = EXIT_SUCCESS;
done:
    umi_ui_property_bag_destroy(properties);
    return result;
}
static int ShowRevision(void)
{
    int result = EXIT_FAILURE;
    UmiUiReactiveObservableStore *store = malloc(sizeof(*store));
    UmiUiValue value, observed;
    REQUIRE(store != NULL);
    umi_ui_reactive_observable_store_init(store);
    REQUIRE(umi_ui_value_set_string(&value, "ready") == UMI_STATUS_OK);
    REQUIRE(umi_ui_reactive_observable_store_put(store, "status", &value) == UMI_STATUS_OK);
    /* Boundary injection in this isolated demonstration only. A production
     * client never edits a live revision to bypass its owner's admission. */
    store->revision = UINT64_MAX;
    REQUIRE(umi_ui_value_set_string(&value, "replacement") == UMI_STATUS_OK);
    REQUIRE(umi_ui_reactive_observable_store_put(store, "status", &value) == UMI_STATUS_CAPACITY_EXCEEDED);
    REQUIRE(store->count == 1U && store->revision == UINT64_MAX);
    REQUIRE(umi_ui_reactive_observable_store_get(store, "status", &observed) == UMI_STATUS_OK);
    REQUIRE(observed.kind == UMI_UI_VALUE_STRING && strcmp(observed.string_value, "ready") == 0);
    printf("Status: CAPACITY_EXCEEDED\nReadable value: %s\nRevision: %" PRIu64 "\n",
        observed.string_value, store->revision);
    result = EXIT_SUCCESS;
done:
    free(store);
    return result;
}
static int ShowArchive(void)
{
    int result = EXIT_FAILURE;
    UmiUiReactiveCommandParameter parameter;
    unsigned char bytes[64], retained[64];
    size_t size = 77U;
    umi_ui_reactive_command_parameter_init(&parameter);
    parameter.value.kind = (UmiUiValueKind)99;
    memset(bytes, 0xa5, sizeof(bytes)); memcpy(retained, bytes, sizeof(bytes));
    REQUIRE(umi_ui_reactive_command_parameter_archive_encode(&parameter, bytes, sizeof(bytes), &size) ==
        UMI_STATUS_INVALID_ARGUMENT);
    REQUIRE(size == 77U && memcmp(bytes, retained, sizeof(bytes)) == 0);
    REQUIRE(umi_ui_value_set_integer(&parameter.value, 7) == UMI_STATUS_OK);
    REQUIRE(umi_ui_reactive_command_parameter_archive_encode(&parameter, NULL, 0U, &size) == UMI_STATUS_OK);
    REQUIRE(size > 0U);
    puts("Malformed kind: refused before output\nAccepted integer: encoded size available");
    result = EXIT_SUCCESS;
done:
    return result;
}
int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: btb-framework-ui-values alias|refused-title|publish|invalid-value|revision|archive\n");
        return EXIT_FAILURE;
    }
    int result;
    if (strcmp(argv[1], "alias") == 0) result = ShowAlias();
    else if (strcmp(argv[1], "refused-title") == 0) result = ShowRefusal();
    else if (strcmp(argv[1], "publish") == 0) result = ShowProperty(0);
    else if (strcmp(argv[1], "invalid-value") == 0) result = ShowProperty(1);
    else if (strcmp(argv[1], "revision") == 0) result = ShowRevision();
    else if (strcmp(argv[1], "archive") == 0) result = ShowArchive();
    else { fprintf(stderr, "Unknown scenario: %s\n", argv[1]); return EXIT_FAILURE; }
    if (result == EXIT_SUCCESS) puts("Shared value observations only; no GUI or command execution.");
    return result;
}
