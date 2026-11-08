<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/deployment-publish-a-complete-plan.md

PURPOSE:
Publish a complete replacement plan

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Publish a complete replacement plan

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

## Start with a useful previous plan

Imagine a user has reviewed a local release and then selects a different target. If that target is disabled or malformed, the old plan should remain available for inspection. Overwriting the destination first and discovering the error later leaves a partially changed object. The replacement composition stages its work in separate allocated storage.

## Follow the transaction

Read umi_build_deployment_plan_compose_default. It first admits the existing plan, checks revision capacity and validates the new artifact and target. It then allocates a candidate, invokes the retained composition logic on that candidate and validates the completed result. Only the successful branch copies the candidate into the caller’s plan. Cleanup releases the temporary allocation on every path.

## Distinguish memory publication from deployment

This transaction concerns one in-memory C value. It provides no rollback for a file copy, installer or remote service. The generation and revision identify the new plan observation; they do not prove an artifact was rebuilt. A later provider must separately define what happens if its external operation fails halfway through.

## Check the failure boundary

Read invalid-compose-preserves and disabled-target-preserves. Each stores the previous complete plan, requests an invalid replacement and compares the full object afterward. Add a test idea for allocation failure, explaining how a controlled allocator would inject it without depending on the machine running out of memory. Do not label that proposed case executed or implemented until its injection path exists.

## Review and recover

Inspect the selected SDK, compiler identity and failing output before changing expectations. Keep actual provider qualification separate from this state-model exercise.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-deployment/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-deployment/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/build/deployment_controller.h)

[Course contents](index.md) · [Previous lesson](deployment-bounded-public-values.md) · [Next lesson](deployment-approval-follows-content.md)
