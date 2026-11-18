<!--
Umicom Bits2Banking
File: content/lessons/05-ai/generative-ai-foundations/18-weight-a-training-objective-deliberately.md

PURPOSE:
Weight a training objective deliberately

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Weight a training objective deliberately

[Course contents](index.md)

## Begin with four scalar predictions

A scalar is one number. Our example uses four predicted values, 1, 2, 3 and 4, with four target values that are all zero. Think of them as four entries in a tiny image-like array. They are not a decoded image and the program does not load an image model. Subtract the target from each prediction to get errors 1, 2, 3 and 4. Squaring those errors gives 1, 4, 9 and 16. Ordinary mean squared error adds these four numbers and divides by four: the result is 7.5. Squaring makes positive and negative errors contribute nonnegative amounts.


## Review binary selection before using continuous weights

The previous lesson used a selection byte of zero or one to exclude or include a value. Select only the first and third entries. Their squared errors are 1 and 9, and their selected mean is (1 + 9) / 2 = 5. This changes the objective because the other two entries are no longer scored. A selection mask is useful for invalid or padded positions. It says whether an entry participates, but it does not express that one participating entry should have three times another entry's influence. Continuous nonnegative weights provide that extra choice.



## Calculate this lesson's weighted mean

Assign weights 1, 0, 3 and 0. Multiply each squared error by its weight, add the weighted errors, and divide by the sum of weights. The numerator is 1 × 1 + 0 × 4 + 3 × 9 + 0 × 16 = 28. The denominator is 1 + 0 + 3 + 0 = 4. The normalized weighted result is therefore 7. The larger third weight pulls the result toward the larger third squared error. The denominator happens to equal the number of entries in this fixture; that coincidence is not the rule.

| Entry | Prediction | Target | Squared error | Weight | Weighted error |
| --- | --- | --- | --- | --- | --- |
| 1 | 1 | 0 | 1 | 1 | 1 |
| 2 | 2 | 0 | 4 | 0 | 0 |
| 3 | 3 | 0 | 9 | 3 | 27 |
| 4 | 4 | 0 | 16 | 0 | 0 |

## Name the normalization rule

Normalization means applying a chosen scale so that quantities can be compared under a stated rule. Framework's WeightedMeanSquaredError divides by the sum of supplied weights. Another objective might divide the weighted sum by the number of entries instead. Those objectives are different. Multiply every weight in this example by five: the numerator becomes 140 and the weight sum becomes 20, so the normalized result stays 7. Dividing by the four entries would instead produce 35. Always record the denominator with a training recipe; a phrase such as weighted MSE alone may be ambiguous.

~~~text
normalized_weighted_loss = sum(weight * squared_error) / sum(weight)
mean_of_weighted_errors  = sum(weight * squared_error) / number_of_entries
~~~


## Follow the derivative by hand

The derivative tells us how the objective changes when one prediction moves slightly. With fixed weights, the derivative for prediction i is 2 × weight_i × (prediction_i − target_i) / sum_weights. For the first entry this is 2 × 1 × 1 / 4 = 0.5. For the third it is 2 × 3 × 3 / 4 = 4.5. The zero-weight entries receive zero contribution from this objective. Target derivatives have the opposite sign. A shared model parameter can still receive gradients through other entries or graph paths; setting one objective weight to zero is not a general parameter-freezing operation. The supplied weights themselves are constants here and do not receive derivatives.


## Take one small update

The laboratory marks the prediction tensor as trainable and uses it as a tiny parameter array. Stochastic gradient descent subtracts learning rate times gradient from each prediction. With learning rate 0.1, the first prediction becomes 1 − 0.1 × 0.5 = 0.95 and the third becomes 3 − 0.1 × 4.5 = 2.55. The second and fourth stay unchanged. Recompute the objective using the new predictions: (0.95 squared + 3 × 2.55 squared) / 4 = 5.1025. This is lower than 7. It demonstrates an update against one known objective, not training a useful image generator.


## Use the native operation

The public function accepts two equal-shaped tensors on the same Framework tape, a weight array with one float per tensor element, its length, and storage for the returned loss handle. A tape owns the graph's tensors and saved data. Every weight must be finite and nonnegative, and their total must be positive. Negative, infinite or NaN weights are refused. NaN means not a number and usually indicates invalid arithmetic. There is no automatic row broadcasting: if one frame-level decision applies to many channels, the caller must deliberately create the corresponding per-element weights.

