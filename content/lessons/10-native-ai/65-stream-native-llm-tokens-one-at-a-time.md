# Lesson 65 — Pull Native LLM Tokens One at a Time with a C23 Session

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation authority:** Umicom Framework C23

## Learning objectives

Understand why streaming requires persistent inference state, how a caller owns the session lifecycle, and why pause/resume within one session must preserve the same sampled token sequence.

## 1. The difference between one-shot and streaming inference

A **one-shot generator** accepts a prompt and output limit, performs the work, and returns a complete sequence. A **pull-based generation session** returns a single next-token ID for each successful request. The application can render an output incrementally, pause before asking for another token, or cancel without resetting the decoder's trained parameters.

Calling a one-shot generator repeatedly for a single token does **not** automatically advance the same conversation. A new call may reconstruct the same prompt and restart the random-number generator. A continuing session must retain the last sampled token, the random state and the relevant cache state between calls.

## 2. Keep state ownership explicit

The Framework contract defines four responsibilities:

1. **Decoder:** caller-owned model and weights; it must outlive a session.
2. **Session:** Framework-managed generation cursor, seed progression, copied policy and KV-cache state.
3. **Sampler:** existing Framework nucleus sampling, not a second random-number generator.
4. **Application:** presentation of returned token IDs or bytes, and the decision to stop requesting further tokens.

The session does not retain a borrowed reference to the caller's original prompt buffer after successful creation, but it does depend on the decoder's lifetime and unchanged parameters. Destroy the session before destroying or retraining the decoder. The documented interface is not safe for concurrent use of that decoder and session.

## 3. Read the Framework lifecycle

The public header `umicom/ai/training/generation_session.h` supplies these operations:

| Framework operation | What the learner should observe |
| --- | --- |
| `UmiAiTrainingGenerationSessionCreate` | Creates a session against the caller's current decoder. |
| `UmiAiTrainingGenerationSessionNext` | Pulls one token ID while retaining random and cache state. |
| `UmiAiTrainingGenerationSessionInspect` | Reports successful pulls and cache-work counters. |
| `UmiAiTrainingGenerationSessionDestroy` | Releases the session without changing model parameters. |

These lines describe an **API study sequence**, not a complete C programme or alternative session implementation. The actual declarations, argument types, return statuses and ownership rules are in the Framework header.

A successful `Next` call returns one token. Its output is an integer token ID, not necessarily a complete printable character. The byte-specific operation `UmiAiTrainingGenerationSessionNextByte` instead returns one raw byte for the Framework's reversible byte-token vocabulary. The caller must maintain the byte count; embedded NUL and invalid UTF-8 remain possible.

## 4. Why keeping the seed is essential

Suppose a generation request uses a fixed seed and asks for 12 tokens. One uninterrupted session should produce the same token IDs as twelve successful pulls from that *same session*, even if the caller pauses between pulls. Pausing must not itself advance the sampler. Creating a brand-new session starts a new generation; it is not a transparent continuation of the previous state.

With the current learned-absolute-position decoder, the initial KV prefill uses the canonical full BOS-left-padded context. After a full-context rollover, keys/values are rebuilt to preserve the positional mathematics. This design improves UI responsiveness and explicit cancellation but does not establish a faster decoder.

## 5. Cancellation is a lifecycle operation

A caller may stop requesting tokens and destroy the session. The Framework frees its session-owned inference state without modifying model weights. Cancellation is not an invitation to rewrite the model or throw away another application's decoder. Applications remain thin consumers of the Framework API.

## 6. Exercises

1. Why is reseeding a sampler for every token generally incorrect for a continuing generated sequence?
2. List which objects must still be alive when `SessionNext` is called.
3. Why is a raw byte output not safely displayed as a NUL-terminated string?
4. Would pausing after five tokens automatically free the KV cache? Explain the intended session lifetime.

<details>
<summary>Worked answers</summary>

1. Reseeding repeats or changes random-state progression compared with one uninterrupted generation.
2. The session and its borrowed decoder must remain valid; the caller must also provide the documented writable token output.
3. NUL is a legitimate data byte and can truncate a C string; non-UTF-8 bytes can also occur.
4. **No.** The session retains state across pauses until it is destroyed or reaches a terminal failure; the caller chooses when to end it.

</details>

**Companion reading:** [Illustrated Lesson 65](../../courses/llm-from-scratch/lessons/65-stream-native-llm-tokens-one-at-a-time.html) · [Previous: Parity and Bounded Memory](64-test-cached-generation-parity-and-memory.md) · [Next: Streaming Verification](66-test-streamed-generation-parity-and-cancellation.md).
