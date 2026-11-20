<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/multikernel-systems/02-tell-startup-from-readiness.md

PURPOSE:
Distinguish controller lifecycle, host enforcement and observed worker readiness.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

# Tell startup from readiness

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

A Framework Master Controller starts local modules in dependency order and owns their lifecycle. A **provider** is the adapter that applies an operation in a particular environment, such as launching a supervised process on a Linux or Windows host. The operating system or hypervisor supplies the underlying protection. A catalogue entry can describe an intended limit. A provider observation establishes whether the platform applied it.

## Trace a worker start

| Observation | What it establishes | What happens next |
| --- | --- | --- |
| The local provider module started | The supervisor can receive requests. | Request a worker. |
| The host identifies a new child | A process exists for this startup attempt. | Bind it to a new generation, which is an identifier for this instance. |
| The correct endpoint answers a current challenge | The trusted transport owner has evidence about the current peer. | Probe the service it is supposed to offer. |
| The live worker returns the expected probe result | The selected endpoint served the probe before its deadline. | Admit work under the stated policy. |

Framework’s readiness guide is a source-reading exercise in those distinctions. It tracks the current process token, generation, challenge and deadline. The host supplies peer verification. Keep that responsibility when adapting the idea to a guest service. [Framework readiness contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/INTEGRATION_PROCESS_READINESS.md)

## Trace a late answer

1. Write down two rows for one worker. Give the original generation 7 and its replacement generation 8.
2. Mark generation 8 as starting. Put an answer from generation 7 in the inbox.
3. Decide whether you can admit a job. The old answer cannot establish readiness for generation 8. Keep the replacement in startup.
4. Add a valid probe from generation 8 after its deadline. Keep the timeout visible. Independently verify that the worker has stopped before releasing resources assigned to it.

As a check, explain why a message printed on a serial console cannot identify the current service by itself. The intended endpoint, current generation and probe result must agree. A new module or guest API is unnecessary for drawing this trace.
