![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

[Umicom icon](../../../content/assets/branding/umicom.ico)

# Trace a native build result from source to evidence

The three Studio workflow lessons use this C23 project to examine object
linkage, exact process results, and a saved artifact identity. It is a
self-contained practice project. The installed Framework SDK and an active
Studio session are optional for reading the lessons.

Run from the Bits2Banking checkout with a C23 compiler, CMake and Ninja on
your build profile.

```powershell
cmake -S labs/framework/studio-build-evidence -B build/studio-build-evidence -G Ninja
cmake --build build/studio-build-evidence
ctest --test-dir build/studio-build-evidence --output-on-failure --no-tests=error
```

<!-- Former count for the initial digest suite retained for review.
Expect six tests.
-->
Expect thirteen tests when running both groups. The digest group has six tests. The changed-artifact and invalid-record tests succeed by
observing their exact expected refusals. The build-owned fixture is under
`build/studio-build-evidence/fixtures`.

Use a different build directory for the intentionally broken link in the
first lesson. The normal build directory stays available for comparison.
The C program compares digest text supplied by its caller. The CMake fixture
computes hashes from known classroom bytes. Neither step determines who
authored a file or whether its contents are suitable for release.

## Read a status in three forms

Build the `umicom-lab-status32` target in the same directory. Run only the status group with this command.

~~~powershell
ctest --test-dir build/studio-build-evidence --output-on-failure --no-tests=error -R "^bits[.]studio[.]status32[.]"
~~~

The valid signed, unsigned and hexadecimal cases produce the same report. The executable accepts one input and does not start a debugger.
