# Software engineering and administration

Learn Git, testing, databases, networking, modular design and system administration.

- [16. Git: remember and review your changes](16-git.md)
- [17. Your first Umicom contribution: fork, change, review, merge](17-first-pull-request.md)
- [18. Compilers, CMake, Ninja and automated tests](18-build-and-tests.md)
- [19. Databases: store tasks, accounts and transactions](19-databases.md)
- [20. System administration on Windows and Linux](20-system-administration.md)
- [21. Networks, HTTP and application APIs](21-networks-and-apis.md)
- [22. Modules, interfaces and software design patterns](22-modules-and-patterns.md)

[Explore the practical source files](../../labs/index.md)

## Deeper build and runtime workshops

- [37. CMake, compilers and build systems](37-cmake-and-build-systems.md)
- [38. Package managers and useful C libraries](38-package-managers-and-c-libraries.md)
- [39. Build a lightweight web server in C](39-build-a-c-web-server.md)
- [41. Other compiled languages and interoperability](41-other-compiled-languages.md)
- [42. HTTP byte scanning in C and Assembly](42-http-and-assembly.md)
- [43. Prepare a reliable website build environment](43-prepare-a-website-build-environment.md)
- [44. Assemble a book from Markdown using C23](44-native-book-manuscripts.md)
- [45. How a C program starts another program](45-run-external-build-tools-safely.md)
- [46. Diagnose a failing build tool](46-diagnose-a-failing-build-tool.md)
- [47. Test child processes with CTest](47-test-child-processes-with-ctest.md)
- [48. Validate a book before publishing](48-validate-a-book-before-publishing.md)

## Publish and verify the educational website

- [50. Publish learning and books together](50-publish-learning-and-books-together.md)
- [51. Verify publication in C23](51-verify-publication-in-c23.md)
- [52. One GitHub Pages deployment](52-one-github-pages-deployment.md)

## Native process and linker troubleshooting

- [56. Diagnose a Windows programme path containing spaces](56-test-windows-process-paths.md)
- [57. Read object files and follow the linker](57-examine-object-files-and-linkers.md)

## Build and publication exercises

- [61. Organise a C library with CMake](61-build-a-c-library-with-cmake.md) — compile an owned Notes model once and link it to a demonstration and tests.
- [62. Build the educational website before serving it](62-build-and-preview-the-education-site.md) — generate `site/index.html`, then preview using the native C server.
## Website configuration and adversarial testing

- [63. Fix a YAML website configuration](63-repair-a-mkdocs-configuration.md)
- [66. Reproduce parser failures with deterministic tests](66-fuzz-bytes-and-check-contracts.md)

## Verify learning content with native C23

- [70. Check website navigation in C23](70-check-website-navigation-in-c23.md) — run read-only validation before rendering.
- [71. Compiler diagnostics and static analysis](71-compiler-diagnostics-and-static-analysis.md) — use GCC and Clang to review C23 source.

## Compilers, object files and binary interfaces

- [72. From C23 source to machine code](72-source-to-machine-code.md) — observe preprocessing, Assembly, object compilation and linking.
- [73. Build and link a reusable C23 library](73-link-one-c-library.md) — use one implementation from an application and independent tests.
- [74. Read ELF, PE and COFF headers](74-read-elf-pe-coff-with-c23.md) — inspect binaries without executing them.
- [75. Understand calling conventions and the stack](75-abi-stack-and-calling-conventions.md) — connect C function declarations to real processor registers.

## Native linking, archives and cross-compilation

- [77. Understand static libraries and archive files](77-understand-static-archives.md) — inspect real `.a` files without executing them.
- [78. Understand public symbols and linker maps](78-symbol-visibility-and-linker-map.md) — trace a function from a C header to a selected object.
- [79. Relocations, sections and position-independent code](79-relocations-and-position-independent-code.md) — understand unresolved addresses and native section layout.
- [80. Cross-compile C23 and Assembly for RISC-V64](80-cross-compile-c23-riscv64.md) — compile objects without running foreign instructions.
- [81. Install and package a native C23 programme](81-install-and-package-a-native-c-program.md) — install a library, header and executable into a private location.

## Native ELF symbols, relocations and kernel linking

- [82. Read ELF symbols from a C23 build](82-inspect-elf-symbols-in-c23.md) — identify public definitions, private helpers and unresolved references without executing an object.
- [83. Follow relocations through linking](83-follow-relocations-and-linker-decisions.md) — connect a C23 caller to Assembly and explain the linker's address adjustments.
- [84. Understand sections and linker scripts](84-read-sections-and-linker-scripts.md) — examine `.text`, `.rodata`, `.data`, `.bss` and the actual Umicom Kernel boot path.
- [85. Check cross-compilation and the ABI](85-cross-compilation-and-abi-checks.md) — distinguish host and target, ELF and COFF, and calling conventions.
- [86. Test native binary-file readers](86-test-native-binary-boundaries.md) — reject malformed offsets, preserve reports after failure and use adversarial tests.


