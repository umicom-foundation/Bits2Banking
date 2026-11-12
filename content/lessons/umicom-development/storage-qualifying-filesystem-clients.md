<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/storage-qualifying-filesystem-clients.md

PURPOSE:
Qualify storage clients across source, SDK and native boundaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Qualify storage clients across source, SDK and native boundaries

Prepare the installed-SDK lab using its README. The following command is a qualification step, not a recorded execution result.

~~~powershell
& .\build\framework-filesystem-clients\filesystem-clients.exe profile-preview C:/umicom/Umicom-Bits2Banking/build/framework-filesystem-clients/qualification/profile-preview
~~~

## Build an evidence chain

A source review, an installed-SDK link and a native filesystem exercise answer different questions. Source review can identify ordering and ownership defects without executing code. An SDK consumer build checks whether the published headers, libraries and dependencies support a real client. Native exercises observe a particular filesystem and runtime. Keep each outcome attached to the source and environment that produced it.

| Layer | Useful evidence | Remaining question |
| --- | --- | --- |
| Source inspection | Named headers, API calls, ordering, retained logic | Will the compiler accept it? |
| Installed consumer | Package origin, compiler/link output | Will native operations behave correctly? |
| Native fixture | Status, retained bytes, report counts | What happens on other filesystems or failure paths? |
| Generated application | Build, tests, launch and branding inspection | Is packaging/distribution also qualified? |

## Follow the lab build guide

The CMake file requires an explicit absolute SDK prefix and checks that the selected package configuration belongs to it. It links Umicom::developer rather than including Framework implementation files. Environment metadata and installed layout checks detect common mismatches before compilation. If a cached consumer build selects the wrong SDK, create another build directory and keep the failed configuration evidence.

## Keep fixtures and skips useful

Native scenarios receive separate CTest parent folders. Within each parent the lab chooses a new run name through exclusive directory creation and prints it. Earlier files remain available for comparison. Framework’s wider platform suite may skip link scenarios when a host cannot construct the required fixture; a skip means missing coverage. Do not combine skips with passes or describe a small successful lab as full platform qualification.

## Check branding at the actual output boundary

The lab build uses Framework’s application branding helper for product metadata and the Windows icon resource. Lesson pages use the shared Umicom SVG wordmark, SVG icon, ICO fallback and approved learning stylesheet. Those authored references are not a visual rendering result. Inspect the produced executable metadata, icon and course pages after the owner-run build, and record font fallback behavior on the target machine.

## Keep the executable’s scope clear

profile-preview should prepare model/profile values without creating project files or registering a project. Live storage scenarios create only their retained fixture data and source examples. They do not build that source, initialize Git, install software, write a device or launch a GUI. Use the separate generated-project guide for later execution, preserving each result as its own qualification step.

## Complete a reproducible record

Record the Framework producer revision, installed prefix, consumer revision, compiler, architecture, runtime, operating system and filesystem. Attach complete configure/build/test output and retained fixture paths. Mark anything not executed as unverified. If an observation fails, preserve it and investigate the responsible layer before changing expected results or claiming the product is ready.

## Source and next steps

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Lab build and source guide](../../../labs/native/framework-filesystem-clients/README.md) · [Qualification record](../../../labs/native/framework-filesystem-clients/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/storage-qualifying-filesystem-clients.html)
-->
[Lab build and source guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-filesystem-clients/README.md) · [Qualification record](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-filesystem-clients/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/storage-qualifying-filesystem-clients.html)

[Previous lesson](storage-project-state-publication.md) · [Course index](index.md)


Continue with [copied native project inputs](native-project-captured-inputs.md).
