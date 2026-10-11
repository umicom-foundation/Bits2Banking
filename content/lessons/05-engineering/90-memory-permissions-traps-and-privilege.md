# 90. Page permissions, privilege levels and faults

Page tables do more than convert addresses. They help determine whether code may **read, write or execute** memory. If a programme tries to do something that its mapping does not permit, the processor can raise an exception instead of silently completing the access.

This chapter builds on [Sv39 translation](89-sv39-virtual-address-translation.md) and prepares you to study Umicom Kernel's real exception paths.

## 1. Understand the permission bits

A RISC-V leaf page-table entry includes several individual bits:

| Bit | Name | Meaning in this lesson |
| --- | --- | --- |
| `V` | Valid | The entry may be used for translation |
| `R` | Read | Loads may be permitted |
| `W` | Write | Stores may be permitted, normally with `R` |
| `X` | Execute | Instruction fetches may be permitted |
| `U` | User | Determines whether user-mode accesses may use the page |
| `A` | Accessed | Tracks whether an access has occurred, or must be pre-set depending on hardware/software policy |
| `D` | Dirty | Tracks or authorises writes according to the platform's A/D handling |

The same physical memory may be mapped through multiple virtual addresses, and privileged access rules add further constraints. Do not interpret the three `R/W/X` bits as a complete security policy by themselves.

## 2. Give different regions different jobs

An application might have the following memory regions:

| Region | Typical initial permission choice | Reason |
| --- | --- | --- |
| Executable instructions | Read and execute | Changing executable bytes should not be an ordinary data write |
| Constant data | Read only | Code should not accidentally overwrite constants |
| Mutable data and stack | Read and write | Variables and stack frames change during execution |
| Unmapped region | No mapping | The programme has no valid object there |

A production system may use additional protections such as write XOR execute (W^X), privilege restrictions and guarded stack regions. Policy decisions depend on the actual kernel, CPU and loader.

## 3. Predict the result of an access

Open [`test_sv39.c`](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/sv39-address-translation/test_sv39.c). The tests ask for a read from a mapped data page, an attempted instruction fetch from that same non-executable page, and a read from an unmapped neighbouring page.

For the initial readable/writable mapping, predict:

```text
READ  from the mapped page       -> permitted
WRITE to the mapped page         -> permitted
EXEC  from the mapped page       -> denied
READ  from an unassigned page    -> no mapping
```

The C23 model returns named result values rather than raising a real CPU page fault. A real CPU would report a *trap* to privileged software, which must identify its cause and decide what to do next.

## 4. Meet machine, supervisor and user modes

On RISC-V systems, *machine mode* (M-mode) provides the highest architectural privilege. Many operating systems run their kernel services in *supervisor mode* (S-mode), with ordinary programmes in *user mode* (U-mode). The exact boot flow and available modes depend on firmware and system design.

The original Umicom Kernel first-boot path begins in machine mode on QEMU RISC-V64 `virt`. It establishes a stack and starts C23 code. Later Umicom Kernel work introduces additional privilege transitions and controlled translation tests. Follow the actual repository source and documentation rather than assuming every research milestone has the same privilege model.

## 5. Understand `satp`, `sfence.vma` and traps

The supervisor address-translation register `satp` describes an active address-translation mode and root page-table address when used in an appropriate privilege configuration. In an Sv39 configuration, a processor may use a translation lookaside buffer (*TLB*) to remember recent translations. An `sfence.vma` instruction orders the processor's translation state after relevant page-table changes; software cannot assume that a changed PTE is instantly visible through stale cached translations.

The [Umicom Kernel hardware-backed translation guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/HARDWARE_ADDRESS_TRANSLATION.md) explains its controlled use of `MPRV` for translated loads and stores while the instruction stream remains in machine mode. It also discusses trap safety and a temporary Physical Memory Protection configuration used for that specific test. Do not copy the temporary permissive protection setup into an operating-system security policy.

## 6. Exercise

A Notes application stores editable text and a compiled callback function. Explain why the editable data should not normally need execute permission, and why executable code should not normally need write permission after loading. Now imagine the user supplies an address with incorrect sign-extension bits in Sv39. Should a page-table walker try to use its index fields, or refuse the address first? The safer choice is to reject it before accessing page tables.

## 7. Continue

[Chapter 91](../06-umicom/91-follow-umicom-kernel-memory-source.md) connects the concepts to the corresponding Umicom Kernel files and build commands.
