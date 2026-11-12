![Umicom](../../../assets/branding/umicom-logo.svg)

# Express position-independent compilation as an explicit request

Some object files need code that can support loading at different addresses. A compiler flag is only one part of that workflow: the target architecture, compiler, linker and final artifact each matter. This lesson uses a narrow request to show how an API can represent intent without claiming a complete shared-library build.

## Inspect the supported mapping

For a C or C++ COMPILE action, the current GCC and Clang providers map position_independent set to true into -fPIC. The PIC lab creates a synthetic GCC provider and checks that the plan contains exactly one such argument. Planning does not inspect an executable or confirm target support.

~~~c
request.position_independent = true;
UmiStatus status = umi_compiler_provider_plan(&provider, &request, &plan);
if (status != UMI_STATUS_OK) return status;
~~~

This fragment requires initialized request, provider and plan storage. The complete lab supplies them. Setting the field to false leaves the driver’s defaults; it does not emit -fno-PIC. Position-independent executables and shared libraries can require additional choices. Do not equate an object-compilation switch with a finished deployment artifact.

## Refuse an unmapped combination

The lab changes the action to CHECK while retaining explicit PIC intent. This combination is not mapped and returns NOT_IMPLEMENTED. The previously valid plan remains byte-for-byte unchanged. Current MSVC and other unsupported mappings likewise must not silently discard the request. A clear refusal allows the caller to present the actual limitation.

## Review raw arguments too

A structured field expresses intent, but the low-level C request can also carry raw arguments. Contradictory raw options may alter a driver’s effective behavior. A product should review the complete plan and decide how it handles conflicting user-supplied options. The presence of one expected argument alone is insufficient evidence that a real compile used the intended policy.

## Exercise and verification

Write separate acceptance statements for plan mapping, actual object compilation and final linking. The supplied scenario checks the first. A platform exercise must choose a real compiler/target, preserve its diagnostics and inspect the resulting artifact using appropriate tools. Consult the compiler’s own documentation for target restrictions; record unsupported targets as limits rather than changing the request until a command happens to succeed.

## Source and practice

Use the [installed C23 lab guide](../../../../labs/native/framework-toolchain-selection/README.md) and [complete source](../../../../labs/native/framework-toolchain-selection/main.c). The examples are authored; no build or execution result is implied.

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Replace a compiler provider and profile together](22-synchronize-compiler-selection.md) · [Next: Qualify the installed client without confusing plans with execution](24-installed-toolchain-lab-qualification.md)

[HTML lesson](../../../courses/learning-build-systems/lessons/23-position-independent-compile-intent.html)

Sammy Hegab · Umicom Foundation · MIT
