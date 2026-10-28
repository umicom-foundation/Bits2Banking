# Lesson 423 — Separate convergence evidence from transport correctness

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation context:** C23 and Assembly where justified; Framework is the reusable owner.  
**Prerequisites:** Existing native AI, numerical reasoning and source-governance foundations.

## Learning outcomes

By the end of this lesson, you should be able to explain **separate convergence evidence from transport correctness**, reproduce the worked reasoning, distinguish observable facts from proposed functionality, and identify a test that would disprove an overly strong claim.

## Concept and background

A protocol can deliver every message correctly while the training algorithm fails to converge. Conversely, a useful trained update can arrive through an unsafe channel. Good experiments separate protocol metrics, numerical parity, held-out quality and operational cost.

This subject sits at the boundary between mathematical learning and reliable systems engineering. Neural computation may be correct while its messages arrive late, twice or under the wrong identity. Conversely, a protocol may deliver every byte correctly while the resulting model becomes less useful. Treat these as independently testable claims rather than one success indicator. Start with synthetic, authorised data and pin an immutable base-checkpoint commitment before investigating network or adversarial behaviour.

## Step-by-step mechanism

1. **Establish a single-worker training control with matched sample/compute budgets.** Write down the invariant or input boundary so that an independent reader can check the outcome.
2. **Use identical base and tokenizer across cooperating workers.** Choose a bounded representation and reject unsupported cases rather than silently guessing values.
3. **Record actual exchanged bytes and retries.** Use an established Umicom Framework service wherever one already owns this responsibility.
4. **Measure accepted-but-harmful update rates.** Make failure and ownership states explicit before invoking numerical or application code.
5. **Compare held-out validation loss at fixed token budgets.** Record which assertion is proved by the available evidence and which still requires an external check.
6. **Test one adversarial and one dropout scenario independently..** Keep the smallest negative test that would distinguish a valid implementation from a convincing-looking demonstration.

## Worked example

A toy three-worker mean gives +0.029 and the codec passes all integrity tests. Those facts alone give no validation loss, perplexity or task-performance evidence. A real supervised experiment must evaluate a candidate checkpoint.

The numbers here are an instructional fixture. Reproduce them with ordinary arithmetic before relying on software output. If a figure represents an estimate, identify the omitted costs; if it represents a test result, identify the exact executable and inputs that produced it.

## Native Umicom application

Use new native C23 services for orchestration but let the established model/tape/optimiser remain mathematical authority; avoid duplicate training implementations in apps.

The Framework remains responsible for reusable behaviour, numerical aggregation, model identity and message contracts. Desktop applications and learning laboratories should consume those APIs rather than create competing maths, protocol, source-governance or security implementations. A local demonstration is not automatically evidence for a production network.

## Security, governance and research limitations

> **Do not overclaim.** A lower network byte count is not proof of improved time-to-target loss or better model quality.

A useful evidence record distinguishes (a) structural validity, (b) identity/authorisation, (c) computational or experimental integrity and (d) independently measured model quality. Record failures as carefully as successes. Use reviewed and synthetic datasets while learning; ordinary access to source code, banking records or research documents is not permission to distribute them for training.

## Exercise — solve before revealing the answer

**Question:** What two independent acceptance gates should a future release require?

<details><summary>Reveal the worked answer</summary>

One protocol/integrity gate (correct data and authorised messages) and one held-out model-quality gate (measured useful behaviour).

</details>

## Extend the investigation

Sketch a negative test, a relevant resource or memory bound, and a realistic experimental control for this topic. Explain what the test could falsify and what it cannot establish. When performance matters, measure the full operation under fixed hardware, compiler flags and a documented input rather than inferring a runtime gain from a smaller algebraic expression.

## Primary reading

- [McMahan et al., FedAvg, AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue learning

[Lesson 422](422-design-provenance-receipts-without-claiming-training-proof.md) · [Lesson 424](424-capstone-qualify-a-bounded-local-federated-handoff.md) · [HTML study route](../../courses/llm-from-scratch/wire-transport-learning-path.html)

*Service to Many Leads to Greatness.*
