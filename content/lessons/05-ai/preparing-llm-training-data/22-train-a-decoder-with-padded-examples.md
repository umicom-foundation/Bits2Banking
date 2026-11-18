<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/22-train-a-decoder-with-padded-examples.md

PURPOSE:
Train a decoder with padded examples

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Train a decoder with padded examples

[Course contents](index.md)

## Move from the arithmetic exercise to a model

The previous lesson used three invented values to distinguish attention selection from objective selection. This lesson carries those policies through a small native decoder. A decoder here is a neural network that receives token IDs and produces scores for possible next tokens. It contains trainable embedding tables, a transformer block and an output projection. You will train this small model on a fixed artificial batch, measure its selected objective and check that temporary graph storage is released after each step.

This is a mechanics exercise. It does not load a large language model, train on your documents or establish useful language ability. We use the existing Framework decoder so that the application code can focus on data policy and lifetime. Before starting, complete the earlier lessons on tokenization, shifted targets, dataset splits, selected loss and attention masks. Keep a page for writing array positions and expected behavior before you compile.


## Understand the six configuration fields

The example configuration is {8, 3, 4, 8, 2, 42}. Read the public configuration declaration beside it instead of memorizing positional numbers. Vocabulary size eight permits token IDs zero through seven. Context length three gives each independent sequence three positions. Four channels describe the embedding width. Eight hidden channels describe the feed-forward expansion. Two attention heads split the four channels into two groups. Seed 42 selects a repeatable initialization within the same implementation; it is not a promise of identical floating-point results on every compiler or machine.


## Lay out two examples on paper

~~~text
input IDs:       [1, 2, 3 | 4, 5, 6]
target IDs:      [2, 3, 4 | 5, 6, 7]
attention:       [1, 0, 1 | 0, 1, 1]
objective:       [0, 0, 1 | 0, 0, 1]
position index:  [0, 1, 2 | 0, 1, 2]
~~~

The vertical bar is a visual separator, not part of the C array. Each group of three is a separate sequence. The first position of the second sequence cannot attend to any position in the first. Targets are the IDs to predict at the corresponding input positions. The last input in each group predicts the last target in that group; only those two predictions are scored. These arrays are invented and already shifted. A real tokenizer and batch builder must produce the actual IDs and target alignment.

The attention mask marks one interior hole and one leading hole. Positions do not collapse when a row is excluded: the final row still has position index two. This matters because the decoder adds position embeddings. Removing a token and shifting all later positions is a different transformation from keeping its storage position but excluding it from attention. Describe the policy explicitly when preparing real data.


## Validate the relationship between the masks

1. Require exactly six bytes in each mask because this fixture has six token rows.
2. Require every byte to be zero or one. A nonzero byte such as two is invalid, not another spelling of true for this API.
3. Require each objective byte of one to have an attention byte of one at the same position. Scored output must represent a real position.
4. Require at least one scored row across the batch. The mean objective needs a nonzero denominator.
5. Check every input and target ID against the vocabulary, including excluded placeholders. Padding does not exempt IDs from the input contract.

The first input ID and the fifth input ID are useful context but have zero objective bytes. Their information can influence the selected predictions and their shared model parameters can receive gradients. A zero objective byte does not freeze a token embedding. Parameter freezing is a separate training feature and should not be inferred from a data mask.


## Read the model lifecycle

~~~c
UmiAiTrainingDecoder *model = NULL;
UmiStatus status = UmiAiTrainingDecoderCreate(&config, &model);
/* Check status before evaluating or training. */
/* The model owns parameters and its temporary training tape. */
UmiAiTrainingDecoderDestroy(model);
~~~

The complete example checks the status after every operation and reaches destruction on both success and failure paths. It does not publish a global model or leave tensors in an application window. The opaque model handle means its private layout belongs to Framework. Consumers use public configuration, inspection, prediction and training functions instead of reaching into private fields.


## Evaluate and then update

~~~c
status = UmiAiTrainingDecoderEvaluatePadded(
    model, input, targets, 6, attention, 6, objective, 6, &first);

status = UmiAiTrainingDecoderTrainPaddedStep(
    model, input, targets, 6, attention, 6, objective, 6,
    0.03F, &pre_update);
~~~

The objective is categorical cross-entropy over two selected prediction rows. Categorical means that each target chooses one vocabulary category. Logits are the unnormalized scores for those categories. Cross-entropy compares the score distribution with the target, using a numerically stable calculation. The mean divides by two selected rows, not by six stored rows. Evaluation leaves parameters unchanged. The training call calculates derivatives and commits one stochastic gradient descent update using learning rate 0.03.

