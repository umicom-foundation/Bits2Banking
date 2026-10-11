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
