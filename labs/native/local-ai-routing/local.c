/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/local-ai-routing/local.c
 *
 * PURPOSE:
 *   Send one explicitly reviewed prompt through the existing Framework loopback provider.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "lab.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "umicom/ai_workspace/providers.h"

static int ReadPort(const char *text, uint16_t *out)
{
    unsigned value = 0U;
    if (text == NULL || text[0] == '\0') return 0;
    for (size_t i = 0U; text[i] != '\0'; ++i) {
        if (text[i] < '0' || text[i] > '9') return 0;
        unsigned digit = (unsigned)(text[i] - '0');
        if (value > (65535U - digit) / 10U) return 0;
        value = value * 10U + digit;
    }
    if (value < 1024U) return 0;
    *out = (uint16_t)value;
    return 1;
}
static int ModelId(const char *text)
{
    size_t length = strlen(text);
    if (length == 0U || length >= UMI_AI_ID_CAPACITY) return 0;
    for (size_t i = 0U; i < length; ++i) {
        unsigned char c = (unsigned char)text[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
              (c >= '0' && c <= '9') || c == '.' || c == '_' ||
              c == '-' || c == '/' || c == ':')) return 0;
    }
    return 1;
}
/* ASCII controls, including terminal escapes, are shown as bytes. Printable
 * UTF-8 is kept intact after the Framework codec has validated the response.
 * This is console presentation, not HTML rendering or a full bidi policy. */
static void PrintText(const char *text)
{
    for (size_t i = 0U; text[i] != '\0'; ++i) {
        unsigned char byte = (unsigned char)text[i];
        if (byte == '\n' || byte == '\t' || (byte >= 0x20U && byte != 0x7fU))
            (void)putchar((int)byte);
        else
            (void)printf("\\x%02X", (unsigned)byte);
    }
    (void)putchar('\n');
}
int LabLocal(const char *portText, const char *model, const char *prompt)
{
    static UmiAiRuntime runtime;
    static UmiAiRequest request;
    static UmiAiResponse response;
    UmiAiWorkspaceCancellation *cancellation = NULL;
    UmiAiProvider provider = {0};
    UmiAiMessage message = {0};
    uint16_t port = 0U;
    UmiStatus status = UMI_STATUS_INVALID_ARGUMENT;
    int result = 1;
    if (!ReadPort(portText, &port) || !ModelId(model) ||
        prompt[0] == '\0' || strlen(prompt) >= UMI_AI_TEXT_CAPACITY) {
        fputs("Invalid port, model ID or prompt capacity.\n", stderr);
        return 2;
    }
    umi_ai_runtime_init(&runtime);
    umi_ai_request_init(&request);
    umi_ai_response_init(&response);
    (void)snprintf(request.request_id, sizeof(request.request_id), "%s", "learning-local-request");
    (void)snprintf(request.model_id, sizeof(request.model_id), "%s", model);
    request.max_output_tokens = 128U;
    request.temperature = 0.2;
    request.allow_tools = 0;
    status = umi_ai_message_set(&message, UMI_AI_ROLE_USER, "learner", prompt);
    if (status != UMI_STATUS_OK) goto done;
    status = umi_ai_request_add_message(&request, &message);
    if (status != UMI_STATUS_OK) goto done;
    if (!UmiAiWorkspaceLocalProviderAvailable()) {
        fputs("Installed Framework has no local HTTP provider support.\n", stderr);
        result = 3;
        goto done;
    }
    status = UmiAiWorkspaceCancellationCreate(&cancellation);
    if (status != UMI_STATUS_OK) goto done;
    status = UmiAiWorkspaceLocalProviderCreate(port, 30000U, cancellation, &provider);
    if (status != UMI_STATUS_OK) goto done;
    status = umi_ai_provider_registry_add(&runtime.providers, &provider);
    if (status != UMI_STATUS_OK) {
        /* Failed registration leaves the created instance with this client. */
        provider.destroy(provider.instance);
        goto done;
    }
    /* Registry ownership lasts until RuntimeDestroy. The borrowed cancellation
     * token survives that destruction. This synchronous client never spawns a
     * server, changes its model, downloads weights or falls back to a cloud. */
    status = umi_ai_runtime_generate(&runtime, "umicom.local-chat", 0, &request, &response);
    if (status != UMI_STATUS_OK) goto done;
    PrintText(response.text);
    printf("Finish reason: %s\n", umi_ai_finish_reason_text(response.finish_reason));
    result = 0;
done:
    umi_ai_runtime_destroy(&runtime);
    UmiAiWorkspaceCancellationDestroy(cancellation);
    if (result == 1) fprintf(stderr, "Local request failed with Framework status %d.\n", (int)status);
    return result;
}
