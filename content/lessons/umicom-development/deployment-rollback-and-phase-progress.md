<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/deployment-rollback-and-phase-progress.md

PURPOSE:
Report rollback progress without erasing failure

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Report rollback progress without erasing failure

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

## Read the two phases

A plan may contain forward steps and separately designated rollback steps. Normal success should not wait for unused rollback work. The snapshot now computes progress from the active phase, while its outcome counters retain all recorded steps. Run complete and observe full progress even though the rollback step was never executed.

## Follow the rollback scenario

Run rollback. The first forward step receives a fictional failure. The host explicitly begins rollback, records the rollback step and completes that phase. The final state is Rolled back, not Succeeded. The failed-step count remains visible. Restoring an earlier state does not turn the attempted new release into a successful release.

## Interpret the percentage carefully

Progress measures accounted step states, not elapsed time, bytes transferred or application health. Cancelled and failed steps are terminal observations too. A failed rollback can therefore show fully accounted progress while the overall state remains Failed. Always read state, last status and failed_step_id alongside the number.

## Check a different plan

Add a second rollback step to an exercise copy, with a distinct identifier and order. Predict the progress after only the first rollback result is recorded. Then model failure in the second. Describe what evidence a real provider would need before claiming restoration: restored bytes or configuration, observed service behavior and the exact target identity. This lesson supplies none of that external evidence.

## Review and recover

Inspect the selected SDK, compiler identity and failing output before changing expectations. Keep actual provider qualification separate from this state-model exercise.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-deployment/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-deployment/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/build/deployment_controller.h)

[Course contents](index.md) · [Previous lesson](deployment-stop-and-completion-evidence.md) · [Next lesson](deployment-revisions-and-layered-qualification.md)
