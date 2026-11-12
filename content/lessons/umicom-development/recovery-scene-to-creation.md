<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/recovery-scene-to-creation.md

PURPOSE:
Compose scene instructions into a creation document

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../assets/branding/umicom-logo.svg)

# Compose scene instructions into a creation document

## Prepare the exercise

Use the installed-SDK lab linked below after the earlier Framework ownership lessons. Configure and build once, then run this lesson’s scenario. Commands and expected results are instructions for qualification, not a claim that this revision has been executed.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\creative-draft-recovery -B .\build\creative-draft-recovery -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_EXPECTED_SDK_PREFIX=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\creative-draft-recovery --parallel 2
ctest --test-dir .\build\creative-draft-recovery --output-on-failure --no-tests=error
& .\build\creative-draft-recovery\creative-draft-recovery.exe pipeline
~~~

## Build an application by composing services

This exercise follows one small application workflow: write two scenes, prepare instructions for the first scene, create a video brief and recover the resulting editable document. Each stage uses an existing Framework service. The client supplies sample content and decides when to call each stage; it does not implement another JSON writer, reference parser or file format.

Read BuildStory and BuildDocument in main.c. A storyboard draft stores ordered scene values. UmiMediaStoryboardCreate validates the active scenes and resolves reference tags against a supplied inventory. UmiMediaStoryboardSceneInstructions then produces owned UTF-8 instruction bytes for one selected scene. The lab deliberately selects one scene because the creation source field has a smaller capacity than a complete storyboard export.

## Cross a bounded interface deliberately

~~~c
UmiStatus status = UmiMediaStoryboardCreate(&story, NULL, 0U, &plan);
if (status == UMI_STATUS_OK)
    status = UmiMediaStoryboardSceneInstructions(plan, 0U, &instructions);
if (status == UMI_STATUS_OK)
    status = CopyText(candidate.draft.source, sizeof(candidate.draft.source),
                      instructions.bytes, instructions.size);
~~~

These lines are an excerpt from BuildDocument, where story, plan, instructions and candidate have already been initialized. CopyText is the lab’s small composition helper. It checks the byte count and rejects an embedded terminator before copying. It leaves the destination unchanged if the text will not fit. This lets the user choose a smaller scene or excerpt rather than silently losing the end of the instructions.

A scene’s requested duration describes intent. It does not establish a video provider’s supported duration, resolution or reference limits. Likewise, the instruction text describes asset references without attaching their bytes. The lesson’s pipeline ends with text preparation and document recovery; rendering and delivery are separate workflows.

## Publish a complete candidate

BuildDocument initializes a private candidate and performs every stage against it. Only after preparation and copying succeed does it assign the candidate to the caller’s output. That assignment is the publication point: the caller observes one complete result. If an earlier stage fails, the caller retains its previous value.

This pattern is often called transactional replacement. Here it does not mean a database transaction or concurrent synchronization. It means that one owner finishes validation and construction before replacing a visible value. Keep the distinction clear when extending the program: a successful local assignment does not protect against two threads writing the same destination at once.

## Follow cleanup in the reverse direction

The storyboard plan, instruction export and prepared brief each have a different destructor. The brief’s prompt is borrowed, so the lab copies it before destroying the brief. The instruction bytes are owned by UmiCreativeExport and released with UmiCreativeExportFree. The final value document owns fixed arrays and remains usable after both producers close.

Run pipeline and inspect the recovered prompt. It should describe the first workshop scene and the selected direction. The program compares the restored fields with the original document before reporting the expected result. It does not treat a printed line alone as proof of a successful round trip.

## Exercise and answer

1. Change the selected scene index from zero to one in a practice copy and predict which text changes.
2. Try an index equal to the scene count. Observe the refusal and check that cleanup still releases every owner.
3. Run bounds to study why a complete long storyboard cannot be copied into a smaller source field.

Answer: selecting scene one should describe the measurement scene. Selecting an index outside the active range must fail. The repair for oversized instructions is an explicit content choice or a different supported interface, not unchecked copying or truncation. Keep reusable changes in Framework and application-specific scene choices in the client.

## Source and qualification

[Complete C exercise](../../../labs/native/creative-draft-recovery/main.c) · [Lab setup](../../../labs/native/creative-draft-recovery/README.md) · [Qualification](../../../labs/native/creative-draft-recovery/QUALIFICATION.md) · [Course contents](index.md)
