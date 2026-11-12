<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/58-own-a-synchronous-progress-context.md

PURPOSE:
Teach own a synchronous progress context through the installed Framework media client.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Own a synchronous progress context

## Before you begin

Read the progress callback in the existing framework-boot-media client before running a cancellation scenario. Locate the context allocation, the synchronous apply call and the point where that context goes out of scope. Use a fresh regular-file destination for each run so an earlier refusal does not mask callback behaviour.

## Identify who calls the callback

UmiBootMediaApply calls its progress function synchronously on the invoking thread. The callback receives a borrowed report and a caller-supplied context pointer. It may request cancellation by returning nonzero. It must not destroy the plan, free transfer inputs or close transport handles. The service remains responsible for unwinding the operation and publishing its final report.


~~~c
typedef struct MediaLessonStop {
    UmiBootMediaPhase phase;
    int observed;
} MediaLessonStop;

static int StopAtPhase(const UmiBootMediaReport *report, void *context)
{
    MediaLessonStop *stop = context;
    if (report->phase != stop->phase) return 0;
    stop->observed = 1;
    return 1;
}
~~~


## Explain why this context remains alive

The lab declares MediaLessonStop in MediaLessonMain and calls Apply before that function returns. Its stack storage therefore outlives every callback in this synchronous invocation. A GUI worker would need a different ownership arrangement: its context must survive until the worker has finished, and GTK widgets must remain on their owning thread. This console example does not implement that GUI lifecycle.


## Keep cancellation small

- Read ReadStopPhase and list the accepted phase names. Invalid names return usage status before review.
- Find the conditional callback and context arguments passed to Apply. Ordinary copy passes neither.
- Add a proposed callback that saves the borrowed report pointer, then explain why copying needed values is safer than retaining that pointer. Do not add it to the working client.


## Expected observation and recovery

The copy-until command prints whether its requested phase was actually observed. A transfer can fail before reaching that phase, so a requested stop is not proof that cancellation caused the final result. Read both the callback observation and returned status. Keep callbacks bounded; a slow callback delays the caller and is not an asynchronous notification queue.

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Complete application](../../../../labs/native/framework-boot-media/main.c) · [Lab setup and recovery](../../../../labs/native/framework-boot-media/README.md)
-->
[Complete application](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/main.c) · [Lab setup and recovery](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/README.md)

[Course contents](index.md) · [Previous lesson](57-read-file-effects-separately-from-status.md) · [Next lesson](59-cancel-before-the-first-payload-write.md)
