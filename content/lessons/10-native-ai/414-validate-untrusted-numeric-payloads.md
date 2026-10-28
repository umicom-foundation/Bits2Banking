# Lesson 414 — Validate untrusted numeric payloads

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation context:** C23 and Assembly where justified; Framework is the reusable owner.  
**Prerequisites:** Existing native AI, numerical reasoning and source-governance foundations.

## Learning outcomes

By the end of this lesson, you should be able to explain **validate untrusted numeric payloads**, reproduce the worked reasoning, distinguish observable facts from proposed functionality, and identify a test that would disprove an overly strong claim.

## Concept and background

The codec must bound the vector length and reject NaN or infinity before passing a contribution to the existing federated arithmetic. Once decoded, the numerical round separately checks model identity, contributor duplication, total sample counts and update norm. Each validation layer handles a distinct failure mode.

This subject sits at the boundary between mathematical learning and reliable systems engineering. Neural computation may be correct while its messages arrive late, twice or under the wrong identity. Conversely, a protocol may deliver every byte correctly while the resulting model becomes less useful. Treat these as independently testable claims rather than one success indicator. Start with synthetic, authorised data and pin an immutable base-checkpoint commitment before investigating network or adversarial behaviour.

## Step-by-step mechanism

1. **Reject unknown schema revisions and frame kinds.** Write down the invariant or input boundary so that an independent reader can check the outcome.
2. **Reject lengths outside configured maxima.** Choose a bounded representation and reject unsupported cases rather than silently guessing values.
3. **Decode only complete IEEE-754 FP32 words.** Use an established Umicom Framework service wherever one already owns this responsibility.
4. **Reject non-finite values.** Make failure and ownership states explicit before invoking numerical or application code.
5. **Compare the expected vector length with the pinned model plan.** Record which assertion is proved by the available evidence and which still requires an external check.
6. **Delegate norm and weighted mean validation to the existing Framework FederatedRound..** Keep the smallest negative test that would distinguish a valid implementation from a convincing-looking demonstration.

## Worked example

A result claiming 4097 floats exceeds the bounded 4096-parameter laboratory. A result containing NaN must be rejected even if the frame checksum is correct. A finite vector of norm 100 can still fail the numeric round maximum norm of 1.

The numbers here are an instructional fixture. Reproduce them with ordinary arithmetic before relying on software output. If a figure represents an estimate, identify the omitted costs; if it represents a test result, identify the exact executable and inputs that produced it.

## Native Umicom application

The model update is not applied to a live decoder merely because a result passes structural checks. A separate evaluator must approve the aggregated candidate.

The Framework remains responsible for reusable behaviour, numerical aggregation, model identity and message contracts. Desktop applications and learning laboratories should consume those APIs rather than create competing maths, protocol, source-governance or security implementations. A local demonstration is not automatically evidence for a production network.

## Security, governance and research limitations

> **Do not overclaim.** Finite values alone do not ensure a mathematically useful or unbiased contribution.

A useful evidence record distinguishes (a) structural validity, (b) identity/authorisation, (c) computational or experimental integrity and (d) independently measured model quality. Record failures as carefully as successes. Use reviewed and synthetic datasets while learning; ordinary access to source code, banking records or research documents is not permission to distribute them for training.

## Exercise — solve before revealing the answer

**Question:** Name one reason a length-valid, SHA-valid result should still be rejected.

<details><summary>Reveal the worked answer</summary>

It may contain a stale checkpoint, duplicated contributor, unauthorised shard, abnormal norm or a harmful model update.

</details>

## Extend the investigation

Sketch a negative test, a relevant resource or memory bound, and a realistic experimental control for this topic. Explain what the test could falsify and what it cannot establish. When performance matters, measure the full operation under fixed hardware, compiler flags and a documented input rather than inferring a runtime gain from a smaller algebraic expression.

## Primary reading

- [McMahan et al., FedAvg, AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue learning

[Lesson 413](413-bind-frames-to-existing-umicom-typed-messaging.md) · [Lesson 415](415-build-a-failure-atomic-native-frame-parser.md) · [HTML study route](../../courses/llm-from-scratch/wire-transport-learning-path.html)

*Service to Many Leads to Greatness.*
