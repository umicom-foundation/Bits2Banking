<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/workflow-plan-stages-and-real-actions.md

PURPOSE:
Map descriptive stages to real actions

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Map descriptive stages to real actions

## Prepare the exercise

Install a C23 compiler, CMake 3.25 or later, Ninja and a matching Framework SDK with the developer lifecycle service. A terminal runs commands; CMake prepares build instructions and Ninja compiles the program. Use your actual SDK prefix and stop on a configure or build error before running an existing executable.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\lifecycle-execution"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
.\build\lifecycle-execution.exe fail-build
ctest --test-dir build --output-on-failure --no-tests=error
```

For fail-build, expect five attempted callbacks, four completed callbacks and zero external commands. The deliberate backend result is 23. This is an expected observation to verify, not a claimed pass on your machine.

## Separate explanation from invocation

The lifecycle plan has fourteen stages for complete, but the controlled host receives eight callbacks. Environment and native dependencies share one check. Four source categories share one scan. Repository stage, commit and push share one publisher. A plan explains required work; it need not create a separate process for every sentence.

## Follow canonical order

Read lifecycle_plan.c before lifecycle_execution.c. The plan owns the order. The executor walks it and groups adjacent stages mapped to the same action. It does not maintain a second independent list of goals. Adding a new stage without a supported action mapping refuses execution before any callback instead of silently skipping the work.

## Exercise

Run complete and draw the fourteen-stage sequence with brackets around each shared action. Match each bracket to first_stage and stage_count in the report. Change the requested goal to update in a local exercise and predict the two actions before executing it. Compare the resulting plan with complete.

## Avoid accidental duplication

Calling the repository publisher three times would not give three independent measurements of stage, commit and push. It would repeat a mutating workflow. When integrating a service, identify its actual unit of execution and keep that boundary visible in both progress reporting and tests.

## Review and recover

A missing header or symbol requires checking the installed SDK identity. Preserve the command and output for a failed lab expectation. Controlled callbacks do not qualify real compilers, repository publication or a native GUI.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/lifecycle-execution/main.c) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/developer/lifecycle_execution.h)

[Course contents](index.md) · [Previous lesson](workflow-admit-the-whole-request.md) · [Next lesson](workflow-check-every-host-capability.md)
