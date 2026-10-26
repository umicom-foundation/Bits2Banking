# Lesson 134 — Understand BOS left-padding and rolling context

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Topic:** Native C23 Transformers, inference and independent validation.

**Learning objective:** Explain how short prompts and longer histories occupy learned absolute positions.

## 1. Understand the engineering problem

A decoder with learned absolute positional embeddings does not treat a token at position zero as the same numerical input as that token at position three. Its position vector is added before the first Transformer layer. Consequently prompt layout is a semantic decision, not a cosmetic memory-copy detail. The stacked generation interface deliberately retains the older full-context, beginning-of-sequence (BOS) left-padding rule.

## 2. Follow a concrete example

With context length four and the two byte tokens for `in`, the numeric prompt is `[109,114]`. The complete input becomes `[BOS,BOS,109,114]`, where BOS is reserved ID 1. The model predicts using logits from index 3. After it emits token `x`, the next context becomes `[BOS,109,114,x]`. After the next emission `y`, it becomes `[109,114,x,y]`. When another token arrives, the oldest ID falls out, the three surviving IDs shift left and their learned positions change.

## 3. Implement through the Framework

`UmiAiTrainingStackedGenerationSessionCreate` validates every supplied ID before constructing the retained context. Even if a prompt has more than four tokens, an invalid older ID is rejected rather than ignored. A permitted prompt can contain up to 4,096 IDs; only its latest context-length entries are retained. The session copies the retained context. Applications need not preserve the original prompt array after successful creation.

## 4. Check the boundaries

Because a rolling context changes the input positions, retaining upper-layer hidden states without a new proof could give different logits. The existing single-block rotary research does not establish correct multi-layer eviction semantics. This implementation intentionally recomputes the entire stack rather than inventing a cache speedup. Use the distinct unpadded-prefix teaching API only when its different semantics are explicitly intended.

## Practice

**Question:** For a five-position context and a three-token prompt, how many BOS tokens precede the prompt?

<details>
<summary>Reveal the worked answer</summary>

Two BOS tokens are inserted on the left: `5 − 3 = 2`. The three real prompt IDs occupy positions 2, 3 and 4.

</details>

## Continue

[Return to the native stacked inference learning path](stacked-inference-learning-path.md). For the mathematical background, read the [stacked inference mathematics guide](../11-maths-for-ai/stacked-inference-mathematics.md). The canonical APIs are in `framework/include/umicom/ai/training/`; implementations and native tests remain in Umicom Framework, not in this educational repository.

*Service to Many Leads to Greatness.*
