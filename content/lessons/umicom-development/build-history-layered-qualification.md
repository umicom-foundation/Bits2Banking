<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/build-history-layered-qualification.md

PURPOSE:
Qualify the runner, installed client and native presentation separately

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Qualify the runner, installed client and native presentation separately

## Use three distinct evidence layers

The shared Framework fixture controls preparation and process boundaries while compiling the real runner. The Bits2Banking laboratory links the installed public SDK and causes a real missing-program refusal. Studio adds native presentation and host lifetime. These layers answer different questions. Keeping them separate makes a failure easier to diagnose and prevents a large test count from being mistaken for complete application readiness.



| Layer | Question | Still separate |
| --- | --- | --- |
| Framework controlled fixture | Does every admitted exit retain one completed observation? | Actual process creation |
| Installed C client | Can a consumer link and observe the public contract? | Studio widgets and event lifetime |
| Native host | Does the correct attempt appear with usable diagnostics? | Other products and environments |



## Read the controlled fixture honestly

The 62 authored Framework cases cover legacy, observed and automatic-test entry points. Controlled failures include source/path preparation, provider command construction, directory storage, environment ownership and parser allocation. Process outcomes are also controlled so their status and output retention can be checked without starting a real tool. Existing process fixtures remain necessary to qualify native launch, cancellation and streaming.



## Use the installed laboratory

The six laboratory scenarios call public APIs rather than including Framework implementation files. Configure with the explicit installed SDK prefix in the README, build successfully, then run CTest and the desired scenario. If a build fails, stop. Executing an older binary would provide evidence about different source. Record the producer revision, consumer revision, toolchain, SDK prefix and complete command output together.



## Review native presentation

- Confirm that a newly refused operation replaces the prior latest status in the host.
- Verify that exit code -1 is described as no observed child exit, not a successful process.
- Check that a queued collector does not append a duplicate of a synchronous runner-owned result.
- Keep skipped, failed and unexecuted scenarios separate from passing observations.



The shared change does not add a public preparation-stage enum or durable log. Presentation should use the available status and operation evidence without inventing more detail. A missing command string is normal if preparation ended before formatting. Investigate the profile and the boundary reached; do not claim that absence of compiler output means the compiler succeeded.



## Check branding at the consumer boundary

The laboratory uses the installed Framework branding helper. It stages approved Umicom SVG assets and embeds the approved Windows ICO through RC, while avoiding unnecessary GTK runtime deployment for this console client. Lesson pages reuse the approved stylesheet with Segoe UI and Cascadia Code fallbacks. Static references and asset hashes are useful checks, but inspect installed executable metadata and rendered lessons on the owner environment too.



## Finish with an evidence statement

Write one paragraph stating which source was authored, which static checks were performed, which build and test commands actually ran, and which native or installed behaviours remain unverified. Current course material and scenarios are authored and statically inspected; no owner execution result is claimed here. If any layer fails, preserve its log and correct the relevant boundary rather than weakening the expected result of a different layer.



## Source and practice

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Build-history laboratory and owner commands](../../../labs/native/framework-build-history/README.md) · [HTML edition](../../courses/umicom-development/lessons/build-history-layered-qualification.html)
-->
[Build-history laboratory and owner commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-build-history/README.md) · [HTML edition](../../courses/umicom-development/lessons/build-history-layered-qualification.html)

<!-- The course continues into UI value ownership; the former endpoint is retained for review.
[Previous lesson](build-history-bounded-identities.md) · [Course index](index.md)
-->
[Previous lesson](build-history-bounded-identities.md) · [Next lesson](ui-values-active-payload.md) · [Course index](index.md)
