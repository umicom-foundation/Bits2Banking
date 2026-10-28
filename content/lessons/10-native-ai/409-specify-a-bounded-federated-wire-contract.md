# Lesson 409 — Specify a bounded federated wire contract

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation context:** C23 and Assembly where justified; Framework is the reusable owner.  
**Prerequisites:** Existing native AI, numerical reasoning and source-governance foundations.

## Learning outcomes

By the end of this lesson, you should be able to explain **specify a bounded federated wire contract**, reproduce the worked reasoning, distinguish observable facts from proposed functionality, and identify a test that would disprove an overly strong claim.

## Concept and background

A wire protocol is a language spoken by separate processes, not a byte dump of a C structure. Pointers, padding, size_t widths and host byte order must not enter the format. Stable schema revision, kind, round, correlation and a bounded payload are the minimum for an inspectable learning experiment.

This subject sits at the boundary between mathematical learning and reliable systems engineering. Neural computation may be correct while its messages arrive late, twice or under the wrong identity. Conversely, a protocol may deliver every byte correctly while the resulting model becomes less useful. Treat these as independently testable claims rather than one success indicator. Start with synthetic, authorised data and pin an immutable base-checkpoint commitment before investigating network or adversarial behaviour.

## Step-by-step mechanism

1. **Identify which values are metadata and which are mathematical arrays.** Write down the invariant or input boundary so that an independent reader can check the outcome.
2. **Define one maximum frame size before allocating.** Choose a bounded representation and reject unsupported cases rather than silently guessing values.
3. **Choose explicit field widths and byte order.** Use an established Umicom Framework service wherever one already owns this responsibility.
4. **Require a finite, known encoding for every parameter.** Make failure and ownership states explicit before invoking numerical or application code.
5. **Separate parsing from caller authorisation.** Record which assertion is proved by the available evidence and which still requires an external check.
6. **Version the entire message, not just the C header..** Keep the smallest negative test that would distinguish a valid implementation from a convincing-looking demonstration.

## Worked example

A 184-byte header and 32-byte digest around one FP32 parameter require 184 + 4 + 32 = 220 bytes. A vector of 4,096 parameters requires 16,600 bytes. Neither number includes transport framing, TLS, TCP or storage metadata.

The numbers here are an instructional fixture. Reproduce them with ordinary arithmetic before relying on software output. If a figure represents an estimate, identify the omitted costs; if it represents a test result, identify the exact executable and inputs that produced it.

## Native Umicom application

The native Framework codec creates the same canonical bytes on little-endian and big-endian hosts, provided float semantics agree. Studio, LLM and the teaching application should consume its C ABI, not implement their own parsers.

The Framework remains responsible for reusable behaviour, numerical aggregation, model identity and message contracts. Desktop applications and learning laboratories should consume those APIs rather than create competing maths, protocol, source-governance or security implementations. A local demonstration is not automatically evidence for a production network.

## Security, governance and research limitations

> **Do not overclaim.** A valid parse is not proof that the sender is authorised or that a worker ran a training step.

A useful evidence record distinguishes (a) structural validity, (b) identity/authorisation, (c) computational or experimental integrity and (d) independently measured model quality. Record failures as carefully as successes. Use reviewed and synthetic datasets while learning; ordinary access to source code, banking records or research documents is not permission to distribute them for training.

## Exercise — solve before revealing the answer

**Question:** Why must a wire format forbid serialising a raw pointer?

<details><summary>Reveal the worked answer</summary>

A pointer is valid only within an address space and lifetime. A remote process cannot dereference it reliably, and encoding it may disclose address-space information.

</details>

## Extend the investigation

Sketch a negative test, a relevant resource or memory bound, and a realistic experimental control for this topic. Explain what the test could falsify and what it cannot establish. When performance matters, measure the full operation under fixed hardware, compiler flags and a documented input rather than inferring a runtime gain from a smaller algebraic expression.

## Primary reading

- [McMahan et al., FedAvg, AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue learning

Previous study route is available in the HTML course. · [Lesson 410](410-encode-integers-and-fp32-deterministically.md) · [HTML study route](../../courses/llm-from-scratch/wire-transport-learning-path.html)

*Service to Many Leads to Greatness.*
