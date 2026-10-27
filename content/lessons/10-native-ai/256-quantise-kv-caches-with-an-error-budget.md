# Lesson 256 — Quantise KV caches with an error budget

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · **Implementation language:** C23

**Learning objective:** Understand reduced-precision storage and how quantisation changes attention.

## 1. Understand the concept

KV-cache quantisation stores previously computed K and V values at fewer bits per element. A common affine scheme maps a real value to an integer using a scale and a zero-point. Quantisation saves bandwidth and capacity, but introduces approximation error and the scale metadata also consumes space. Different schemes quantise per tensor, head, channel or block; each has different numerical and operational consequences.

A quantised KV cache is not the same as low-bit model weights. It changes the inputs presented to the attention operator at inference time. The correct comparison therefore includes attention outputs and eventual vocabulary logits, not just reconstructed tensor element error.

## 2. Work through the numbers

For an illustrative symmetric int8 mapping with scale `s=0.02`, the value `0.37` maps to `q=round(0.37/0.02)=19` and dequantises to `19×0.02=0.38`; its absolute error is `0.01`. A value `−0.31` maps to `−16` and reconstructs as `−0.32`. Both operations require clipping to the representable integer range and a documented rounding rule.

A cache of 1,000,000 scalar FP32 elements uses 4,000,000 bytes before metadata. Storing each scalar as int8 uses 1,000,000 bytes, but extra scales and block descriptors reduce the net saving.

## 3. Apply the concept to native model engineering

To evaluate KV quantisation, begin with a float reference cache and generate an int8 candidate without modifying the original tensors. Compare reconstructed K/V values, attention rows, every vocabulary logit and generation behaviour. Classify error on ordinary inputs and on extreme or out-of-range values. Models trained for one precision should not be assumed automatically compatible with another.

The current standalone Framework candidate takes finite FP32 arrays. It does not implement quantised KV cache storage or dequantisation; those are separate design and validation questions.

## 4. Check the mathematical foundation

The related exercise is [Mathematics for AI — Unit 142](../11-maths-for-ai/142-quantise-a-float-with-a-symmetric-scale.md). Work out the arithmetic independently before inspecting an implementation.

## 5. Test your understanding

**Question:** Why can a small element-wise dequantisation error cause a large change in sampled output?

<details>
<summary>Reveal the worked answer</summary>
<p>Errors perturb attention scores, softmax probabilities and downstream logits. Near a decision boundary, even a modest logit change can reorder token probabilities or change which tokens lie in top-p.</p>
</details>

## 6. Key distinctions

The mathematical examples are deliberately small and inspectable. Changes to attention topology, positional schemes, quantisation and decoding policy require explicit model or algorithm contracts. A standalone operator test does not establish complete Transformer equivalence or measured inference acceleration.

## Continue learning

[255 — Measure key/value bandwidth per decode step](255-measure-key-value-bandwidth-per-decode-step.md) · [257 — Understand paged KV memory and block tables](257-understand-paged-kv-memory.md) · [HTML learning path](../../courses/llm-from-scratch/efficient-decoding-learning-path.html)

*Service to Many Leads to Greatness.*
