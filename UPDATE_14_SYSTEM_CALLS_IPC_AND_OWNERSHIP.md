# Bits2Banking — Update 14: System calls, IPC and message ownership

## What you can build

The first exercise builds a bounded C23 channel for Notes events. The channel owns complete copied payloads and refuses incomplete receives, unauthorised recipients and sends to a full queue. The second exercise builds a small hosted service dispatcher that reads a training clock or records a fictional Notes event after checking rights, revision and input bytes. Both exercises deliberately remain in one user-space programme; they do not claim to cross a hardware privilege boundary.

The Framework-owned `umicom-education` utility gains a new native C23 command:

```text
umicom-education ipc-trace --file PATH
```

It inspects the **educational** `UMIIPC1` trace format, validates lengths and FIFO order and prints a bounded report. It never sends or receives real IPC messages. The format is not the Umicom Kernel syscall or IPC ABI.

## New lessons

- [97. How a programme asks the operating system for a service](content/lessons/05-engineering/97-how-programmes-request-kernel-services.md).
- [98. Build a copied-message channel in C23](content/lessons/05-engineering/98-build-a-copied-message-channel.md).
- [99. Inspect a bounded IPC trace using native C23](content/lessons/05-engineering/99-inspect-an-ipc-trace-with-c23.md).
- [100. Design a checked service request in C23](content/lessons/05-engineering/100-design-checked-service-requests.md).
- [101. Follow IPC ownership through Umicom Kernel](content/lessons/06-umicom/101-follow-umicom-kernel-ipc-ownership.md).

Source laboratories are under `labs/native/bounded-channel/` and `labs/native/syscall-dispatch/`. The RISC-V `ecall` source file in the latter is for inspection only and is **not** linked into the hosted programme. Video scripts 30 and 31 are ready for recording; accompanying illustrations are editable SVG files.

## Why the source stays in two repositories

Umicom Framework owns the reusable, bounded C23 trace inspector and its tests. The educational repository owns the instructional application and explanation. Actual Umicom Kernel IPC remains in the independent `umicom-kernel` repository, where it enforces protected handles, task identity, user-memory validation, channels and blocked-call lifetimes.

No existing Framework public interface, historical manuscript, Umicom Kernel file, original *Islam: Blueprint for Life* chapter, website deployment workflow or BookForge implementation is deleted or replaced by this update. The navigation additions preserve the original volume and every earlier chapter.

## Verification boundary

Linux qualification uses the accumulated Update 13 education-tool source baseline, compiled with GCC and Clang with AddressSanitizer/UndefinedBehaviorSanitizer. Windows UCRT64 compilation and the complete real MkDocs site must still be run on the developer's checkout. The generated CTest fixture is synthetic, not a captured operating-system or financial-system message. A passing lab does not establish that Umicom Kernel ran under QEMU.

For all commands and Git commit order, read [Update 14 Build, Test and Git](UPDATE_14_BUILD_TEST_AND_GIT.md).
