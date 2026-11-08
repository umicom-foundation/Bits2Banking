<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/deployment-models-and-real-providers.md

PURPOSE:
Separate a deployment model from real operations

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate a deployment model from real operations

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

## Read what the program owns

The installed-SDK exercise creates an artifact record, a target record, a plan and a controller. These are C values describing intended work. The path fictional/package.zip is never opened. A flag saying the artifact is present is supplied by the lesson; it is not the result of a filesystem check. Follow the initializers in main.c and mark each supplied claim.

## Find the execution boundary

The loop obtains a step, starts it in the controller and supplies an exit code. No process API, network client or installer appears between those calls. In a real host, a provider would perform the operation and return its result. Keeping that responsibility separate lets Studio and a CLI share state rules without pretending that a state change itself installs software.

## Run a controlled failure

Select fail. The lesson deliberately supplies exit 7 for the first step, then expects the controller to report Failed. The demonstration returns zero because that expected scenario was observed. Explain why the demonstration exit code and the modeled deployment exit code answer different questions. Save both values in your exercise notes.

## Choose evidence for the next layer

Before replacing a fictional result with a real provider, name the command, working directory, destination and output evidence it will own. A successful local copy does not establish remote availability or application health. Keep the current exercise provider-free while you review those requirements. The existing Studio CMake deploy route performs a local installation; it does not supply a general remote release service.

## Review and recover

Inspect the selected SDK, compiler identity and failing output before changing expectations. Keep actual provider qualification separate from this state-model exercise.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-deployment/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-deployment/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/build/deployment_controller.h)

[Course contents](index.md) · [Previous lesson](workflow-qualify-the-integration-layers.md) · [Next lesson](deployment-bounded-public-values.md)
