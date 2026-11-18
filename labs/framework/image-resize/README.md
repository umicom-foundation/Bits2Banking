![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Resize a decoded image and measure what was lost

This original C23 exercise calls Framework's bounded nearest-center RGB resampler
and histogram service. Four alternating black/white pixels become two white
pixels. Enlarging that result cannot recover the discarded black pixels.

The operation selects the nearest source pixel center independently on each
axis. Exact ties select the higher coordinate. It copies RGB triples, does not
average neighbors, and does not apply antialias filtering or a color transform.

## Configure, build and run

Use a matching existing Framework checkout. This narrow source consumer is
not installed-SDK qualification. Run commands separately and stop on errors.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
cmake -S labs/framework/image-resize -B build/image-resize -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/image-resize --parallel 2
ctest --test-dir build/image-resize --output-on-failure
& .\build\image-resize\umicom-image-resize.exe
~~~

Expected output:

~~~text
Original red bins: 0=2 255=2
Reduced red bins: 0=0 255=2
Upsampling does not restore the missing dark pixels.
Insufficient output capacity was refused without changing the previous image.
~~~

The original constant array, reduced array and restored array have separate
ownership. Borrowed view descriptors stay valid only while their pixel arrays
are alive and stable. The failed-capacity exercise keeps the earlier reduced
image unchanged. Source and destination overlap is outside the API contract.

The Windows target uses the Framework branding helper and approved ICO.
No file decoder, GUI, model download, remote request or training occurs.
A nearest-neighbor exercise does not establish the preprocessing policy of
a particular diffusion model. Follow its documented resolution, interpolation,
normalization and caption rules before preparing a real dataset.

## Compare a second interpolation policy

The same build also creates umicom-image-bilinear.exe. Run it after the
configure, build and test commands above:

~~~powershell
& .\build\image-resize\umicom-image-bilinear.exe
~~~

Expected output:

~~~text
Nearest center: 240 250 255
Bilinear center: 135 145 154
Short output leaves the previous image unchanged.
Six stripes to two: 255 0; no area antialiasing.
~~~

The center of a two-by-two source is equally distant from four pixels.
Nearest chooses the lower-right pixel under its higher-coordinate tie rule.
Bilinear mixes all four, then rounds once. It interpolates encoded bytes;
it does not linearize light or infer a model's preprocessing policy.
The six-stripe example deliberately exposes remaining downsampling aliasing.
Keep categorical labels separate: interpolating class numbers creates invented
classes. Read the [step-by-step interpolation lesson](../../../content/courses/generative-ai-foundations/lessons/32-choose-an-image-interpolation-policy.html).