## ELF loading, physical memory and virtual addresses

- [87. From an ELF file to a memory-loading plan](87-read-elf-program-headers-and-load-plan.md) — read loadable segments without executing the file.
- [88. Allocate and protect physical memory pages](88-physical-pages-and-frame-ownership.md) — track free, reserved and allocated 4 KiB frames.
- [89. Translate a virtual address with RISC-V Sv39](89-sv39-virtual-address-translation.md) — follow three page-table indices to a physical frame.
- [90. Page permissions, privilege and faults](90-memory-permissions-traps-and-privilege.md) — understand R/W/X and why invalid accesses are refused.
- [91. Follow actual Umicom Kernel memory source](../06-umicom/91-follow-umicom-kernel-memory-source.md) — compare the classroom exercises with the original RISC-V Kernel.

## Processes, page faults and executable protection

- [92. Understand a process address space](92-understand-a-process-address-space.md) — follow executable regions into a fictional process address space.
- [93. Understand page faults in C23](93-understand-page-faults-in-c23.md) — distinguish unmapped access from permission refusal and preserve output on failure.
- [94. Review executable-memory protection](94-review-executable-memory-protection.md) — inspect ELF byte ranges and page-rounded W^X conflicts through the Framework's C23 audit.
- [95. Model a process lifecycle](95-model-a-process-lifecycle-in-c23.md) — run a small state machine with explicit transitions and revision checks.

## System calls, IPC and message ownership

- [97. How a programme requests a kernel service](97-how-programmes-request-kernel-services.md) explains user mode, kernel mode, system-call checks and the RISC-V `ecall` instruction.
- [98. Build a copied-message channel](98-build-a-copied-message-channel.md) develops a bounded FIFO queue in C23 with explicit ownership and no partial delivery.
- [99. Inspect an IPC trace](99-inspect-an-ipc-trace-with-c23.md) reads a versioned byte format and tests record order, capacity and truncation through a Framework-owned C23 inspector.
- [100. Design checked service requests](100-design-checked-service-requests.md) implements a hosted service dispatcher with permissions, revision checks and failure-atomic updates.

## Scheduling and blocking service requests

- [102. How the scheduler gives each task a turn](102-understand-round-robin-scheduling.md) — distinguish Ready, Running and Waiting using one C23 queue.
- [103. Wait and wake without busy-spinning](103-wait-and-wake-without-spinning.md) — build a Notes service that waits for copied messages.
- [104. Protect task handles and service lifetimes](104-task-handles-and-service-lifetimes.md) — refuse stale handles and cancel a wait without erasing accepted work.
- [105. Inspect a scheduling trace with C23](105-inspect-a-scheduler-trace-with-c23.md) — validate bounded binary transitions with the Framework-owned inspector.


## Monotonic time, events and Kernel scheduling

- [107. Understand monotonic clocks and checked deadlines](107-monotonic-clocks-and-checked-deadlines.md) — distinguish wall time from elapsed time, reject deadline overflow and run a deterministic C23 timer.
- [108. Understand event signals, waits and recovery](108-event-signals-waits-and-recovery.md) — manual/auto-reset events, coalescing, lost wake-ups and cancellation.
- [109. Build a timed Notes service in C23](109-compose-a-timed-service-wait.md) — compose the existing scheduler and logical clock without duplicating their implementations.
- [110. Inspect a timer trace using native C23](110-inspect-a-timer-trace-in-c23.md) — read a versioned binary trace, check event keys and deadlines, and examine malformed records.

## Interrupt ownership and safe recovery

- [112. Who owns an interrupt? Critical sections and leases](112-interrupt-ownership-and-critical-sections.md) — discover how a privileged source can have one owner and a checked lifetime.
- [113. Cancellation is not acknowledgement](113-cancellation-is-not-acknowledgement.md) — distinguish cancelling future work from completing accepted events.
- [114. Restore a service after a failure](114-restore-a-service-after-failure.md) — compose one reusable C23 ownership model with an explicit in-memory revision checkpoint.
- [115. Inspect interrupt ownership traces](115-inspect-interrupt-ownership-traces.md) — decode a bounded binary source trace with a Framework-owned read-only C23 command.
- [116. Follow the real Umicom Kernel interrupt source](../06-umicom/116-read-umicom-kernel-interrupt-and-recovery.md) — read the actual RISC-V Assembly and C23 authority checks.

## Diagnostics, driver lifetimes and retained evidence

