# Lesson 421 — Keep data, gradients and private metadata off public ledgers

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation context:** C23 and Assembly where justified; Framework is the reusable owner.  
**Prerequisites:** Existing native AI, numerical reasoning and source-governance foundations.

## Learning outcomes

By the end of this lesson, you should be able to explain **keep data, gradients and private metadata off public ledgers**, reproduce the worked reasoning, distinguish observable facts from proposed functionality, and identify a test that would disprove an overly strong claim.

## Concept and background

Blockchain consensus is an optional governance choice around the training loop, not a replacement for model arithmetic. Publishing full gradients, private datasets or full checkpoints on a public chain can expose confidential information and create severe storage and rights-handling problems.

This subject sits at the boundary between mathematical learning and reliable systems engineering. Neural computation may be correct while its messages arrive late, twice or under the wrong identity. Conversely, a protocol may deliver every byte correctly while the resulting model becomes less useful. Treat these as independently testable claims rather than one success indicator. Start with synthetic, authorised data and pin an immutable base-checkpoint commitment before investigating network or adversarial behaviour.

## Step-by-step mechanism

1. **Retain dataset bytes in authorised storage.** Write down the invariant or input boundary so that an independent reader can check the outcome.
2. **Publish only carefully selected commitments if a multi-party ledger is justified.** Choose a bounded representation and reject unsupported cases rather than silently guessing values.
3. **Assess whether hashes of predictable personal data enable guessing attacks.** Use an established Umicom Framework service wherever one already owns this responsibility.
4. **Keep source rights and revocation metadata with the governed archive.** Make failure and ownership states explicit before invoking numerical or application code.
5. **Record verification outcomes rather than raw training traces.** Record which assertion is proved by the available evidence and which still requires an external check.
6. **Measure ledger finality and cost separately from model convergence..** Keep the smallest negative test that would distinguish a valid implementation from a convincing-looking demonstration.

## Worked example

An 80-MiB checkpoint recorded every ten steps would quickly dominate ledger storage; a 32-byte commitment is far smaller. However, a short hash of a low-entropy private identifier can still be guessed, so confidentiality is not guaranteed by hashing.

The numbers here are an instructional fixture. Reproduce them with ordinary arithmetic before relying on software output. If a figure represents an estimate, identify the omitted costs; if it represents a test result, identify the exact executable and inputs that produced it.

## Native Umicom application

The Framework record-chain service is a candidate for permissioned audit receipts; record-chain storage is not by itself a consensus blockchain.

The Framework remains responsible for reusable behaviour, numerical aggregation, model identity and message contracts. Desktop applications and learning laboratories should consume those APIs rather than create competing maths, protocol, source-governance or security implementations. A local demonstration is not automatically evidence for a production network.

## Security, governance and research limitations

> **Do not overclaim.** Immutable records may conflict with deletion requirements; plan off-chain storage and controlled lifecycle, not permanent publication of protected content.

A useful evidence record distinguishes (a) structural validity, (b) identity/authorisation, (c) computational or experimental integrity and (d) independently measured model quality. Record failures as carefully as successes. Use reviewed and synthetic datasets while learning; ordinary access to source code, banking records or research documents is not permission to distribute them for training.

## Exercise — solve before revealing the answer

**Question:** Would publishing a dataset’s SHA-256 on a public chain automatically protect its confidentiality?

<details><summary>Reveal the worked answer</summary>

No. Predictable small datasets can be guessed and hashed by outsiders; hashes are commitments, not encryption or a lawful disclosure policy.

</details>

## Extend the investigation

Sketch a negative test, a relevant resource or memory bound, and a realistic experimental control for this topic. Explain what the test could falsify and what it cannot establish. When performance matters, measure the full operation under fixed hardware, compiler flags and a documented input rather than inferring a runtime gain from a smaller algebraic expression.

## Primary reading

- [Systematisation of blockchain-based decentralised AI](https://arxiv.org/abs/2411.17461)

## Continue learning

[Lesson 420](420-plan-frame-budgets-and-backpressure.md) · [Lesson 422](422-design-provenance-receipts-without-claiming-training-proof.md) · [HTML study route](../../courses/llm-from-scratch/wire-transport-learning-path.html)

*Service to Many Leads to Greatness.*
