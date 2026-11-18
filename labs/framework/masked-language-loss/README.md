![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Observe a loss mask before adapting a model

This C23 exercise has four score rows, three target classes and a mask that
selects only the final two rows. Framework computes categorical cross-entropy,
differentiates it and updates the toy score tensor once. It verifies zero
contribution to excluded score rows and a lower selected-row objective after
the update. No tokenizer, dataset file, pretrained model or provider is used.

1. Open the Bits2Banking repository and use a C23 compiler, CMake and Ninja.
2. Configure with the matching primary Framework source path below. Substitute
   an absolute path if your checkouts are arranged differently.
3. Build, run the test, then run the small executable to inspect its output.
4. Stop after a failure. A missing symbol means the selected Framework source
   lacks this operator; do not copy an isolated header over another version.

~~~powershell
cmake -S labs/framework/masked-language-loss -B build/masked-language-loss -G Ninja -DUMICOM_FRAMEWORK_SOURCE=../Umicom-Applications/framework
cmake --build build/masked-language-loss --parallel 2
ctest --test-dir build/masked-language-loss --output-on-failure
& ".\build\masked-language-loss\umicom-masked-language-loss.exe"
~~~

Expect a starting loss near 1.0986123, a lower result after one update and a
message that the two excluded score rows received zero gradient from this
objective. The denominator is two selected rows, not all four rows. A loss mask
does not hide prompt tokens from attention or stop shared model weights from
receiving gradients through another path.

The tape owns every tensor. Destroy it once on all exit paths. Rewind retains
the score leaf while invalidating the old loss node; recompute after changing
parameters. Framework copies targets and selection into its owned node. All
rows still need valid target indices, and an all-zero mask is refused.

This is a focused source lab. It does not validate an installed SDK, select a
chat template, shift token labels, implement a complete fine-tuner or prove
that a model improves on unseen data. Continue with the paired data-preparation
lesson before replacing invented scores with real model outputs.

## Train selected decoder targets

The second executable, `umicom-masked-decoder`, applies the same objective to the existing Framework decoder. Its six input IDs form two independent sequences of three positions. The selection bytes score one target in the first sequence and two in the second. The mean divides by three selected predictions across the batch.

<!-- The earlier follow-up mixed the repository-root build directory with lab-folder commands. The consistent root-relative sequence below replaces it; retained for review.
Use the configure and build commands above with matching current Framework sources, then run `ctest --test-dir build --output-on-failure` and `& ".\build\umicom-masked-decoder.exe"` from this lab folder on Windows.
-->

Use the configure and build commands above from the Bits2Banking repository root, then run `ctest --test-dir build/masked-language-loss --output-on-failure` and `& ".\build\masked-language-loss\umicom-masked-decoder.exe"` on Windows. Other generators may place the executable in a configuration subfolder. The program performs forty CPU SGD steps, prints before/after selected-target loss, and checks that every step releases temporary graph storage. A successful fixed fixture has lower final loss; the printed graph byte counts depend on the compiled implementation and do not represent total process memory.

The zero-valued mask entries exclude objective terms. They do not hide prompt inputs, freeze prompt embeddings or change causal attention. All target IDs must remain within the vocabulary, including excluded ones. This example supplies already-shifted integer targets; it does not parse chat roles, tokenize JSONL or load a pretrained model. Checkpoints retain weights and step count, but the data order and mask policy must be preserved separately for a reproducible continuation.

The production implementation still belongs to Framework. This lab directly compiles a narrow selection of matching sources for teaching; it does not establish that an installed SDK or a full application has passed qualification.

## Keep prompt context while excluding padding

The third executable, `umicom-padding-attention`, compares attention selection `[1, 0, 1]` with objective selection `[0, 0, 1]` over three scalar values `[2, 100, 6]`. With zero queries and keys, all permitted keys receive equal weight. A loss-only mask gives final output 36 and squared error 1296; excluding padding from attention gives output 4 and squared error 16. The prompt value still receives a derivative of 4, the padded value receives zero and changing that padding does not change the selected prediction.

After the same repository-root configure/build/test sequence, run `& ".\build\masked-language-loss\umicom-padding-attention.exe"`. The program checks 32 padding values and destroys each tape. The existing decoder example above still demonstrates an objective mask; it does not automatically gain attention-mask plumbing from this separate primitive.

Read [Separate attention masks from loss masks](../../../content/lessons/05-ai/preparing-llm-training-data/21-separate-attention-and-loss-masks.md) for definitions, hand calculations, exact commands, expected output and recovery steps. The three programs compile matching Framework sources for teaching, not an installed SDK or a complete fine-tuning system.

## Train with both selections

The fourth executable, `umicom-padded-decoder`, calls the explicit padded decoder APIs with separate attention and objective arrays. It changes excluded input IDs and checks identical public logits, then performs forty native SGD steps and verifies that each step releases temporary tape storage. It prints initial and final selected objective values; the final value must be lower for the fixed fixture.

Run `& ".\build\masked-language-loss\umicom-padded-decoder.exe"` after the repository-root commands above. Read [Train a decoder with padded examples](../../../content/lessons/05-ai/preparing-llm-training-data/22-train-a-decoder-with-padded-examples.md) for the configuration fields, target alignment, position policy, output meaning and memory boundaries. This is a small from-scratch decoder fixture, not fine-tuning an imported model.

## Preserve AdamW state across a selected training run

The fifth executable, `umicom-selected-adamw`, trains the same small padded fixture with AdamW. It takes twenty steps, encodes the model together with its first and second moments, decodes an independent copy, and continues both for twenty more identical steps. It compares their complete final encoded states, checks reduced loss, and checks retained graph and optimizer-state sizes.

From the Bits2Banking repository root, rerun the configure/build/test commands above against matching Framework sources. Then run `& ".\build\masked-language-loss\umicom-selected-adamw.exe"`. Expect `completed_steps=40` and `resumed_state=identical`; the final loss must be smaller than the initial loss for this fixture. Floating-point values are not a cross-toolchain guarantee.

Read [Keep optimizer memory when training selected tokens](../../../content/lessons/05-ai/preparing-llm-training-data/23-keep-optimizer-memory-for-selected-tokens.md). This demonstration uses in-memory checkpoints and releases all owned handles. It does not download models, launch a server, write a checkpoint file or qualify a complete application.

## Reduce graph peaks with selected microbatches

The sixth executable, `umicom-selected-microbatches`, compares one complete
five-sequence graph with one-sequence microbatches. The objectives select zero,
one, three, two and zero positions across those sequences. Both calculations
therefore divide by six selected targets. The accumulated call makes one AdamW
update, including when some groups need no graph.

Use the same root-relative configure/build sequence, then run
`ctest --test-dir build/masked-language-loss -R lesson.training.selected-microbatches --output-on-failure`
and `& ".\build\masked-language-loss\umicom-selected-microbatches.exe"`.
Expect five sequences, six scored targets and 41 completed updates after the
comparison and repeated-learning exercise. The microbatch tape peak must be
lower for this fixture; retained tape storage must remain stable.

Read [Accumulate uneven selected microbatches](../../../content/lessons/05-ai/preparing-llm-training-data/24-accumulate-uneven-selected-microbatches.md)
before interpreting the byte counts. Tape peaks exclude reducer arrays, optimizer
storage, input arrays and allocator overhead. The experiment uses invented
tokens and a small CPU decoder; it does not qualify pretrained fine-tuning or
total process memory.

## Prepare an actual byte pair before training

The seventh executable, `umicom-byte-pair-training`, prepares prompt `Q:` and
completion `A` through Framework’s byte-pair adapter. Its eight-row context has
four real input rows and two scored targets: A and EOS. No target shift is
performed in the application.

Use the same configuration above, then build `umicom-byte-pair-training` and run
`ctest --test-dir build/masked-language-loss -R "^lesson.training.byte-pair$" --output-on-failure`.
Add `-V` to inspect the exact row table. The program repeats one sample for
forty SGD steps and requires finite decreasing selected loss and stable
retained tape storage after graph cleanup. Floating-point loss values are not
a cross-toolchain guarantee.

Read [Prepare a byte pair without shifting twice](../../../content/lessons/05-ai/preparing-llm-training-data/27-prepare-a-byte-pair-without-shifting-twice.md).
The vocabulary is the native 260-entry byte teaching vocabulary. This is not
pretrained-model fine-tuning, held-out quality evidence or a complete assistant.