- [117. Understand interrupt diagnostics and event order](117-interrupt-diagnostics-and-event-order.md) — reconstruct an incident from owner, generation and sequence values.
- [118. Build a driver lifecycle from reusable C23 services](118-build-a-driver-lifecycle.md) — combine existing ownership and service-recovery contracts into one fictional driver.
- [119. Keep diagnostic records in a bounded C23 ring](119-keep-diagnostics-in-a-bounded-ring.md) — bound memory usage, account for overwritten records and return owned snapshots.
- [120. Inspect a chained evidence trace with SHA-256](120-inspect-a-chained-evidence-trace.md) — validate a versioned, read-only file with explicit hash-chain and state checks.


## Device I/O requests and completion ownership

- [122. Follow a device request from submission to completion](122-device-io-from-submit-to-completion.md) — understand why accepted work is not yet a completed result.
- [123. Build a bounded completion queue](123-build-a-bounded-completion-queue.md) — implement a copied FIFO ring that does not overwrite accepted results.
- [124. Cancel, quiesce and release device work](124-cancel-quiesce-and-release-device-work.md) — distinguish cancellation intent, terminal completion and safe resource release.
- [125. Inspect a device I/O trace in native C23](125-inspect-device-io-traces-in-c23.md) — use a bounded read-only state-machine validator.


## Device discovery, memory-mapped I/O and VirtIO

- [127. Discover hardware by reading a device tree in C23](127-inspect-device-tree-in-c23.md) — inspect a bounded FDT blob without touching hardware.
- [128. MMIO and transport feature negotiation](128-mmio-and-transport-negotiation.md) — understand register addresses, permissions and supported device features.
- [129. DMA buffer ownership](129-dma-buffer-ownership.md) — keep shared buffers alive after publication, cancellation and timeout.
- [130. VirtIO split queues in C23](130-understand-virtio-split-queues.md) — build a safe classroom queue and check completion ownership.


## Block storage, filesystems and durable Notes data

- [132. From device sectors to files and directories](132-from-device-sectors-to-filesystems.md) — follow a Notes Save operation through a filesystem, block driver and persistence boundary.
- [133. Build a write-back sector store in C23](133-build-a-writeback-sector-store.md) — stage and flush 512-byte sectors, simulate interruptions and inspect exported images.
- [134. Write-ahead journalling and recovery in C23](134-write-ahead-journalling-and-recovery.md) — commit a Notes revision in the correct order and replay after a controlled interruption.
- [135. Filesystem paths, directories and metadata](135-filesystem-paths-and-metadata.md) — validate path authority and understand how file contents and directory metadata relate.
- [136. Follow the actual Kernel storage stack](../06-umicom/136-follow-kernel-filesystems-and-storage.md) — compare classroom models with VFS, RAMFS, FAT16 and VirtIO ownership.


## FAT16 and native filesystem inspection

- [137. FAT16 boot sector and volume layout](137-understand-fat16-boot-sector-and-volume-layout.md)
- [138. Build a read-only FAT16 inspector in C23](138-build-a-read-only-fat16-inspector.md)
- [139. Follow a FAT cluster chain](139-fat-cluster-chains-and-file-content.md)
- [140. Write ordering, flush and recovery](140-write-ordering-and-filesystem-recovery.md)
- [141. Read the Umicom Kernel filesystem implementation](141-read-umicom-kernel-fat16-source.md)


## Virtual filesystems, descriptors and providers

- [142. How a VFS finds a file](142-how-a-virtual-filesystem-finds-a-file.md) — resolve a pathname, choose a mounted provider and open a Notes document.
- [143. Descriptors and shared positions](143-file-descriptors-open-descriptions-and-offsets.md) — distinguish filenames, file objects, open descriptions and generation-tagged tokens.
- [144. Build a Notes filesystem provider](144-build-a-notes-filesystem-provider.md) — copy bytes, preserve an unlinked open file and reject oversized writes.
- [145. Connect two storage providers](145-compose-two-filesystem-providers.md) — reuse one VFS with editable Notes and a read-only reference library.
- [146. Follow the Umicom Kernel VFS](146-follow-the-umicom-kernel-vfs.md) — examine the actual Kernel VFS, RAMFS, FAT16 and user-file ownership source.

## Process-owned files and networking in C23

- [147. How a process reads a file safely](147-process-owned-file-services.md) — trust boundaries, checked byte offsets and an actual VFS file read.
- [148. Checked copies and file lifetimes](148-checked-file-copies-and-descriptor-lifetimes.md) — accepted results, generation-tagged handles, cleanup and preserved output on refusal.
- [149. TCP/IP and native sockets](149-tcp-ip-and-native-c23-sockets.md) — IP addresses, ports, byte streams and an IPv4 loopback listener.
- [150. Parse HTTP/1.1 bytes safely](150-parse-http11-request-bytes-safely.md) — exact CRLF framing, counted buffers, Host checks, GET/HEAD and error responses.
- [151. Read the Umicom Kernel and Framework sources](151-connect-vfs-and-networking-to-umicom-source.md) — compare education-sized interfaces with the authoritative system components.
