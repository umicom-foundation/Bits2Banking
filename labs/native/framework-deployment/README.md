<!--
Umicom Bits2Banking
File: labs/native/framework-deployment/README.md

PURPOSE:
Rehearse shared deployment planning and state transitions through the installed SDK.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Rehearse Framework deployment state

This C23 client calls the installed `Umicom::build` service. It supplies fictional provider outcomes; it never opens the named package, changes an installation, contacts a server or starts a child process. A model state of Succeeded means all declared forward outcomes were recorded as successful. It does not prove software was deployed.

## Prepare and run

1. Install the matching Framework development SDK with the same compiler and architecture as this consumer.
2. Open PowerShell and run each command separately. Stop on any unexpected error.
3. Compare the five outputs with the expected states below.

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

The complete case ends in Succeeded with 10000/10000 active-phase progress. The fail case ends in Failed and retains exit 7. Rollback ends in Rolled back and retains the earlier failed-step count. Cancel ends in Cancelled after the current modeled step returns. Revise prints approval 0 because an added step changes the reviewed content. The executable returns zero when its selected teaching scenario matches the expected state, including the intentionally failed scenario.

## Follow the source

Read `main.c`, then Framework `deployment_plan.h` and `deployment_controller.h`. The plan copies bounded metadata. The controller owns a copied plan and one running step. The host would execute real operations separately and report their outcomes. This lab deliberately has no provider implementation.

The older [deployment rehearsal](../deployment-rehearsal/README.md) remains a fictional evidence-review exercise. This companion demonstrates the actual shared Framework API instead of copying that implementation.

## Recover from a mismatch

If CMake cannot find UmicomFramework, inspect the installed development package and prefix. If the new refusal cases or progress values differ, confirm which SDK revision supplied the library and headers; a source update alone does not update an installed archive. Keep the failing output and compiler identity. Do not change expected values merely to obtain a pass. A remote release, Qt package, Wt server or mobile bundle still needs its own provider, dependency, signature and runtime checks.

## Extend the exercise

Add a health-check step between installation and promotion, then model a nonzero health result. Predict the final state and failed step before running. Next try placing promotion before installation: complete plan validation should refuse it. Compare a request to stop with actual provider cancellation; the controller cannot interrupt an operation it does not execute.
