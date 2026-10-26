# Backpropagate through several Transformer blocks

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Progressive native C23 / AI engineering

## One loss, gradients through the whole stack

Training works only if an error at the final vocabulary head can influence earlier learnable weights. Write the forward path as `H1 = Block1(X)`, `H2 = Block2(H1)`, and `L = Loss(Logits(H2), targets)`. The backward pass traverses these dependencies in reverse. It must differentiate the vocabulary projection, Block 2, Block 1, position/token embeddings, and all parameters that contributed to the selected outputs.

The stacked model does not implement a second differentiation algorithm. It uses the existing `UmiAiTrainingBackward`, then updates all trainable leaves in one `UmiAiTrainingSgdStepMany` transaction. This is **full-model educational SGD**, not adapter-only fine-tuning. The selected-token loss is the Framework's existing `UmiAiTrainingSelectedCrossEntropy` composition.

## Updating safely

A train step performs forward computation, selected loss, backwards differentiation and transactional parameter update. Then it rolls the transient graph back to the retained parameter prefix. The weights persist; old intermediate activations do not. A failed candidate SGD transaction must not leave a partially updated layer.

The returned loss describes **before-update** cross-entropy. To measure the new model, call the evaluation API again after the update. A single training example may improve while a held-out example worsens; neither outcome should be concealed.

## Practical use

```c
UmiAiTrainingStackedStep step = {0};
UmiStatus status = UmiAiTrainingStackedDecoderTrainSelected(
    model, inputs, targets, lossMask, contextLength,
    0.025F, &step);
```

The caller owns the token arrays and mask; `model` owns every tensor and optimiser write. Do not mutate the model concurrently from a user interface or background worker.

## Practice

If the model has 27 trainable tensors, should the application perform 27 independent weight updates? Why not?

<details><summary>Worked answer</summary>

No. Pass all parameter handles to the Framework's existing transactional multi-parameter updater. It validates the complete candidate update before changing weights. Independently applying updates can leave an inconsistent partial model if a later parameter fails.

</details>

---

[Native stacked Transformer reading path](stacked-transformer-learning-path.md) · [Mathematics for AI](../11-maths-for-ai/stacked-transformer-mathematics.md)
