<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/compiler-installed-qualification.md

PURPOSE:
Qualify the installed compiler client and report what it proves

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Qualify the installed compiler client and report what it proves

## Identify the dependency before running examples

This laboratory links Umicom::compiler from an installed Framework package. The source tree, installed headers and installed library must describe the same API revision. A successful edit in the mirror does not update an installation. Record which Framework source produced the prefix before interpreting compiler or test results.


Follow the laboratory README in order: qualify and install Framework, configure the client against that prefix, build it, and then run CTest. Stop after a failed build. Executing an older binary left in the output directory does not qualify the newly authored source. Preserve the complete output when reporting a mismatch.


~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\framework-compiler-ownership"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
ctest --test-dir build --output-on-failure
~~~


## Read the checker contract

Each of the seven scenarios compares complete standard output, exit zero and an empty error stream. The C client checks its expected invariants before printing them. An expected refusal is a passing scenario only when the previous owner also remains correct. This prevents a printed status label from standing in for actual preservation.


| Layer | Evidence needed |
| --- | --- |
| Authored source | Reviewed APIs, bounds, ownership and expected output |
| Installed client | Matching headers and library, successful build and seven executed checks |
| Compiler workflow | Real tool invocation, artifacts, diagnostics and results |
| Native application | Studio interaction and visible state under its approved design |


## Use the installed branding service

The CMake target calls the Framework application-branding helper. It supplies approved SVG resources and the Windows ICO resource through RC. The console lab requests NO_RUNTIME_DEPLOYMENT because it does not launch GTK. The paired lessons use the approved shared learning stylesheet with Segoe UI and Cascadia Code fallbacks.


Inspect staged resources and executable metadata during owner qualification. Font declarations and correct asset hashes are useful static evidence, but their actual appearance depends on fonts, operating-system behavior and the renderer. Keep visual inspection separate from successful C API observations.


## Write an honest conclusion

At authoring time the lessons, client and checks are statically reviewed only. Compiler, linker, scenario execution, resources and site rendering remain unverified. A future seven-case pass would establish this installed metadata client, not all compiler actions or complete Studio functionality. Allocation-failure injection also remains separate coverage.


For the final exercise, trace one project setting from an existing application into Framework. Identify its record owner, refusal behavior, plan publication and later execution evidence. Reuse the shared service and approved product design. Propose one integration check at each boundary rather than copying laboratory logic into the application.


## Source and practice

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Compiler ownership laboratory and owner commands](../../../labs/native/framework-compiler-ownership/README.md) · [HTML edition](../../courses/umicom-development/lessons/compiler-installed-qualification.html)
-->
[Compiler ownership laboratory and owner commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-compiler-ownership/README.md) · [HTML edition](../../courses/umicom-development/lessons/compiler-installed-qualification.html)

<!-- The former course ending is retained for review; the next link continues the same learning sequence.
[Previous lesson](compiler-borrowed-arguments.md) · [Course index](index.md)
-->
[Previous lesson](compiler-borrowed-arguments.md) · [Course index](index.md) · [Next lesson](compiler-preview-actions.md)
