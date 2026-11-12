<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/compiler-preview-json-arguments.md

PURPOSE:
Present compiler arguments as structured JSON

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Present compiler arguments as structured JSON

## Keep one argument separate from its neighbors

A source path containing spaces is one argument. A macro definition can contain quotes. A Windows path contains backslashes. Joining these strings with spaces produces an ambiguous command description and encourages accidental shell interpretation. The shared JSON serializer keeps an ordered array of strings, with the executable and intended working directory in separate fields.

Read Json in the installed laboratory. It constructs a real Framework plan, appends a quoted argument and serializes the result. The client checks that quotes and backslashes are escaped and that the source path remains one JSON string. It also checks the explicit false values for execution and toolchain verification.

## Use the shared presentation service

~~~c
UmiStatus status = umi_compiler_plan_json(
    &plan, json, sizeof(json));
if (status != UMI_STATUS_OK) return false;
/* Parse the complete document; arguments remain an ordered array. */
~~~

Allocate the documented maximum capacity when a fixed output buffer is appropriate. The serializer uses the existing Protocol JSON writer, which validates UTF-8 and escapes JSON control characters. It reads admitted inline argument storage, not cached borrowed argument pointers. The output must not overlap the plan, and neither owner may be changed concurrently.

## Interpret the evidence fields

Schema version one includes provider, executable, working directory, language, action and arguments. Language and action use the Framework enum numbers; the native CLI currently emits C or C++ and compile or check. The executed and toolchain_verified fields are always false. They prevent a successful metadata operation from pretending to be evidence about a compiler process.

The native command prints the same JSON contract. A consumer should preserve argument order and boundaries. It should not join the array and execute the result through a shell. Process creation, shell interpretation and authorization are separate responsibilities, even when every string came from a correctly serialized document.

## Practice

Write down a path with spaces and a definition containing a quoted phrase. Predict their JSON spelling and their decoded values separately. Run the json scenario, then inspect its checks. Explain why escaped text is not a security approval and why a valid document cannot establish that its executable exists.

## Source and practice

[Compiler preview laboratory and owner commands](../../../labs/native/framework-compiler-preview/README.md) · [Browser edition](../../courses/umicom-development/lessons/compiler-preview-json-arguments.html)

[Previous lesson](compiler-preview-driver-identity.md) · [Next lesson](compiler-preview-qualification.md) · [Written course contents](index.md) · [Course index](../../courses/umicom-development/index.html)
