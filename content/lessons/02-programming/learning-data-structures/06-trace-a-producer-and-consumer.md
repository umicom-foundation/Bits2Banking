<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/06-trace-a-producer-and-consumer.md

PURPOSE:
Explain the lesson: Trace a producer and a consumer.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Trace a producer and a consumer

A producer creates work. A consumer processes it. They may progress at different speeds, so a queue holds work between them.

## Prepare

Open queue_pipeline.c and collections.h in the collections lab. The lab's WORKFLOWS.md gives compiler setup and commands. You can first complete this exercise with a pencil: no tool installation is needed to trace the state.

The example has twenty numbered jobs and storage for eight waiting jobs. Both activities run in one program, one step at a time.

## Follow the first six jobs

Make columns for next_job, expected_job, queued count and received value.

1. The producer tries to append next_job.
2. A successful append advances next_job.
3. The consumer sometimes removes the oldest queued value.
4. That value must equal expected_job.
5. Only successful receipt advances expected_job.

The values are identities, not array positions. Job 9 can occupy an array slot previously used by job 1.

## Find the pressure point

Continue until the queue is full. BtbQueuePush returns BTB_FULL. The producer does not advance next_job. This preserves the job for another attempt.

If the producer advanced anyway, the consumer would eventually expect a missing job. Returning an error is useful only when the caller responds correctly.

## Run and inspect

Build the lab using WORKFLOWS.md, then run btb-queue_pipeline. Expected final text: all 20 jobs arrived in order. Earlier lines show received identities and the remaining queue length.

A nonzero exit code means an expectation failed, even if some output looks correct.

## Try a change

Change the consumer schedule to accept work more often. Predict whether the queue will still become full. The final check currently requires at least one full-queue observation; adjust your experiment description rather than silently treating that check as a universal queue requirement.

Umicom's job and message services face the same ownership question: who retains work when acceptance fails? This lab isolates that question without threads or external messages.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/collections/queue_pipeline.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-container-invariants.md) · [Next lesson](07-separate-slot-and-job-identity.md)

