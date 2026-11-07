/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/connector-lifetime/main.c
 *
 * PURPOSE:
 *   Demonstrate copied connector callbacks, bounded queries and reentrant close ownership.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "umicom/data/connector.h"

typedef struct LessonConnection { size_t available_rows; } LessonConnection;
typedef struct LessonContext {
    UmiDataConnectorHandle *handle;
    unsigned close_calls;
    bool saw_closed_handle;
} LessonContext;

/* This fixture owns no credentials and opens no network connection. */
static UmiStatus lesson_open(const UmiDataConnectorOpenRequest *request,
                            void *context, void **out_connection)
{
    LessonConnection *connection;
    (void)context;
    if (request == NULL || out_connection == NULL) return UMI_STATUS_INVALID_ARGUMENT;
    connection = malloc(sizeof(*connection));
    if (connection == NULL) return UMI_STATUS_OUT_OF_MEMORY;
    connection->available_rows = 4U;
    *out_connection = connection;
    return UMI_STATUS_OK;
}

static UmiStatus lesson_execute(void *state,
                               const UmiDataConnectorQueryRequest *request,
                               UmiDataConnectorQuerySummary *summary,
                               void *context)
{
    const LessonConnection *connection = state;
    (void)context;
    if (connection == NULL || request == NULL || summary == NULL)
        return UMI_STATUS_INVALID_ARGUMENT;
    if (!request->read_only || strcmp(request->query_text, "lesson-titles") != 0)
        return UMI_STATUS_INVALID_ARGUMENT;
    summary->column_count = 2U;
    summary->row_count = request->row_limit < connection->available_rows
        ? request->row_limit : connection->available_rows;
    summary->affected_rows = 0U;
    summary->has_more = summary->row_count < connection->available_rows;
    return UMI_STATUS_OK;
}

/* A notification can request another close. The guard keeps this demonstration
 * bounded even against an older SDK; main reports that SDK's wrong state. */
static void lesson_close(void *connection, void *context)
{
    LessonContext *owner = context;
    owner->close_calls += 1U;
    if (owner->close_calls != 1U) return;
    owner->saw_closed_handle = !owner->handle->open && owner->handle->connection == NULL;
    umi_data_connector_handle_close(owner->handle);
    free(connection);
}

/* Explicit checks still execute when an optimized build defines NDEBUG. */
#define REQUIRE(condition) do { if (!(condition)) {     fprintf(stderr, "Check failed at line %d: %s\n", __LINE__, #condition);     goto done; } } while (0)

int main(void)
{
    UmiDataConnectorRegistry *registry = NULL;
    UmiDataConnectorDescriptor descriptor = {0};
    UmiDataConnectorHandle handle = {0};
    LessonContext context = {&handle, 0U, false};
    UmiDataConnectorOpenRequest request = {"fixture", "lessons", "fixture-reference", true};
    UmiDataConnectorQueryRequest query = {"lesson-titles", true, 2U};
    UmiDataConnectorQuerySummary summary = {0};
    int result = EXIT_FAILURE;

    (void)snprintf(descriptor.connector_id, sizeof(descriptor.connector_id), "%s", "lesson.document");
    (void)snprintf(descriptor.display_name, sizeof(descriptor.display_name), "%s", "Document fixture");
    descriptor.family = UMI_DATA_CONNECTOR_DOCUMENT;
    descriptor.open = lesson_open;
    descriptor.execute = lesson_execute;
    descriptor.close = lesson_close;
    descriptor.driver_context = &context;
    REQUIRE(umi_data_connector_registry_create(1U, &registry) == UMI_STATUS_OK);
    REQUIRE(umi_data_connector_registry_register(registry, &descriptor) == UMI_STATUS_OK);
    REQUIRE(umi_data_connector_registry_open(registry, "lesson.document", &request, &handle) == UMI_STATUS_OK);
    umi_data_connector_registry_destroy(registry);
    registry = NULL;
    REQUIRE(umi_data_connector_handle_execute(&handle, &query, &summary) == UMI_STATUS_OK);
    REQUIRE(summary.row_count == 2U && summary.has_more);
    printf("Rows: %zu; more: yes\n", summary.row_count);
    umi_data_connector_handle_close(&handle);
    umi_data_connector_handle_close(&handle);
    REQUIRE(context.close_calls == 1U && context.saw_closed_handle);
    REQUIRE(umi_data_connector_handle_execute(&handle, &query, &summary) == UMI_STATUS_INVALID_ARGUMENT);
    puts("Provider releases: 1; nested close observed an empty handle.");
    result = EXIT_SUCCESS;
done:
    umi_data_connector_handle_close(&handle);
    umi_data_connector_registry_destroy(registry);
    return result;
}
