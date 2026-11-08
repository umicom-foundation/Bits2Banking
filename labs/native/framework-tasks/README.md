<!--
Umicom Bits2Banking
File: labs/native/framework-tasks/README.md

PURPOSE:
Teach task admission, transactional mutation and registry ownership through an installed SDK.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Review Framework tasks without executing them

A task describes a command, its working directory, inputs and outputs. This C23 lab calls the installed Framework service to validate and copy that description. It never runs the command stored in the task.

## Prepare and run

1. Install a matching Framework development SDK, including the new checked registry reset API. Use the same compiler and architecture for the SDK and this consumer.
2. Run the following PowerShell commands separately and stop on an unexpected error.
3. Repeat the last command with `shape`, `owned`, `reset` and `revision`.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-tasks -B .\build\framework-tasks -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-tasks --parallel 2
ctest --test-dir .\build\framework-tasks --output-on-failure --no-tests=error
& .\build\framework-tasks\btb-framework-tasks.exe atomic
```

The five registered checks expect: an oversized directory leaves the command unchanged; a malformed count is rejected before traversal; a registry retains its own copy after the caller clears the input; checked reset empties the registry and advances its identity; and an exhausted revision refuses mutation. Each program invocation returns zero only when its selected scenario matches those assertions.

## Follow the ownership boundary

Read `main.c` and Framework `include/umicom/build/task.h`. Initialize every public snapshot before editing it. Builder calls accept incomplete executable metadata, but registry publication additionally requires full semantic validation. Counts describe active rows, so every active string must terminate within its fixed array. The service cannot validate an arbitrary dangling pointer supplied in place of a complete object.

A registry owns copied task values. Changes to a caller snapshot after upsert do not alter the stored task. Updating an existing ID retains its position and advances the stored revision. Reset reports an error when no newer registry identity is representable; the older void clear interface remains compatible but cannot return that status.

## Diagnose a mismatch

If configuration cannot find the SDK, inspect `CMAKE_PREFIX_PATH` and the installed development package. An undefined reset symbol usually means headers and the library came from different revisions. Preserve the configure output and identify the actual archive before changing the example. If an assertion fails, keep the selected scenario and diagnostic line; do not weaken the expected result.

## Extend the exercise

Add a configure task and make build depend on it. Validate each task, then build a task graph using the existing Framework graph API to resolve dependency IDs. Local descriptor validation alone cannot prove that another task exists or that dependencies are acyclic. No successful validation in this lab proves that a compiler exists, inputs match their recorded identities, output files were produced or a deployment is ready.
