![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Train a tiny noise predictor in C

This CPU exercise uses Umicom Framework's automatic-differentiation tape. It predicts the noise added to one scalar value. It creates no image or video, downloads no model and makes no network request. Read the [guided lesson](../../../content/courses/generative-ai-foundations/lessons/11-run-a-native-denoising-experiment.html) for the mathematics and source walkthrough.

## 1. Locate the two repositories

You need the Bits2Banking repository containing this folder and a matching Framework source checkout containing `include/umicom/ai/training/denoising.h`. The commands below assume the usual sibling folders under `C:\umicom`. Replace that location with your own development directory if necessary.

A repository is a folder containing the project's source and history. CMake describes how to build those files; Ninja runs the required compiler commands. A compiler translates C source into machine instructions. This exercise needs a C23-capable compiler; the Windows example uses the existing MSYS2 UCRT64 GCC toolchain.

Open PowerShell and run each command separately. Stop if any command reports an error.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
Test-Path "..\Umicom-Applications\framework\include\umicom\ai\training\denoising.h"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --version
ninja --version
gcc --version
~~~

The path check must print `True`. Each version command should identify a program. Adding a folder to this shell's PATH lets PowerShell find tools there; it does not install them or permanently change system settings. If a tool is absent, finish the development-environment course before proceeding. Do not download a random DLL to satisfy a missing dependency.

## 2. Configure and compile

~~~powershell
cmake -S labs/framework/denoising-objective -B build/denoising-objective -G Ninja -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/denoising-objective
~~~

`-S` selects the source directory; `-B` selects a separate directory for generated files. `-G Ninja` chooses the build tool. The final argument identifies the existing Framework source. This small lab compiles the actual Framework tape, matrix and denoising sources. It does not copy their algorithms into the application or qualify the installed SDK package.

On Linux, use the same commands with your Framework directory, for example `-DUMICOM_FRAMEWORK_SOURCE="$HOME/umicom/Umicom-Applications/framework"`. Use an installed C23 compiler and Ninja. The executable has no `.exe` suffix there. Other platforms require separate toolchain qualification.

## 3. Run the checks and read the result

~~~powershell
ctest --test-dir build/denoising-objective --output-on-failure
& ".\build\denoising-objective\umicom-denoising-objective.exe"
~~~

<!-- Earlier single-executable expectation retained: CTest should report one passing test. -->
CTest should report two passing tests: the original objective and the separate noise-statistics exercise. The program performs 500 updates. Initial mean squared error is approximately 0.5; final error is very small. The learned slope approaches 1.414214 and the bias approaches -0.25. Printed zeros are rounded, not proof of exact arithmetic.

The familiar clean value 0.25 reconstructs close to 0.25. The unfamiliar clean value 0.80 also reconstructs close to 0.25: that is the deliberate generalisation failure. The test passes only if this limitation remains visible. It would be misleading to describe this model as a working image denoiser.

The program reports retained leaf bytes and peak graph bytes. Exact byte counts depend on the compiler and platform. Repeated fixed-size training iterations must return to the same leaf footprint after rewind. These counters exclude allocator overhead, temporary operator scratch, executable memory and other process memory.

## 4. Connect the numbers to the code

The clean scalar is a number representing one simplified brightness measurement. Each row receives a known noise value. Framework mixes them using `sqrt(alphaBar) * clean + sqrt(1 - alphaBar) * noise`, with `alphaBar = 0.5`.

Each input row contains two numbers: its noisy value and the constant 1. Multiplication by two trainable weights gives `slope * noisy + bias`. A weight is a model parameter changed during training. The constant column allows the second weight to act as a bias.

The target is the known noise. Mean squared error averages the squared differences between predicted and known noise. Backward differentiation computes how changing each weight would change the loss. Stochastic gradient descent takes a small step in the opposite direction using a learning rate of 0.1.

The tape owns every tensor and its buffers. Three leaf tensors survive each iteration: input features, target noise and trainable weights. Two temporary tensors hold predictions and loss. Rewind discards those temporary results while retaining updated weights. After rewind, their old handles are invalid. One destroy call releases the tape at the end, including failure paths.

## 5. Investigate without overstating the result

Before editing, save your work in your own working copy. Change the learning rate to 0.05 and predict the effect on convergence. Rebuild and compare the final loss. A smaller rate generally needs more steps; convergence is not guaranteed for arbitrary choices.

Then examine why all clean values are 0.25. The learned rule can infer noise by assuming this same clean value every time. It therefore fails on another brightness. Real denoising requires diverse data, a more expressive model, suitable noise schedules and independent evaluation. Splitting frames from one video across training and evaluation can hide memorisation; keep related samples grouped.

Do not remove the generalisation assertion to make arbitrary experimental changes look successful. Create a separate experimental variant with its own stated expectations. Keep this reference exercise as a known, inspectable comparison.

## Troubleshooting

- **Missing denoising.h:** the chosen Framework source does not include this API. Use the matching complete source; mixing headers and implementation revisions is unsafe.
- **Compiler not found:** check PATH in the same shell. Configure a fresh build directory if you intentionally change compilers.
- **Shadow warning:** a local variable has the same name as another visible variable. The checked-status macro deliberately uses a distinct name; warning checks stay enabled.
- **Loss or graph-size assertion fails:** preserve the full output, compiler version and modified source. A failing numerical check is evidence to investigate, not a reason to disable the check.
- **A build of every application starts:** confirm that `-S` names this lab directory. This exercise does not require the whole Applications tree.

## 6. Measure normal noise separately

After the same configure/build steps, run `umicom-noise-statistics.exe` from
the build directory (without `.exe` on Linux). It requests 8,192 samples with
mean zero, standard deviation one and seed 42. It prints an observed mean,
variance and ten histogram bins whose counts sum to 8,192. The mean should be
near zero and the variance near one; a finite sample need not match exactly.

The sampler uses Framework’s existing seeded integer RNG and a Box-Muller
transform. No model is loaded or trained. Platform math may differ in the last
bits. Record the seed, sample count, API version and environment for comparisons.
An odd-sized call discards an unused partner, so changing call boundaries can
change later samples. This exercise leaves the original fixed-noise lesson
unchanged; it does not turn that deliberately overfit model into an image generator.

## 7. Separate beta from cumulative alphaBar

The third executable, `umicom-noise-schedule`, passes four per-step beta values
0.1, 0.2, 0.3 and 0.4 to Framework’s checked cumulative schedule function. It
expects alphaBar values 0.9, 0.72, 0.504 and 0.3024. Index zero means after the
first beta is applied; the earlier unnoised coefficient is implicitly one.

Reconfigure and build this lab with the commands above. CTest now runs three
lesson checks. Run `umicom-noise-schedule.exe` from the build directory to see
the table (omit `.exe` on Linux). Each row mixes the same original clean value
and known noise with that row’s cumulative coefficient, then reconstructs it.
The recovered value should remain near 0.25. No model predicts that noise;
known-noise reconstruction verifies arithmetic only.

The public API accepts at most 4,096 finite beta values in [0,1), rejects a
cumulative product below the target’s minimum normal float, and leaves all
output unchanged on refusal. Do not clip an invalid schedule or confuse beta
with alphaBar. Read lesson 13 for the numerical derivation, diagram, complete
commands, expected results and controlled experiments. This is not a reverse
sampler or evidence of compatibility with a pretrained image/video model.

## Compare compatible epsilon predictions

`guidance.c` supplies four synthetic clean values, known noise and two prediction vectors. The conditioned vector is deliberately equal to the true noise. The Framework guidance operation combines predictions for scales 0, 0.5, 1 and 3; the existing reconstruction operation then estimates the clean values. Scale 1 preserves the exact predictor in this fixture. Scale 3 extrapolates past it and increases reconstruction error. This arithmetic example does not generate an image or establish a preferred scale for a real model.

After configuring with matching Framework sources, rebuild and run `ctest --test-dir build --output-on-failure`. Run `& ".\build\umicom-noise-guidance.exe"` for the four printed rows on Windows. The single-configuration Ninja build places the executable directly in build. The test checks the exact-predictor case and the worsening extrapolation without relying on every displayed decimal.

Both predictions must refer to the same noisy sample, timestep, tensor layout and epsilon prediction convention. A caller must enforce those identities; a float array alone cannot prove them. The native operation validates bounds and finite arithmetic, preserves output on refusal and performs no model call. Training with dropped conditioning and inference guidance are separate stages. A larger guidance scale may hurt detail, diversity or temporal coherence and must be evaluated on a real compatible pipeline.

## Follow a deterministic trajectory

`trajectory.c` calls the Framework-owned `UmiAiDenoisingDeterministicStep` at cumulative signal levels 0.0625, 0.25, 0.5625 and 1. It compares an exact synthetic epsilon array with the same array biased by 0.05. The exact case should reconstruct the four clean values within floating-point tolerance; the biased case has a final mean squared error near 0.0375. These are constructed numeric fixtures, not learned image or video generation.

Use the existing configure/build commands above, then run `ctest --test-dir build -R "lesson[.]denoising[.]trajectory" --output-on-failure --no-tests=error` if your chosen build directory is `build`. Keep the actual directory consistent with configuration. A successful test checks the arithmetic fixture, not a full model scheduler, decoder, image pipeline or installed SDK.

The Framework operation implements a deterministic epsilon DDIM step with eta zero. Its two input arrays are stable and its destination is disjoint; the example copies the completed next state only after a successful call. A real model must predict again using each current sample and timestep. No stochastic term, clipping, thresholding or new tensor allocation is introduced by the operation.

## Convert the prediction convention explicitly

The new example, `velocity.c`, forms three synthetic clean values, three known noise values, and the matching diffusion velocity target. It tests cumulative signal coefficients 0, 0.25 and 1. Framework converts the velocity array to both epsilon and a clean estimate without division or temporary allocation. The endpoint checks are defined by this variance-preserving convention; they do not imply that a real model predicts accurately at either endpoint.

Rebuild this same lab. Run `ctest --test-dir build -R "lesson[.]denoising[.]velocity" --output-on-failure --no-tests=error`. From the lab directory on Windows, `& ".\\build\\umicom-denoising-velocity.exe"` prints three coefficient rows with maximum reconstruction errors close to zero. At 0.25, it also deliberately passes velocity to the epsilon reconstruction function; that wrong-convention path has a maximum error above 1.0. The program checks both the correct result and the visible mismatch. All six lesson tests remain available with the unfiltered CTest command.

The array is mathematically defined as v = sqrt(alphaBar) * epsilon - sqrt(1-alphaBar) * clean. Other models may use another quantity named velocity, particularly flow-matching models. Check the actual model contract before using these conversions. The example does not load weights, train a model, render an image, decode video or qualify an installed SDK. Lesson 16 explains the formulas and each command from the beginning.


## Score observed frames rather than padding

The seventh executable, `umicom-padded-frame-loss`, uses two synthetic clips stored
as two rows with three scalar frame slots each. The first clip has three observed
frames; the second has one. Its last two slots are padding. The selected-value
objective uses four observations and ignores the two storage slots.

Reconfigure and build with the commands in section 2, then run:

~~~powershell
ctest --test-dir build/denoising-objective -R "lesson[.]denoising[.]padded-frame-loss" --output-on-failure --no-tests=error
& ".\build\denoising-objective\umicom-padded-frame-loss.exe"
~~~

With zero padding, the complete mean squared error is 5. With padding set to 9,
it is 32. The selected mean stays 7.5 in both cases. Selected derivatives are
0.5, 1, 1.5, 2, 0 and 0; one learning-rate-0.1 update changes the four predictions
to 0.95, 1.90, 2.85 and 3.80 while leaving padding unchanged. The executable
checks these expectations before printing them. All seven lesson tests remain
available through the unfiltered CTest command using this same build directory.

The Framework operation copies one mask byte per tensor value and releases it
with the owning tape node. It refuses mismatched shapes, nonbinary masks and an
empty selection. The mask chooses individual values, not whole rows. A real
frame adapter must expand frame validity across its pixels and channels. A
black observed pixel is valid; numerical zero does not identify padding.

The equal-value objective weights longer clips more heavily. It is not an
equal-clip average, an attention mask, a temporal model or a trained generator.
Read [lesson 17](../../../content/courses/generative-ai-foundations/lessons/17-exclude-padding-from-a-training-objective.html)
for the arithmetic, complete source walkthrough and controlled exercises.

## Normalize continuous objective weights

The eighth executable, `umicom-weighted-pixel-loss`, compares binary selection
with continuous nonnegative weights. Predictions 1, 2, 3 and 4 against zero
targets produce selected loss 5 for mask 1, 0, 1, 0, but normalized weighted loss
7 for weights 1, 0, 3, 0. The denominator is the sum of weights.

Use the repository-root configure/build sequence above, then run
`ctest --test-dir build/denoising-objective -R lesson.denoising.weighted-pixel-loss --output-on-failure`
and `& .\build\denoising-objective\umicom-weighted-pixel-loss.exe`.
Expect gradients 0.50, 0.00, 4.50 and 0.00 and a post-update loss near 5.1025.

The program changes its original weights after constructing the loss and checks
that backward propagation uses the Framework-owned copy. It also checks release
after rewind. This is a scalar CPU objective experiment, not an image model.
Read [Weight a training objective deliberately](../../../content/lessons/05-ai/generative-ai-foundations/18-weight-a-training-objective-deliberately.md)
before using continuous weights in a model-specific recipe.

## Choose step noise explicitly

`stochastic_step.c` compares a single epsilon-based DDIM transition at eta 0.75 with the existing eta-zero deterministic path. Framework supplies the bounded arithmetic and normal-noise generator. The caller owns the random state, coefficients and arrays. Resetting the seed reproduces the supplied noise on the same build; normal sampling uses platform math and is not a promise of identical floating-point results on every system. A real model must predict from each current noisy state. This four-value exercise neither trains a model nor generates an image or video.

After configuring this lab as above, build `umicom-stochastic-step` and run `ctest --test-dir build/denoising-objective -R "lesson.denoising.stochastic-step" --output-on-failure --no-tests=error`, adjusting the build directory to the one you selected. Expect four arrays, a replay message and a preserved-output refusal for nonfinite noise.
