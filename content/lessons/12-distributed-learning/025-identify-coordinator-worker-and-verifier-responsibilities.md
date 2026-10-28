# Lesson 025 — Identify coordinator, worker and verifier responsibilities

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation context:** C23 and Assembly where justified; Framework is the reusable owner.  
**Prerequisites:** Existing native AI, numerical reasoning and source-governance foundations.

## Learning outcomes

By the end of this lesson, you should be able to explain **identify coordinator, worker and verifier responsibilities**, reproduce the worked reasoning, distinguish observable facts from proposed functionality, and identify a test that would disprove an overly strong claim.

## Concept and background

A coordinator owns round admission and pending tickets; a worker receives an approved assignment and returns a bounded result; a verifier checks identity, policy and numerical evidence. These roles need not run on the same machine, but initially are trusted and permissioned.

This subject sits at the boundary between mathematical learning and reliable systems engineering. Neural computation may be correct while its messages arrive late, twice or under the wrong identity. Conversely, a protocol may deliver every byte correctly while the resulting model becomes less useful. Treat these as independently testable claims rather than one success indicator. Start with synthetic, authorised data and pin an immutable base-checkpoint commitment before investigating network or adversarial behaviour.

## Step-by-step mechanism

1. **Identify the coordinator-owned state.** Write down the invariant or input boundary so that an independent reader can check the outcome.
2. **Describe the worker-visible message.** Choose a bounded representation and reject unsupported cases rather than silently guessing values.
3. **Separate numerical claims from security claims.** Use an established Umicom Framework service wherever one already owns this responsibility.
4. **Construct one safe synthetic example.** Make failure and ownership states explicit before invoking numerical or application code.
5. **Consider a duplicate, stale or malicious input.** Record which assertion is proved by the available evidence and which still requires an external check.
6. **Explain the independently checked acceptance condition.** Keep the smallest negative test that would distinguish a valid implementation from a convincing-looking demonstration.

## Worked example

Draw three boxes: coordinator, worker, verifier. Mark which holds the private local ticket (coordinator), which can access assigned training data (worker), and which should evaluate a candidate on an independent held-out set (verifier).

The numbers here are an instructional fixture. Reproduce them with ordinary arithmetic before relying on software output. If a figure represents an estimate, identify the omitted costs; if it represents a test result, identify the exact executable and inputs that produced it.

## Native Umicom application

Use the existing Framework job, messaging and provenance APIs to express this experiment. Education and LLM applications should present a thin workbench, while reusable implementation stays in Framework.

The Framework remains responsible for reusable behaviour, numerical aggregation, model identity and message contracts. Desktop applications and learning laboratories should consume those APIs rather than create competing maths, protocol, source-governance or security implementations. A local demonstration is not automatically evidence for a production network.

## Security, governance and research limitations

> **Do not overclaim.** An honest local example cannot demonstrate security against unknown external workers or improvement on real training data.

A useful evidence record distinguishes (a) structural validity, (b) identity/authorisation, (c) computational or experimental integrity and (d) independently measured model quality. Record failures as carefully as successes. Use reviewed and synthetic datasets while learning; ordinary access to source code, banking records or research documents is not permission to distribute them for training.

## Exercise — solve before revealing the answer

**Question:** Why should a worker never receive an internal job ticket?

<details><summary>Reveal the worked answer</summary>

The ticket is process-local authority. Send only public correlation values and independently verified assignment metadata.

</details>

## Extend the investigation

Sketch a negative test, a relevant resource or memory bound, and a realistic experimental control for this topic. Explain what the test could falsify and what it cannot establish. When performance matters, measure the full operation under fixed hardware, compiler flags and a documented input rather than inferring a runtime gain from a smaller algebraic expression.

## Primary reading

- [McMahan et al., FedAvg, AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue learning

Previous study route is available in the HTML course. · [Lesson 26](026-construct-a-round-scoped-assignment.md) · [HTML study route](../../courses/distributed-learning/worker-messaging-and-replay.html)

*Service to Many Leads to Greatness.*
