<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/34-resolve-stage-dependencies-through-framework.md

PURPOSE:
Resolve stage dependencies through Framework

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Resolve stage dependencies through Framework

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

## Build a dependency graph

A directed edge means that one stage waits for another. A configure stage may precede compile, and compile may precede package. The recipe schema permits forward references, so declaration order is not execution order. The existing task graph resolves the names and rejects cycles; the recipe reader does not implement a second scheduling algorithm. Read the dependencies array in a stage and find where it becomes a task dependency.

## Distinguish data claims from dependencies

Stage inputs name root source IDs, not previous stage outputs. The format does not infer dataflow by matching output paths to input paths. Declare required ordering explicitly and keep output files distinct. A diamond graph can have two checks depend on one compilation and one package depend on both checks. Explain why that graph is valid, whereas compile waiting for package while package waits for compile is a cycle.

## Extend the exercise deliberately

Create an exercise copy with a second stage that depends on compile and writes a different output. Keep its input list empty if it has no root-source reference. Inspect it, then deliberately misspell the dependency ID and record the refusal. Restore the valid name and verify the stage count. These observations exercise metadata resolution only: no stage becomes complete, no output file is created, and no scheduler execution is implied.

## Review and recover

Keep the selected JSON, diagnostic and executable identity when a check fails. Reconcile SDK headers and libraries before changing source. Correct malformed metadata without weakening the validator, and preserve unexecuted build, target and provenance checks separately from inspection results.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-recipes/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-recipes/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/source-build-recipes.md)

[Course contents](index.md) · [Previous lesson](33-admit-portable-source-and-output-paths.md) · [Next lesson](35-own-recipes-and-projected-tasks-separately.md)
