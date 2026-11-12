<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/60-record-configuration-inputs-with-honest-limits.md

PURPOSE:
Record configuration inputs with honest limits

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Record configuration inputs with honest limits

A file name identifies a location. A checksum identifies the bytes observed there. Neither tells you whether a compiler actually used those bytes. This lesson builds a small evidence vocabulary before collecting a record.

## Make three separate statements

“The source tree was observed” describes an inventory. “The executable was compiled” describes an executed build. “The tests passed” describes specific test outcomes. One statement cannot stand in for the other two. Umicom C now writes a configuration-input observation and deliberately leaves compilationVerified false.

Open cmake/UmicomCInputIdentity.cmake. Its function returns immediately when the project is embedded rather than top-level. The Kernel's runtime-only integration still uses UmicomCRuntime.cmake and does not acquire hosted file inspection or a Framework dependency.

## Collect and inspect

1. In your Umicom C checkout, configure with the existing preset.

~~~powershell
cmake --preset windows-ucrt64-debug
~~~

2. Open build/windows-ucrt64-debug/qualification/configuration-inputs.json in a text editor. Find sourceFiles, generatedFiles, toolFiles and unknownInputs. Each answers a different question.

3. Find src/lexer.c in sourceFiles. Its checksum covers comments as well as executable statements. The check is about source bytes; it does not attempt semantic equivalence.

4. Find CMAKE_C_COMPILER in the recipe and toolFiles. The path and the driver checksum belong together. A driver can load other libraries, so this pair does not close the whole toolchain dependency graph.

5. Build and run the normal tests. Keep their results separately from the configuration record. Use native-debug instead on the supported Linux host workflow.

## Explain the generated files

The package configuration and Windows resource script are generated inputs with their own checksums. Copying an old resource script into a new build directory can change which icon is compiled even when the main C source is unchanged. The record compares these selected files; it does not claim to inventory every generated build rule or object.

## Exercise

Write down the evidence needed for “this executable used this source.” Compare it with the record you just inspected. You still need an observed build, artifact identity, controlled input continuity and dependency context. The current record explicitly does not supply those facts.

Expected answer: configuration evidence is a useful prerequisite, not a signed provenance statement. A null optional tool entry means no path was observed for that tool; it does not prove the tool is irrelevant in every possible build.

## Recovery and extension

If configuration refuses a linked input or a missing compiler path, inspect the selected workspace and toolchain. Do not remove inventory checks to manufacture a record. Extending the toolchain requires adding declared inputs and tests while retaining an explicit unknown set. No test-result reuse is enabled by this lesson.

[Course contents](index.md) · [Previous lesson](59-separate-instruction-fuel-from-wall-clock-time.md) · [Next lesson](61-refuse-stale-input-records-without-repairing-them.md)
