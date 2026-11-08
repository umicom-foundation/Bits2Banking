<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/workflow-preview-and-optional-audits.md

PURPOSE:
Separate previews from optional audit policy

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate previews from optional audit policy

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

## Understand what preview proves

A preview builds the plan and action groups without invoking the host. It can succeed without a compiler, a publisher callback or a publication message. That makes it useful for inspection, but it cannot prove that a preset exists, a repository is clean or an external scanner is available.

## Locate policy ownership

The dependency vulnerability stage may be marked optional in the plan when strict mode is absent. The existing audit backend decides how to report unavailable external tooling. The executor still stops on a nonzero callback result; it does not discard failures by inspecting the optional label. Strict mode asks that backend to require its external scanner.

## Exercise

Run preview and verify zero callback calls. Read the strict field in the request and its forwarding in command_workflow.c. Compare the strict regression with the default plan’s dependency stage. Write separate expected records for planned scanning, unavailable optional tooling and an executed scan result.

## Keep the user informed

Do not display a green security result merely because a preview returned zero. Explain whether the scanner ran, was unavailable under a permitted policy, or failed. Preserve the tool’s own findings and versions separately from the lifecycle’s action counts.

## Review and recover

A missing header or symbol requires checking the installed SDK identity. Preserve the command and output for a failed lab expectation. Controlled callbacks do not qualify real compilers, repository publication or a native GUI.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/lifecycle-execution/main.c) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/developer/lifecycle_execution.h)

[Course contents](index.md) · [Previous lesson](workflow-attempted-and-completed-evidence.md) · [Next lesson](workflow-adapters-and-option-scope.md)
