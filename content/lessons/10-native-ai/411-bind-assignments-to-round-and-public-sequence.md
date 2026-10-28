# Lesson 411 — Bind assignments to round and public sequence

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation context:** C23 and Assembly where justified; Framework is the reusable owner.  
**Prerequisites:** Existing native AI, numerical reasoning and source-governance foundations.

## Learning outcomes

By the end of this lesson, you should be able to explain **bind assignments to round and public sequence**, reproduce the worked reasoning, distinguish observable facts from proposed functionality, and identify a test that would disprove an overly strong claim.

## Concept and background

The existing FederatedJob ticket carries an in-process job identity, serial and slot index. These are capability handles, not credentials that should cross process boundaries. A public round and sequence instead give a remote worker a correlation identifier; the coordinator still owns the actual ticket.

This subject sits at the boundary between mathematical learning and reliable systems engineering. Neural computation may be correct while its messages arrive late, twice or under the wrong identity. Conversely, a protocol may deliver every byte correctly while the resulting model becomes less useful. Treat these as independently testable claims rather than one success indicator. Start with synthetic, authorised data and pin an immutable base-checkpoint commitment before investigating network or adversarial behaviour.

## Step-by-step mechanism

1. **Create and admit an assignment locally.** Write down the invariant or input boundary so that an independent reader can check the outcome.
2. **Save its ticket in coordinator-owned memory.** Choose a bounded representation and reject unsupported cases rather than silently guessing values.
3. **Publish only approved metadata and the public round/sequence.** Use an established Umicom Framework service wherever one already owns this responsibility.
4. **Require the result to echo that correlation.** Make failure and ownership states explicit before invoking numerical or application code.
5. **Match its immutable worker, model, shard and policy identities.** Record which assertion is proved by the available evidence and which still requires an external check.
6. **Use the private ticket only for local completion..** Keep the smallest negative test that would distinguish a valid implementation from a convincing-looking demonstration.

## Worked example

Worker B receives round 41 and sequence 2. Its result must echo both. The coordinator also checks a previously admitted worker-B commitment. A response with sequence 1 is not an alternative ticket, even if its float vector is well formed.

The numbers here are an instructional fixture. Reproduce them with ordinary arithmetic before relying on software output. If a figure represents an estimate, identify the omitted costs; if it represents a test result, identify the exact executable and inputs that produced it.

## Native Umicom application

Transport adapters can deliver messages to Studio or an LLM workbench without exposing the job object or mutable storage to applications.

The Framework remains responsible for reusable behaviour, numerical aggregation, model identity and message contracts. Desktop applications and learning laboratories should consume those APIs rather than create competing maths, protocol, source-governance or security implementations. A local demonstration is not automatically evidence for a production network.

## Security, governance and research limitations

> **Do not overclaim.** A sequence number is not a cryptographically unpredictable nonce and does not authenticate a worker.

A useful evidence record distinguishes (a) structural validity, (b) identity/authorisation, (c) computational or experimental integrity and (d) independently measured model quality. Record failures as carefully as successes. Use reviewed and synthetic datasets while learning; ordinary access to source code, banking records or research documents is not permission to distribute them for training.

## Exercise — solve before revealing the answer

**Question:** If a worker supplies the right model hash but the wrong public sequence, should the coordinator submit its delta?

<details><summary>Reveal the worked answer</summary>

No. Correlation with the pending round and sequence is required in addition to all immutable identity and policy checks.

</details>

## Extend the investigation

Sketch a negative test, a relevant resource or memory bound, and a realistic experimental control for this topic. Explain what the test could falsify and what it cannot establish. When performance matters, measure the full operation under fixed hardware, compiler flags and a documented input rather than inferring a runtime gain from a smaller algebraic expression.

## Primary reading

- [McMahan et al., FedAvg, AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue learning

[Lesson 410](410-encode-integers-and-fp32-deterministically.md) · [Lesson 412](412-distinguish-a-checksum-from-authenticated-learning.md) · [HTML study route](../../courses/llm-from-scratch/wire-transport-learning-path.html)

*Service to Many Leads to Greatness.*
