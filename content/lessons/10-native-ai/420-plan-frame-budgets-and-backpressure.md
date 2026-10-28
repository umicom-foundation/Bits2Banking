# Lesson 420 — Plan frame budgets and backpressure

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation context:** C23 and Assembly where justified; Framework is the reusable owner.  
**Prerequisites:** Existing native AI, numerical reasoning and source-governance foundations.

## Learning outcomes

By the end of this lesson, you should be able to explain **plan frame budgets and backpressure**, reproduce the worked reasoning, distinguish observable facts from proposed functionality, and identify a test that would disprove an overly strong claim.

## Concept and background

Bounding the payload before allocation is central to both memory safety and network fairness. The wire service has an explicit maximum of 4,096 FP32 parameters. Higher-level admission reserves a declared transfer budget separately; that reservation is a forecast and must not be mistaken for actual bytes measured on a network interface.

This subject sits at the boundary between mathematical learning and reliable systems engineering. Neural computation may be correct while its messages arrive late, twice or under the wrong identity. Conversely, a protocol may deliver every byte correctly while the resulting model becomes less useful. Treat these as independently testable claims rather than one success indicator. Start with synthetic, authorised data and pin an immutable base-checkpoint commitment before investigating network or adversarial behaviour.

## Step-by-step mechanism

1. **Calculate fixed framing overhead and maximum payload.** Write down the invariant or input boundary so that an independent reader can check the outcome.
2. **Check the declared transfer capacity before issuing a job.** Choose a bounded representation and reject unsupported cases rather than silently guessing values.
3. **Account for retries and cryptographic channel overhead separately.** Use an established Umicom Framework service wherever one already owns this responsibility.
4. **Set limits for concurrent outstanding jobs.** Make failure and ownership states explicit before invoking numerical or application code.
5. **Measure actual bytes at the transport boundary.** Record which assertion is proved by the available evidence and which still requires an external check.
6. **Apply backpressure rather than buffering unbounded results..** Keep the smallest negative test that would distinguish a valid implementation from a convincing-looking demonstration.

## Worked example

At 4,096 parameters, 16,384 payload bytes plus a 216-byte header/trailer yield 16,600 total bytes. At 10 Mbps, ideal serialisation alone is 13.28 milliseconds. Real transfer time also includes RTT, TCP/TLS, scheduling and contention.

The numbers here are an instructional fixture. Reproduce them with ordinary arithmetic before relying on software output. If a figure represents an estimate, identify the omitted costs; if it represents a test result, identify the exact executable and inputs that produced it.

## Native Umicom application

The same bounded admission concepts will serve future Umicom Bank/TMS messaging and distributed data services, with stricter domain-specific validation.

The Framework remains responsible for reusable behaviour, numerical aggregation, model identity and message contracts. Desktop applications and learning laboratories should consume those APIs rather than create competing maths, protocol, source-governance or security implementations. A local demonstration is not automatically evidence for a production network.

## Security, governance and research limitations

> **Do not overclaim.** A byte-budget forecast is not equal to measured network utilisation and cannot support performance claims by itself.

A useful evidence record distinguishes (a) structural validity, (b) identity/authorisation, (c) computational or experimental integrity and (d) independently measured model quality. Record failures as carefully as successes. Use reviewed and synthetic datasets while learning; ordinary access to source code, banking records or research documents is not permission to distribute them for training.

## Exercise — solve before revealing the answer

**Question:** What is the maximum schema-one result frame size for 4,096 FP32 values?

<details><summary>Reveal the worked answer</summary>

184 + (4,096 × 4) + 32 = 16,600 bytes.

</details>

## Extend the investigation

Sketch a negative test, a relevant resource or memory bound, and a realistic experimental control for this topic. Explain what the test could falsify and what it cannot establish. When performance matters, measure the full operation under fixed hardware, compiler flags and a documented input rather than inferring a runtime gain from a smaller algebraic expression.

## Primary reading

- [Douillard et al., DiLoCo, 2023/2024](https://arxiv.org/abs/2311.08105)

## Continue learning

[Lesson 419](419-prevent-stale-and-cross-round-result-acceptance.md) · [Lesson 421](421-keep-data-gradients-and-private-metadata-off-public-ledgers.md) · [HTML study route](../../courses/llm-from-scratch/wire-transport-learning-path.html)

*Service to Many Leads to Greatness.*
