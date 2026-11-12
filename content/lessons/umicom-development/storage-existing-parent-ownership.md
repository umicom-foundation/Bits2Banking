<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/storage-existing-parent-ownership.md

PURPOSE:
Prepare directories below an explicit existing parent

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Prepare directories below an explicit existing parent

Prepare the installed-SDK lab using its README. The following command is a qualification step, not a recorded execution result.

~~~powershell
& .\build\framework-filesystem-clients\filesystem-clients.exe directory-chain C:/umicom/Umicom-Bits2Banking/build/framework-filesystem-clients/qualification/directory-chain
~~~

## Choose the root deliberately

An application should know which directory owns its output. Passing a relative path and relying on the process working directory makes that identity depend on how the program was launched. The lab receives an absolute parent as its second argument. Native exercises ask the shared service to create a fresh run folder below that parent; they never change the process directory or search for a convenient fallback location.

~~~c
UmiRootedDirectoryCreation progress;
UmiStatus status = UmiRootedDirectoryEnsure(
    fixture_root, "notes/source", &progress);
/* Inspect status, complete and directories_created together. */
~~~

## Read the fixture owner

Open fixture.c. LabFixture tries a bounded sequence of run names using exclusive native directory creation. It advances to another name only when the result is ALREADY_EXISTS and reports no creation. Any other failure stops immediately, including failure after a directory was created. The printed fixture path identifies retained evidence. This is deliberately different from deleting an earlier test folder to obtain a convenient empty destination.

## Observe ensure semantics

The directory-chain scenario prepares notes/source and expects two newly created directories. Calling Ensure again should succeed with a creation count of zero. Both results can be complete: the count describes work performed by this call, not the total number of components that exist. The shared service validates the complete relative path before opening or creating an earlier component.

| Boundary | Owner |
| --- | --- |
| Existing absolute parent | The caller selects and controls it |
| Checked descendants during a call | Framework native directory service |
| Serialized application edits | The calling application |
| Retained fixture after completion | The person qualifying the lab |

## Know the limit of a held directory

Framework uses its native checked-parent traversal while performing each rooted operation. That reduces reliance on unchecked descendant path strings, but it does not hold the entire project open across later calls. Ancestors above the selected root remain trusted. Do not describe successful directory preparation as permission to execute a project, or as a lock against every external process. A workflow must still serialize its own edits and record native failures.

## Diagnose the correct layer

A missing selected parent should be reported as missing; the lab does not create it recursively. Prepare the parent explicitly, confirm its identity, and rerun in another retained fixture. A name-policy refusal calls for reviewing the request. A native access or link refusal calls for inspecting that specific environment. Neither is repaired by substituting the current directory.

## Source and next steps

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Lab build and source guide](../../../labs/native/framework-filesystem-clients/README.md) · [Qualification record](../../../labs/native/framework-filesystem-clients/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/storage-existing-parent-ownership.html)
-->
[Lab build and source guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-filesystem-clients/README.md) · [Qualification record](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-filesystem-clients/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/storage-existing-parent-ownership.html)

[Previous lesson](storage-portable-path-admission.md) · [Course index](index.md) · [Next lesson](storage-exclusive-directory-reservation.md)
