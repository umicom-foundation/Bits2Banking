![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Borrow a crop without copying pixels

This native C23 exercise selects the right two columns of a small original RGB image through Framework, then packs HWC floats with the existing converter. The view retains the source row stride and lifetime. Its readable span is 18 bytes, but it contains only 12 selected channel bytes; the gaps are not selected image data. Do not serialize the entire view span as a packed image.

Run each command separately and stop on errors:

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/framework/borrowed-image-crop -B build/borrowed-image-crop -G Ninja -DCMAKE_BUILD_TYPE=Debug -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/borrowed-image-crop --parallel 2
ctest --test-dir build/borrowed-image-crop --output-on-failure
.\build\borrowed-image-crop\umicom-borrowed-image-crop.exe
~~~

Expected output on the selected platform with four-byte float:

~~~text
Source: 21 bytes; crop starts at byte 3
Crop: 12 visible RGB bytes; 18 readable span bytes
Original row stride: 12 bytes
HWC: 0 1 0 0 0 1 1 0 1 1 1 0
Tensor storage: 48 bytes
Outside rectangle refused; previous view retained.
No decoder, pixel allocation, resize, model or training was run.
~~~

The source array remains alive during both synchronous operations. A copied descriptor does not retain its backing allocation. The source is limited by Framework’s bounded training image profile; this exercise is not an unbounded media decoder, image redaction tool or installed-SDK qualification. It uses the production C source owner in a narrow standalone build.
