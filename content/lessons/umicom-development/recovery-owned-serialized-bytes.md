<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/recovery-owned-serialized-bytes.md

PURPOSE:
Keep serialized bytes alive for every reader

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../assets/branding/umicom-logo.svg)

# Keep serialized bytes alive for every reader

## Prepare the exercise

Use the installed-SDK lab linked below after the earlier Framework ownership lessons. Configure and build once, then run this lesson’s scenario. Commands and expected results are instructions for qualification, not a claim that this revision has been executed.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\creative-draft-recovery -B .\build\creative-draft-recovery -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_EXPECTED_SDK_PREFIX=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\creative-draft-recovery --parallel 2
ctest --test-dir .\build\creative-draft-recovery --output-on-failure --no-tests=error
& .\build\creative-draft-recovery\creative-draft-recovery.exe owned-bytes
~~~

## Distinguish a value, an owner and a borrowed view

The editable document is a C value containing fixed arrays. Exporting it creates an immutable UmiCreativeAsset that owns a separate serialized capture. Asking that asset for its bytes returns a borrowed pointer and size. These are three different lifetimes even when they contain the same words.

A borrowed pointer is a temporary view into another object’s storage. It does not keep that object alive. The asset must remain alive and unchanged for every import that reads the view. Destroying it immediately after obtaining bytes and then importing through the old pointer would be a use-after-free defect. Copying the pointer into another variable would not repair the ownership.

## Keep the owner around the whole read

~~~c
UmiCreativeAsset *asset = NULL;
const void *bytes = NULL;
size_t size = 0U;
UmiStatus status = UmiMediaBriefDocumentExport(document, NULL, &asset);
if (status == UMI_STATUS_OK)
    status = UmiCreativeAssetBytes(asset, &bytes, &size);
if (status == UMI_STATUS_OK)
    status = UmiMediaBriefDocumentImport(bytes, size, NULL, out);
UmiCreativeAssetDestroy(asset);
~~~

This is the core of the lab’s RoundTrip helper. Its caller provides stable input and output values. Each stage executes only after the previous stage succeeds. Cleanup is outside the success chain so the asset is released even when a later operation fails. The import finishes while the borrowed bytes are still valid.

Initialize the output owner to NULL. The export contract refuses an already-live output rather than replacing it and leaking the previous asset. If you need two captures, use two owners and destroy both deliberately. If you need to reuse one variable, release its old owner and set the variable to NULL before the next export.

## Observe capture independence

Run owned-bytes. The scenario prepares a document and exports it, then changes the source value’s source and prompt fields. It imports from the earlier asset and compares the result with the captured document. The expected result is the earlier content. Later edits to a value do not reach back into an immutable serialized capture.

This property is useful for worker jobs. A UI can capture the content that was actually selected for a save, then let a worker use that stable capture. It still needs a separate policy for edits made while the worker runs. Capturing bytes prevents a data race on the saved content; it does not decide whether a late load result may replace newer editor text.

## Review cleanup as part of the interface

Do not use free directly on a Framework asset or on a pointer borrowed from it. The matching public destructor knows the object’s allocation and clearing rules. The instruction export from the previous lesson is another type with another release function. Similar-looking pointers are not interchangeable ownership contracts.

Draw the lifetime of each owner on paper. Mark creation, every borrowed read and destruction. Then trace each failure path: export refusal, byte-view failure and import refusal. A good cleanup structure makes all three paths easy to inspect without duplicating business logic.

## Exercise and answer

1. Explain why changing document.prompt after export does not change the imported capture.
2. Move the source edit before export in a practice copy and predict the restored value before running it.
3. Write a review note identifying the exact line after which bytes must never be used.

Answer: export owns a copy, so the order of capture determines the stored content. The borrowed view expires when UmiCreativeAssetDestroy releases its owner. Do not demonstrate an invalid lifetime by intentionally executing undefined behavior; identify the unsafe ordering in source and keep the executable exercise within the documented contract.

## Source and qualification

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Complete C exercise](../../../labs/native/creative-draft-recovery/main.c) · [Lab setup](../../../labs/native/creative-draft-recovery/README.md) · [Qualification](../../../labs/native/creative-draft-recovery/QUALIFICATION.md) · [Course contents](index.md)
-->
[Complete C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/creative-draft-recovery/main.c) · [Lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/creative-draft-recovery/README.md) · [Qualification](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/creative-draft-recovery/QUALIFICATION.md) · [Course contents](index.md)
