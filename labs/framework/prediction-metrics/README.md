![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Count predictions before calculating percentages

This C23 laboratory sends four invented vocabulary-score rows to the shared
Framework service. It executes no model, changes no weights and downloads nothing.
It demonstrates all-row counts, two unequal batches, selected answer positions,
and an explicitly unavailable result when no positions are selected.

1. Install CMake, Ninja and a C23-capable compiler such as UCRT64 GCC.
2. Select matching Bits2Banking and Framework source checkouts. The lab requires
   `prediction_metrics.h` and its implementation from the same Framework tree.
3. Run the commands below from Bits2Banking. Stop when any command fails.
4. Compare the printed fractions before converting them to percentages.

```powershell
cmake -S labs/framework/prediction-metrics -B build/learning-prediction-metrics -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/learning-prediction-metrics
ctest --test-dir build/learning-prediction-metrics --output-on-failure
& ".\build\learning-prediction-metrics\umicom-prediction-metrics.exe"
```

Expected output:

```text
all rows: top-one=1/4 top-two=2/4
unequal batches: 1/1 and 0/3; combined 1/4
selected answers: top-one=1/3 top-two=2/3
no selected rows: accuracy unavailable
```

One successful prediction out of four is 25%. Averaging the two batch rates,
100% and 0%, incorrectly gives 50% for this token-weighted question. Selection
changes the denominator deliberately; it is not an attention mask or a new
train/evaluation split. An all-zero selection is an empty measurement, not 100%.

The lab builds the actual Framework source through a small local composition.
It is not an installed SDK deployment check. The Windows icon and staged SVG
resources come from Framework’s existing branding helper.

Read [the full lesson](../../../content/courses/preparing-llm-training-data/lessons/26-count-selected-predictions-before-percentages.html)
for vocabulary, ranking, ties, loss versus accuracy and recovery steps.

## Measure probability assigned to the target

The second executable, umicom-prediction-loss, calls the read-only loss service.
It prints 1.524398 nats per token from four invented score rows. Combining a
three-token batch and a one-token batch gives the same sum and count as evaluating
all four rows. Averaging the two batch means would incorrectly give 2.355649 for
this token-weighted question. No training graph or model weights are allocated.

After the configure and build steps above, run:

~~~powershell
& ".\build\learning-prediction-metrics\umicom-prediction-loss.exe"
~~~

A zero selected count means the mean and perplexity are unavailable. Finite
log-loss can still have an unrepresentable exponential; the example checks that
reporting boundary explicitly. The source composition also requires Framework
src/ai/training/categorical_loss.h from the matching checkout.

Read [the loss and denominator lesson](../../../content/courses/preparing-llm-training-data/lessons/32-measure-token-loss-with-the-right-denominator.html)
for the probability calculation, stable arithmetic, mask contract and exercises.

## Stream checked evaluation summaries

The third executable, `umicom-prediction-aggregate`, passes each batch summary to
`UmiAiTrainingPredictionLossMerge`. It checks count/sum overflow before updating
the accumulator and uses separate mean/perplexity reporting. Zero selected rows
produce `UNAVAILABLE`; an exponential outside finite double range produces
`CAPACITY_EXCEEDED` while the mean remains separately available.

After the same configure and build steps, run:

~~~powershell
& ".\build\learning-prediction-metrics\umicom-prediction-aggregate.exe"
~~~

The four invented rows produce the same mean as the second example. The existing
manual arithmetic example remains available for comparison; this client delegates
the reusable checks to Framework. The source composition also requires
`src/ai/training/prediction_summary.inc` from the matching checkout.

Read [the checked aggregation lesson](../../../content/courses/preparing-llm-training-data/lessons/33-aggregate-evaluation-with-checked-summaries.html)
for ownership, retry identity, compatible evaluation policies and recovery.
