# AI Research Frontiers — Lesson 049: Pre-register FedAvg versus local-SGD comparisons

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** AI Research Frontiers · **Method:** reason → compute → test → qualify

## Learning objective

Optimisation research needs a falsifiable comparison with data/compute matched baselines. A lower network byte count is not sufficient if final model quality degrades.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

Optimisation research needs a falsifiable comparison with data/compute matched baselines. A lower network byte count is not sufficient if final model quality degrades. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

Hold total training tokens and initial checkpoint fixed while varying local steps 1,4,16 and WAN RTT 10/100 ms.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Record experiment identity and data manifests in Framework; no Python project functionality is introduced.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** What should the primary endpoint be?

<details><summary>Reveal a worked answer</summary>

Pre-register held-out loss or time to a fixed quality threshold, then report bytes and energy as secondary measures.

</details>

## Security, scientific and governance limits

Different non-IID partitions can change both convergence and fairness.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [DiLoCo research](https://arxiv.org/abs/2311.08105)
- [LoRA research](https://arxiv.org/abs/2106.09685)
- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Previous lesson](048-write-a-falsifiable-native-merkle-research-protocol.md)
- [Next lesson](050-test-verification-cost-against-malicious-behaviour.md)
- [Browser lesson](../../courses/ai-research/lessons/049-pre-register-fedavg-versus-local-sgd-comparisons.html)
- [Complete study route](../../courses/ai-research/verifiable-learning-research-methods.html)

*Service to Many Leads to Greatness.*
