<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/26-recognize-stale-tests-after-a-failed-build.md

PURPOSE:
Recognize stale tests after a failed build

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Recognize stale tests after a failed build

[Course contents](index.md)

## What a passing test actually proves

A source file is the text you edit. An executable is a separate file containing instructions the operating system can run. Editing the text does not immediately change those instructions. A compiler first translates source into object files. A linker combines objects and libraries into an executable. CTest then runs the commands registered by the project. A passing result proves something about the program that was actually executed and its test inputs; it does not, by itself, prove that your newest source was successfully compiled and linked.

| Stage | Input | Output | Failure means |
| --- | --- | --- | --- |
| Compile | Source plus included headers and options | Object file (.o or .obj) | The new object might not exist; an older file can remain |
| Archive | A collection of objects | Static library (.a or .lib) | Consumers may still see an older library |
| Link | Objects plus libraries | Executable (.exe on Windows) | An older executable can remain at the same path |
| Test | Registered command and test data | Observed result | The result applies to the executed artifact, not automatically to edited source |

## Why this matters in a large project

Imagine that a test executable was linked on Monday. On Tuesday you change a library, but one newly referenced header is missing. Compilation stops before a fresh library and test executable can be produced. The Monday executable can still be on disk. If you manually run CTest after ignoring the build failure, that executable may pass, fail, or crash for reasons unrelated to your Tuesday changes. A failed test is still an observation worth recording. It cannot yet establish whether the current source repair works. Different targets in a partially completed build can have different histories, so do not label the entire directory old or new from one timestamp.


## Prepare the small experiment

Use the earlier build dependency graph lab, not a production application. You need the Bits2Banking checkout, CMake 3.26 or newer, Ninja and a C23 compiler. The lab reuses the small Notes service. Its deliberate failure is disabled in normal builds. The check creates a separate child build directory with a fresh random suffix, preserving its files for inspection. It does not edit your source, delete another build, or alter any installed application.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/native/build-dependency-graph -B build/dependency-graph -G Ninja -DBUILD_TESTING=ON
cmake --build build/dependency-graph --parallel 2
ctest --test-dir build/dependency-graph --output-on-failure --no-tests=error
~~~

1. Open PowerShell. Change to your Bits2Banking checkout with Set-Location. A checkout is the directory containing the project files obtained through Git.
2. Ensure the UCRT64 compiler, CMake and Ninja are available. Follow the lab README if you have not installed these tools.
3. Configure the parent lab, build it, and only if each command succeeds run its tests. Execute the commands one at a time.


## Walk through the controlled check

Open check_stale_preview.cmake beside the lab CMakeLists.txt. execute_process runs one program and captures its exit result, standard output and error output. A result of zero normally means success; a nonzero result means failure. file(SHA256 ...) computes a fingerprint of the file bytes. Comparing fingerprints tells this exercise whether the executable changed. It is more precise than deciding from the displayed date alone, although it does not prove that every possible build input was correct.

1. The script configures an isolated child project with LESSON_REFUSE_PREVIEW_BUILD=OFF. It builds lesson-note-preview and checks the expected preview output.
2. It records the executable SHA-256 fingerprint. This identifies the successful executable before the demonstration.
3. It reconfigures that child with LESSON_REFUSE_PREVIEW_BUILD=ON. preview.c now encounters a deliberately enabled #error directive. The compiler must refuse this build.
4. The script checks that the failure contains the intended diagnostic. An unrelated compiler failure is not accepted as a successful demonstration.
5. It confirms that the executable fingerprint remains unchanged. It deliberately runs only the harmless retained preview test and observes that this older program still passes.
6. Finally it refuses to treat that old pass as qualification of the source whose build failed. The lesson test passes because it detected this situation correctly.


## Read the C switch

defined asks whether the named preprocessing macro exists. The preprocessor evaluates this condition before normal C compilation. #error tells the compiler to stop and show the message. We use it here as a deterministic teaching trigger. You do not need to damage a real header or introduce an accidental syntax error to reproduce a build refusal. The CMake option adds this macro only to the preview target in the isolated exercise.

~~~c
#if defined(LESSON_REFUSE_PREVIEW_BUILD)
#error Deliberate preview compilation refusal for the stale-artifact lesson
#endif
~~~


## Inspect the evidence without deleting it

A successful exercise reports three parent tests passing, including bits.build-graph.stale-preview. Under build/dependency-graph/stale-preview-proof/attempt-... inspect initial-build.log, expected-build-refusal.log and retained-executable-test.log. A compiler error inside expected-build-refusal.log is intentional. The parent test fails if the expected refusal did not occur, if the executable changed unexpectedly, or if the old preview observation could not be reproduced. The experiment therefore distinguishes its expected failure from an unexpected product build failure.

