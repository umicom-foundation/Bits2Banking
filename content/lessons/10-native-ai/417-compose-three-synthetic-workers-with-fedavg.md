# Lesson 417 — Compose three synthetic workers with FedAvg

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation context:** C23 and Assembly where justified; Framework is the reusable owner.  
**Prerequisites:** Existing native AI, numerical reasoning and source-governance foundations.

## Learning outcomes

By the end of this lesson, you should be able to explain **compose three synthetic workers with fedavg**, reproduce the worked reasoning, distinguish observable facts from proposed functionality, and identify a test that would disprove an overly strong claim.

## Concept and background

The producer/consumer interface should not duplicate the existing Framework weighted aggregation. The coordinator decodes three worker results, checks each public correlation against its owned ticket, constructs borrowed contribution views and calls the established FederatedJobComplete API.

This subject sits at the boundary between mathematical learning and reliable systems engineering. Neural computation may be correct while its messages arrive late, twice or under the wrong identity. Conversely, a protocol may deliver every byte correctly while the resulting model becomes less useful. Treat these as independently testable claims rather than one success indicator. Start with synthetic, authorised data and pin an immutable base-checkpoint commitment before investigating network or adversarial behaviour.

## Step-by-step mechanism

1. **Admit three authorised assignments against one base digest.** Write down the invariant or input boundary so that an independent reader can check the outcome.
2. **Issue round-scoped public sequences.** Choose a bounded representation and reject unsupported cases rather than silently guessing values.
3. **Decode three independently generated synthetic results.** Use an established Umicom Framework service wherever one already owns this responsibility.
4. **Reject wrong round/sequence/shard before consuming the ticket.** Make failure and ownership states explicit before invoking numerical or application code.
5. **Pass each accepted delta through FederatedJobComplete.** Record which assertion is proved by the available evidence and which still requires an external check.
6. **Finalise once all pending jobs have been completed or cancelled..** Keep the smallest negative test that would distinguish a valid implementation from a convincing-looking demonstration.

## Worked example

Samples 100/250/150 with deltas +0.05/−0.01/+0.08 give (5 − 2.5 + 12) / 500 = +0.029. The result is a scalar toy, not a measured improvement in a real language model.

The numbers here are an instructional fixture. Reproduce them with ordinary arithmetic before relying on software output. If a figure represents an estimate, identify the omitted costs; if it represents a test result, identify the exact executable and inputs that produced it.

## Native Umicom application

The three-worker example separates arithmetic, process exchange, policy checks and future model evaluation. It can later be extended to real authorised local training without changing the wire format arbitrarily.

The Framework remains responsible for reusable behaviour, numerical aggregation, model identity and message contracts. Desktop applications and learning laboratories should consume those APIs rather than create competing maths, protocol, source-governance or security implementations. A local demonstration is not automatically evidence for a production network.

## Security, governance and research limitations

> **Do not overclaim.** Aggregated sample counts are caller-claimed; this experiment cannot prove the datasets contained that many distinct authorised examples.

A useful evidence record distinguishes (a) structural validity, (b) identity/authorisation, (c) computational or experimental integrity and (d) independently measured model quality. Record failures as carefully as successes. Use reviewed and synthetic datasets while learning; ordinary access to source code, banking records or research documents is not permission to distribute them for training.

## Exercise — solve before revealing the answer

**Question:** What is the weighted mean of the three synthetic deltas in the example?

<details><summary>Reveal the worked answer</summary>

+0.029, because their sample-weighted contributions sum to 14.5 and total 500 samples.

</details>

## Extend the investigation

Sketch a negative test, a relevant resource or memory bound, and a realistic experimental control for this topic. Explain what the test could falsify and what it cannot establish. When performance matters, measure the full operation under fixed hardware, compiler flags and a documented input rather than inferring a runtime gain from a smaller algebraic expression.

## Primary reading

- [McMahan et al., FedAvg, AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue learning

[Lesson 416](416-run-a-local-two-process-message-handoff.md) · [Lesson 418](418-handle-retries-duplicates-and-acknowledgements.md) · [HTML study route](../../courses/llm-from-scratch/wire-transport-learning-path.html)

*Service to Many Leads to Greatness.*
