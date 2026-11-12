<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/native-project-task-admission.md

PURPOSE:
Admit a GTK task before transferring lifetime ownership

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Admit a GTK task before transferring lifetime ownership

Read the focused native project guide first. Code fragments below explain the shared Framework implementation; they are not standalone applications or recorded execution results.

## A reference is a lifetime promise

Each active dialog callback temporarily retains the controller so a GTK notification cannot free memory it is still using. The writer completion must retain that protection after the click handler returns. Follow the acquired reference from CreateClicked into DeveloperProjectCreationCompleted. Identify its completion release and the early-return releases before scheduling.



~~~c
GTask *task = g_task_new(NULL, NULL, DeveloperProjectCreationCompleted, dialog);
g_task_set_task_data(task, job, g_free);
g_task_run_in_thread(task, DeveloperProjectCreationWorker);
g_object_unref(task);
/* Completion owns the acquired dialog reference. */
~~~



## Construct after admission

This fragment belongs after copying and validating inputs, disabling controls and rechecking the owner. Control changes can emit notifications that hide or destroy the form before scheduling. The unsubmitted job can then be freed directly. Constructing a GTask earlier would require returning a task result even if admission were subsequently refused. The existing application-module form follows the same corrected ordering.



## Separate the two owners

GTask retains itself for worker execution and owns cleanup of the plain job. The dialog reference is a separate GTK-thread responsibility released by completion. Do not put a controller release into a destructor that may execute on another thread. Unreferencing the local task pointer is not the same as releasing the controller.



## Compare the boundaries

- notify-before-start destroys the ordinary form during a sensitivity notification; no task should be submitted.
- application-admission-hide hides the module form before scheduling; its job is released and controls become editable again.
- owner-retired destroys the owner after scheduling; work completes without adopting into that host.



## Qualification exercise

The test dispatcher holds a task, then releases it to a real GTask thread. Completion still uses the event context. Explain which reference keeps each object alive at each boundary. Retain GLib diagnostics and the matching runtime identity during owner qualification. A clean source review cannot prove that the compiled reference-counting paths execute safely.



## Source and next steps

<!-- The checkout-only guide route is retained for review: [Native project source and qualification guide](../../../docs/guides/native-project-forms.md) -->
[Native project source and qualification guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/docs/guides/native-project-forms.md) · [HTML edition](../../courses/umicom-development/lessons/native-project-task-admission.html)

[Previous lesson](native-project-captured-inputs.md) · [Next lesson](native-project-result-publication.md) · [Course index](index.md)
