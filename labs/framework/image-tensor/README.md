![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Read image pixels as model inputs

Follow [the step-by-step lesson](../../../content/courses/generative-ai-foundations/lessons/20-read-pixels-as-an-explicit-tensor.html). The original two-by-two RGB image is embedded in main.c. No photograph or downloaded dataset is needed.

This C23 laboratory calls Framework’s shared image converter; it does not copy the conversion implementation. HWC means height, width, channel order. CHW means channel, height, width order. The two calls deliberately select different value ranges so the output makes both decisions visible.

1. Open PowerShell in the Bits2Banking checkout.
2. Select a matching Framework checkout containing image_tensor.h and image_tensor.c.
3. Run each command separately and stop if it fails.

~~~powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/framework/image-tensor -B build/learning-image-tensor -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/learning-image-tensor
ctest --test-dir build/learning-image-tensor --output-on-failure
& ".\build\learning-image-tensor\umicom-image-tensor.exe"
~~~

Expected output:

~~~text
HWC unit: 1 0 0 0 1 0 0 0 1 1 1 1
CHW signed: 1 -1 -1 1 -1 1 -1 1 -1 -1 1 1
Short input refused; previous tensor unchanged.
No image decoder, model or training operation was run.
~~~

The input has six useful bytes per row and an eight-byte stride. Only the inter-row gap is stored. The converter checks the last readable byte, skips the gap, and leaves the previous output unchanged when the input is one byte short. Input length/stride are bytes; output capacity is floats. Keep the input and output storage separate and stable.

The narrow learning build compiles the real Framework implementation and uses its branding helper. It does not qualify an installed SDK. An installed consumer links Umicom::ai and requires matching image-conversion headers and library symbols. If configuration reports a missing file, select the complete matching Framework source instead of creating an empty header. If compilation fails, do not run an older executable left in the output folder.

This is bounded code-value conversion, not image decoding, color management, alpha compositing, resizing, latent encoding or model training. The model’s documented preprocessing contract decides whether either layout/range is appropriate.


## Apply an explicit model preprocessing contract

Follow [the channel-standardization lesson](../../../content/courses/generative-ai-foundations/lessons/29-apply-explicit-channel-normalization.html). The same configure/build commands also create umicom-image-standardize. Run it separately:

~~~powershell
& ".\build\learning-image-tensor\umicom-image-standardize.exe"
~~~

Expected output after a successful build:

~~~text
HWC standardized: -1 0 -4 1 1 0
CHW standardized: -1 1 0 1 -4 0
Zero scale refused; previous tensor unchanged.
Parameters are an example, not a model recommendation.
~~~

The shared service first packs bytes into unit floats, then applies (unit - mean[channel]) / scale[channel]. The example intentionally uses different RGB parameters to reveal channel-order mistakes. It does not infer parameters from measured image statistics. Positive finite scales and finite representable endpoint results are required before output changes. RGB input, parameter struct and output must occupy separate stable storage. This exercise has no model, image decoder, training loop or second image allocation.


## Convert model output values into bytes

Follow [the explicit pixel-conversion lesson](../../../content/courses/generative-ai-foundations/lessons/30-turn-model-values-into-explicit-pixels.html). The same build now includes `umicom-image-quantize`. It calls `UmiAiTrainingImageUnpackRgb8` with strict admission, then with explicit clipping. Every required value must be finite in either policy. A complete admission pass precedes all pixel writes; row gaps and unused capacity stay intact.

~~~powershell
& ".\build\learning-image-tensor\umicom-image-quantize.exe"
~~~

Expected output:

~~~text
Strict unit RGB: 0 128 255 64 191 0
Outside values refused; previous pixels unchanged.
Explicitly clipped signed RGB: 0 128 255
NaN refused even when clipping is selected.
This converts code values; it does not decode a latent or train a model.
~~~

The conversion rounds to nearest with exact halfway values going upward. It does not invert channel standardization or decode model latents. UNIT and SIGNED_UNIT are explicitly selected code-value ranges; they do not infer a color space. The service retains its 16,384-element teaching bound and caller-owned disjoint storage contract.
