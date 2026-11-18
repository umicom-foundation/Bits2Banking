![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Explicit image orientation laboratory

This C23 program composes three Framework services: borrow a two-by-two crop, mirror its pixels horizontally into packed RGB bytes, then pack those bytes into a model-facing HWC float tensor. The crop keeps its original padded row stride; the materialized output uses a new packed stride. The code does not implement a second crop, flip or normalization algorithm.

## Build and run

From this laboratory directory, run each PowerShell line separately and stop on an error. Use a matching existing Framework source checkout; this focused learning mode is not an installed-SDK qualification.

~~~powershell
$env:Path = "C:/msys64/ucrt64/bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
.\build\umicom-image-orientation.exe
~~~

Expected output:

~~~text
Borrowed crop: 2x2, stride 12, readable span 18 bytes
Packed flipped RGB: 12 bytes, stride 6
HWC: 0 0 1 0 1 0 1 1 0 1 0 1
Two horizontal flips restore the visible crop.
Unknown transform refused without changing output.
Synthetic pixels only: no decoder, caption rewrite, RNG, model or training.
~~~

The test requires exit zero. It checks the exact bytes, normalized tensor, restoration and unchanged output on an unknown flag. If configuration reports a missing header or source, integrate the matching complete Framework files before retrying. Do not create empty placeholder headers. If a test fails, read its first diagnostic or exit code and rebuild the current sources; an older executable is not proof for edited files.

## Ownership and units

The caller owns every array. The crop borrows the original pixels. Flip copies to a disjoint byte array and retains no pointer. Pack writes to a disjoint float array. Twelve bytes of RGB and twelve floats are different storage amounts. A crop's readable span includes gaps between rows; it is not necessarily a packed image.

Framework provides this function through the AI SDK and the native training target. Installed package discovery, ABI compatibility and other toolchains need their own qualification. This laboratory deliberately compiles a narrow source set and applies the shared Windows icon/metadata helper.

## Training meaning

A flip is a data transformation, not a trainer. Horizontal flips can invalidate text, handedness and left/right captions; vertical flips can produce unrealistic scenes. Apply a consistent policy to masks, boxes and video frames, and retain original source-group identity for train/evaluation separation. No automatic label correction or model-quality claim is made here. The generative-AI course explains these choices before a real dataset is transformed.
