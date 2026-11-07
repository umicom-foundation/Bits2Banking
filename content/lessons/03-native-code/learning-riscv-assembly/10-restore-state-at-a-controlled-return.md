<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv-assembly/10-restore-state-at-a-controlled-return.md

PURPOSE:
Explain the lesson: Restore state at a controlled return.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Restore state at a controlled return

Returning from a trap changes processor state as well as control flow. The restoration sequence must keep its own working storage usable until the last required load.

## Prepare the source study

Open the section after UmicomRiscvMachineTrapDispatchGuarded in trap_entry.S. Read its comments beside the named status fields.

This lesson follows the current kernel path. It does not claim that every trap handler uses the same policy.

## 1. Use a checked result

The guarded dispatcher validates the frame and the policy result before assembly restores mepc and mstatus.

In this path the restored status keeps ordinary interrupts masked during the remaining loads and clears MPRV, so those loads do not inherit an unintended memory-access privilege setting.

The exact meaning of a status bit belongs to the processor architecture; the chosen allowed combination belongs to the kernel policy.

## 2. Restore working registers late

Temporary register t0 is used for control-register writes. Its interrupted value is restored near the end, after that work is complete.

The old sp is restored after the owned frame has supplied the needed values. Restoring it early would lose the reliable base address for subsequent frame loads.

## 3. Identify the final transition

The last instruction is mret. It performs the architecture's machine-mode trap return, including the defined interrupt-state transition.

An ordinary ret instruction returns through a general-purpose return-address register. It does not perform the same processor-control operation.

## Exercise

Mark every instruction that still needs the owned frame. Place the old-sp restoration after those accesses in your diagram.

Then explain why a second trap uses an emergency route while the first frame is being handled. Reusing the same storage could overwrite the evidence needed to understand the original failure.

## Evidence

A convincing change needs matched source review and target execution evidence. A host-side model can check policy decisions but cannot execute the machine-mode return instruction on an unrelated host.

Record any emulator configuration with your result; platform behavior and source identity are part of the observation.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/trap_entry.S). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-understand-stack-sentinels.md)


[Next: Walk an array with loads](11-walk-an-array-with-loads.md)
