# Lesson 265 — Trace one query through the stacked decoder

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · Native C23

**Learning objective:** Identify the hand-off between the learned Transformer and its retained K/V state.

## 1. Concept and motivation

A decoder block first normalises the newest hidden state, obtains its Q/K/V projections, uses historical keys and values to calculate causal attention, and then applies the output projection, residual, second normalisation and feed-forward network. The cached rows are not token embeddings. They are layer-specific projections produced by a particular frozen checkpoint and absolute token position. Before optimisation, tracing the exact interfaces is more useful than counting abstract operations.

## 2. Worked example

For a two-layer model with three retained tokens, layer 0 reads its three K/V rows and calculates one new Q/K/V; its output becomes layer 1’s input. Layer 1 uses its own three historical K/V rows rather than reusing layer 0’s. The new token occupies position 3 in both layers. The result is a single vocabulary-logit vector, not two independent predictions.

## 3. Native Framework implementation and evidence

Follow the C23 call chain `UmiAiTrainingStackedKvIncrementalSessionNext` → `UmiAiTrainingStackedKvStepPropose` → `KvStepLayer`. Inspect the model identity, the store row count and the tape checkpoint before following Q, K and V. A token is sampled only after the candidate logits are accepted.

## 4. Mathematical companion

Read [Mathematics Unit 149 — Locate the newest query row](../11-maths-for-ai/149-locate-the-newest-query-row.md). Check each numerical assumption against the example above before running a program.

## 5. Exercise

**Question:** Why would substituting layer 0 historical values for layer 1 historical values produce an invalid model?

<details>
<summary>Reveal the worked answer</summary>

Each layer has its own weights and its own hidden-state inputs. Therefore the projections belong to different mathematical spaces even when their shapes happen to match.

</details>

## 6. Interpretation

The model checkpoint and absolute-position policy determine whether a cached row may be reused.

## Continue learning

[Lesson 264](264-complete-the-native-inference-qualification-capstone.md) · [266 — Distinguish forward inference from automatic differentiation](266-distinguish-forward-inference-from-autodiff.md) · [Browser learning path](../../courses/llm-from-scratch/integrated-attention-learning-path.html)
