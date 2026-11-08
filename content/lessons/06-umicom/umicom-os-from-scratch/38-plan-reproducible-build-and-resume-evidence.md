<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/38-plan-reproducible-build-and-resume-evidence.md

PURPOSE:
Plan reproducible build and resume evidence

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Plan reproducible build and resume evidence

## Prepare the exercise

Install a matching native Framework SDK with the recipe API, then build this C23 consumer using the same compiler and architecture. Run each command separately and stop on unexpected errors. The recipe stages themselves are never executed by this exercise.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-recipes -B .\build\framework-recipes -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-recipes --parallel 2
ctest --test-dir .\build\framework-recipes --output-on-failure --no-tests=error
& .\build\framework-recipes\btb-framework-recipes.exe inspect C:/umicom/Umicom-Bits2Banking/labs/native/framework-recipes/recipe.json
```

The inspect scenario should report recipe-lab with one input and one stage. CTest registers inspect, owned, identity and refuse. These are expected observations; the commands must be run to establish results in your environment.

## List what reproducibility requires

A repeatable stage graph is only one part of a reproducible build. Source bytes, compiler and linker identities, dependency versions, flags, environment, timestamps and packaging behavior may affect output. The present recipe deliberately does not encode arbitrary commands or promise deterministic binaries. Use its admitted metadata as a reviewed starting point and list the additional execution inputs a future provider must own.

## Do not infer resumability

The shared task graph can represent progress, failure and retry in memory. That does not establish a durable checkpoint format, crash recovery or safe reuse of existing artifacts. A resumed build would need to verify its prior recipe identity, source observations, provider configuration and output bytes before treating a stage as reusable. If any required identity changes, invalidation must be explicit. Record these as implementation requirements rather than calling the current inspector a resume engine.

## Write an acceptance plan

Choose one small cross-build project and write separate checks for parsing, source verification, tool qualification, compilation, target execution and artifact comparison. Assign expected evidence to each step and mark unexecuted steps honestly. Reuse the existing task and process services when implementing the next step; avoid adding a second dependency graph to an application. This keeps OS development connected to the shared Framework while preserving a clear boundary between authored capability and observed results.

## Review and recover

Keep the selected JSON, diagnostic and executable identity when a check fails. Reconcile SDK headers and libraries before changing source. Correct malformed metadata without weakening the validator, and preserve unexecuted build, target and provenance checks separately from inspection results.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-recipes/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-recipes/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/source-build-recipes.md)

[Course contents](index.md) · [Previous lesson](37-distinguish-digest-claims-from-provenance.md)
