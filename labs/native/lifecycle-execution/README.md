<!--
Umicom Bits2Banking
File: labs/native/lifecycle-execution/README.md

PURPOSE:
Teach workflow admission and evidence through a controlled installed-SDK exercise.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Execute a reviewed lifecycle

This C23 lab uses the installed Framework developer service. Its callbacks print action names; they do not launch compilers, tests, Git or applications. The word complete names the requested plan, not a claim that a product was qualified.

## Prepare and run

1. Install a matching Framework SDK containing lifecycle_execution.h and the developer library. Install a C23 compiler, CMake 3.25 or later and Ninja.
2. Open PowerShell in this directory. Replace the SDK location below with your installed prefix.
3. Run each command separately and stop on an error.

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
.\build\lifecycle-execution.exe preview
.\build\lifecycle-execution.exe complete
.\build\lifecycle-execution.exe fail-build
ctest --test-dir build --output-on-failure --no-tests=error
```

## Interpret the result

| Scenario | Expected adapter calls | Meaning |
| --- | ---: | --- |
| preview | 0 | Plan inspection has no host side effects. |
| complete | 8 | Each grouped action ran once in canonical order. |
| fail-build | 5 | Four succeeded; build returned 23; later actions did not run. |
| missing-backend | 0 | Even the final missing callback is detected before the first action. |
| missing-message | 0 | Required publication input is checked before qualification starts. |

These are expected outcomes for you to verify. The executable returns zero when the requested scenario matched its expectation, including an intentionally refused request. Its status field is the Framework result, not the process exit code.

## Read and extend

Read Explain in main.c, then lifecycle_execution.h and lifecycle_execution.c in Framework. The existing lifecycle_plan.c owns order. Adjacent descriptive stages share one backend: environment/dependencies, four source-scan categories, and stage/commit/push. A failed publish callback cannot identify which internal Git actions completed; retain that backend report.

Change the controlled failure from BUILD to TEST, predict the new attempted and completed counts, then update the lab expectation before running it. Keep real process execution in a separately reviewed adapter. Requests borrow immutable strings for the synchronous call.

## Recover

A missing header or symbol means the SDK does not match the lab. Rebuild and install the intended Framework revision separately, then use a fresh lab build directory. An assertion or nonzero lab result requires retaining the command, source revision and output. A successful controlled lab proves neither real CMake execution nor repository publication.

Continue in [the Framework course](../../../content/courses/umicom-development/index.html).
