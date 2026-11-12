<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/115-execute-forward-vm-paths-in-user-mode.md

PURPOSE:
Execute forward VM paths in user mode

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Execute forward VM paths in user mode

## Goal

Qualify the shared forward-branch runtime inside an isolated RISC-V user program. Keep three responsibilities separate: the bytecode validator admits the graph, the interpreter follows one path, and the Kernel owns the native process and its physical frames.

## Reuse the canonical runtime

The CVM envelope links Umicom C runtime sources. It does not carry another interpreter or compile source text inside the Kernel. Select the matching Umicom C source directory during configuration. Forward branches require the header capability UMC_FORWARD_BRANCH_PROFILE and canonical wire format 4.

The bytecode cannot issue a syscall or contain a native address. Its native envelope invokes EXIT after checking the result. A successful guest test therefore needs both a correct VM result and a correct user-to-Kernel transition.

## Follow the guarded program

CheckBranches in programs/cvm/main.c encodes eight records. The first pushes zero and the next conditionally jumps to record 6. Records 2–5 contain a division that would fail if selected. Record 6 pushes zero, and record 7 returns it.

The selected path is 0, 1, 6, 7. It consumes four instructions, not eight. A trace records those original indices. With only three fuel units, the attempted RETURN is reported as exhausted and the completed result remains unchanged. Selecting the other arm evaluates division by zero and produces an arithmetic error instead.

## Read each selector's obligation

| Selector | Expected boundary |
| --- | --- |
| 19 | Skip the division and return zero with four trace rows |
| 20 | Select the division and retain its arithmetic failure |
| 21 | Exhaust fuel at RETURN after a forward jump |
| 22 | Reject format-4 operations mislabeled as format 3 |
| 23 | Reject a local initialized on only one incoming arm |
| 24 | Reject a backward target |
| 25 | Reject unequal stack depths at a join |

Earlier selectors remain intact. kernel/cvm_validation.c runs all selectors at O0 and O2. For each process it checks the expected exit value, user-mode trap, one EXIT call, refusal of terminal reentry, destruction and restored allocated/free/reserved frame counts.

## Build before the guest fixture

Use a fresh or source-matching mirror build directory and the documented RISC-V toolchain. The following commands assume a configured build-kernel directory with CVM enabled and the intended Umicom C source selected:

~~~powershell
cmake --build .\build-kernel --target umicom-kernel-evidence --parallel 4
ctest --test-dir .\build-kernel -R "^kernel[.]riscv64[.]cvm$" --verbose --output-on-failure --no-tests=error
~~~

Run each command separately and stop on errors. The explicit build completes dependencies before the bounded build.current fixture. Expect the fixture and guest test to pass, markers for selectors 0 through 25 under both optimization headings, and UMICOM_KERNEL_CVM_READY. Read the exact selected source/ELF identities alongside the output.

## Diagnose the correct layer

A failed build fixture means the dependent guest did not run; it is neither a guest pass nor proof of a VM runtime failure. An undefined hosted symbol at O0 can indicate an accidental compiler-generated library dependency. A user trap or frame leak is a Kernel-envelope problem even when the host VM tests pass. A wire-profile refusal suggests a mismatch between artifact and runtime before any guest arithmetic starts.

The validator now uses bounded per-record stack-depth and local-initialization arrays. Keep their storage within the native user stack contract and qualify both optimization settings. Do not enlarge a stack or weaken a join check merely to conceal an unexplained failure.

## Exercise

Explain why the one-arm local fixture is rejected before the trace capacity is considered. Then compare a host trace with a guest selector result: identify which evidence proves path behavior, which proves process cleanup, and what neither proves about physical hardware. QEMU user-mode qualification does not validate a real board, a NIC, a filesystem or other Kernel subsystems.

[Course contents](index.md) · [Previous lesson](114-qualify-private-vm-locals-in-user-mode.md)
