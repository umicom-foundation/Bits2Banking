<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/recovery-draft-and-readiness.md

PURPOSE:
Separate recoverable text from a prepared request

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../assets/branding/umicom-logo.svg)

# Separate recoverable text from a prepared request

## Prepare the exercise

Use the installed-SDK lab linked below after the earlier Framework ownership lessons. Configure and build once, then run this lesson’s scenario. Commands and expected results are instructions for qualification, not a claim that this revision has been executed.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\creative-draft-recovery -B .\build\creative-draft-recovery -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_EXPECTED_SDK_PREFIX=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\creative-draft-recovery --parallel 2
ctest --test-dir .\build\creative-draft-recovery --output-on-failure --no-tests=error
& .\build\creative-draft-recovery\creative-draft-recovery.exe unfinished
~~~

## Begin with the work a person can lose

A creative editor has useful work long before it has a complete request. Someone may have written an opening sentence, selected a media type and left the title empty. If saving calls the same validator as generation preparation, that unfinished work can be refused exactly when it most needs protection. Start by writing down the two decisions: can these values be represented safely, and is there enough information to prepare the next operation?

Umicom Framework makes those decisions through separate public contracts. UmiMediaBriefDocument contains the editable draft and a prompt buffer. UmiMediaBriefDocumentValidate admits bounded, terminated UTF-8 text even when title or source is empty. UmiMediaBriefCreate requires visible title and source text before it prepares a deterministic prompt. Neither operation contacts a model. A document that can be stored is therefore not automatically ready for generation.

## Make the distinction visible in C

~~~c
UmiMediaBriefDocument document = {0};
strcpy(document.prompt, "Keep this opening idea while I choose a source.");
UmiStatus storage = UmiMediaBriefDocumentValidate(&document);
UmiMediaBrief *prepared = NULL;
UmiStatus preparation = UmiMediaBriefCreate(&document.draft, &prepared);
UmiMediaBriefDestroy(prepared);
~~~

The zero initializer terminates every array and selects the first valid creation kind. The literal copied here is smaller than the destination; user input would need a checked copy. Expect storage to be UMI_STATUS_OK and preparation to be UMI_STATUS_INVALID_ARGUMENT. Read both results. Replacing them with a single Boolean would hide which boundary refused the operation.

Run the unfinished scenario in the accompanying lab. It exports the value, imports it into a fresh destination and checks that the opening idea survives. It then attempts preparation. The scenario succeeds only if recovery succeeds and preparation still refuses the empty inputs. This is a useful example of a test whose expected behavior includes a refusal.

## Store values without inventing authority

The serialized creation document contains a format marker, a version, the four draft fields and the independently editable prompt. It does not contain a selected model, credentials, a send approval or a generation receipt. Those facts belong to an execution workflow with its own lifetime. Restoring a file should recover the words the person wrote, then invite a fresh review.

Keep the same distinction in product language. Save creation text describes a storage action. Prepare text describes a local transformation. Send to a provider would be another action with another result. Showing a recovered prompt in an editor is not evidence that the source is complete, that the prompt matches it or that a service accepted anything.

## Exercise and explain the result

1. Build the installed-SDK lab using its README and run the unfinished scenario. Record the program exit status separately from the explanatory line.
2. Change the prompt literal, keep the title empty and repeat the scenario. Predict which value changes after import.
3. Add a visible title and source in a copy of the exercise. Adjust the expected preparation result only after explaining why it changes.

Answer: the edited prompt must survive in both cases. Preparation changes from refusal to success only when its own input contract is met. The imported document still grants no provider permission. If the unfinished case fails at export, check the actual status and the installed header/archive identity before weakening validation. A missing terminator or malformed UTF-8 is a storage defect, not an incomplete creative idea.

## Source and qualification

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Complete C exercise](../../../labs/native/creative-draft-recovery/main.c) · [Lab setup](../../../labs/native/creative-draft-recovery/README.md) · [Qualification](../../../labs/native/creative-draft-recovery/QUALIFICATION.md) · [Course contents](index.md)
-->
[Complete C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/creative-draft-recovery/main.c) · [Lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/creative-draft-recovery/README.md) · [Qualification](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/creative-draft-recovery/QUALIFICATION.md) · [Course contents](index.md)
