![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Prepare two decoded frames for a model

Read [the video preparation lesson](../../../content/courses/generative-ai-foundations/lessons/21-prepare-a-video-sample-with-explicit-frame-order.html). This original C23 example uses four embedded two-pixel RGB frames. It selects indices 1 and 3, describes the required storage, and calls Framework for THWC and TCHW packing.

1. Open PowerShell in the Bits2Banking checkout.
2. Choose a matching complete Framework checkout with image_tensor and video_tensor headers and sources.
3. Run each command separately. Stop on errors rather than executing an older binary.

~~~powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/framework/video-tensor -B build/learning-video-tensor -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/learning-video-tensor
ctest --test-dir build/learning-video-tensor --output-on-failure
& ".\build\learning-video-tensor\umicom-video-tensor.exe"
~~~

Expected output on a target with four-byte float:

~~~text
Selected source frames: 1 3
Float storage: 48 bytes (12 values)
THWC: 1 0 0 0 1 0 0 0 1 1 1 1
TCHW: 1 0 0 1 0 0 0 1 0 1 1 1
Short final frame refused; previous tensor unchanged.
No decoder, frame-rate conversion, model or training was run.
~~~

The program calculates storage with sizeof instead of assuming that a C float is always four bytes. THWC means time, height, width, channel; TCHW means time, channel, height, width. Both keep whole frames consecutive. Neither is CTHW. A real model contract must identify the actual axis order and normalization.

Selection uses positive index steps. It does not interpret timestamps, convert frame rates or repeat an endpoint to complete a sample. Packing accepts up to 64 frames and 65536 float values total, subject to the smaller per-image bound. These are deliberately small preparation limits, not a full-resolution production video claim.

The output remains unchanged when the second frame is too short because the service admits every frame before conversion. Keep borrowed pixels and descriptors stable and keep the writable output separate. No decoder, weights or personal training media are needed for this exercise.

This narrow build compiles the real Framework sources. It does not qualify an installed SDK. An installed consumer links Umicom::ai and must use matching headers and symbols. Source selection and pixel conversion are implementation; generating a learned image or video remains a separate model capability.

## Select by presentation time

The additional timing.c program uses four timestamps in microseconds: 0, 40000, 100000 and 160000. Queries at 0, 50000, 100000 and 150000 select indices 0, 1, 2 and 2 under the explicit at-or-before policy. Index stepping would choose 0, 1, 2 and 3 instead. The example packs the selected one-pixel frames through the existing RGB tensor owner and refuses a later query beyond the source interval without replacing the previous indices.

After configuring with matching video_timing headers and source, run:

~~~powershell
cmake --build build/learning-video-tensor --target umicom-video-timing
ctest --test-dir build/learning-video-tensor -R lesson.training.video-timing --output-on-failure
& ".\build\learning-video-tensor\umicom-video-timing.exe"
~~~

Expected lines include `Index step: 0 1 2 3` and `Time hold: 0 1 2 2`. Repeated indices are permitted by this policy, not evidence that a decoder froze. The example does not convert container timestamps, estimate a frame rate or train a model. Read [the timestamp lesson](../../../content/courses/generative-ai-foundations/lessons/27-select-video-frames-by-time-with-an-explicit-policy.html) before applying the policy to real footage.

## Convert an entire output clip

The `output.c` example supplies two two-pixel frames as floats, calls `UmiAiTrainingVideoUnpackRgb8`, then proposes a changed first pixel and a nonfinite final channel. Both previously converted buffers must remain unchanged on refusal. Clipping does not admit NaN.

After the configure/build commands above, run the same CTest command to include `lesson.training.video-output`. You may also run `.\build\learning-video-tensor\umicom-video-output.exe`. Expect:

~~~text
Frame 0: red, green
Frame 1: blue, gray (128)
A bad final value preserved both earlier output buffers.
Padding stayed unchanged. No video file or model was produced.
~~~

Read [the whole-clip output lesson](../../../content/courses/generative-ai-foundations/lessons/31-validate-every-frame-before-publishing-a-clip.html) before adapting this stage. Destinations and descriptors stay caller-owned and disjoint; model decoding, branding, timing and video encoding remain separate stages.
