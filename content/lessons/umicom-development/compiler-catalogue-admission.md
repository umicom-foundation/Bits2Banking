<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/compiler-catalogue-admission.md

PURPOSE:
Check catalogue storage before selecting a compiler

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Check catalogue storage before selecting a compiler

## Treat the count as a claim

A fixed-capacity catalogue contains an array and a count. The array has storage determined by its C type; the count is a value a producer can change. A safe consumer compares those facts before indexing. The Framework provider registry, sysroot catalogue and runtime catalogue now perform that admission before lookup or insertion.


Read the catalogue scenario. It initializes a real provider registry, registers a provider, then deliberately writes an oversized count as an isolated malformed fixture. The client expects validation to fail, lookup to return no record and registration to return INVALID_STATE without changing owner bytes. Production clients should correct the producer rather than clamp a damaged count and continue.


~~~c
umi_compiler_registry_init(&registry);
UmiStatus status = umi_compiler_registry_register(
    &registry, &provider);
if (status != UMI_STATUS_OK) return status;
if (!umi_compiler_registry_valid(&registry))
    return UMI_STATUS_INVALID_STATE;
~~~


## Inspect the complete active set

A matching first row is not enough when a later active row is malformed. The shared validator checks every active record before returning a borrowed result. Each fixed text field must terminate inside its array. Unused slots are ignored because they are outside the declared active set. The same policy applies to the runtime and sysroot owners.


| Observation | Meaning |
| --- | --- |
| INVALID_ARGUMENT | The incoming record or required argument is malformed |
| INVALID_STATE | The existing owner is malformed |
| ALREADY_EXISTS | The admitted owner already holds the identifier |
| CAPACITY_EXCEEDED | A new insertion lacks a slot or revision capacity |


## Preserve useful observations at a boundary

A duplicate identifier remains ALREADY_EXISTS even when the array is full or its revision is exhausted. Duplicate registration does not replace the stored record. Read operations also remain available at the maximum revision when storage is valid. This preserves observation without silently recycling an identity.


A selected record is borrowed from the catalogue. Keep that owner alive and serialize access through the complete lookup-and-use interval. A validator cannot prevent another thread from changing a public record immediately afterward. Adding a local mutex to only the caller would be insufficient unless every participant follows the same ownership rule.


## Practice with two different claims

Write down why a provider marked available is not necessarily available now. Registration copies that flag; it does not launch the command or inspect a filesystem. For the exercise, describe one test for storage admission and one separate check for a genuinely usable compiler. Keep their results distinct in a project report.


## Source and practice

[Compiler ownership laboratory and owner commands](../../../labs/native/framework-compiler-ownership/README.md) · [HTML edition](../../courses/umicom-development/lessons/compiler-catalogue-admission.html)

[Previous lesson](compiler-record-ownership.md) · [Next lesson](compiler-request-composition.md) · [Course index](index.md)
