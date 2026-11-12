<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/native-project-captured-inputs.md

PURPOSE:
Copy a project request before starting background work

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Copy a project request before starting background work

Read the focused native project guide first. Code fragments below explain the shared Framework implementation; they are not standalone applications or recorded execution results.

## Start with the visible problem

A click handler runs on the GTK event thread. If it creates many files before returning, that thread cannot promptly repaint the window or process another input event. A background worker separates filesystem work from presentation. It does not make the operation transactional or give the worker permission to read widgets. Locate developer_project_creation_gtk4.inc in the Framework GTK adapter and identify where each input is copied.



~~~c
typedef struct DeveloperProjectCreationJob {
    UmiDeveloperProjectGenerationRequest request;
    UmiDeveloperProjectGeneratorReport report;
    UmiDeveloperProjectModel model;
    UmiBuildProfile profile;
    UmiStatus status;
} DeveloperProjectCreationJob;
~~~



## Understand the ownership boundary

This is the structure used by the adapter. Its request contains owned character arrays rather than pointers into entry widgets. Its model, profile and report are output values belonging to the job. The complete job is allocated on the heap so the click handler can return before it finishes. A local stack allocation would expire when the handler returned.



## Keep the service private

The worker creates its own UmiDeveloperProjectService, calls UmiDeveloperProjectCreateNew and destroys the service before returning its GTask result. Mutable registries remain confined to one operation while generation rules stay in Framework. Applications should consume the shared form instead of copying this worker into each product.



## Trace the capture

- Map the five COPY_INPUT calls to their request fields.
- Find the visibility check before task construction and explain why a notification can invalidate admission.
- Read the owned-request regression, which changes an insensitive entry after capture and checks the completed identity still uses the original request.



## Expected observation and recovery

Disabling a widget helps the user follow the workflow but does not prevent programmatic edits. Correctness comes from copied inputs and guarded publication. The expected test observes one worker invocation with the captured path and a distinct service on another thread. If it differs, retain the tested source identity and capture before changing expectations. This source walkthrough is not an executed GTK result.



## Source and next steps

<!-- The checkout-only guide route is retained for review: [Native project source and qualification guide](../../../docs/guides/native-project-forms.md) -->
[Native project source and qualification guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/docs/guides/native-project-forms.md) · [HTML edition](../../courses/umicom-development/lessons/native-project-captured-inputs.html)

[Previous lesson](storage-qualifying-filesystem-clients.md) · [Next lesson](native-project-task-admission.md) · [Course index](index.md)
