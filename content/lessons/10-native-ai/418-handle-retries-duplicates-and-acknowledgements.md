# Lesson 418 — Handle retries, duplicates and acknowledgements

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation context:** C23 and Assembly where justified; Framework is the reusable owner.  
**Prerequisites:** Existing native AI, numerical reasoning and source-governance foundations.

## Learning outcomes

By the end of this lesson, you should be able to explain **handle retries, duplicates and acknowledgements**, reproduce the worked reasoning, distinguish observable facts from proposed functionality, and identify a test that would disprove an overly strong claim.

## Concept and background

Distributed systems must assume at-least-once delivery unless there is an explicitly proven exactly-once protocol. A sender may retry after its result is accepted but before its acknowledgement arrives. The coordinator must identify the duplicate and avoid applying the delta twice.

This subject sits at the boundary between mathematical learning and reliable systems engineering. Neural computation may be correct while its messages arrive late, twice or under the wrong identity. Conversely, a protocol may deliver every byte correctly while the resulting model becomes less useful. Treat these as independently testable claims rather than one success indicator. Start with synthetic, authorised data and pin an immutable base-checkpoint commitment before investigating network or adversarial behaviour.

## Step-by-step mechanism

1. **Record round and correlation alongside the authorised worker ID.** Write down the invariant or input boundary so that an independent reader can check the outcome.
2. **Keep immutable admission state until the round closes.** Choose a bounded representation and reject unsupported cases rather than silently guessing values.
3. **Treat a retransmitted accepted result as an already-closed ticket.** Use an established Umicom Framework service wherever one already owns this responsibility.
4. **Return an idempotent acknowledgement rather than submitting again.** Make failure and ownership states explicit before invoking numerical or application code.
5. **Distinguish temporary transport failure from numerical rejection.** Record which assertion is proved by the available evidence and which still requires an external check.
6. **Make durable replay a separate Framework messaging concern..** Keep the smallest negative test that would distinguish a valid implementation from a convincing-looking demonstration.

## Worked example

A worker sends result sequence 2. The coordinator accepts it, then the acknowledgement is lost. The worker resends sequence 2. The local job rejects second completion of the same generation-stamped ticket; accepted contributor count remains 1.

The numbers here are an instructional fixture. Reproduce them with ordinary arithmetic before relying on software output. If a figure represents an estimate, identify the omitted costs; if it represents a test result, identify the exact executable and inputs that produced it.

## Native Umicom application

New durable inbox/outbox logic should reuse Framework messaging ownership rather than inventing a separate AI-only delivery mechanism.

The Framework remains responsible for reusable behaviour, numerical aggregation, model identity and message contracts. Desktop applications and learning laboratories should consume those APIs rather than create competing maths, protocol, source-governance or security implementations. A local demonstration is not automatically evidence for a production network.

## Security, governance and research limitations

> **Do not overclaim.** A retry should not be counted as a new distinct training contribution, even if it has a fresh transport packet identifier.

A useful evidence record distinguishes (a) structural validity, (b) identity/authorisation, (c) computational or experimental integrity and (d) independently measured model quality. Record failures as carefully as successes. Use reviewed and synthetic datasets while learning; ordinary access to source code, banking records or research documents is not permission to distribute them for training.

## Exercise — solve before revealing the answer

**Question:** If a result is retried three times, how many contributions should the numeric aggregation count?

<details><summary>Reveal the worked answer</summary>

Exactly one if the first submission was accepted; subsequent identical retries should not advance the numeric round.

</details>

## Extend the investigation

Sketch a negative test, a relevant resource or memory bound, and a realistic experimental control for this topic. Explain what the test could falsify and what it cannot establish. When performance matters, measure the full operation under fixed hardware, compiler flags and a documented input rather than inferring a runtime gain from a smaller algebraic expression.

## Primary reading

- [McMahan et al., FedAvg, AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue learning

[Lesson 417](417-compose-three-synthetic-workers-with-fedavg.md) · [Lesson 419](419-prevent-stale-and-cross-round-result-acceptance.md) · [HTML study route](../../courses/llm-from-scratch/wire-transport-learning-path.html)

*Service to Many Leads to Greatness.*
