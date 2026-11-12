<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/recovery-reference-and-prompt-review.md

PURPOSE:
Review restored references and edited prompts

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../assets/branding/umicom-logo.svg)

# Review restored references and edited prompts

## Prepare the exercise

Use the installed-SDK lab linked below after the earlier Framework ownership lessons. Configure and build once, then run this lesson’s scenario. Commands and expected results are instructions for qualification, not a claim that this revision has been executed.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\creative-draft-recovery -B .\build\creative-draft-recovery -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_EXPECTED_SDK_PREFIX=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\creative-draft-recovery --parallel 2
ctest --test-dir .\build\creative-draft-recovery --output-on-failure --no-tests=error
& .\build\creative-draft-recovery\creative-draft-recovery.exe unresolved
~~~

## Keep a reference editable before it is available

A storyboard can mention an asset that is not currently in the library. That is normal during drafting: the author may be describing a photograph to capture later. The editable document preserves the tag as text. Preparing a storyboard requires a matching asset inventory, because instructions must describe which references were actually resolved.

The lab uses the tag @{workshop-image}. BuildStory accepts the scene text and the document exporter preserves it. Import restores the same text. UmiMediaStoryboardCreate with an empty inventory then returns UMI_STATUS_NOT_FOUND. The scenario subsequently supplies an explicit inventory entry and tries preparation again.

## Supply metadata without pretending to upload an asset

~~~c
UmiCreativeAssetLibraryEntry inventory = {0};
strcpy(inventory.id, "workshop-image");
strcpy(inventory.asset.label, "Workshop reference description");
inventory.asset.declared_kind = UMI_CREATIVE_ASSET_IMAGE;
status = UmiMediaStoryboardCreate(&restored, &inventory, 1U, &plan);
~~~

This excerpt provides the identity, label and declared kind needed for reference resolution. It does not load an image, validate a decoder, attach bytes or prove permission to transmit a file. The lab intentionally uses descriptive metadata so the boundary is easy to see. A real application obtains its inventory from the owning asset library and runs the separate content and provider checks needed for an actual submission.

Tags are case-sensitive identities. A path that happens to have a similar filename is not automatically the same asset. Malformed or unknown tags remain recoverable drafting text but cannot silently become resolved references. Explain the distinction to the user instead of discarding the paragraph that contains the unresolved tag.

## Review an edited prompt independently

Creation documents preserve their prompt field independently of the current source and direction. A user may have deliberately changed the wording after preparation. Regenerating it automatically on load would destroy those edits. Treat restored text as a draft that can be compared with a fresh preparation, then let the person decide whether to keep or replace it.

The native creation workspace marks recovered text as unprepared for handoff. A nonempty restored prompt is treated as edited, and preparing replacement text requires the existing explicit replacement decision. Recovering words must not restore an old approval or imply that a current provider is compatible with them.

## Carry branding through the final production workflow

The shared storyboard instruction output asks for the canonical Umicom SVG watermark in the final export. That instruction is a production requirement, not proof that a watermark has been composited. The text-only exercise never renders a video, image or document. A real media export must use the approved asset and independently verify its placement and visibility.

Use the canonical wordmark and symbol from the Framework brand resources. Native Windows targets use the ICO through the shared CMake branding helper; teaching pages use the shared course stylesheet and local SVG references. Keep typography and asset geometry intact rather than drawing an approximate logo with text or a substitute font.

## Exercise and answer

1. Run unresolved and identify the point where the missing asset first causes refusal.
2. Change the inventory ID’s letter case in a practice copy. Predict and inspect the preparation result.
3. Compare an edited recovered prompt with freshly prepared text without overwriting either copy.

Answer: recovery accepts the text; reference resolution is the later boundary that needs the inventory. A case-changed identity must not match silently. Keeping both prompt versions supports a deliberate review, while provider permission and final export branding still require their own observed workflow.

## Source and qualification

[Complete C exercise](../../../labs/native/creative-draft-recovery/main.c) · [Lab setup](../../../labs/native/creative-draft-recovery/README.md) · [Qualification](../../../labs/native/creative-draft-recovery/QUALIFICATION.md) · [Course contents](index.md)
