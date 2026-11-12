<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/01-read-a-local-ai-project.md

PURPOSE:
Teach read a local ai project before designing your own.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Read a local AI project before designing your own

## What you will learn
Separate a user interface, an inference engine and a complete product. You will turn a small reference application into a set of requirements without copying its code or artwork.

## Trace one request
In the reviewed [reference application](https://github.com/MaokunZhang/local-nsfw-model-router/blob/76c0420ed60e8a83c00cbbfc26b1d7c38a742dbe/app.py), a user selects a model, enters a message and sees incremental text. Its [generation function](https://github.com/MaokunZhang/local-nsfw-model-router/blob/76c0420ed60e8a83c00cbbfc26b1d7c38a742dbe/utils/gen_response.py) passes messages and sampling controls to NexaTextInference. That is a text-chat integration, not an image or video generator. Uploading an avatar changes presentation; it does not synthesize an image.

A model is the learned numerical state used to produce predictions. An engine loads that state and performs computation. A router selects a suitable engine/model combination. A chat interface manages the interaction. Those responsibilities can be implemented and qualified separately.

## Turn observations into requirements
1. Draw the path: message → request → policy → provider → engine → response → display.
2. Mark which component owns each allocation and which component can perform I/O.
3. Describe model selection as “choose a compatible available runtime,” without importing the reference project's hard-coded model list.
4. Describe persona editing as an explicit configuration transaction, not a hidden change to conversation history.
5. List absent capabilities separately: retrieval, durable conversations, media generation and application integration need their own evidence.

The reference [loaders](https://github.com/MaokunZhang/local-nsfw-model-router/blob/76c0420ed60e8a83c00cbbfc26b1d7c38a742dbe/utils/initialize.py) and UI use different context-setting keys. This is a source-level reason to trace every control to the actual call, rather than assume that a slider changes inference. It is not a reproduced SDK failure.

## Exercise
Write three acceptance conditions for a model switch. Include loading failure, an active reply and a change in context capacity. Keep the old conversation available until a new runtime is ready; define whether the new conversation starts empty or includes an explicitly reviewed history.

**Expected result:** each condition names an observable outcome. “Model works” is too broad.

**Knowledge check:** does a C interface prove that an engine is implemented in C? No. An ABI describes how callers cross a boundary; the implementation behind it may use other languages.

## Recovery
When a claimed feature is visible only in a README or screenshot, inspect its call path and dependency. Label it a claim or design until you find implementation and execution evidence. A successful import of an SDK does not establish usable weights, compatible hardware or correct output.

[Course contents](index.md) · [Next lesson](02-map-framework-and-applications.md)
