<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/deployment-revisions-and-layered-qualification.md

PURPOSE:
Qualify revision limits and deployment layers

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Qualify revision limits and deployment layers

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

## Treat revisions as identities

A revision tells observers that a value changed. If UINT64_MAX wraps to zero, old observations can appear current again. The plan and controller now refuse mutations that cannot represent the next identity. Operations affecting several step counters reserve every required increment before changing the first step, so a late exhausted counter cannot cause partial cancellation.

## Inspect the boundary tests

The lifecycle test includes the actual controller implementation so it can place private counters at exhaustion. Normal behavior is still exercised through public calls. This is a focused test seam, not a public setter for production. The refusal checks compare the complete owner before and after; they are stronger than checking only the returned status.

## Build an evidence ladder

First execute the shared admission and lifecycle cases in Framework. Next build this consumer against the installed SDK and run its five scenarios. Then qualify a real provider in an isolated destination, capturing its source, tools and outputs. Finally exercise the native UI that invokes it. A pass at one layer cannot substitute for the next.

## Record the unresolved work

Keep authored coverage separate from executed results, and retain skips with their reasons. Record the installed library revision when a consumer result differs from source expectations. Remote deployment, signing, health verification and recovery require provider-specific implementations and evidence. End your exercise with a table of what was modeled, what was actually executed and what remains unverified.

## Review and recover

Inspect the selected SDK, compiler identity and failing output before changing expectations. Keep actual provider qualification separate from this state-model exercise.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-deployment/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-deployment/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/build/deployment_controller.h)

[Course contents](index.md) · [Previous lesson](deployment-rollback-and-phase-progress.md) · [Next lesson](task-descriptor-storage-before-meaning.md)
