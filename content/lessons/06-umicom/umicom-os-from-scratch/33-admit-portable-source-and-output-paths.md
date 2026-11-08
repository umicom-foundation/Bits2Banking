<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/33-admit-portable-source-and-output-paths.md

PURPOSE:
Admit portable source and output paths

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Admit portable source and output paths

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

## Treat file claims as identities

Two spellings can name one file on a platform that ignores case or trailing dots. Recipe admission uses a deliberately narrow portable path policy: forward slashes, ordinary ASCII name characters and no traversal. It also treats every compiler, manifest, source and output claim as a file. A claim called src therefore conflicts with src/main.c because a file cannot simultaneously serve as the directory that contains another file.

## Reproduce an alias refusal

Copy the exercise JSON and change its output to MAIN.C while the input remains main.c. Inspection should reject the case-insensitive overlap. Try a parent segment and a reserved device stem as separate examples, preserving each input and diagnostic. Compare those failures with an internal space in an ordinary filename, which is valid metadata and never expanded by a shell. The format describes exact files, so wildcard patterns are also refused.

## Keep path policy separate from confinement

A portable relative path does not prove that a later filesystem operation remains inside a trusted root. Parent directory aliases, concurrent replacement and root selection are execution concerns. The current recipe service opens only its selected JSON file; it does not open the declared sources. A future executor must choose a root and validate access through appropriate platform services. Document that boundary instead of claiming the parser is a filesystem sandbox.

## Review and recover

Keep the selected JSON, diagnostic and executable identity when a check fails. Reconcile SDK headers and libraries before changing source. Correct malformed metadata without weakening the validator, and preserve unexecuted build, target and provenance checks separately from inspection results.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-recipes/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-recipes/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/source-build-recipes.md)

[Course contents](index.md) · [Previous lesson](32-distinguish-build-host-and-target-identities.md) · [Next lesson](34-resolve-stage-dependencies-through-framework.md)
