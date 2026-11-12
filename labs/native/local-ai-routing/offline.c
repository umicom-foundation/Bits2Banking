/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/local-ai-routing/offline.c
 *
 * PURPOSE:
 *   Exercise real Framework routing and policy with deterministic offline fixtures.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "lab.h"
#include <stdio.h>
#include <string.h>
#include "umicom/ai/runtime.h"
#include "umicom/ai/runtime_catalogue.h"

typedef struct Fixture { unsigned calls; unsigned destroys; } Fixture;
/* Fixed fixture strings have compile-time bounds. They are deliberately
 * different from a discovered server: health here is supplied test data. */
static UmiAiRuntimeDescriptor Descriptor(const char *id, uint32_t context, int local)
{
    UmiAiRuntimeDescriptor d = {0};
    (void)snprintf(d.runtime_id, sizeof(d.runtime_id), "%s", id);
    (void)snprintf(d.provider_id, sizeof(d.provider_id), "%s", local ? "lab.local" : "lab.remote");
    (void)snprintf(d.display_name, sizeof(d.display_name), "%s", id);
    (void)snprintf(d.model_id, sizeof(d.model_id), "%s", "fixture-model");
    d.provider_kind = local ? UMI_AI_PROVIDER_LOCAL : UMI_AI_PROVIDER_REMOTE;
    d.transport = UMI_AI_RUNTIME_IN_PROCESS;
    d.capabilities = UMI_AI_RUNTIME_CHAT;
    d.context_tokens = context;
    d.max_output_tokens = 128U;
    d.configured = 1;
    d.local = local;
    d.health.available = 1;
    return d;
}
static int CatalogueCase(const char *scenario)
{
    UmiAiRuntimeCatalogue *catalogue = NULL;
    UmiAiRuntimeDescriptor chosen = {0};
    UmiAiRuntimeDescriptor small = Descriptor("lab.small", 2048U, 1);
    UmiAiRuntimeDescriptor large = Descriptor("lab.large", 8192U, 1);
    UmiAiRuntimeDescriptor remote = Descriptor("lab.cloud", 1024U, 0);
    UmiStatus status = umi_ai_runtime_catalogue_create(&catalogue);
    int result = 1;
    if (status != UMI_STATUS_OK) goto done;
    if (umi_ai_runtime_catalogue_upsert(catalogue, &large) != UMI_STATUS_OK ||
        umi_ai_runtime_catalogue_upsert(catalogue, &small) != UMI_STATUS_OK ||
        umi_ai_runtime_catalogue_upsert(catalogue, &remote) != UMI_STATUS_OK) goto done;
    if (strcmp(scenario, "selection") == 0) {
        status = umi_ai_runtime_catalogue_select(catalogue, UMI_AI_RUNTIME_CHAT, 1024U, 1, &chosen);
        if (status != UMI_STATUS_OK || strcmp(chosen.runtime_id, "lab.small") != 0) goto done;
        puts("Selected lab.small; remote candidate excluded.");
    } else if (strcmp(scenario, "capability") == 0) {
        status = umi_ai_runtime_catalogue_select(catalogue, UMI_AI_RUNTIME_EMBEDDINGS, 1024U, 1, &chosen);
        if (status != UMI_STATUS_NOT_FOUND) goto done;
        puts("No embedding runtime; no chat fallback.");
    } else if (strcmp(scenario, "context") == 0) {
        status = umi_ai_runtime_catalogue_select(catalogue, UMI_AI_RUNTIME_CHAT, 9000U, 1, &chosen);
        if (status != UMI_STATUS_NOT_FOUND) goto done;
        puts("No runtime fits 9000 tokens.");
    } else if (strcmp(scenario, "health") == 0) {
        UmiAiHealth unavailable = small.health;
        unavailable.available = 0;
        if (umi_ai_runtime_catalogue_set_health(catalogue, small.runtime_id, &unavailable) != UMI_STATUS_OK) goto done;
        status = umi_ai_runtime_catalogue_select(catalogue, UMI_AI_RUNTIME_CHAT, 1024U, 1, &chosen);
        if (status != UMI_STATUS_OK || strcmp(chosen.runtime_id, "lab.large") != 0) goto done;
        puts("Unavailable small runtime excluded; selected lab.large.");
    } else {
        result = 2;
        goto done;
    }
    result = 0;
done:
    umi_ai_runtime_catalogue_destroy(catalogue);
    return result;
}
static UmiStatus FixtureGenerate(void *instance, const UmiAiRequest *request, UmiAiResponse *response)
{
    Fixture *fixture = instance;
    /* This adapter checks the caller's teaching request. Its constant answer
     * exercises dispatch and ownership; it is never labelled inference. */
    if (fixture == NULL || request == NULL || response == NULL ||
        request->message_count != 1U || request->max_output_tokens != 128U ||
        strcmp(request->model_id, "fixture-model") != 0)
        return UMI_STATUS_INVALID_ARGUMENT;
    ++fixture->calls;
    umi_ai_response_init(response);
    response->finish_reason = UMI_AI_FINISH_STOP;
    return umi_ai_response_set_text(response, "Fixture answer; no model executed.");
}
static void FixtureDestroy(void *instance)
{
    Fixture *fixture = instance;
    if (fixture != NULL) ++fixture->destroys;
}
static int DispatchCase(int remote)
{
    /* A request contains many fixed-size messages. Static storage suits this
     * single-threaded short-lived exercise, not a shared application session. */
    static UmiAiRuntime runtime;
    static UmiAiRequest request;
    static UmiAiResponse response;
    Fixture fixture = {0};
    UmiAiProvider provider = {0};
    UmiAiMessage message = {0};
    UmiStatus status;
    int result = 1;
    umi_ai_runtime_init(&runtime);
    provider.structure_size = (uint32_t)sizeof(provider);
    provider.abi_version = 1U;
    provider.provider_id = remote ? "lab.remote" : "lab.local";
    provider.kind = remote ? UMI_AI_PROVIDER_REMOTE : UMI_AI_PROVIDER_LOCAL;
    provider.instance = &fixture;
    provider.generate = FixtureGenerate;
    provider.destroy = FixtureDestroy;
    if (umi_ai_provider_registry_add(&runtime.providers, &provider) != UMI_STATUS_OK) goto done;
    umi_ai_request_init(&request);
    (void)snprintf(request.request_id, sizeof(request.request_id), "%s", "lab-request");
    (void)snprintf(request.model_id, sizeof(request.model_id), "%s", "fixture-model");
    request.max_output_tokens = 128U;
    if (umi_ai_message_set(&message, UMI_AI_ROLE_USER, "learner", "Explain a routing contract.") != UMI_STATUS_OK ||
        umi_ai_request_add_message(&request, &message) != UMI_STATUS_OK) goto done;
    umi_ai_response_init(&response);
    status = umi_ai_runtime_generate(&runtime, provider.provider_id, 0, &request, &response);
    if (remote) {
        if (status != UMI_STATUS_PERMISSION_DENIED || fixture.calls != 0U) goto done;
        puts("Remote request denied before callback.");
    } else {
        if (status != UMI_STATUS_OK || fixture.calls != 1U ||
            strcmp(response.text, "Fixture answer; no model executed.") != 0) goto done;
        puts(response.text);
    }
    result = 0;
done:
    umi_ai_runtime_destroy(&runtime);
    if (result == 0 && fixture.destroys != 1U) result = 1;
    return result;
}
int LabOffline(const char *scenario)
{
    int result;
    if (strcmp(scenario, "dispatch") == 0) result = DispatchCase(0);
    else if (strcmp(scenario, "policy") == 0) result = DispatchCase(1);
    else result = CatalogueCase(scenario);
    if (result == 1) fputs("Contract observation failed.\n", stderr);
    if (result == 2) fputs("Unknown offline scenario.\n", stderr);
    return result;
}
