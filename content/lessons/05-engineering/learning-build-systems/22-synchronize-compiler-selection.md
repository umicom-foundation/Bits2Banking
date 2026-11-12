![Umicom](../../../assets/branding/umicom-logo.svg)

# Replace a compiler provider and profile together

Toolchain discovery and compiler planning serve different purposes. A toolchain profile describes selected tools. A compiler provider maps requests into arguments for a driver family. A compiler profile supplies a named target and policy. Keeping these records synchronized prevents a preview from using yesterday’s driver path.

## Follow the explicit bridge

~~~c
UmiStatus status = umi_compiler_centre_sync_toolchain(
    centre, toolchain, "selected");
if (status != UMI_STATUS_OK) return status;
~~~

The initialized centre remains caller-owned. The bridge admits an explicitly selected GCC, Clang or MSVC C compiler, converts its metadata and publishes the provider and named compiler profile together. The operation activates that profile. Missing or failed selections are unavailable; unrelated tool kinds are not silently interpreted as GCC.

## Repeat a selection

In the Compiler lab, both synthetic profiles use the selected identifier and GCC family. The second operation changes the executable path. The checks require one provider and one profile, then inspect both the provider executable and profile linker driver. A test that only counts profiles would miss a stale provider; a test that only reads the active identifier would miss both stale paths.

## Understand replacement limits

Synchronization uses Framework debug defaults. A product that needs a custom policy should construct it deliberately and call umi_compiler_centre_configure_profile. That operation stages provider replacements and validates the candidate profile before publication. Readers and writers remain caller-serialized. It preserves the centre on refusal, but does not make borrowed pointers safe across later mutation.

Other providers and profiles remain in the centre. Changing from GCC to Clang does not delete GCC if another profile still needs it. Previously planned commands also remain historical records until explicitly replanned. Configuration publication does not silently rewrite the compilation database or execute a compiler.

## Exercise and recovery

Extend your decision table with repeated same-family selection and a family change. Predict provider count, active profile provider and the status of old commands. For an unsupported selection, record the refusal and keep the previous centre. Do not substitute a different compiler merely because it is available; that would change the user’s requested toolchain. Review the existing compiler-publication lessons for command refresh and custom policy planning.

## Source and practice

Use the [installed C23 lab guide](../../../../labs/native/framework-toolchain-selection/README.md) and [complete source](../../../../labs/native/framework-toolchain-selection/main.c). The examples are authored; no build or execution result is implied.

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Keep borrowed process pointers inside their receiving owner](21-environment-pointer-ownership.md) · [Next: Express position-independent compilation as an explicit request](23-position-independent-compile-intent.md)

[HTML lesson](../../../courses/learning-build-systems/lessons/22-synchronize-compiler-selection.html)

Sammy Hegab · Umicom Foundation · MIT