~~~c
const float weights[4] = {1, 0, 3, 0};
UmiAiTrainingTensor *loss = NULL;
UmiStatus status = UmiAiTrainingWeightedMeanSquaredError(
    tape, prediction, target, weights, 4, &loss);
~~~


## Keep saved coefficients alive through their owner

Framework copies the weights into the new loss node before publishing it. The caller can release or change its original array after a successful call without changing that node's objective. The laboratory deliberately overwrites its original array with zeros before running backward propagation. It still expects derivatives 0.5, 0, 4.5 and 0. This catches an implementation that accidentally borrows the caller's array. The copied four floats add sixteen logical payload bytes when a float occupies four bytes. The tape reports the actual sizeof-based total as auxiliary memory and includes it in the graph budget. Rewind and destroy release the copy.


## Build and run from the repository root

Open PowerShell in the Bits2Banking repository. Use the matching Framework checkout, an installed C23 compiler, CMake and Ninja. Configure creates instructions for this focused teaching build. The build compiles the shared Framework sources and the thin laboratory. CTest checks the expected behavior. Run the executable separately to inspect its printed measurements. Stop on any error; do not interpret output from an older executable as a new result.

~~~powershell
cmake -S labs/framework/denoising-objective -B build/denoising-objective -G Ninja -DUMICOM_FRAMEWORK_SOURCE=../Umicom-Applications/framework
cmake --build build/denoising-objective --parallel 2
ctest --test-dir build/denoising-objective -R lesson.denoising.weighted-pixel-loss --output-on-failure
& .\build\denoising-objective\umicom-weighted-pixel-loss.exe
~~~

1. Read weighted_pixels.c and identify the prediction, target and weight arrays.
2. Predict the binary selected loss and the normalized weighted loss.
3. Run the commands one at a time.
4. Expect initial results 5 and 7, derivatives 0.50 0.00 4.50 0.00, and a lower post-update result near 5.1025.


## Interpret refusal and memory observations

Construction validates shape, ownership, weights and representable loss before committing a graph node. If allocation or the graph budget refuses the node, the existing graph and output-handle variable remain unchanged. The caller still owns its original inputs. The regression suite injects each weight-node allocation failure and checks that no allocation remains owned after cleanup. Those checks are more specific than looking only for a successful forward value. A stable tape counter is evidence about tape ownership, not a proof that an entire media application has no memory leaks. Model workers, decoded frames, device buffers and runtime libraries need separate observations.


## Connect the arithmetic to image and video training

A training recipe might assign different importance to examples, timesteps or valid regions. It must explain where those weights come from, how they are expanded to values, and how the result is normalized. A diffusion recipe that uses signal-to-noise weighting may use a different denominator or prediction convention from this generic operator. Do not substitute this function into a published recipe merely because both mention weights. A video recipe must also specify how frame count, channel count and clip length affect example weighting. Otherwise a long clip can dominate simply because it contains more scored values. Keep source grouping and validation-set separation from the earlier lessons.


## Experiment and explain the result

First change the weights to 1, 0, 1 and 0 and predict the binary selected objective of 5. Then use four equal positive weights and predict ordinary MSE of 7.5. Multiply all weights by the same positive factor and predict an unchanged normalized objective, allowing small floating-point differences. Use all zeros and expect refusal rather than division by zero. In a separate copy, use a negative weight and check that no new loss handle is published. Keep the target convention and value scaling unchanged while testing one policy difference at a time.


## Recognize what remains outside the example

The program updates four numbers using a CPU tape. It contains no image decoder, text encoder, latent autoencoder, attention network for images, temporal video model, dataset loader, GPU kernel or checkpointable full trainer. Framework owns a reusable mathematical operation that future training components can call. A complete generative system still requires model architecture, compatible preprocessing, data provenance, evaluation, resource planning and user-facing recovery. A decreasing loss in this fixture should be described as a verified numerical exercise, not evidence of image quality or competing-service feature parity.


[Previous: Exclude padding from a training objective](17-exclude-padding-from-a-training-objective.md)

[Next: Own the noise in a stochastic denoising step](19-own-the-noise-in-a-stochastic-denoising-step.md)
