<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/ui-values-installed-qualification.md

PURPOSE:
Qualify a branded installed client and report its limits

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Qualify a branded installed client and report its limits

## Identify the exact dependency being exercised

A source tree, an installed header directory and an installed library can represent different revisions. This lab deliberately uses find_package and Umicom::ui so it exercises the exported SDK contract. Before building, identify the Framework source revision that produced the installed prefix. A new header combined with an old library is not a valid way to qualify a new public API.


Follow the laboratory README in order. Qualify and install Framework through its owner workflow, configure this client with the matching prefix, build it, then run its six CTest cases. Stop on a failed build. Running an older executable after a failed rebuild cannot validate the source you just edited.


~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\framework-ui-values"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
ctest --test-dir build --output-on-failure
~~~


## Read what the checker actually proves

The checker compares the complete standard output, exit zero and an empty error stream for each scenario. This catches stale titles, partial publication and unexpected extra diagnostics. An expected refusal is a successful observation only when the preserved value and other stated invariants also match. Merely printing CAPACITY_EXCEEDED would be insufficient.


| Layer | Evidence to retain | Remaining boundary |
| --- | --- | --- |
| Framework regression | Matching source, target and CTest output | Installed package identity |
| Installed laboratory | Prefix, compiler, full scenario results | Product integration |
| Product workflow | Native interactions and current model observations | Other workflows and platforms |
| Branding | Staged assets, executable metadata, rendered pages | Other renderers and font availability |


## Inspect approved branding through the installed service

The CMake target calls umicom_apply_application_branding from the installed Framework package. It stages approved SVG assets and embeds the approved Windows ICO through RC. NO_RUNTIME_DEPLOYMENT keeps this console client from requesting GTK runtime deployment. The lessons share the approved learning stylesheet with Segoe UI and Cascadia Code fallbacks.


Check those assets and native metadata after building. Font declarations are source evidence; actual appearance also depends on installed fonts and the renderer. Keep visual review distinct from API execution. This lab does not create a new layout or claim that a native application already matches its approved mockup.


## Write a precise evidence statement

Complete a short record containing the authored change, static checks, exact executed commands, tested source and SDK identity, observed results and remaining limits. At authoring time these lessons and cases have only static review; owner compiler, test, resource and website execution remain unverified. Replace that statement only when corresponding evidence exists.


For the final exercise, choose one existing application model that publishes a title or status. Trace its path into Framework, identify where refusal should preserve the prior display, and propose the smallest integration check. Reuse the shared service and existing approved design. Do not copy this laboratory's assertions into product logic or mistake six successful console cases for complete Studio, Trader or TMS qualification.

## Source and practice

[UI value laboratory and owner commands](../../../labs/native/framework-ui-values/README.md) · [HTML edition](../../courses/umicom-development/lessons/ui-values-installed-qualification.html)

<!-- The series now continues into compiler ownership. Previous endpoint navigation retained for review:
[Previous lesson](ui-values-archive-admission.md) · [Course index](index.md)
-->
[Previous lesson](ui-values-archive-admission.md) · [Next lesson](compiler-record-ownership.md) · [Course index](index.md)
