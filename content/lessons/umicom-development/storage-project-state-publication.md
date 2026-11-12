<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/storage-project-state-publication.md

PURPOSE:
Publish project state only after successful file creation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Publish project state only after successful file creation

Prepare the installed-SDK lab using its README. The following command is a qualification step, not a recorded execution result.

~~~powershell
& .\build\framework-filesystem-clients\filesystem-clients.exe service-refusal C:/umicom/Umicom-Bits2Banking/build/framework-filesystem-clients/qualification/service-refusal
~~~

## Compose the application from shared services

A project wizard needs more than files. It also needs a model identifying the project, a build profile describing later tool use, and a registry entry that other application features can find. These states must agree about success. The shared new-project service prepares and validates model/profile candidates before filesystem effects, then publishes them only after the checked writer succeeds.

~~~c
UmiStatus status = umi_developer_project_service_generate_new(
    service, &request, &report, &model, &profile);
/* On refusal, model and profile retain their previous contents. */
~~~

## Trace the refusal example

The service-refusal scenario creates an ordinary project destination inside a fresh fixture, then asks the service to create a new project there. Before that call, the lab fills model and profile storage with known bytes and saves complete snapshots. It expects ALREADY_EXISTS, no registered project, fresh zero effect counts, and unchanged output storage. The snapshot is copied with memcpy because a byte-for-byte comparison must preserve padding bytes as well as fields.

## Understand the ordering defect this prevents

Writing files first and validating a profile afterwards can leave a registered project even though the frontend receives a failure. Checking files_skipped after registration has the same problem. Admission should precede effects wherever possible, and project-state publication should follow completed effects. Later I/O failure can still leave physical source files, so the service promises unchanged public state on refusal rather than pretending to roll back the filesystem.

## Separate preview from registration

Run profile-preview to obtain a candidate model and validated build profile without native fixture creation or registry mutation. Then run service-create in a separate prepared parent to observe live creation. The new service keeps existing registry upsert semantics: a successfully created project using an existing application ID can replace that ID’s registered model. A fresh folder therefore does not automatically mean a fresh application identity.

## Keep ownership visible in the client

The service owns its registries until destruction. Model and profile outputs are copied values that the lab retains independently. projects.c destroys the service before examining those copied outputs, while main.c owns and finally releases the large heap state. Inputs and output storage must remain distinct and stable during the call. The caller must serialize service and destination mutation.

## Expected observations and next checks

A qualified refusal should leave project_count at zero and preserve both snapshots. A qualified live creation should publish one model and a valid profile. Neither observation builds or launches the generated application. Record that later qualification separately, including the exact source, SDK and toolchain identities.

## Source and next steps

[Lab build and source guide](../../../labs/native/framework-filesystem-clients/README.md) · [Qualification record](../../../labs/native/framework-filesystem-clients/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/storage-project-state-publication.html)

[Previous lesson](storage-progress-and-partial-results.md) · [Course index](index.md) · [Next lesson](storage-qualifying-filesystem-clients.md)
