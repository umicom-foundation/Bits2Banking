<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/deployment-approval-follows-content.md

PURPOSE:
Keep approval attached to the reviewed content

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep approval attached to the reviewed content

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

## Observe a changed plan

Run the revise scenario. The exercise approves its fictional plan, appends a cleanup step and prints Approval after edit: 0. Approval referred to the earlier list of actions. Reusing it after adding a new action would allow work the reviewer had not seen. The Framework mutation now revokes approval whenever the target requires it.

## Follow both mutation paths

Read add_step and bind. Adding a step changes the content; rebinding changes the artifact or destination identity. Both use the target’s approval requirement when setting the new approval state. A target that does not require approval remains usable through the same public contract. The code does not create an identity system or prove who reviewed the plan.

## Validate before approving

The approval function now validates the complete plan before changing the approval bit. An empty binding, malformed step or missing forward safety gate cannot become acceptable merely because a caller invokes approve. The metadata-only limitation still applies: valid syntax and ordered actions do not establish trust in a remote endpoint.

## Design a review sequence

Write five steps for a host: compose, display the complete plan, obtain its own authorized review, approve the unchanged plan and load a copied controller plan. Identify where a new edit must restart that sequence. A concurrent editing interface would need its own synchronization and identity comparison; these APIs require single-owner access and do not make a racy review safe automatically.

## Review and recover

Inspect the selected SDK, compiler identity and failing output before changing expectations. Keep actual provider qualification separate from this state-model exercise.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-deployment/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-deployment/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/build/deployment_controller.h)

[Course contents](index.md) · [Previous lesson](deployment-publish-a-complete-plan.md) · [Next lesson](deployment-one-running-step.md)
