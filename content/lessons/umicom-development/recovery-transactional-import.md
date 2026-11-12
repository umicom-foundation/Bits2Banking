<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/recovery-transactional-import.md

PURPOSE:
Refuse a damaged document without losing current work

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../assets/branding/umicom-logo.svg)

# Refuse a damaged document without losing current work

## Prepare the exercise

Use the installed-SDK lab linked below after the earlier Framework ownership lessons. Configure and build once, then run this lesson’s scenario. Commands and expected results are instructions for qualification, not a claim that this revision has been executed.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\creative-draft-recovery -B .\build\creative-draft-recovery -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_EXPECTED_SDK_PREFIX=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\creative-draft-recovery --parallel 2
ctest --test-dir .\build\creative-draft-recovery --output-on-failure --no-tests=error
& .\build\creative-draft-recovery\creative-draft-recovery.exe refused
~~~

## Treat an external document as a proposed replacement

Opening a file proposes a new editor state. The file may be damaged, produced by a future version or simply unrelated to this application. The current document should remain usable when that proposal is refused. Clearing the editor before parsing would turn a normal input error into lost work.

Framework imports creation documents into a private candidate. It admits the complete version-one shape, field types, bounded text and creation kind before publishing the candidate to the destination. Unknown or duplicate members are refused. The caller receives a status and keeps its existing destination on every failure. This is a stronger promise than “parsing stopped before the last field.”

## Make refusal observable

~~~c
UmiMediaBriefDocument before;
memcpy(&before, &document, sizeof(before));
UmiStatus rejected = UmiMediaBriefDocumentImport(
    unsupported, sizeof(unsupported) - 1U, NULL, &document);
if (rejected == UMI_STATUS_OK ||
    memcmp(&before, &document, sizeof(before)) != 0)
    return UMI_STATUS_INVALID_STATE;
~~~

The unsupported input in the lab is a complete-looking document with version 99. The test must observe both refusal and preservation. Checking only that the function returns an error would miss a parser that partially overwrites the destination before discovering the unsupported version.

Here memcpy captures the exact initialized destination representation before the call. The byte comparison is intentional for the “unchanged on failure” contract. For successful round trips the lab compares named fields instead; padding bytes are not part of the meaning of a C structure. Keep these two forms of comparison attached to the property each is meant to establish.

## Keep format evolution explicit

A version number identifies the schema that the reader understands. It is not permission to guess how later fields should be interpreted. A future application may change the meaning of a field while preserving its spelling. Refusing unsupported versions prevents an older reader from silently converting a document it cannot faithfully represent.

When adding a future format, design a reviewed migration that can state what it preserves, what it transforms and what it cannot represent. Retain the original input until the migrated result has been accepted. Do not “fix” a future-version refusal by changing the number in a user’s file without understanding the schema.

## Extend coverage with distinct adverse inputs

The shared document tests cover more than the one teaching scenario: missing members, wrong types, unknown fields, malformed text, oversized input and cancellation have separate admission paths. The small lab demonstrates how an installed consumer observes the contract. It is not a substitute for the service’s complete regression suite.

For each additional fixture, write the expected refusal and the preservation requirement before authoring the input. Use short synthetic strings without personal content. If the service reports an unexpected status, retain the input and the tested SDK identity; changing the expected result immediately can conceal a regression.

## Exercise and answer

1. Run refused and explain why its successful exit means an invalid input was rejected correctly.
2. Create a practice fixture with a duplicate prompt field. Check the complete destination after refusal.
3. Replace the proposed title with a distinctive marker and verify that the marker never reaches the current document on failure.

Answer: the destination must preserve every byte on failed import. The application can show an error while leaving the current editor intact. Successful import is a separate replacement decision: a native UI must obtain approval before invoking a load that would replace current work, and must recheck whether that work changed while the load was running.

## Source and qualification

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Complete C exercise](../../../labs/native/creative-draft-recovery/main.c) · [Lab setup](../../../labs/native/creative-draft-recovery/README.md) · [Qualification](../../../labs/native/creative-draft-recovery/QUALIFICATION.md) · [Course contents](index.md)
-->
[Complete C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/creative-draft-recovery/main.c) · [Lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/creative-draft-recovery/README.md) · [Qualification](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/creative-draft-recovery/QUALIFICATION.md) · [Course contents](index.md)
