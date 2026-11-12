<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/06-stream-cancel-and-display-text.md

PURPOSE:
Teach stream cancel and display model text.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Stream cancel and display model text

## What you will learn
Design incremental output without confusing a collector, a transport and a native model generator.

## Three different contracts
Framework's ai/stream.h accumulates text chunks into a bounded collector and invokes a sink. It does not itself open a connection, decode an HTTP event stream or enforce a request lifecycle. The loopback provider used by this course is nonstreaming. The educational native generation sessions under ai/training can pull tokens from their model contracts; this is another path again.

A UI should expose streaming only when the selected route supports it. Adding a STREAMING bit to a catalogue entry cannot implement the missing behavior.

## Design an event boundary
For a future shared streaming adapter, specify request identity, sequence number, payload length and terminal state. Then write acceptance cases before connecting it to a pane:

1. Start request A and accept its first chunk.
2. Cancel A and start B.
3. Deliver a late A chunk. It must not enter B's transcript.
4. Deliver B's terminal event twice. Only one terminal transition is allowed.
5. Close the pane during work. Release it only when callbacks cannot target freed state.

Cancellation is a request to stop. It does not erase already-generated text or guarantee that a remote job stopped computing. Serialize mutable state and join workers before destroying borrowed objects.

## Decode bytes carefully
UTF-8 represents some characters with several bytes. A transport chunk may end halfway through a character. Keep incomplete bytes until a later chunk completes the character; distinguish invalid input from an incomplete final sequence. Native byte-token generation can also produce invalid UTF-8. Never assume one token equals one printable character.

For web or markup-backed views, render generated text as text or through an explicitly constrained renderer. Model output must not create executable HTML merely because it resembles a tag. For terminals, escape control sequences.

## Exercise
Use the bytes E2 82 AC, the UTF-8 encoding of the euro sign, as a three-chunk input. Predict the visible output after each byte: nothing complete, nothing complete, then one euro sign. On cancellation after E2, do not display a fabricated valid character or attach the byte to a later request.

## Continue existing lessons
Study the [native generation and UTF-8 sequence](../../../courses/llm-from-scratch/index.html) for the actual decoder and text-admission implementations. Reuse those boundaries where applicable rather than adding another decoder in an application.

**Recovery:** when text appears in the wrong chat, capture request and operation identity first. A faster refresh timer cannot correct ownership of late events.

[Course contents](index.md) · [Next lesson](07-ground-answers-with-reviewed-sources.md)
