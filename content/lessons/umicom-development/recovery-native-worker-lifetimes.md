<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/recovery-native-worker-lifetimes.md

PURPOSE:
Keep native file workers independent of widgets

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../assets/branding/umicom-logo.svg)

# Keep native file workers independent of widgets

## Prepare the exercise

Use the installed-SDK lab linked below after the earlier Framework ownership lessons. Configure and build once, then run this lesson’s scenario. Commands and expected results are instructions for qualification, not a claim that this revision has been executed.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\creative-draft-recovery -B .\build\creative-draft-recovery -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_EXPECTED_SDK_PREFIX=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\creative-draft-recovery --parallel 2
ctest --test-dir .\build\creative-draft-recovery --output-on-failure --no-tests=error
& .\build\creative-draft-recovery\creative-draft-recovery.exe source-change
~~~

## Separate the editor lifetime from the file operation

A native editor may close while a file operation is still running. It may also remain open while its source text changes. A worker that holds raw pointers into widget storage can read freed memory or overwrite newer work when it completes. The worker therefore needs its own stable inputs and a completion rule that checks whether the result still belongs to the visible editor state.

Inspect the Framework GTK4 creation-brief adapter and its recovery tests alongside this lesson. The file job owns a document value, path and cancellation token, and keeps a weak reference to the root widget. The worker performs shared file operations without accessing widgets. Completion returns to the owning UI thread, reacquires the root if it still exists and checks whether the result is still applicable.

## Treat a late result as a proposal

The adapter disables normal editing and file controls while a file job is active. That reduces ordinary interaction races but does not prove that the state is immutable: callbacks, programmatic changes or teardown can still occur. Source, prompt and path changes invalidate the pending replacement decision. A late open result must not replace text that changed during the operation.

A weak reference prevents the job from keeping a closed workspace alive solely to deliver a result. It is not permission to access the object from any thread. The worker must never acquire the widget and use GTK calls in its background function. Thread ownership and object lifetime are separate requirements.

## Understand what the console scenario can show

~~~c
before = document;
strcpy(document.draft.source, "The workshop closes at sunset.");
status = RoundTrip(&document, &restored);
if (status == UMI_STATUS_OK)
    status = UmiMediaBriefCreate(&restored.draft, &fresh);
~~~

These lines come from SourceChange in the lab. They demonstrate a content distinction: the recovered prompt can remain the earlier text while the source changes and a newly prepared prompt differs. They do not start a worker, close a widget or simulate a GTK main loop. Use the console result to understand the values, then use the native tests to qualify the lifetime behavior.

The adapter also consumes one-shot Save and Open replacement approvals. Editing a relevant value or selecting another path clears them. This binds the decision to the content and destination the person reviewed. A checkbox remembered from an earlier operation must not authorize a later replacement after the context has changed.

## Review cleanup without touching a retired view

A completion that discovers a retired workspace still owns resources that need release. It must free the candidate and job state without trying to update status labels or action sensitivity. If the root survives, completion clears the active job relationship and reports either a successful operation or a refusal to apply a stale result.

Cancellation is cooperative. Requesting it during teardown can reduce unnecessary work, but the object-lifetime design must remain correct if the file call returns successfully before it notices the request. Do not make safety depend on a particular timing outcome.

## Exercise and answer

1. Run source-change and explain why preserving the earlier prompt is useful even though it is now stale.
2. Read the authored native cases for a retired open and a source or path change during open. Identify the observation each case requires.
3. Perform the native workflow only in a separately qualified application build: begin an open, change the relevant state through the supported test mechanism and observe whether the late result is refused.

Answer: recoverable user text and current preparation validity are independent. The console case checks content; native cases check lifetime and completion admission. A source review or a console pass does not prove focus, pointer interaction, accessibility, window teardown or real file timing in the graphical product.

## Source and qualification

[Complete C exercise](../../../labs/native/creative-draft-recovery/main.c) · [Lab setup](../../../labs/native/creative-draft-recovery/README.md) · [Qualification](../../../labs/native/creative-draft-recovery/QUALIFICATION.md) · [Course contents](index.md)
