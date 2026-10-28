# Lesson 416 — Run a local two-process message handoff

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation context:** C23 and Assembly where justified; Framework is the reusable owner.  
**Prerequisites:** Existing native AI, numerical reasoning and source-governance foundations.

## Learning outcomes

By the end of this lesson, you should be able to explain **run a local two-process message handoff**, reproduce the worked reasoning, distinguish observable facts from proposed functionality, and identify a test that would disprove an overly strong claim.

## Concept and background

A controlled native process test is a useful intermediate stage between in-memory unit tests and remote-network deployment. Separate OS processes exchange the same canonical files. This exercises serialisation and independent address spaces without pretending to test network security or distributed learning.

This subject sits at the boundary between mathematical learning and reliable systems engineering. Neural computation may be correct while its messages arrive late, twice or under the wrong identity. Conversely, a protocol may deliver every byte correctly while the resulting model becomes less useful. Treat these as independently testable claims rather than one success indicator. Start with synthetic, authorised data and pin an immutable base-checkpoint commitment before investigating network or adversarial behaviour.

## Step-by-step mechanism

1. **The coordinator writes a versioned assignment to a temporary file.** Write down the invariant or input boundary so that an independent reader can check the outcome.
2. **A distinct worker process reads and checks the frame.** Choose a bounded representation and reject unsupported cases rather than silently guessing values.
3. **The worker computes a clearly labelled synthetic delta.** Use an established Umicom Framework service wherever one already owns this responsibility.
4. **It writes a new checksum-protected result file.** Make failure and ownership states explicit before invoking numerical or application code.
5. **A distinct coordinator process reads and matches the result.** Record which assertion is proved by the available evidence and which still requires an external check.
6. **CTest fixture dependencies prevent running consumers before producers..** Keep the smallest negative test that would distinguish a valid implementation from a convincing-looking demonstration.

## Worked example

An assignment is 216 bytes; the worker returns one FP32 scalar so the result is 220 bytes. Three processes can use ordinary local files, but the measured time includes filesystem behaviour rather than TCP latency.

The numbers here are an instructional fixture. Reproduce them with ordinary arithmetic before relying on software output. If a figure represents an estimate, identify the omitted costs; if it represents a test result, identify the exact executable and inputs that produced it.

## Native Umicom application

The native demonstration provides `emit`, `worker` and `finish` modes, and keeps its files under the build tree rather than the public source repository.

The Framework remains responsible for reusable behaviour, numerical aggregation, model identity and message contracts. Desktop applications and learning laboratories should consume those APIs rather than create competing maths, protocol, source-governance or security implementations. A local demonstration is not automatically evidence for a production network.

## Security, governance and research limitations

> **Do not overclaim.** A local-file process boundary is not a LAN/WAN experiment and is not a cryptographically authenticated channel.

A useful evidence record distinguishes (a) structural validity, (b) identity/authorisation, (c) computational or experimental integrity and (d) independently measured model quality. Record failures as carefully as successes. Use reviewed and synthetic datasets while learning; ordinary access to source code, banking records or research documents is not permission to distribute them for training.

## Exercise — solve before revealing the answer

**Question:** What new property does a separate-process test validate that a single-process struct copy does not?

<details><summary>Reveal the worked answer</summary>

The recipient has a separate address space and must interpret the serialised representation; host pointers and implicit shared memory cannot be relied upon.

</details>

## Extend the investigation

Sketch a negative test, a relevant resource or memory bound, and a realistic experimental control for this topic. Explain what the test could falsify and what it cannot establish. When performance matters, measure the full operation under fixed hardware, compiler flags and a documented input rather than inferring a runtime gain from a smaller algebraic expression.

## Primary reading

- [Ryabinin et al., SWARM Parallelism](https://arxiv.org/abs/2301.11913)

## Continue learning

[Lesson 415](415-build-a-failure-atomic-native-frame-parser.md) · [Lesson 417](417-compose-three-synthetic-workers-with-fedavg.md) · [HTML study route](../../courses/llm-from-scratch/wire-transport-learning-path.html)

*Service to Many Leads to Greatness.*
