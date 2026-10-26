# Supervise only the reviewed completion tokens

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Progressive native C23 / AI engineering

## Prompt context is different from an answer target

An assistant receives instructions and surrounding text, then produces a response. During supervised fine-tuning we often want the prompt to condition the response without treating every prompt token as an answer the model should imitate. The existing Framework `UmiAiTrainingSupervisedByteWindowBuild` prepares fixed-width input IDs, next-token targets and a zero/one loss mask.

`UmiAiTrainingStackedDecoderTrainSelected` accepts those arrays and delegates row selection and cross-entropy to `UmiAiTrainingSelectedCrossEntropy`. In the loss, a selected row contributes one negative log-probability of the correct next token. Mask-zero rows do not contribute direct loss. Selected rows can still backpropagate through earlier prompt-token representations because the response is *conditioned* on those tokens.

## A four-position example

For a one-byte prompt `Q` and a one-byte answer `A`, a complete stream is `[BOS, Q, A, EOS]`. The teaching window uses the first three items as inputs, the next three as targets, and right-pads to a four-token context. The mask is `[0, 1, 1, 0]`: predicting the answer and EOS is supervised, while prompt imitation and padding are ignored.

## Provenance remains mandatory

Masking does not grant permission to train. A real document or caption must pass the existing Umicom rights/privacy review and source-hash checks. The current native byte tokenizer preserves UTF-8 bytes but does not provide subword vocabulary, conversation role semantics or automated PII removal.

## Practice

A context has six positions with loss mask `[0,0,1,1,1,0]`. How many targets contribute to the mean loss? Does a mask-zero prompt position necessarily receive zero gradient everywhere?

<details><summary>Worked answer</summary>

Three targets contribute to the mean. A prompt position contributes no **direct** cross-entropy row loss, but its representation can influence later selected response rows through causal attention and can therefore receive indirect gradients.

</details>

---

[Native stacked Transformer reading path](stacked-transformer-learning-path.md) · [Mathematics for AI](../11-maths-for-ai/stacked-transformer-mathematics.md)
