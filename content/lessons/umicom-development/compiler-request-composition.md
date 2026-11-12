<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/compiler-request-composition.md

PURPOSE:
Compose a bounded compiler request and preserve refused edits

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Compose a bounded compiler request and preserve refused edits

## Build a draft through its owner

A compiler request holds project and unit identifiers, paths, language settings and three option collections. An include directory, a macro definition and an additional option are different fields, even though all are strings. Use the corresponding Framework additions so every client receives the same capacity and failure behavior.


~~~c
UmiStatus status = umi_compiler_request_add_include(
    &request, "include");
if (status != UMI_STATUS_OK) return status;
status = umi_compiler_request_add_definition(
    &request, "DEMO=1");
if (status != UMI_STATUS_OK) return status;
~~~


## Separate storage from readiness

Storage validity establishes bounded scalar text, bounded target text and valid active option extents. Empty scalar fields can still describe a draft. Full request validation additionally requires project, unit, source and output metadata and recognized language and action values. A draft can therefore be safe to inspect while still incomplete for planning.


The three option counts are independent. A valid include count does not establish a valid definition count. A malformed unused slot does not matter until it becomes active, but an active empty or unterminated option is refused. This is why the shared storage validator checks all active collections before any incremental addition.


## Observe the entire refusal

The request laboratory supplies an option with no terminator inside its permitted capacity. The addition returns CAPACITY_EXCEEDED and preserves every request byte. Checking only option_count would miss a previous implementation that had already overwritten an unused slot before discovering truncation. A future append could otherwise encounter unexpected leftover data.


The accepted example then adds the same text through a pointer borrowed from the first option slot. The new slot owns its copied bytes. This is ordinary aliasing, not ownership transfer: the caller does not hand Framework a heap allocation to free. Reading the full example beside the header makes that distinction visible.


## Practice a boundary explanation

Run the request scenario and compare its two observations. One edit is refused without publication; the next two edits succeed and create independent active entries. Explain why the program exits successfully even though it deliberately requested one invalid operation.


For an exercise, propose a request with a source path that fits its path array but is too long for one command argument. Predict whether request storage validation or provider planning should report the failure. The next lesson follows that later boundary. Do not enlarge public arrays in the application to evade the installed library contract.


## Source and practice

[Compiler ownership laboratory and owner commands](../../../labs/native/framework-compiler-ownership/README.md) · [HTML edition](../../courses/umicom-development/lessons/compiler-request-composition.html)

[Previous lesson](compiler-catalogue-admission.md) · [Next lesson](compiler-plan-publication.md) · [Course index](index.md)
