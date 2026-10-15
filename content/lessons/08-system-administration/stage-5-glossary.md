# Stage 5 glossary — Virtual machines and safe deployments

**Architecture** — Processor instruction set required by an executable, such as x86-64 or RISC-V64.  
**ABI** — Rules for how compiled components interact at the binary boundary.  
**Artifact** — A result produced by a build, such as an executable or packaged file.  
**Baseline** — A recorded known state used to interpret later changes.  
**Build directory** — Location of generated CMake, compiler, linker and test files.  
**Capture ID** — A classroom identifier that orders observations; it is not a trusted timestamp or signature.  
**Configuration drift** — A difference between expected and actual settings.  
**CMake preset** — A named set of project build settings.  
**DLL** — Windows shared library loaded at run time.  
**Emulator** — Software that reproduces a machine's hardware behaviour.  
**Guest** — Operating system instance running inside a VM or emulator.  
**Host** — The real computer and operating system running the virtual machine.  
**Hypervisor** — Technology that supervises virtual machines.  
**Image** — A file representing installation media, a disk, a filesystem or other system artefact.  
**Install prefix** — Destination root for installed build output.  
**Liveness** — Evidence that a process is active or responding, not necessarily useful.  
**Least privilege** — Limit an identity to permissions necessary for its task.  
**QEMU** — Emulator and virtualisation program used in Umicom kernel laboratories.  
**Readiness** — Evidence that required dependencies are available so work can be accepted.  
**Relocation** — Starting an application from an installation location different from its original build folder.  
**Rollback** — A controlled return to a previously accepted system state with later verification.  
**Root filesystem** — Main user-space directory tree used by a Linux system.  
**SHA-256** — Cryptographic digest algorithm; comparing an independently trusted checksum can detect changes.  
**Snapshot** — Recorded VM state; not an automatic substitute for host backups.  
**Staging** — Copying built files into a controlled location before wider release.  
**Toolchain** — Compiler, linker and build tools needed for a target.  
**Virtual disk** — File presented to a guest operating system as storage.  
**VM** — Virtual machine with virtual hardware and a guest OS.

A **claimed hash** is not a **computed hash**. Update 42's native evidence model receives claimed values; its tests never claim to have checked a real on-disk package.
