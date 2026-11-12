<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/recovery-layered-qualification.md

PURPOSE:
Qualify storage, SDK clients and native workflows separately

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../assets/branding/umicom-logo.svg)

# Qualify storage, SDK clients and native workflows separately

## Prepare the exercise

Use the installed-SDK lab linked below after the earlier Framework ownership lessons. Configure and build once, then run this lesson’s scenario. Commands and expected results are instructions for qualification, not a claim that this revision has been executed.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\creative-draft-recovery -B .\build\creative-draft-recovery -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_EXPECTED_SDK_PREFIX=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\creative-draft-recovery --parallel 2
ctest --test-dir .\build\creative-draft-recovery --output-on-failure --no-tests=error
& .\build\creative-draft-recovery\creative-draft-recovery.exe bounds
~~~

## Ask which layer a result actually exercises

A complete application depends on several layers: pure document logic, filesystem publication, installed SDK linkage, native worker completion and visible user interaction. One passing executable cannot establish all of them. Begin a qualification record by naming the layer, source revision, build configuration and environment that produced each observation.

The console lab calls installed public APIs. It can observe prepared text, owned captures, refusal and field preservation. The shared Framework tests reach additional parser and injected-I/O cases. Native recovery tests exercise adapter lifetime and action state. A manual application walkthrough is still needed for the approved layout, keyboard focus, file-entry interaction and visible result.

## Use boundaries that could fail differently

Run bounds. Its first part fills a fixed source array without a terminating zero and expects export to refuse it. Its second part creates long scene instructions that exceed the smaller creation source field. The checked composition helper must refuse that copy and preserve its previous destination.

These two failures are different. The first is invalid C string storage. The second is valid text that does not fit the next interface. Increasing a buffer or cutting off text blindly would hide the distinction. A useful test suite names the specific boundary so a failure points to the right contract.

## Record outcomes without collapsing them

1. Record the Framework revision installed in the SDK, the lab source revision and compiler identity before configuring.
2. Configure and build the lab using its explicit SDK prefix. Stop if either command fails; do not interpret a later run of an old executable as the new build.
3. Run CTest with --no-tests=error and inspect each named scenario. Keep failures, skips and unavailable GUI coverage separate.
4. Run the shared document, injected-I/O and native recovery selections from the matching Framework build. Keep the generated test listing with the results.
5. Complete the native application walkthrough with disposable files and record what was actually visible.

An installed header can be newer than the linked archive or runtime library. If an API is missing at link time, verify the selected package configuration and installed layout before editing the client to use a different API. If runtime behavior differs, record the loaded binary identity as well as the source checkout.

## Keep publication and execution evidence separate

A source change being authored, packaged or committed does not establish that its tests ran. Likewise, a clean static review does not establish that the compiler accepted the code or that a GUI opened. The qualification guide deliberately leaves results unexecuted until the corresponding commands are run and their output is retained.

When a test fails, preserve the first relevant diagnostic and its source identity. Fix the underlying ownership or admission problem, add the missing regression where it belongs, and repeat the affected qualification. Avoid changing an expected status merely to make a check green without explaining why the contract changed.

## Exercise and answer

1. Create a result table with separate rows for source inspection, lab build, eight console scenarios, injected I/O, native tests and manual GUI review.
2. For every row, write the evidence needed to change its state from unexecuted to observed.
3. Explain why successful text recovery does not establish video rendering, provider integration or bootable media support.

Answer: each result supports only the behavior it actually exercises. The eight lab scenarios can establish their documented console contracts when executed against an identified SDK. They cannot establish unrelated product features. Preserve that precision when turning an engineering repair into a course example or user guide.

## Source and qualification

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Complete C exercise](../../../labs/native/creative-draft-recovery/main.c) · [Lab setup](../../../labs/native/creative-draft-recovery/README.md) · [Qualification](../../../labs/native/creative-draft-recovery/QUALIFICATION.md) · [Course contents](index.md)
-->
[Complete C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/creative-draft-recovery/main.c) · [Lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/creative-draft-recovery/README.md) · [Qualification](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/creative-draft-recovery/QUALIFICATION.md) · [Course contents](index.md)
