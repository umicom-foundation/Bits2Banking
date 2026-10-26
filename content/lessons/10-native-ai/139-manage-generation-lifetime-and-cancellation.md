# Lesson 139 — Manage generation lifetime and cancellation

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Topic:** Native C23 Transformers, inference and independent validation.

**Learning objective:** Design sessions that remain valid across user-interface interactions and failures.

## 1. Understand the engineering problem

An application may display one token, receive a cancel request, or change projects while an AI assistant is generating. Session lifetime must therefore be explicit. In native C23, ownership cannot be left to a scripting garbage collector. The Framework separates the caller-owned model from the session-owned context, sampler policy, random state and generation count.

## 2. Follow a concrete example

Suppose the user cancels after three successful pulls. A session that has a four-token context and two layers has requested 12 full-context rows and 24 token-layer rows. Destroying the session releases its own state. It does not undo the three tokens already displayed, change model weights or create a background task. A subsequent request constructs a fresh session with its own seed and context. An attempted 65th pull after 64 successes is rejected without consuming a random number.

## 3. Implement through the Framework

Use `Create` only with an output pointer initialised to `NULL`. Use `Next` only while the borrowed decoder is alive and not being trained concurrently. Check each returned `UmiStatus` before reading a token. `Inspect` can obtain the number of successful pulls; it refuses a model that no longer matches its captured checkpoint. `Destroy` accepts NULL, simplifying cleanup after partial construction in application code.

## 4. Check the boundaries

A GUI adapter may request cancellation, but that does not make the decoding call itself interruptible mid-computation. The current synchronous boundary checks between tokens, not within every matrix multiplication. Future asynchronous scheduling should compose approved Framework task and cancellation services; it must not copy inference or RNG logic into the application.

## Practice

**Question:** Who owns the decoder if a session is destroyed after a user cancels generation?

<details>
<summary>Reveal the worked answer</summary>

The application still owns the decoder. Destroying the session releases only session-owned context and random state; the caller must destroy the model separately when no user needs it.

</details>

## Continue

[Return to the native stacked inference learning path](stacked-inference-learning-path.md). For the mathematical background, read the [stacked inference mathematics guide](../11-maths-for-ai/stacked-inference-mathematics.md). The canonical APIs are in `framework/include/umicom/ai/training/`; implementations and native tests remain in Umicom Framework, not in this educational repository.

*Service to Many Leads to Greatness.*
