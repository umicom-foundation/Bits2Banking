<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/04-own-providers-and-requests-in-c.md

PURPOSE:
Teach own providers and requests in c.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Own providers and requests in C

## What you will learn
Use Framework's C function table without duplicating its registry or policy logic. Track ownership across success and failure.

## Read the complete client
The [lab](../../../../labs/native/local-ai-routing/README.md) contains source files, an installed-SDK CMake project and seven offline checks. Its offline callback returns a constant sentence, clearly marked as a fixture. This exercises integration without pretending to be inference.

A provider table contains a function pointer for generation, an instance pointer and a destroy callback. An instance is adapter-owned state; the registry owns it after successful registration. If registration fails, the creator still owns it and must release it.

## Follow the lifetime
1. Initialize UmiAiRuntime.
2. Create or initialize an adapter and fill its provider table.
3. Register it with umi_ai_provider_registry_add.
4. Initialize UmiAiRequest, set its bounded identifiers and add messages.
5. Dispatch through umi_ai_runtime_generate.
6. Inspect status before consuming the response.
7. Destroy the runtime after work has finished. Then release objects borrowed by the adapter.

The local client follows this real sequence:
~~~c
status = umi_ai_provider_registry_add(&runtime.providers, &provider);
if (status != UMI_STATUS_OK) {
    provider.destroy(provider.instance);
    goto done;
}
status = umi_ai_runtime_generate(
    &runtime, "umicom.local-chat", 0, &request, &response);
~~~

The zero approval argument does not bypass policy. The configured local policy permits this provider; the same argument would fail a remote request requiring approval.

## Avoid hidden resource errors
A fixed-size request is large because it contains many messages. The serial teaching executable uses static storage, with that limitation documented. A GUI must give each operation explicit owned state and a worker lifetime; sharing that static request across threads would be wrong.

Checks execute through ordinary if statements, not side effects inside assert. Disabling assertions in a release build must not disable setup or validation.

## Exercise
Run offline dispatch and offline policy. The first expects exactly one callback; the second expects zero callbacks because policy refuses the remote fixture. Both verify a single destroy callback after successful registration.

**Answer:** an error return from generation is not permission to destroy the instance twice. Registration, generation and destruction have different ownership transitions.

## Recovery
If a callback sees an unexpected model ID, inspect the complete request and selected provider. Do not substitute a hard-coded answer in the live path. Preserve the error and report the failing layer.

[Course contents](index.md) · [Next lesson](05-call-an-existing-local-model.md)