The training call returns the loss before that update. Evaluate again to obtain the post-update value. If a request is refused, its loss output, model weights and completed-step count remain unchanged. Temporary graph nodes are rewound to the retained parameter prefix. The original unmasked APIs and objective-only masked APIs still exist; choosing a new function is an explicit request for padding behavior.


## Build and run the example

Use the same C23 compiler, CMake and Ninja setup as the previous lesson. Open PowerShell at the Bits2Banking repository root. Supply the path of the matching Framework source checkout. Stop on an error and inspect the first diagnostic before running the next command.

~~~powershell
Set-Location C:\umicom\Umicom-Bits2Banking
cmake -S labs/framework/masked-language-loss -B build/masked-language-loss -G Ninja -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/masked-language-loss --parallel 2
ctest --test-dir build/masked-language-loss --output-on-failure
& ".\build\masked-language-loss\umicom-padded-decoder.exe"
~~~

On Linux, use the corresponding local paths and run ./build/masked-language-loss/umicom-padded-decoder. The focused source composition builds the Framework training services needed by these examples. It does not install an SDK or launch a complete Umicom application. The target uses the shared branding helper and does not download or redistribute fonts.


## Interpret the result instead of memorizing decimals

The program prints an objective before training and another after forty steps. The latter must be smaller for this fixed fixture. It also prints the pre-update loss returned by the final training call. These last two values describe different parameter states and need not match. A native check fails if the values are not finite or if the fixture objective does not decrease.

It prints that changing padding IDs left selected logits unchanged. This is checked before training by replacing the excluded IDs while preserving all attended IDs and both masks. The returned excluded rows are zero-filled placeholders. Do not feed those rows into a sampler or treat them as meaningful uniform predictions. A consumer must use the attention policy to decide which output rows can be read as predictions.


## Inspect memory at a precise boundary

The program records committed tape bytes, tensor count and auxiliary bytes immediately after model creation. After each training step, those three quantities must return to the same retained baseline. The model parameters remain allocated; temporary forward and derivative graph nodes do not. The report is about this decoder tape, not the entire process or total machine memory.

Peak graph storage can be higher than the retained baseline. Padding semantics do not make the tensor engine sparse: embedding, residual and feed-forward rows still occupy storage. Set a graph budget when the caller needs a persistent-storage ceiling, but also plan total process memory separately. The focused regressions exercise early, middle and final-node budget refusal and check that a refusal does not partially update parameters.


## Recover from a failed run

1. For a missing symbol or declaration, reconcile matching Framework headers and implementation sources. The new public name alone cannot supply an older library with the implementation.
2. For invalid argument, check the two mask counts, binary byte values, objective subset relationship, context divisibility and all vocabulary IDs.
3. For capacity exceeded, inspect the geometry and graph budget. A refusal should preserve model state; do not bypass validation to force the fixture through.
4. For a nondecreasing objective, first verify the exact small fixture and learning rate. A different seed, data policy or model configuration changes the experiment.
5. For retained-byte growth after each step, capture the model/tape report at the same lifecycle boundary. An operating-system task-manager number includes different allocations and cannot be substituted for the same assertion.


## Know what a checkpoint preserves

The existing checkpoint format still stores model parameters and completed-step count. The new padding interface changes no checkpoint layout. A reproducible continuation also needs data order, tokenizer identity, target shift, context size, masks and position policy. Save those as separate experiment metadata. Reloading weights while silently changing the objective policy is a new experiment, even if the checkpoint bytes are identical.

The padded interfaces currently cover logits, evaluation and one-batch SGD. Existing AdamW and accumulated-gradient APIs retain their previous contracts; they do not automatically receive these arrays. This example is not a complete trainer for externally downloaded models, and it has no image or video quality claim. Keep training and held-out evaluation separate when the artificial fixture is replaced with a real task.


## Check your understanding

1. Count the selected target rows and explain why the denominator is two.
2. Explain why the first sequence keeps position two for its final row even though its middle row is padding.
3. Change only an excluded input ID to another valid ID. Predict which returned rows may change. None of the public padded logits should change: selected rows are isolated and excluded rows are zero-filled.
4. Explain why changing an attended prompt ID can change an answer whose prompt objective byte is zero.
5. List what belongs in experiment metadata in addition to checkpoint weights. Include the tokenizer and both selection policies.


## Further reading

- [Complete native padded decoder example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/masked-language-loss/padded_decoder.c)
- [Framework padded decoder guide](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/padded-decoder-training.md)

[Previous: Separate attention masks from loss masks](21-separate-attention-and-loss-masks.md)

[Next: Keep optimizer memory when training selected tokens](23-keep-optimizer-memory-for-selected-tokens.md)
