<!--
Umicom Bits2Banking
File: content/lessons/05-ai/generative-ai-foundations/11-run-a-native-denoising-experiment.md

PURPOSE:
Run a native denoising experiment and observe overfitting

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Run a native denoising experiment and observe overfitting

[Course contents](index.md)

## What you will learn

This lesson turns the earlier denoising equation into a small C program. You will train two numbers, observe a loss decrease, check bounded graph reuse and discover why the result fails on an unfamiliar input. You need the earlier lessons on pixels, noise and loss, plus the C setup course. No account, GPU, photograph or downloaded model is required. The exercise runs on the CPU, the general-purpose processor in your computer. It is a numerical teaching model, not an image generator.


## 1. Read one training row

Imagine that a brightness measurement is the scalar 0.25. A scalar is one number; an image would contain many values arranged by height, width and colour channel. Choose a known noise value, such as 0.5. Noise is a deliberately added disturbance. With alphaBar equal to 0.5, the mixing equation multiplies both numbers by approximately 0.707107 and adds them. The resulting noisy measurement is approximately 0.530330. The training task is to predict the known noise, 0.5, from that noisy measurement. We can check a prediction because we constructed this pair ourselves.

~~~text
clean = 0.25
noise = 0.50
alphaBar = 0.50
noisy = sqrt(alphaBar) * clean + sqrt(1 - alphaBar) * noise
      = 0.530330 approximately
~~~


## 2. Understand what can change

Our model predicts noise using slope * noisy + bias. Slope and bias are the two weights that training changes. The input contains two columns: the noisy value and the constant 1. Multiplying these columns by a two-row weight matrix expresses the same equation. Matrix multiplication is a reusable Framework operation. It records enough information on the training tape to differentiate the result later. At the beginning both weights are zero, so every prediction is zero. The five target noise values are -1, -0.5, 0, 0.5 and 1. These fixed values make the exercise reproducible; they are not a random Gaussian-noise implementation.


## 3. Follow one update

Mean squared error, abbreviated MSE, subtracts the target from each prediction, squares each difference and averages the results. Squaring makes negative and positive mistakes contribute positively. A loss is a number measuring the selected error; smaller is better for this particular measure. Backward differentiation computes a gradient: how sensitively the loss changes with each weight. Gradient descent subtracts the gradient multiplied by a learning rate. The rate controls step size. It is neither a probability nor a guarantee of convergence.

~~~c
UmiAiTrainingMatmul(tape, inputs, weights, &prediction);
UmiAiTrainingMeanSquaredError(tape, prediction, targets, &loss);
UmiAiTrainingBackward(tape, loss);
UmiAiTrainingSgdStep(tape, weights, 0.1F);
UmiAiTrainingTapeRewind(tape, 3U);
~~~


## 4. Build and run the complete checked example

The short excerpt above shows the sequence, but omits error checks for readability. Use the complete main.c in labs/framework/denoising-objective; every operation is checked there. Open its README and follow the numbered setup and build instructions. Run each PowerShell command separately and stop at the first error. CMake prepares the build; the compiler creates the executable; CTest runs its checks. This lab compiles selected existing Framework sources and does not exercise the installed SDK export.

1. Find the Bits2Banking repository and matching Framework source checkout.
2. Confirm that the denoising header exists and that CMake, Ninja and a C23 compiler are available.
3. Configure only the denoising-objective lab, then build it.
4. Run its CTest check and then the executable so you can read the values.
5. Write down initial loss, final loss, learned slope and bias, and the two reconstruction results.


## 5. Interpret a passing result carefully

After 500 steps the slope should be near 1.414214 and the bias near -0.25. The loss should fall from about 0.5 to a very small number. Output rounded to 0.00000000 does not establish exact mathematical zero. The model can reconstruct a familiar clean value near 0.25, even with a noise value not used among the five training rows. However, an unfamiliar clean value 0.80 also reconstructs near 0.25. This is overfitting: a model has learned a narrow property of its training examples rather than the broader behaviour you wanted. The reference check intentionally requires this failure to remain visible.


## 6. Explain the failure before changing the model

Every training example used the same clean value. The model therefore learned a rule equivalent to assuming that clean brightness is always 0.25. A new noise value is not a sufficiently independent test of new image content. For an image project, evaluation must include suitable unseen subjects and scenes. For video, related frames and clips should remain in the same partition. Otherwise near-duplicate material can appear in both training and evaluation, creating an overly favourable result. Better data is necessary, but data alone does not guarantee that this two-weight model can solve a realistic task.


## 7. Observe memory ownership

A tensor is a shaped collection of numbers. The Framework tape owns all tensor storage in this exercise. Inputs, targets and weights are three leaf tensors: original values rather than results of earlier recorded operations. Prediction and loss are temporary operation results. Each iteration adds two such results, performs differentiation and then rewinds to the three leaves. Rewind invalidates discarded handles; using prediction or loss afterward would be a lifetime error. The check verifies that the retained byte count returns to the same value each time. This is evidence about this graph's reuse, not proof that the whole process or every application is leak-free.


## 8. Make one controlled experiment

Record the original output before editing. Change the learning rate from 0.1 to 0.05, rebuild and compare how close the final weights are after the same 500 steps. State your prediction first. Then restore the reference rate. A larger experiment should use a separate source variant and describe its data, expected outputs and failure criteria. Do not delete assertions simply because an experiment violates them. A useful investigation distinguishes a deliberate change in the task from a defect in the implementation.


## 9. Connect this lesson to image and video training

A diffusion-style image trainer may add noise to image or latent tensors at many selected noise levels, predict a specified target and update a large network. A latent is a compressed numerical representation created by another model. Our exercise has one scalar feature and one noise level; it has no image codec, encoder, text conditioning, temporal model, sampler, dataset downloader or checkpoint format. The new Framework operations mix and recover bounded finite float arrays. Recovery assumes noise prediction, often called epsilon prediction. Models predicting clean samples or velocity use different conversions. They cannot be substituted merely because their output arrays have matching dimensions.


## Check your understanding

Explain why the target is known before training. Identify the two parameters that change and the three tensors retained after rewind. Explain why a very small training loss can coexist with a large error on new content. Finally, name three components required for a real image trainer that this exercise does not contain. If you cannot answer yet, trace one row on paper and reread the relevant stage rather than increasing the model size.


## What the checks do and do not establish

| Observation | Supported conclusion | Still unverified |
| --- | --- | --- |
| Loss decreases | The tiny fixed objective can be optimised | Image quality or broad generalisation |
| Rewind restores leaf bytes | This training graph reuses bounded owned storage | Total process memory and every other allocation |
| Unfamiliar brightness fails | The fixture demonstrates memorisation | Performance of a real generative model |
| C source exercise passes | Selected Framework sources work in this harness | Installed SDK packaging and full applications |

[Previous: plan the native project](10-native-framework-project-plan.md)

[Next: Measure normal noise before using it in a training loop](12-measure-noise-before-training.md)
