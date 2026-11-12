<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/recovery-explicit-file-operations.md

PURPOSE:
Choose a recovery path and interpret cancellation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../assets/branding/umicom-logo.svg)

# Choose a recovery path and interpret cancellation

## Prepare the exercise

Use the installed-SDK lab linked below after the earlier Framework ownership lessons. Configure and build once, then run this lesson’s scenario. Commands and expected results are instructions for qualification, not a claim that this revision has been executed.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\creative-draft-recovery -B .\build\creative-draft-recovery -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_EXPECTED_SDK_PREFIX=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\creative-draft-recovery --parallel 2
ctest --test-dir .\build\creative-draft-recovery --output-on-failure --no-tests=error
& .\build\creative-draft-recovery\creative-draft-recovery.exe cancel
~~~

## Make the destination part of the request

A recovery operation needs a path chosen by the caller. Framework does not guess a working directory, choose an automatic recovery filename or infer permission from a previous save. UmiMediaBriefDocumentSave accepts an ordinary absolute path in a trusted parent directory and uses the shared atomic writer. It may replace an existing destination and create missing parents, so the application must obtain the appropriate replacement decision before calling it.

The lab exposes that decision as an explicit --replace argument. Its open operation likewise requires --replace-current. These command-line switches are teaching-client policy, not switches parsed by the Framework functions. A native application obtains the same decisions through its UI and consumes them for the selected operation. Do not persist those approvals inside the editable document.

## Rehearse with a disposable file

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& .\build\creative-draft-recovery\creative-draft-recovery.exe save "C:\umicom\_local\practice\creative-draft.json" --replace
& .\build\creative-draft-recovery\creative-draft-recovery.exe open "C:\umicom\_local\practice\creative-draft.json" --replace-current
~~~

Run each command separately after building the lab. Stop on an unexpected result. The first command may overwrite the named practice file; choose a path whose content you are willing to replace. The second prints restored text and reminds you that recovery restores no send permission. Keep real user documents out of this exercise.

A relative path should be refused. Do not recover by concatenating the process working directory without showing the resulting destination to the user. The shared contract also does not make arbitrary parent directories trustworthy. An absolute spelling is necessary for this workflow but is not a general filesystem sandbox.

## Interpret cancellation at the publication boundary

The cancel scenario requests cancellation before export and import. It expects no new asset and no change to the current destination. This deterministic case establishes early cancellation behavior. It does not establish what happens at every instant during real disk I/O.

Save checks cancellation during preparation and before publication. Once atomic publication starts, it returns the actual write result even if a cancellation request arrives later. A success after a late request is possible and must be reported honestly. Saying “canceled, nothing changed” merely because the token is now set would contradict a file that was already published.

## Understand the limits of atomic replacement

Atomic replacement aims to prevent readers from observing a partially written replacement at the publication point. It does not provide a compare-and-swap protocol between two editors. Two successful saves to the same path replace the destination in completion order. If an application needs conflict detection, it must design an additional content or revision check around that workflow.

The shared bounded reader handles load admission and the document importer preserves the destination on refusal. A native client should run blocking file work on a worker and bring only a complete result back to the owner thread. Closing a progress indicator is not the same as proving that the file operation has stopped.

## Exercise and answer

1. Run cancel and identify the two unchanged outputs checked by the lab.
2. Use the explicit save/open commands with a disposable absolute path, then try a relative path and retain the reported status.
3. Explain what the UI should report if cancellation was requested after a successful atomic publication began.

Answer: early cancellation leaves the asset owner NULL and the destination document unchanged. A late cancellation request must not erase the actual publication outcome. Keep a record of the requested action and the returned status; do not infer a rollback or delete the saved file as an automatic response.

## Source and qualification

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Complete C exercise](../../../labs/native/creative-draft-recovery/main.c) · [Lab setup](../../../labs/native/creative-draft-recovery/README.md) · [Qualification](../../../labs/native/creative-draft-recovery/QUALIFICATION.md) · [Course contents](index.md)
-->
[Complete C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/creative-draft-recovery/main.c) · [Lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/creative-draft-recovery/README.md) · [Qualification](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/creative-draft-recovery/QUALIFICATION.md) · [Course contents](index.md)
