<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/120-qualify-shared-vm-slices-in-a-guest.md

PURPOSE:
Qualify shared VM slices in a guest

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Qualify shared VM slices in a guest

[Course contents](index.md)
A runtime can pass on the development computer and still fail in a freestanding guest because its environment differs. Hosted tests use the host C library and process model. A Kernel guest has its own executable format, system calls, stack limits and startup path. Qualification should identify which environment actually executed the code.


## 1. Share the interpreter implementation

The CVM guest uses canonical Umicom C runtime sources instead of a second interpreter. Its slice fixtures check normal completion, arithmetic refusal, fuel exhaustion and invalid budgets. The fixture workspace is static so a large machine structure does not consume the guest's small call stack.


## 2. Understand selector results

A selector is a small input value choosing one guest exercise. New selectors 56 through 59 exercise slices. Their distinct return markers allow the Kernel-side validator to distinguish the expected path from a generic process exit. A marker is useful only when the test also checks the process and saved-frame behavior around it.

~~~text
56 -> bounded completion
57 -> arithmetic fault after successful prefix
58 -> lifetime fuel exhaustion
59 -> invalid slice-budget preservation
~~~


## 3. Check both host and guest

tests/cvm_runtime calls the guest entry contract in a host process. This catches envelope dispatch mistakes and missing runtime linkage quickly. The RISC-V CVM guest test boots the configured image under QEMU and checks the actual guest path. Neither should be described as the other.

~~~powershell
Set-Location C:/umicom/umicom-kernel
cmake -S tests/cvm_runtime -B build/cvm-envelope-host -G Ninja -DCMAKE_C_COMPILER=gcc -DUMICOM_C_SOURCE_DIR=C:/umicom/umicom-c
cmake --build build/cvm-envelope-host --parallel 2
ctest --test-dir build/cvm-envelope-host --output-on-failure --no-tests=error
~~~

Run commands separately and stop on errors. Use the Kernel's documented RISC-V toolchain configuration for the guest build. Building a host test is not a substitute for producing the guest image.


## 4. Protect the source-to-image relationship

A build receipt records fingerprints of the runtime source, guest fixtures, build recipe and image. The evidence checker rejects changed or missing required inputs. Adding a new fixture header requires adding it to that identity list. Otherwise an old image could appear current after the fixture changes.

A negative test must also verify why an operation failed. For example, deleting the slice fixture should produce the missing-source diagnostic. Merely checking for any nonzero exit could hide an unrelated tool failure. The evidence regression keeps that distinction explicit.


## 5. Interpret the result narrowly

Guest slice success establishes bounded execution for the exercised integer VM cases. It does not establish full C23 support, native-code generation, arbitrary host-language interoperability or a production scheduler. Keep those features as separate implementation and qualification tasks.

Exercise: change a required fixture after building but before qualification. What should happen? The evidence check should refuse the stale image. Rebuild from the changed source and capture a fresh receipt before interpreting a new guest result.


[Previous lesson](119-test-wraparound-and-refused-acknowledgments.md)

[Next: Encode a UDP frame without sending it](121-encode-a-udp-frame-without-sending-it.md)
