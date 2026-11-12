<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/108-distinguish-input-identity-from-guest-evidence.md

PURPOSE:
Distinguish input identity from guest evidence

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Distinguish input identity from guest evidence

A host tool and a RISC-V guest can use the same runtime source while producing different binaries. A checksum from one side cannot certify execution on the other. Keep the input observation, target artifact and guest transcript connected but distinct.

## Read the existing CVM boundary

Open cmake/CvmEvidence.cmake in the Kernel. It inventories named Umicom C runtime files, selected Kernel CVM sources, the workload recipe, and the O0 and O2 ELF files. Capture writes a record; verify compares the current identities with that record. A missing or changed input refuses qualification.

The compiler's new standalone configuration record answers a narrower host question. It observes a declared source tree and selected tools at configure time. It does not contain the Kernel's user-mode ELF identity, CPU configuration or serial transcript.

## Trace a change across repositories

1. Imagine changing the runtime's capability profile header.

2. The host compiler input observation should become stale until explicitly refreshed.

3. The Kernel CVM receipt includes that header separately. Its own current-input verification must also be rerun.

4. Rebuild the relevant guest workload, then execute its qualified QEMU check at both optimization levels.

5. Keep the complete serial evidence and the exact ELF identities with the result.

A passing host unit test does not replace steps 3 through 5. A passing emulator run does not establish behavior on real hardware.

## Use the existing targeted checks

After configuring the Kernel's documented RISC-V build and building its tests, run the focused group in your selected build directory:

~~~powershell
ctest --test-dir build -R 'kernel.(riscv64.cvm|cvm.evidence)' --output-on-failure --no-tests=error
~~~

Replace build with the directory you actually configured. CTest may add a required build fixture. Read the reported test names and distinguish setup from guest execution. A missing tool or failed setup is not a successful guest result.

## Explain what remains unknown

The current Kernel qualification record keeps sourceStableDuringBuildVerified false. Taking a checksum after a build does not prove the source remained unchanged while the compiler read it. A stronger future workflow must bracket the build, compare observations and bind the resulting artifact; simply adding another checksum field cannot establish that sequence.

## Exercise and recovery

Consider four observations: current source matches; the ELF hash changed; a transcript contains an old success marker; the emulator exits unsuccessfully. Which one authorizes a pass? None on its own. The artifact mismatch and failed execution require investigation, and the old transcript cannot be reused.

Preserve the earlier record and failing transcript. Review which source or tool changed, rebuild through the configured workflow and collect fresh execution evidence. Do not rewrite the stored ELF hash merely to silence the verifier. These checks connect the evidence; they do not authenticate an untrusted machine or prove the Kernel is ready for deployment.

[Course contents](index.md) · [Previous lesson](107-separate-a-guest-runtime-from-source-grammar.md) · [Next lesson](109-admit-udp-with-an-explicit-checksum-policy.md)
