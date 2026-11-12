<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/native-project-result-publication.md

PURPOSE:
Publish created source and adoption state in separate steps

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Publish created source and adoption state in separate steps

Read the focused native project guide first. Code fragments below explain the shared Framework implementation; they are not standalone applications or recorded execution results.

## Two successes answer different questions

Creating source means the shared writer completed its file operations. Opening the project means the host adopted its model and profile into a workspace. The first can succeed while the second fails. Treating both as one boolean encourages retrying generation over files that already exist. Trace the generated flag and identify how it selects the adoption-only path.



~~~c
if (dialog->generated) {
    DeveloperProjectCreationAdopt(dialog);
    dialog->accepting = 0;
    DeveloperRelease(dialog);
    return;
}
~~~



## Publish the identity that was written

Completion copies the successful model and profile into the owned form, restores displayed fields from the captured request and changes the action to Open Project. Another callback can change even an insensitive entry programmatically. Displaying that later draft would misidentify the source destination. The captured request is the identity associated with the actual write.



## Guard publication and adoption

Opening an editor or updating a model can emit another signal, recursively click the button or retire the host. The accepting and projectCreating guards stay set through completion publication. Native lifetime and visibility are checked before calling the host and again before using its result. A failed adoption remains retryable without submitting another writer.



| Outcome | Retained state | Next action |
| --- | --- | --- |
| Writer refused | Editable draft and progress | Correct inputs or choose another destination |
| Partial write | Partial files; no adopted project | Inspect evidence and select a fresh destination |
| Adoption failed | Completed model/profile | Retry Open Project |
| Adoption succeeded | Host owns copied state | Review settings and execution trust |



## Read the regression evidence

The adoption-retry scenario expects two adoption calls and one writer invocation. The adoption-reentrant scenario expects a recursive click to create neither another adoption nor another writer. Explain why each counter matters. Partial-file descriptions come from the shared formatter, not a blanket existing-folder message. These are authored expectations until an owner-run test identifies the compiled source and environment.



## Source and next steps

<!-- The checkout-only guide route is retained for review: [Native project source and qualification guide](../../../docs/guides/native-project-forms.md) -->
[Native project source and qualification guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/docs/guides/native-project-forms.md) · [HTML edition](../../courses/umicom-development/lessons/native-project-result-publication.html)

[Previous lesson](native-project-task-admission.md) · [Next lesson](native-project-hidden-retired.md) · [Course index](index.md)
