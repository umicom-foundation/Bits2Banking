<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/deployment-bounded-public-values.md

PURPOSE:
Admit bounded deployment values before reading them

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Admit bounded deployment values before reading them

## Prepare the exercise

Use a matching installed Framework development SDK and the provider-free C23 consumer. Run commands separately and stop on unexpected errors.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-deployment -B .\build\framework-deployment -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-deployment --parallel 2
ctest --test-dir .\build\framework-deployment --output-on-failure --no-tests=error
& .\build\framework-deployment\btb-framework-deployment.exe complete
& .\build\framework-deployment\btb-framework-deployment.exe fail
& .\build\framework-deployment\btb-framework-deployment.exe rollback
& .\build\framework-deployment\btb-framework-deployment.exe cancel
& .\build\framework-deployment\btb-framework-deployment.exe revise
```

The five scenarios report modeled outcomes. None installs a package, launches an application or contacts a target.

## Understand a fixed array

A field such as step_id has space reserved inside its struct. It is a C string only when a zero byte occurs within that space. An external adapter can fill every byte and leave no terminator. Calling strcmp or strlen on that field first can read beyond the member. The shared validators now use bounded searches before comparisons or copies.

## Check counts before traversal

A plan has a fixed number of step slots and a separate step_count. The count is caller-owned data, so a loop cannot assume it fits the array. Find DeploymentPlanShape and follow the capacity check before its first step access. Then inspect snapshot and step_at: both admit the shape before reading records or changing their outputs.

## Compare refusal contracts

The regression count-snapshot uses an impossible count and a prefilled output. Its two expectations are capacity refusal and unchanged output bytes. The artifact-text and target-text cases corrupt each text member in turn. They check the real public validators rather than a copy of the validation rule. These cases are authored coverage until you build and execute them.

## Practice with a complete object

In a local exercise copy, initialize a plan normally and then set step_count to SIZE_MAX. Call validate and record the status without traversing steps yourself. Restore the count before further use. Explain why structure_size and api_version are also checked: a consumer must agree about the layout before interpreting its fields. None of these checks authenticate the supplied artifact or target.

## Review and recover

Inspect the selected SDK, compiler identity and failing output before changing expectations. Keep actual provider qualification separate from this state-model exercise.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-deployment/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-deployment/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/build/deployment_controller.h)

[Course contents](index.md) · [Previous lesson](deployment-models-and-real-providers.md) · [Next lesson](deployment-publish-a-complete-plan.md)
