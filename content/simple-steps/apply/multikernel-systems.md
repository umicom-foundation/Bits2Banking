<!--
Umicom Bits2Banking
File: content/simple-steps/apply/multikernel-systems.md

PURPOSE:
Give learners an additional practical case for Multikernel systems and workload isolation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Write a little worker ownership record

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional document draft stays in the editor. A separate worker prepares preview text from copied input.

1. List the input owner, the worker identity and the output that may be replaced. Mark the worker’s ready state before sending a request.
2. Trace a successful preview, then a failed request from the same worker. Write which durable item remains editable.

**Check your result.** The editor continues to own the draft. Only an accepted worker result changes the visible preview.

[Step-by-step course guide](../course-guides/multikernel-systems.md) · [Full course](../../courses/multikernel-systems/index.html) · [Small projects by course](index.md) · [First practice case](../practice/multikernel-systems.md)
