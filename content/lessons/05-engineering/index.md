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
