<!--
Umicom Bits2Banking
File: content/lessons/05-ai/generative-ai-foundations/19-own-the-noise-in-a-stochastic-denoising-step.md

PURPOSE:
Own the noise in a stochastic denoising step

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Own the noise in a stochastic denoising step

[Course contents](index.md)

## Training and sampling answer different questions

Training changes model parameters using examples and an objective. Sampling uses a model to construct a new result. Earlier lessons introduced noisy inputs, predicted noise and a deterministic reverse step. This lesson adds optional fresh noise to one reverse step. It does not update parameters or train a network. You will run a four-value arithmetic exercise, inspect every input, and learn which parts of a larger image or video pipeline still belong to the caller.


## Give each kind of noise a name

The word noise can refer to different arrays. The current noisy sample is the state being processed. Predicted noise is the epsilon estimate produced by a compatible model for that state and timestep. Step noise is an additional newly drawn random array used by the stochastic transition. Confusing predicted noise with fresh step noise changes the algorithm. Reusing an earlier step-noise array at every transition also changes the intended statistical process.


| Value | Who supplies it? | Meaning |
| --- | --- | --- |
| noisy | Caller’s current sampler state | Current image-like or latent scalar array |
| predictedNoise | Compatible model, or known teaching fixture | Epsilon prediction for this state and timestep |
| stepNoise | Caller’s random generator | Fresh independent unit-normal values for this transition |
| currentAlphaBar and previousAlphaBar | Reviewed model schedule | Cumulative signal coefficients, not timestep indices |
| eta | Caller’s sampling policy | Stochasticity coefficient restricted here to zero through one |


## Recall the clean estimate

Let a be the current cumulative alpha and p the previous cumulative alpha. Moving backwards in the noising schedule means moving to at least as much clean signal, so 0 < a <= p <= 1. If x is the current noisy value and e is the predicted epsilon, the clean estimate is (x - sqrt(1-a)*e)/sqrt(a). The square-root symbol means the nonnegative number whose square is the value inside it. The estimate can be wrong because the prediction can be wrong. Successful arithmetic does not prove a high-quality generated image.


## Add a controlled random contribution

The DDIM family gives each step a noise scale sigma. This implementation uses sigma = eta * sqrt((1-p)/(1-a) * (1-a/p)). The new value is sqrt(p)*cleanEstimate + sqrt(1-p-sigma*sigma)*e + sigma*z, where z is the fresh unit-normal step noise. Unit-normal means mean zero and variance one. The noise generator’s earlier lesson explains these statistical terms. The formula is a model-specific sampling relation; it is not a universal rule for every system that describes its output as a velocity, flow or noise prediction.

~~~text
clean estimate      = (x - sqrt(1-a) * e) / sqrt(a)
new signal          = sqrt(p) * clean estimate
remaining direction = sqrt(1-p-sigma*sigma) * e
fresh contribution  = sigma * z
previous value      = new signal + remaining direction + fresh contribution
~~~


## Work out a simple coefficient example

Take a = 0.25 and p = 0.5. Then sigma squared is eta squared divided by three. The remaining direction coefficient is sqrt(0.5 - eta squared/3). Increasing eta allocates more of that transition’s residual variance to fresh noise. It does not mean adding noise without also changing the other coefficient. These are coefficients, not image quality scores.


| eta | sigma, approximately | Direction coefficient, approximately |
| --- | --- | --- |
| 0 | 0 | 0.707107 |
| 0.5 | 0.288675 | 0.645497 |
| 1 | 0.577350 | 0.408248 |


## Inspect the native service contract

Open include/umicom/ai/training/denoising.h in the Framework checkout and find UmiAiDenoisingStochasticStep. It takes three input arrays, an element count, the two coefficients, eta, an output array and its capacity. Counts are numbers of floats, not bytes. The arrays must be valid for the declared lengths. Output must not overlap any input. The inputs must stay unchanged while the function is running. The service performs no allocation, random sampling, model execution, file access or image decoding.

~~~c
UmiStatus status = UmiAiDenoisingStochasticStep(
    noisy, prediction, noise, 4,
    0.25F, 0.5F, 0.75F, sampled, 4);
if (status != UMI_STATUS_OK) {
    return 1;
}
~~~


## Recognize the special endpoints

