<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/31-describe-a-source-build-before-running-it.md

PURPOSE:
Describe a source build before running it

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Describe a source build before running it

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

## Separate intention from evidence

A source recipe records what a build intends to consume and produce. It is useful before a compiler exists because reviewers can inspect the dependencies and identities without granting execution. In the exercise, main.c is a source claim, out/main.o is an intended output, and compile is a semantic build stage. None of those names proves that compilation happened. Read recipe.json alongside main.c and identify the exact point where UmiBuildRecipeReadFile returns accepted metadata.

## Trace the native boundary

Follow the inspector from the selected absolute JSON path into the shared reader, parser, immutable recipe and task projection. The service does not construct a shell command from a label or output name. UmiBuildRecipeCreateTasks creates descriptors whose command text is empty. An execution provider would need its own configuration and authorization. Write down the missing decisions: compiler arguments, source-root mapping, environment, cancellation and result capture.

## Exercise the refusal path

Run the lab in refuse mode with command-refused.json. The added command member must cause a parse error and leave the output owner null. Compare this with inspect mode, which should report one source and one stage. Explain why silently ignoring the command member could allow two tools to interpret the same document differently. Preserve the refused file as a regression example instead of editing the parser to accept unknown fields.

## Review and recover

Keep the selected JSON, diagnostic and executable identity when a check fails. Reconcile SDK headers and libraries before changing source. Correct malformed metadata without weakening the validator, and preserve unexecuted build, target and provenance checks separately from inspection results.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-recipes/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-recipes/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/source-build-recipes.md)

[Course contents](index.md) · [Previous lesson](30-distinguish-installation-from-boot-integration.md) · [Next lesson](32-distinguish-build-host-and-target-identities.md)
