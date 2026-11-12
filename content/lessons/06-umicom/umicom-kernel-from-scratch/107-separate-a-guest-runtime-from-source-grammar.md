<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/107-separate-a-guest-runtime-from-source-grammar.md

PURPOSE:
Separate a guest runtime from source grammar

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate a guest runtime from source grammar

## Before you begin
Complete the Kernel CVM and linked-profile lessons. Open programs/cvm/main.c, kernel/cvm_validation.c and the sibling Umicom C profile header. Keep the configured Kernel build and its source checkout together. This is a RISC-V user-mode validation workload, not a native C compiler running inside the Kernel.

## A compiler feature need not be a runtime feature
The hosted Umicom C compiler now recognizes hexadecimal and binary integer spellings. Both become ordinary PUSH instructions containing signed values. The freestanding runtime executes those instructions; it contains no source lexer.

That separation lets a Kernel program use a small checked interpreter without linking a hosted command-line compiler or adding file-system and allocation dependencies. A source-level feature can be useful to developers while adding no new runtime operation.

## Follow selector 13
The CVM workload keeps its existing selectors and uses selector 13 for linked runtime capabilities. It queries the library that is actually linked into the RISC-V program. The required mask includes arithmetic, comparison, tracing and inspection. It excludes logical-not source lowering and the hexadecimal/binary source bits.

~~~c
const uint32_t features = umc_runtime_profile(UMC_PROFILE_FEATURES);
const uint32_t source_only = UMC_FEATURE_HEXADECIMAL_LITERALS |
    UMC_FEATURE_BINARY_LITERALS;
/* The guest's real predicate requires (features & source_only) == 0. */
~~~

Read the complete predicate in the source. It also checks the API value, wire-version mask, program and stack limits, and zero results for unsupported properties. A matching feature mask alone is not the whole test.

1. Find the success sentinel returned by selector 13.
2. Find the Kernel code that invokes the workload and checks its returned value.
3. Follow the workload builds at O0 and O2.
4. Explain why a host profile query cannot prove this guest call happened.
5. Explain why a new header alone cannot add a function to an old linked library.

## Run the target-specific checks
From the configured Kernel source directory, use the build directory established by the Kernel setup guide. Stop after a failure.

~~~powershell
cmake --build build --parallel 4
ctest --test-dir build -R "kernel.(riscv64.cvm|cvm.evidence)" --output-on-failure --no-tests=error
~~~

The tests require the configured RISC-V toolchain and QEMU. Build-current and qualification-identity fixtures may be included automatically. Read the generated test list and actual result rather than assuming a fixed count on another checkout.

The guest transcript must reach the expected CVM completion markers. Separate evidence checks deliberately alter a copied source, header, image or recipe identity and require the stale evidence to be refused. These operate on isolated test fixtures. They do not modify the real source to manufacture a passing receipt.

## Why profile.h belongs in the receipt
Changing a feature definition can change the compiled predicate even when main.c is unchanged. The receipt therefore includes the public profile header among its input identities. Source identity, compiler flags, runtime source and final image are separate evidence. A successful boot does not make a stale source receipt current.

If identity checks fail, inspect the named input and rebuild from the intended checkout. Do not edit the expected digest to match a different binary without understanding its origin. If the guest returns the failure sentinel, inspect the actual runtime feature and limit implementation before weakening the predicate.

## What the result does not establish
This exercise qualifies the selected runtime query inside the configured guest at the exercised optimization settings. It does not claim self-hosting, full C23 support, compilation of source inside the Kernel, hardware-driver qualification or a physical-machine boot. Those are separate implementation and evidence tasks.

[Course contents](index.md) · [Previous lesson](106-require-a-complete-guest-test-transcript.md) · [Next lesson](108-distinguish-input-identity-from-guest-evidence.md)
