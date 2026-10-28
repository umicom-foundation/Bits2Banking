# Lesson 033 — Separate signed receipts and useful-learning proofs

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation context:** C23 and Assembly where justified; Framework is the reusable owner.  
**Prerequisites:** Existing native AI, numerical reasoning and source-governance foundations.

## Learning outcomes

By the end of this lesson, you should be able to explain **separate signed receipts and useful-learning proofs**, reproduce the worked reasoning, distinguish observable facts from proposed functionality, and identify a test that would disprove an overly strong claim.

## Concept and background

A signature binds a key to a statement; a byte commitment identifies content; a verification challenge checks a subset of claimed execution; a quality benchmark checks observed utility. These are distinct claims.

This subject sits at the boundary between mathematical learning and reliable systems engineering. Neural computation may be correct while its messages arrive late, twice or under the wrong identity. Conversely, a protocol may deliver every byte correctly while the resulting model becomes less useful. Treat these as independently testable claims rather than one success indicator. Start with synthetic, authorised data and pin an immutable base-checkpoint commitment before investigating network or adversarial behaviour.

## Step-by-step mechanism

1. **Identify the coordinator-owned state.** Write down the invariant or input boundary so that an independent reader can check the outcome.
2. **Describe the worker-visible message.** Choose a bounded representation and reject unsupported cases rather than silently guessing values.
3. **Separate numerical claims from security claims.** Use an established Umicom Framework service wherever one already owns this responsibility.
4. **Construct one safe synthetic example.** Make failure and ownership states explicit before invoking numerical or application code.
5. **Consider a duplicate, stale or malicious input.** Record which assertion is proved by the available evidence and which still requires an external check.
6. **Explain the independently checked acceptance condition.** Keep the smallest negative test that would distinguish a valid implementation from a convincing-looking demonstration.

## Worked example

A public receipt states “base digest A, delta digest B, worker key K”. A successful signature check confirms only the key-bound statement, under its trust policy. It does not certify the dataset contents or convergence.

The numbers here are an instructional fixture. Reproduce them with ordinary arithmetic before relying on software output. If a figure represents an estimate, identify the omitted costs; if it represents a test result, identify the exact executable and inputs that produced it.

## Native Umicom application

Use the existing Framework job, messaging and provenance APIs to express this experiment. Education and LLM applications should present a thin workbench, while reusable implementation stays in Framework.

The Framework remains responsible for reusable behaviour, numerical aggregation, model identity and message contracts. Desktop applications and learning laboratories should consume those APIs rather than create competing maths, protocol, source-governance or security implementations. A local demonstration is not automatically evidence for a production network.

## Security, governance and research limitations

> **Do not overclaim.** An honest local example cannot demonstrate security against unknown external workers or improvement on real training data.

A useful evidence record distinguishes (a) structural validity, (b) identity/authorisation, (c) computational or experimental integrity and (d) independently measured model quality. Record failures as carefully as successes. Use reviewed and synthetic datasets while learning; ordinary access to source code, banking records or research documents is not permission to distribute them for training.

## Exercise — solve before revealing the answer

**Question:** What does a valid signature fail to establish?

<details><summary>Reveal the worked answer</summary>

Whether the claimed learning actually happened and improved independent model quality.

</details>

## Extend the investigation

Sketch a negative test, a relevant resource or memory bound, and a realistic experimental control for this topic. Explain what the test could falsify and what it cannot establish. When performance matters, measure the full operation under fixed hardware, compiler flags and a documented input rather than inferring a runtime gain from a smaller algebraic expression.

## Primary reading

- [Proof of Learning (PoLe), research preprint](https://arxiv.org/abs/2007.15145)

## Continue learning

[Lesson 32](032-measure-verified-work-instead-of-gpu-hour-claims.md) · [Lesson 34](034-compare-privacy-of-individual-and-aggregated-updates.md) · [HTML study route](../../courses/distributed-learning/worker-messaging-and-replay.html)

*Service to Many Leads to Greatness.*
