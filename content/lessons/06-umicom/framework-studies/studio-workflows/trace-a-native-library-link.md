![Umicom](../../../../assets/branding/umicom-wordmark.svg)

[Umicom icon](../../../../assets/branding/umicom.ico)

# Trace a missing native library symbol

[Previous lesson](source-navigation-commands.md) · [Next lesson](qualify-an-exact-test-exit.md)

A source file can compile while its executable still fails to link. Use the exact archive and symbol in a small C23 practice project to find which build stage stopped.

In a C project the header gives the caller a function declaration. The compiler uses its parameter and return types to produce an object file. During linking, the linker must find a definition in an input object or library. A static archive is a collection of such objects.

In this project, evidence.c owns one external definition and the CMake target umicom_lab_evidence owns the archive. The main.c translation unit includes only evidence.h. Keep both observations separate so fixing an include path does not masquerade as a link fix.

The option in the disposable build removes exactly one dependency edge. It leaves the declaration and both source files intact. That makes the intended missing provider distinguishable from a missing header, malformed C syntax, or a missing compiler.

After reproducing the failure, compare the verbose link command in both folders. A learner should be able to point to the extra library in the normal command and explain why it can supply the unresolved name. The exact archive extension can vary by toolchain.

To restore the working exercise, configure the disposable folder with -DUMICOM_LAB_OMIT_PROVIDER=OFF and build the same target. Before gathering new test results, verify which executable belongs to that folder.

## Repeat the exercise

```powershell
cmake -S labs/framework/studio-build-evidence -B build/studio-evidence -G Ninja
cmake --build build/studio-evidence --target umicom-lab-evidence --verbose
cmake -S labs/framework/studio-build-evidence -B build/studio-evidence-omit -G Ninja -DUMICOM_LAB_OMIT_PROVIDER=ON
cmake --build build/studio-evidence-omit --target umicom-lab-evidence --verbose
```

The normal executable links. The disposable build stops at the link step and identifies UmicomLabCompareEvidence as unresolved. The linker wording depends on the compiler. In Studio, inspect the first relevant link line before moving to tests.

If the compiler cannot find evidence.h, the exercise has stopped earlier than intended. Confirm that the checkout has all six laboratory files and both build directories point to the same source folder.

[Back to course](../../../../courses/framework-and-finance/studio-workflows/index.html)
