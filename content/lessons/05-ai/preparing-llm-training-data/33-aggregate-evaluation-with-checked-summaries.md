<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/33-aggregate-evaluation-with-checked-summaries.md

PURPOSE:
Aggregate evaluation with checked summaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Aggregate evaluation with checked summaries

[Course contents](index.md)

## Retain a small result instead of every score array

The previous lesson calculated a token’s loss from the probability assigned to its true answer. A real evaluation may contain many batches. Keeping every vocabulary-score array merely to calculate one final mean wastes memory. You can instead retain a few statistics after each batch: the number of rows inspected, the number selected for evaluation, and the sum of their negative log-likelihoods. These are sufficient for this particular token-weighted mean; they cannot reconstruct individual predictions, percentiles or every other metric.

1. Review the token-loss and denominator lesson first, especially nats, selection masks and unequal batch sizes.
2. Open labs/framework/prediction-metrics/aggregate.c. It calls the existing Framework score service and the new checked summary helpers.
3. This lab uses four invented score rows. It loads no model, downloads no weights and performs no training.


## Know what the three fields mean


| Field | Meaning | Example |
| --- | --- | --- |
| rows | All inspected prediction rows, including unselected rows | Seven rows inspected |
| selectedRows | Rows included in this reported objective | Four rows scored |
| negativeLogLikelihoodSum | The additive loss from selected rows, in nats | A sum of ten nats |


## Work a two-batch example by hand

Suppose batch A inspected four rows, selected three, and accumulated six nats. Batch B inspected three rows, selected one, and accumulated four nats. The combined result inspected seven rows, selected four, and accumulated ten nats. Its mean is ten divided by four: 2.5 nats per selected token. Averaging the batch means, two and four, would give three; that answers a different weighting question.


| Batch | Inspected | Selected | Loss sum | Batch mean |
| --- | --- | --- | --- | --- |
| A | 4 | 3 | 6 | 2 |
| B | 3 | 1 | 4 | 4 |
| Combined | 7 | 4 | 10 | 2.5 |


## Initialize the empty accumulator

An accumulator is a small value that gathers results over time. The initializer {0} sets every field to zero. It means no batches have been included yet. It does not mean a model has achieved zero loss. The reporting API distinguishes that empty state from a measurement containing actual tokens.

~~~c
UmiAiTrainingPredictionLossSummary total = {0};
UmiAiTrainingPredictionLossSummary batch;
~~~


## Score one borrowed batch, then merge its summary

The loss function reads the score and target arrays without retaining them. Merge then checks the existing and incoming summaries before publishing their combined value. The output may be the same object as total: the service reads and validates both inputs before writing. Check each status before continuing. A failed score call leaves batch unchanged, so merging it anyway could count a previous batch twice.

~~~c
if (UmiAiTrainingPredictionLoss(logits, rows, vocabulary, targets,
        selected, selectedCount, &batch) != UMI_STATUS_OK) {
    /* Report the error and stop this evaluation. */
    return 1;
}
if (UmiAiTrainingPredictionLossMerge(&total, &batch, &total) != UMI_STATUS_OK) {
    /* total still contains the earlier accepted aggregate. */
    return 2;
}
~~~


## Understand the ownership sequence

1. The caller owns the current logits, targets and optional selection mask. They must stay valid and unchanged while the loss call reads them.
2. The loss service publishes a separate summary after complete input admission. No pointer to the arrays is stored in that summary.
3. The merge service combines counts and sums without allocating memory or retaining either input pointer.
4. After the loss call returns, the caller can reuse its batch arrays if no other operation still needs them. Merging the summary does not extend the arrays’ lifetime.
5. The caller retains total until reporting finishes. Ownership is still explicit; C does not automatically free the caller’s arrays.


## What checked aggregation refuses

A summary can come from a valid service call or from incorrect caller code. The merge helper therefore validates its structure too. It cannot read your mind or establish that two measurements describe the same experiment.


