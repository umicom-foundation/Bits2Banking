<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/storage-progress-and-partial-results.md

PURPOSE:
Report refusal and partial progress without inventing rollback

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Report refusal and partial progress without inventing rollback

Prepare the installed-SDK lab using its README. The following command is a qualification step, not a recorded execution result.

~~~powershell
& .\build\framework-filesystem-clients\filesystem-clients.exe invalid-directory C:/umicom/Umicom-Bits2Banking/build/framework-filesystem-clients/qualification/invalid-directory
~~~

## Describe what happened in this attempt

A progress report answers a different question from a final status. The status says whether the requested operation completed; counts say which effects occurred before it stopped. Initialize or reset reports for each attempt so a rejected request cannot accidentally display counts from a previous success. Framework performs that reset at the shared boundary, which keeps CLI and graphical clients consistent.

~~~c
if (status != UMI_STATUS_OK) {
    printf("Directories created before refusal: %zu\n", progress.directories_created);
    /* Retain partial work. A failed status does not imply zero effects. */
}
~~~

## Start with an admission refusal

The invalid-directory scenario supplies new/../outside. Complete lexical admission should reject the traversal before creating new. The lab checks a zero directory count and then confirms that a child beneath new is absent. This case proves a specific zero-effect admission boundary when executed. It does not prove that every later native I/O failure is also free of effects.

## Reason through a later failure

Suppose creation of the first directory succeeds and the second component cannot be created. The report should retain the first creation count while complete remains false. A file can similarly be created before its write fails. Treat those outputs as observations to preserve, not as an instruction to delete a tree. Recursive cleanup could remove files written by another actor or destroy useful diagnostic evidence.

| Failure layer | Possible effects | Recovery direction |
| --- | --- | --- |
| Request admission | None under the admitted contract | Correct the request |
| Native directory traversal | Some directories may exist | Inspect status and retained paths |
| File write, flush or close | A partial new file may exist | Inspect accepted-byte count and file |
| Later project publication | Created source may remain | Preserve source and project-state evidence |

## Use controlled failure coverage

The installed lab demonstrates real admission and collision behavior. Framework qualification also includes injected native-boundary outcomes for partial roots, parents and files, plus native platform cases. An injected failure is useful for checking report arithmetic and stop order because it is reproducible. It cannot establish how a particular filesystem behaves under a real access or concurrency failure. Keep both kinds of evidence and their scope.

## Write a useful failure message

Include the operation, destination, returned status, created-object counts and accepted-byte count where relevant. State that partial work was retained. Avoid saying rolled back unless a separately implemented and verified rollback actually occurred. After correcting the cause, choose a new destination for a fresh creation attempt instead of weakening the exclusive policy to make a retry appear successful.

## Source and next steps

[Lab build and source guide](../../../labs/native/framework-filesystem-clients/README.md) · [Qualification record](../../../labs/native/framework-filesystem-clients/QUALIFICATION.md) · [HTML edition](../../courses/umicom-development/lessons/storage-progress-and-partial-results.html)

[Previous lesson](storage-empty-files-owned-reads.md) · [Course index](index.md) · [Next lesson](storage-project-state-publication.md)
