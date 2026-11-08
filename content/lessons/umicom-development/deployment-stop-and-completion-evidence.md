<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/deployment-stop-and-completion-evidence.md

PURPOSE:
Preserve cancellation when the running step returns

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Preserve cancellation when the running step returns

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

## Separate a request from interruption

Run cancel. The controller marks pending forward steps cancelled while the current modeled step remains running. The lesson then reports that step as successful. This sequence represents a stop request arriving during work that finishes before it can be interrupted. It does not imply that a real process was terminated.

## Read the terminal result

After the current step returns, the controller enters Cancelled and retains UMI_STATUS_CANCELLED as its last status. The completed-step count still includes the work that succeeded. Both facts matter: cancellation is a workflow result, while the completed action is historical evidence. Overwriting the status with OK would hide why the remaining steps did not run.

## Choose provider cancellation separately

A real host may ask a process executor to cancel, but it must wait for that executor’s result before reporting the current step. It cannot safely claim the external operation stopped merely because the plan accepted a stop request. An installer may have made partial changes; preserve its output and destination identity for recovery.

## Compare two timings

Compare cancel-idle with cancel-running in the regression source. The first has no active operation and can immediately reach a cancelled state. The second preserves the current operation until its result arrives. Draw both timelines and list which steps are completed, cancelled or still pending. Then explain why a stop requested from another thread requires an explicit host handoff rather than direct unsynchronized controller mutation.

## Review and recover

Inspect the selected SDK, compiler identity and failing output before changing expectations. Keep actual provider qualification separate from this state-model exercise.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-deployment/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-deployment/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/build/deployment_controller.h)

[Course contents](index.md) · [Previous lesson](deployment-one-running-step.md) · [Next lesson](deployment-rollback-and-phase-progress.md)
