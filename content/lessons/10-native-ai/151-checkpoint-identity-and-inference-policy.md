# Lesson 151 — Keep model identity separate from generation policy

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Native C23 and AI engineering.

## Learning objectives

Understand the core engineering invariant, work through a bounded example, identify what Umicom Framework already implements and distinguish verified facts from proposed improvements.

## 1. The idea from first principles

A model checkpoint contains a particular family of weights. The input-construction policy decides where the prompt tokens appear, which special token is used for padding, and when a context rolls. These are separate aspects of reproducibility.

Consider a four-position decoder receiving two token IDs, `10` and `11`. A left-padded input might be `[BOS, BOS, 10, 11]`, whereas a growing-prefix input begins `[10, 11]` at position zero. A model with learned absolute positions is allowed to give different predictions in these two cases. Giving both results the same checkpoint hash does not mean they are numerically comparable.

A trustworthy experiment records at least the exact checkpoint digest, configuration, prompt token IDs, context-construction rule, temperature, top-K/top-p settings, seed and number of tokens. A hash identifies bytes, not the identity of their publisher or the truthfulness of the generated text.

## 2. Connect the lesson to Umicom Framework

The existing `UmiAiTrainingStackedModelIdentityCapture` and `Verify` APIs bind execution to the canonical stacked checkpoint. `UmiAiTrainingStackedGenerationEvidenceBuild` and `Verify` reproduce generated IDs with the same supported policy and seed. They do not authenticate a publisher or approve model output for banking workflows.

Before attempting a new cache or positional model, preserve the original stacked family and introduce an opt-in architecture or policy identifier with its own tests. Do not reinterpret saved learned-absolute weights as rotary weights.

## 3. Practice

**Question:** Can two generation experiments use exactly the same model checkpoint but produce different outputs without either being a software defect?

<details><summary>Reveal the worked answer</summary>

Yes. Their token placement, sampling settings or seed may differ. A correct comparison fixes all declared inputs and records the policy along with checkpoint bytes.

</details>

## Further reading

Review [the multi-layer inference lesson](148-build-and-qualify-native-stacked-inference.md), [the introduction to the stacked decoder](121-build-a-real-multi-layer-transformer.md) and [the mathematics companion](../11-maths-for-ai/stacked-inference-mathematics.md).

*All numerical examples are educational; no model-generated source or financial transaction is executed. Service to Many Leads to Greatness.*
