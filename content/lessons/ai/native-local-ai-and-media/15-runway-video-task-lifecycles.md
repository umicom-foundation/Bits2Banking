<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/15-runway-video-task-lifecycles.md

PURPOSE:
Teach runwayML video tasks and recovery.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# RunwayML video tasks and recovery

RunwayML provides hosted media generation. Treat it as an external provider with its own account, billing, model capabilities and API version. A local C application can call a remote HTTP API without changing its implementation language, but the request still leaves the machine. Review the exact prompt and source asset before submitting it.

## Follow a task receipt

The [Runway SDK guide](https://docs.dev.runwayml.com/api-details/sdks/) maps image-to-video generation to POST /v1/image_to_video and task inspection to GET /v1/tasks/{id}. A generation response supplies a task ID. The ID is a receipt for an operation, not the resulting video. Check the current model-specific input schema rather than inventing a universal duration, resolution or model name.

1. Prepare a draft containing the reviewed prompt, source asset identity and supported model settings. Keep credentials outside the draft.
2. Persist a local operation ID before dispatch. Record the provider task ID as soon as a valid receipt arrives.
3. Perform bounded status checks with a deadline and a documented delay policy. Repeated transport failure is not a terminal provider state.
4. After success, inspect the returned asset references, download through a controlled transport and verify the bytes.
5. Import the media through the creative workspace, add the approved Umicom watermark to the export, and separately check playback and provenance.

## Model uncertainty explicitly

```text
Prepared -> dispatch began -> receipt known -> provider processing
                                          -> terminal failure
                                          -> output available -> verified import
Dispatch began + timeout -> outcome unknown -> reconcile, never assume no job
```

This is an educational state model, not a set of Runway wire-state spellings. A timeout can happen after the service accepted a charged request. Unless the selected protocol supplies a verified idempotency contract, retrying creation can produce a second job. A cancellation request and confirmed cancellation must also be recorded separately.

## Reuse existing Framework ownership rules

Inspect media_generation/pixverse.h as an existing Framework example of separate prepare, review and execute operations. UmiPixVerseResult retains creation_may_exist and creation_confirmed. Its provider endpoints and numeric states belong to PixVerse and must not be relabelled as Runway support. A new adapter should share suitable lower-level transport and persistence services while implementing Runway-specific parsing.

## Exercise and troubleshooting

Design fixtures for invalid input, a valid task receipt, an interrupted status check, terminal failure and an expired output reference. The expected result must state what the application knows, what remains unknown and whether another creation is allowed. Keep secret keys and signed asset URLs out of public logs.

The useful Framework additions are durable job receipts, bounded polling, explicit cancellation scope and artifact admission. They benefit Media and LLM clients without embedding billing or provider logic in each UI. No live Runway request or native Runway adapter is qualified by this lesson.

[Course contents](index.md) · [Previous lesson](14-comfyui-workflows-and-local-jobs.md) · [Next lesson](16-langchain-retrieval-and-native-boundaries.md)
