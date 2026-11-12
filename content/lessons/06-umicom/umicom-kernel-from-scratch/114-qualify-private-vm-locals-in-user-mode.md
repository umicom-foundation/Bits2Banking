<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/114-qualify-private-vm-locals-in-user-mode.md

PURPOSE:
Qualify private VM locals in user mode

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Qualify private VM locals in user mode

## Goal and boundary

Qualify a reusable integer VM inside a real RISC-V user process. Hosted tests cover language and runtime contracts. The Kernel test adds the native envelope, process boundary, optimization settings, trap result and frame lifetime. It does not compile source inside the guest or provide a full C operating-system application ABI.

## Read the two layers

In programs/cvm/main.c, CheckLocals supplies immutable instruction fixtures to the canonical Umicom C runtime. Its automatic bytecode, decoded instruction, trace and result buffers belong to the user program. The interpreted instructions have no syscall or pointer operations. The native envelope issues its exit syscall only after checking the VM result.

In kernel/cvm_validation.c, CheckImage loads the envelope and runs each selector in user mode. It checks the expected exit value, the user-mode environment-call trap, one accepted exit call, refusal to reenter an exited process, and physical frame counts before and after destruction.

## Follow the local selectors

| Selector | Contract |
| --- | --- |
| 14 | Store, read and overwrite slot 31; return 42 with eight trace entries |
| 15 | A later uninitialized read fails despite an earlier successful execution |
| 16 | Fuel ends before the second store; no result is published |
| 17 | Format-3 records mislabeled as format 2 are rejected |
| 18 | Slot index 32 is refused before execution |

Both O0 and O2 images run the same cases. O0 matters because aggregate copies can reveal unexpected hosted helper dependencies in a freestanding link. Immutable fixtures avoid introducing such copies simply to prepare a test.

## Build before measuring the guest

Follow the Kernel repository's toolchain guide to configure a mirror or disposable build with UMICOM_KERNEL_CVM=ON and UMICOM_C_SOURCE_DIR pointing to the intended Umicom C checkout. Use the real configured path for build below.

~~~powershell
cmake --build build --target umicom-kernel-evidence --parallel 2
ctest --test-dir build -R "^kernel.riscv64.cvm$" --verbose --output-on-failure --no-tests=error
~~~

Run commands separately and stop on an error. The explicit build completes changed dependent images before the bounded CTest build fixture runs. If that fixture times out, the dependent guest may be Not Run. Record those outcomes separately; neither is a VM assertion result. Finish the build, investigate any compiler or linker error, then rerun the fixture and guest without suppressing either.

## Read evidence rather than one green line

Expect cvm.optimization=O0 and O2, each followed by completed selectors 0 through 18, then UMICOM_KERNEL_CVM_READY. The earlier selectors still exercise arithmetic, trace failures, comparisons and linked capability queries. The source receipt binds the canonical runtime files, envelope, recipe and linked images used by this check.

Check the complete CTest result and the receipt verification before claiming target qualification. A source hash does not by itself prove execution. A generic ready marker without the expected cases can come from an older workload. This test uses the QEMU virt configuration; it establishes neither physical hardware boot support nor a desktop GUI workflow.

## Exercise and recovery

Compare the VM's instruction fuel with the Kernel process budget. The first bounds interpreted operations; the second bounds the native process run. Explain why one cannot replace the other. Then identify every condition checked after process destruction. A correct value of 42 is insufficient if the process leaves frames allocated.

Do not edit a captured runtime source and reuse its old receipt. Rebuild the affected images and capture current identity. Keep failures, skipped checks and successful retries as separate observations so the next developer can reconstruct what actually ran.


[Course contents](index.md) · [Previous lesson](113-prove-refusal-with-models-and-a-real-guest.md) · [Next lesson](115-execute-forward-vm-paths-in-user-mode.md)
