<!--
Umicom Bits2Banking
File: labs/native/c-library-composition/README.md

PURPOSE:
Native library composition and exact fixture bytes

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Native library composition and exact fixture bytes

This independent C23 lab demonstrates a linker collision between two components and verifies the exact representation of test data. It has no Framework dependency, does not install anything, and performs no file or network operations when its tests run.

## Prepare and build

Use an installed C23 compiler, CMake 3.24 or newer and Ninja. Run each command separately and stop on an unexpected error. From the repository root:

~~~powershell
cmake -S labs/native/c-library-composition -B build/c-library-composition -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/c-library-composition --parallel 2
ctest --test-dir build/c-library-composition --output-on-failure --no-tests=error
~~~

The expected result is five passing tests. Two executables link the archives in opposite orders. Three cases inspect hexadecimal escape boundaries, unsigned UTF-8 bytes and signed zero. These tests qualify this teaching example, not a Framework application or a complete compiler.

## Inspect the boundaries

1. Read service_api.h. Its public functions name their units: source pages and catalogue bytes.
2. Read scanner.c and catalogue.c. Both use the short helper name Count, but their parameter lists and meanings differ. Private macro aliases emit different external symbols while retaining the local spelling.
3. Read composition_test.c. Both services are called, so both archive members must enter the final executable. Boundary checks include zero, the next page and multiplication overflow.
4. Read fixture_test.c. Its expected byte array is independent of the string spelling under test. A byte count includes UTF-8 octets; it is not a character count.

With GNU tools, inspect the archive symbols without executing either program:

~~~text
nm -g --defined-only build/c-library-composition/libbtb-source-pages.a
nm -g --defined-only build/c-library-composition/libbtb-catalogue-bytes.a
~~~

Look for BtbSourceInternalCount and BtbCatalogueInternalCount. Object-format naming conventions can decorate those spellings. A helper used only in one translation unit can instead be static; this lab keeps external linkage deliberately so the composition problem is visible.

## Reproduce the original class of failure

Keep the successful build directory. Configure a separate practice build with the explicit teaching switch:

~~~powershell
cmake -S labs/native/c-library-composition -B build/c-library-collision -G Ninja -DBTB_TEACH_UNQUALIFIED_HELPERS=ON
cmake --build build/c-library-collision --parallel 2
~~~

The second command is expected to fail at linking with duplicate Count definitions. Successful compilation of scanner.c and catalogue.c does not qualify their combination. Do not run an older executable after this expected failure. Return to build/c-library-composition for the valid variant; do not add an allow-multiple-definition linker option.

If configuration fails first, the collision experiment has not reached its intended stage. Resolve compiler discovery or generator errors before interpreting the result. If the negative build unexpectedly links, inspect the link line and symbol table: both public functions must be referenced and both archives must participate.

## Extend the exercise

Add a third component with its own private prefix. Give it a different unit and a boundary test. Then deliberately reference only one service and observe why an unreferenced archive member can conceal a duplicate. Keep that experiment separate from the two complete composition checks.

The compiler course continuation explains how these small examples relate to the native Framework command's library composition. Framework regression execution remains a separate qualification task.