At eta zero, the stochastic service delegates to the existing deterministic service. If the two alpha values are equal, it is an identity step and preserves the current values, including signed zero. At previous alpha one, no residual noise remains and the step becomes clean-estimate recovery. All supplied step-noise elements must still be finite at these endpoints. A NaN is a floating-point value representing an invalid numerical result; infinity is also refused. A disabled contribution is not permission to pass an invalid input buffer.


## Build the small exercise

Use the existing denoising-objective lab in Bits2Banking. It compiles selected canonical Framework source into a small learning program. This avoids building every application, but it does not qualify the installed SDK package. You need a C23 compiler, CMake, Ninja and the primary Framework checkout. Follow the repository setup lesson if these terms are new. Run the commands one at a time and stop on any reported error.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/framework/denoising-objective -B build/denoising-objective -G Ninja -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/denoising-objective --target umicom-stochastic-step --parallel 2
ctest --test-dir build/denoising-objective -R "lesson.denoising.stochastic-step" --output-on-failure --no-tests=error
~~~


## Read the program in order

1. Open stochastic_step.c. Locate four clean values and a known four-value prediction. These are a constructed example, not a learned network.
2. UmiAiDenoisingMix creates the current noisy values at alpha 0.25. This gives the exercise a known starting point.
3. Seed the existing Framework random state with 42, then draw four normal values. The next draw advances the same state and supplies another group.
4. Reset the seed to 42 and draw again. The first group is reproduced on this build. The example verifies replay before using the arrays.
5. Run the stochastic step at eta 0.75 twice with the replayed inputs and compare the result bytes. Then run eta zero and compare it with the existing deterministic function.
6. Finally replace the last noise value with NaN. Check that the operation is refused and the earlier output remains unchanged.


## Understand what replay does and does not promise

A seed initializes pseudorandom state. Repeating the same sequence of operations with the same initial state on the same supported build reproduces this exercise. Starting the generator once and continuing to draw is different from resetting it before every transition. A production sampler needs a deliberate stream policy and enough state to resume at the correct point. Normal generation uses floating-point mathematics, so do not promise identical bit patterns across arbitrary processors, libraries and compiler settings. Save the model identity, coefficients, prediction convention, random-state policy and relevant environment alongside a reproducible run.


## Explain the expected result

The program prints four arrays: current noisy values, fresh step noise, output at eta 0.75 and output at eta zero. It then reports that repeated supplied noise reproduced the output on this build. The last message confirms that nonfinite noise was refused without changing the previous output. The numerical arrays are observations, not evidence of a trained image model. Four values are too few to assess a random distribution, image realism or video motion. Use the separate larger normal-noise statistics lab for its limited distribution checks.


## Keep memory use bounded

The Framework function checks every candidate result before publishing any output. It computes scalar intermediates in double precision, then repeats the bounded arithmetic to write floats. This costs a second pass but avoids allocating a full extra clean-estimate tensor. It refuses an element count above 16,384, insufficient capacity, invalid coefficients, nonfinite input or an output outside finite float range. This bound describes this service, not the memory requirement of a complete model. Model weights, attention buffers, image decoders, latents and video frames still need their own budgets.


## Know what a complete sampler still needs

A real model must be evaluated again for each current state and timestep. It must use the expected epsilon convention, compatible latent scaling and reviewed schedule. The caller owns conditioning, guidance, fresh random draws and any checkpoint/resume policy. An image decoder converts model output to pixels only under its own trained contract. Video also requires compatible temporal behavior; independently applying this scalar transition to unrelated frames does not create motion coherence. Never keep the fixture’s prediction constant in a real sampler merely because this example does.


## Practice and review

1. For eta zero, explain why changing a finite step-noise array cannot change the output. Its coefficient is zero and the deterministic implementation is reused.
2. For a = p, explain why the current sample is preserved. There is no movement along the schedule.
3. For p = 1, identify the terms that disappear. Residual noise has zero coefficient, leaving the clean estimate.
4. Describe the difference between training loss, model prediction and a sampling transition. They are separate stages with different evidence.
5. Before adapting this to a model, write down its prediction parameterization and schedule. A matching array size alone is insufficient.


## Read the original mathematical source


- [Denoising Diffusion Implicit Models — Jiaming Song, Chenlin Meng and Stefano Ermon](https://arxiv.org/abs/2010.02502)


[Previous: Weight a training objective deliberately](18-weight-a-training-objective-deliberately.md)

[Next: Read pixels as an explicit tensor](20-read-pixels-as-an-explicit-tensor.md)
