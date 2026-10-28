# Lesson 019 — Study LoRA-factor invariance before federated merging

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation context:** C23 and Assembly where justified; Framework is the reusable owner.  
**Prerequisites:** Existing native AI, numerical reasoning and source-governance foundations.

## Learning outcomes

By the end of this lesson, you should be able to explain **study lora-factor invariance before federated merging**, reproduce the worked reasoning, distinguish observable facts from proposed functionality, and identify a test that would disprove an overly strong claim.

## Concept and background

For LoRA, the actual weight-space update is B×A. Different factor pairs can represent the same update, so averaging A and B separately is generally not equivalent to averaging products.

This subject sits at the boundary between mathematical learning and reliable systems engineering. Neural computation may be correct while its messages arrive late, twice or under the wrong identity. Conversely, a protocol may deliver every byte correctly while the resulting model becomes less useful. Treat these as independently testable claims rather than one success indicator. Start with synthetic, authorised data and pin an immutable base-checkpoint commitment before investigating network or adversarial behaviour.

## Step-by-step mechanism

1. **State a narrowly falsifiable research question.** Write down the invariant or input boundary so that an independent reader can check the outcome.
2. **Identify the strongest prior published baseline.** Choose a bounded representation and reject unsupported cases rather than silently guessing values.
3. **Set a fixed model and authorised data split.** Use an established Umicom Framework service wherever one already owns this responsibility.
4. **Vary one experimental factor at a time.** Make failure and ownership states explicit before invoking numerical or application code.
5. **Measure both quality and cost with repeated seeds.** Record which assertion is proved by the available evidence and which still requires an external check.
6. **Document negative results and threats to validity.** Keep the smallest negative test that would distinguish a valid implementation from a convincing-looking demonstration.

## Worked example

Compare (A1,B1)=(1,1) and (A2,B2)=(-1,-1). Both yield product +1. Independent factor averages yield zeros and product zero; direct delta averaging yields +1.

The numbers here are an instructional fixture. Reproduce them with ordinary arithmetic before relying on software output. If a figure represents an estimate, identify the omitted costs; if it represents a test result, identify the exact executable and inputs that produced it.

## Native Umicom application

The relevant experiments belong in Framework-owned native C23 services; application GUIs may display results via standard typed channels. External research implementations serve as comparison baselines, not silent dependencies.

The Framework remains responsible for reusable behaviour, numerical aggregation, model identity and message contracts. Desktop applications and learning laboratories should consume those APIs rather than create competing maths, protocol, source-governance or security implementations. A local demonstration is not automatically evidence for a production network.

## Security, governance and research limitations

> **Do not overclaim.** A literature-supported research possibility is not the same as verified novelty or an implemented production capability.

A useful evidence record distinguishes (a) structural validity, (b) identity/authorisation, (c) computational or experimental integrity and (d) independently measured model quality. Record failures as carefully as successes. Use reviewed and synthetic datasets while learning; ordinary access to source code, banking records or research documents is not permission to distribute them for training.

## Exercise — solve before revealing the answer

**Question:** What should an aggregation baseline average for comparable adapters?

<details><summary>Reveal the worked answer</summary>

The effective weight-space deltas, or an explicitly proven equivalent low-rank representation.

</details>

## Extend the investigation

Sketch a negative test, a relevant resource or memory bound, and a realistic experimental control for this topic. Explain what the test could falsify and what it cannot establish. When performance matters, measure the full operation under fixed hardware, compiler flags and a documented input rather than inferring a runtime gain from a smaller algebraic expression.

## Primary reading

- [Hu et al., LoRA, 2021](https://arxiv.org/abs/2106.09685)

## Continue learning

[Lesson 18](018-compare-fedavg-and-diloco-under-poor-links.md) · [Lesson 20](020-quantify-verifier-cost-under-a-useful-work-threat-model.md) · [HTML study route](../../courses/ai-research/trust-and-protocol-frontiers.html)

*Service to Many Leads to Greatness.*
