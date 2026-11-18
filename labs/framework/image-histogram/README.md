![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Count RGB values before preparing model tensors

This original C23 exercise calls Framework's shared image histogram and crop
services. Six decoded RGB pixels produce exact per-channel frequencies. A
weighted red sum is 766; dividing by six gives 127.666667 code units when rounded
to six decimal places. This is an arithmetic mean of byte codes, not a measure
of brightness in linear light, model quality or the whole training dataset.

## Configure and run

Use a matching Framework checkout. This deliberately narrow source consumer
compiles the real services; it does not test an installed package or GUI.
Run each command separately and stop on any error.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
cmake -S labs/framework/image-histogram -B build/image-histogram -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/image-histogram --parallel 2
ctest --test-dir build/image-histogram --output-on-failure
& .\build\image-histogram\umicom-image-histogram.exe
~~~

Expect six full-image pixels, red bins 0:1, 64:2, 128:1 and 255:2, the weighted
sum and mean above, then a four-pixel crop with two red values at 64 and two at
255. An incomplete input is refused while the previous crop report remains.
Zero process exit means the example's explicit checks succeeded.

The view borrows stable RGB8 storage; the result owns three fixed 256-bin count
arrays. It retains no source pointer. Input padding is skipped and the complete
view is admitted before pixels are read. The source/view/result must be valid
and disjoint. No allocation, image decoding, remote request or training occurs.
A histogram loses pixel positions, so equal counts do not establish equal
images. Keep source-group splits intact when using measurements to plan training.

The Windows executable uses the Framework branding helper and supplied ICO.
A successful source consumer does not qualify installed SDK exports, visual
appearance or integration into Umicom Media. The detailed course lesson explains
bins, weighted means, padding, crop effects and dataset leakage from first principles.


## Read channel means and population variance

The same build now includes umicom-image-moments from moments.c. It calls
Framework's histogram/moment services on two invented pixels. Run it from the
build directory after a successful build. Expected numeric observations:

~~~text
red: mean=127.50; population variance=16256.25; minimum=0; maximum=255
green: mean=20.00; population variance=100.00; minimum=10; maximum=30
blue: mean=255.00; population variance=0.00; minimum=255; maximum=255
~~~

The program then corrupts one histogram channel's count and checks that refusal
preserves the previous complete result. CTest runs both the original frequency
lab and the new moment lab. No input image is normalized or loaded from disk.
Read [the Framework contract](../../../../Umicom-Applications/framework/docs/learning/image-moments.md)
and the generative-AI course before choosing a model preprocessing policy.
