<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/36-use-native-recipe-inspection-and-exit-status.md

PURPOSE:
Use native recipe inspection and exit status

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Use native recipe inspection and exit status

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

## Call the shared native route

After installing the matching tool, run: umicom recipe inspect --file C:/umicom/Umicom-Bits2Banking/labs/native/framework-recipes/recipe.json. The CLI requires an explicit absolute file and delegates reading and admission to Framework. It reports the ID, digest, triples, source count and stage count. Compare this output with the installed SDK exercise; both clients should interpret the same service contract.

## Interpret all three exit classes

Exit 0 means metadata inspection and output succeeded. Exit 1 reports a file, parsing or output failure. Exit 2 reports invalid command arguments. In PowerShell, inspect $LASTEXITCODE immediately after the native command and stop on an unexpected result. Adding --apply is an argument error because this route has no execution mode. Passing a command-bearing recipe should instead reach file admission and return a recipe refusal.

## Retain evidence without overstating it

Save the exact input bytes, tool revision and command output outside product source when investigating a failure. Do not convert the phrase metadata accepted into a build-success badge. The command does not run CMake or CTest. Use the existing configure, build and test commands only through the separate owner qualification workflow. If the recipe subcommand is unknown, locate the actual executable being invoked and reconcile its installation with the headers used by the exercise.

## Review and recover

Keep the selected JSON, diagnostic and executable identity when a check fails. Reconcile SDK headers and libraries before changing source. Correct malformed metadata without weakening the validator, and preserve unexecuted build, target and provenance checks separately from inspection results.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-recipes/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-recipes/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/source-build-recipes.md)

[Course contents](index.md) · [Previous lesson](35-own-recipes-and-projected-tasks-separately.md) · [Next lesson](37-distinguish-digest-claims-from-provenance.md)