| Input problem | Reported status | Why it matters |
| --- | --- | --- |
| selectedRows exceeds rows | INVALID_ARGUMENT | The count cannot describe these inspected rows |
| Negative, infinite or NaN loss sum | INVALID_ARGUMENT | The categorical loss summary is malformed |
| Zero selected tokens with a nonzero sum | INVALID_ARGUMENT | There is no contributing token for that sum |
| Count addition exceeds SIZE_MAX | CAPACITY_EXCEEDED | Unsigned wrapping would produce a misleading smaller count |
| Finite sums add to a nonfinite result | CAPACITY_EXCEEDED | The accumulated result no longer fits its representation |


## Ask separately for mean and perplexity

The mean divides the sum by the selected count. Perplexity applies the exponential to that mean for this categorical objective measured in natural-log units. A finite mean can have an exponential too large for a double. Preserve and display the finite mean while reporting that perplexity is unavailable at this range. Do not replace an overflow with zero, infinity shown as a successful score, or an arbitrary maximum.

~~~c
double mean;
UmiStatus status = UmiAiTrainingPredictionLossMean(&total, &mean);
if (status == UMI_STATUS_UNAVAILABLE) {
    /* No selected tokens: show "not evaluated". */
} else if (status == UMI_STATUS_OK) {
    /* Report mean, then request perplexity separately if needed. */
}
~~~


## No data is a useful explicit state

A summary may have six inspected rows and zero selected rows. Perhaps a mask excluded every position. The mean and perplexity functions return UNAVAILABLE and leave the output variable unchanged. That preserved value is only a memory guarantee: the caller must not accidentally display a previous result as current. Keep the status alongside the number in the user interface.


## Check compatibility before merging

1. Use the same tokenizer and vocabulary interpretation. A byte-token average and a subword-token average have different units.
2. Use the same dataset snapshot, context policy and objective. Evaluation from a different test set should not silently join this result.
3. Use the intended selection rule, such as answer-token evaluation. A different mask changes the question being measured.
4. Keep batch identity or progress separately so retries cannot add the same batch twice. Merge intentionally accepts equal summaries; equal numbers do not prove duplicate input.
5. Remember that floating-point addition depends slightly on ordering. Fix the traversal order for reproducibility and compare numerical results with an appropriate tolerance.


## Configure, build and test the original C lab

Select matching Framework and Bits2Banking source trees. These commands build a small source consumer with the approved Framework logo/icon resources. They do not build or install the entire Framework SDK. Run each command separately and stop on errors.

~~~powershell
Set-Location C:\umicom\Umicom-Bits2Banking
cmake -S labs/framework/prediction-metrics -B build/learning-prediction-metrics -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/learning-prediction-metrics
ctest --test-dir build/learning-prediction-metrics --output-on-failure
& ".\build\learning-prediction-metrics\umicom-prediction-aggregate.exe"
~~~


## Interpret the lab output

The first lines should report four selected tokens and a mean near 1.524398 nats. The example then checks a zero-selection report and an invented mean of 1000 nats whose exponential cannot fit. These are deliberate arithmetic exercises, not measured quality from a trained model.

~~~text
Selected tokens: 4
Mean: 1.524398 nats
...
Zero selected tokens: unavailable; previous result unchanged.
Mean 1000 nats remains reportable; its exponential exceeds range.
Invented scores only; no model, training, download or retained tensor.
~~~


## Exercises and recovery

1. Split the four rows into a group of three and a group of one instead of four single-row calls. Keep the same sum and selected denominator; allow tiny floating-point differences.
2. Exclude all four rows. Confirm that the summary is valid but reporting returns UNAVAILABLE.
3. Create a deliberately malformed summary with two inspected rows and three selected rows. Verify refusal and unchanged output.
4. Simulate retrying a completed batch. The arithmetic helper will count it twice; design a separate batch-identity rule to prevent that application mistake.
5. If the new function names are missing at link time, check that the matching prediction_metrics.c and prediction_summary.inc are in the chosen Framework tree. A new header alone cannot add symbols to an old library.


## What this does not implement

The service does not deduplicate records, verify provenance, run an LLM, alter model weights, track experiments on disk or qualify an installed SDK. It supplies one reusable, allocation-free reporting boundary. Keep data admission, model evaluation, experiment identity and presentation as separate responsibilities.


[Previous: Measure token loss with the right denominator](32-measure-token-loss-with-the-right-denominator.md)
