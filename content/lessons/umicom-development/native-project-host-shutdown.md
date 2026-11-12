<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/native-project-host-shutdown.md

PURPOSE:
Keep a host alive until its shared source writer completes

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Keep a host alive until its shared source writer completes

Read the focused native project guide first. Code fragments below explain the shared Framework implementation; they are not standalone applications or recorded execution results.

## The host owns normal shutdown

Closing the last application window may stop its event loop before a writer completion arrives. Framework exposes UmiGtk4DeveloperDialogWritePending so a host can inspect the shared state instead of maintaining a second busy flag. It covers admission, background writing and completion publication for both project forms. Read-only previews are excluded.



~~~c
/* Fragment in a GTK close-request callback with a live owned form. */
if (UmiGtk4DeveloperDialogWritePending(host->project_form)) {
    /* Use existing host feedback, then keep the native window open. */
    return TRUE;
}
/* Continue existing unsaved-document and running-tool checks. */
~~~



## Respect the query contract

Call on the GTK thread with a not-yet-destroyed handle. NULL is idle. A pointer used after Destroy is invalid even if a task still retains internal memory. The query performs no callbacks or state changes, but its answer is a snapshot. Do not carry it across unrelated event-loop work and treat it as a reservation.



## Protect replacement too

Opening another project form can discard the first owner-visible result while files continue writing. Studio checks shared activity before replacing either project form and returns BUSY while writing. Normal close and Close Anyway also wait. Existing terminal, test and unsaved-document checks remain; this addition does not grant permission to discard other work.



## Require a fresh close decision

Do not automatically close after completion. Adoption may open source, change the workspace or display information requiring review. Ask the user to close again after the result. Explicit controller destruction and forced process termination remain separate actions that cannot promise completion or rollback.



## Exercise the integration

The three Studio wizard-during-write cases act immediately after the click returns, before GTK processes completion. They check that normal close keeps the host open or form replacement returns BUSY, then await the real writer result. This ordering is deterministic even on a fast disk. Their names are registered in first_use_cases.inc, the same catalogue used for native argument admission. Execution evidence remains owner-run.



## Source and next steps

[Native project source and qualification guide](../../../docs/guides/native-project-forms.md) · [HTML edition](../../courses/umicom-development/lessons/native-project-host-shutdown.html)

[Previous lesson](native-project-hidden-retired.md) · [Next lesson](native-project-qualification-evidence.md) · [Course index](index.md)