1. Find the message Deliberate preview compilation refusal in the expected refusal log.
2. Find the passing preview check in retained-executable-test.log.
3. Explain why both observations can be true at the same time: the source was refused, while an earlier executable remained runnable.
4. Do not copy the deliberate continuation into an ordinary build script. Outside this controlled experiment, stop before tests when the required build fails.


## Use a failure gate in PowerShell

PowerShell normally continues to the next statement after a native command returns a nonzero exit code. Setting a preference for PowerShell cmdlet errors is not a portable substitute for checking native results in every supported shell version. $LASTEXITCODE records the most recent native program exit code. Check it immediately, before another native program can replace it. throw stops this script and explains which stage failed. This small gate is useful when automating the normal lab workflow.

~~~powershell
cmake --build build/dependency-graph --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Build failed; tests were not started." }
ctest --test-dir build/dependency-graph --output-on-failure --no-tests=error
if ($LASTEXITCODE -ne 0) { throw "Tests failed; do not install or publish this result." }
~~~


## Recover a real build deliberately

Start with the first failing compiler command, not just the final Ninja stopped line. If a required source or header is absent, restore the intended complete source change from its reviewed origin. If the source is present but an include path is wrong, correct the target dependency or include configuration. Keep previous implementations and unrelated local changes. Reconfigure when build definitions changed, build the affected targets successfully, then run the relevant tests. Record the source revision and local changes, toolchain, commands and results. A clean build directory can help investigate inconsistent configuration, but deleting caches is not a substitute for finding a missing input.

1. Check that the required source inputs exist in the checkout being built. A file present in a comparison folder does not make it available to the compiler in a different checkout.
2. Confirm which executable CTest actually runs by inspecting the registered test command or using ctest --show-only=json-v1.
3. After a successful build, confirm the affected target was rebuilt or was correctly considered up to date by the dependency graph.
4. Keep skipped and missing-executable tests separate from executed passes. Never turn Not Run into a successful test count.



## A wrapper can fail before its subject starts

CTest can launch a script rather than the program being tested. The script is called a wrapper: it prepares inputs, runs a child executable and checks its output. If CMake itself starts successfully but the child executable is missing, CTest can record Failed rather than Not Run. The wrapper ran; the subject did not. Read the command and nested error before attributing the failure to a parser, a model or application logic.


## Distinguish three observations

| Observation | What ran | What you can conclude |
| --- | --- | --- |
| CTest reports Not Run because its registered executable is absent | No registered test command | The required artifact was unavailable; no pass occurred |
| A CMake wrapper reports no such file or directory while launching a child | The wrapper, but not its missing child | The wrapper failed on a prerequisite; the child behavior remains untested |
| The child returns a nonzero numeric exit status after launch | The subject and possibly its wrapper | Inspect the child output and source identity to diagnose the observed behavior |


## Check prerequisites before creating fixtures

~~~cmake
if(NOT EXISTS "${SUBJECT}" OR IS_DIRECTORY "${SUBJECT}")
    message(FATAL_ERROR "Test subject is missing or not a file; build its target first.")
endif()
# Only now create inputs and launch the child.
~~~

This is a CMake-script fragment, not a shell command. SUBJECT is the already selected executable path. EXISTS asks whether an entry exists; IS_DIRECTORY prevents a folder from being treated as a program file. FATAL_ERROR keeps the test failed. It does not skip the check, fabricate a pass, fetch a replacement or start a broad build. Existence alone still does not prove executable format, runtime DLL availability or matching source identity. Keep launch errors and numeric child failures distinct after this admission.


## Use the detailed counts when reporting results

Suppose a report has twelve failures and five skipped tests. If four failures are wrappers that never launched their subjects, keep the original report totals and explain the four separately. Do not relabel them as passing or silently subtract them from the failure count. Likewise, a later focused source test can pass while the original owner build still lacks its executable. Both observations belong in the record with their own artifact identities and environments.

## Check your understanding

Suppose a source file was saved at 10:00, its object file was rebuilt at 10:02, and the executable still has yesterday’s fingerprint because a dependent library failed. Does the new object alone prove the executable contains the fix? No: linking still has to complete with all required inputs. Suppose an executable changed its fingerprint: does that prove the tests passed? No: it establishes a changed artifact, not its correctness. Build evidence, artifact identity and test observations answer different questions. Keep all three when explaining a result.


[Previous: Detect incomplete source before a long compilation](25-detect-incomplete-source-before-compilation.md)
