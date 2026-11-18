<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/38-follow-nested-static-array-copies.md

PURPOSE:
Follow nested static-array copies

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Follow nested static-array copies

[Course contents](index.md)

## Use one tiny image to see ownership

When an edit appears to do nothing, the program may have changed a copy rather than the original storage. When an edit changes too much, several variables may share storage unexpectedly. This exercise makes that distinction visible with a two-by-two RGB image. RGB means red, green and blue channel values. A byte in this example holds one unsigned channel from zero to 255. We use red and green on the top row and blue and white on the bottom row. The twelve channel values total 1530. There is no image file or model involved.

1. Open static_pixel_arrays.d in the language boundary laboratory.
2. Draw the four pixels and write their RGB triples: (255,0,0), (0,255,0), (0,0,255) and (255,255,255).
3. Keep the drawing unchanged while following which program variables receive copies and which receive references.


## Build a type from the inside outward

An alias gives another name to an existing type. Pixel names an array of three ubyte elements. Row names an array of two Pixels. Image names an array of two Rows. The lengths belong to these types and are known at compilation. Here “static array” describes fixed length; it does not mean the local variable lasts for the whole program. The aliases make the dimensional meaning easier to read than a stack of bracketed numbers.

~~~d
alias Pixel = ubyte[3];
alias Row = Pixel[2];
alias Image = Row[2];
static assert(Image.sizeof == 12);
~~~


## Read shape and indices separately

image[1][0][2] selects row one, then pixel zero within that row, then channel two within that pixel. In our convention this is the blue channel of the bottom-left pixel, with value 255. The equivalent nested type spelling is ubyte[3][2][2]: begin with three channel bytes, group two such pixels into a row, then group two rows into an image. By naming the intermediate types we avoid guessing which bracket describes which dimension. The compile-time assertion checks twelve bytes for this exact representation; it is not a general image-format compatibility test.


| Expression or type | Meaning here |
| --- | --- |
| Pixel | Three channel values |
| Row | Two Pixel values |
| Image | Two Row values |
| image[0][1] | The green pixel on the top row |
| image[1][0][2] | The blue component of the bottom-left pixel |


## Initialize a complete original value

originalImage constructs an Image, assigns every pixel’s three channel values and returns the completed image. There is no borrowed pointer to a temporary local. The result is an array value. channelTotal deliberately receives a twelve-byte value parameter and adds all channels. That small copy is acceptable for this teaching exercise, but it would be a poor default for a large frame. A production interface should state whether it borrows a view, owns a buffer or makes an explicit copy. The choice belongs in the contract, not in a guess based on a function name.


## Follow a reference parameter into copied rows

editRowCopies receives ref Image, so its image parameter refers to the caller’s Image. However, foreach (row; image) creates a value variable for each row. Row is a static array, so this row variable contains a copy of that row’s pixel values. The inner loop uses ref pixel, but that reference points into the copied row. Setting pixel[0] to zero therefore edits the local copy’s red channel. The original image remains unchanged. A reference at one level does not automatically turn every nested variable into a reference.

~~~d
foreach (row; image)
    foreach (ref pixel; row)
        pixel[0] = 0;
~~~


## Trace the first iteration on paper

Start with the caller’s first row containing red and green. The outer loop copies those six channel bytes into row. The inner loop selects the copied red pixel and clears its first component, turning that copied pixel black. It then clears the copied green pixel’s red component, which was already zero. The copied row is finished and the next row is copied. No assignment writes a row back into image. After both iterations, the caller’s total is still 1530. This explains why an apparently reasonable edit can have no visible result without any crash.

1. Draw two boxes: caller image and loop row copy. Draw an arrow from ref pixel into the loop-copy box.
2. Cross out the copied red value 255 and replace it with zero. Leave the caller box unchanged.
3. Write the expected output before running: Editing row copies: original total = 1530.


## Use references at both levels for an intentional edit

removeRed uses foreach (ref row; image). Now row refers to a row inside the caller’s image. Its inner ref pixel refers to a pixel in that same storage. Clearing each pixel’s red component updates the original. Red becomes black, green stays green, blue stays blue and white becomes cyan, whose triple is (0,255,255). Two red components of 255 have been removed: 1530 minus 510 gives 1020. The function stores no reference for later use; the caller grants the edit only for this call.

~~~d
foreach (ref row; image)
    foreach (ref pixel; row)
        pixel[0] = 0;
~~~


## Save an independent static-array value

Before removeRed runs, main assigns Image saved = image. In this example every nested element is a static array or an integer value, so saved contains an independent copy of all twelve channel bytes. After the edit, image totals 1020 while saved still totals 1530. Do not extend this conclusion blindly to a struct containing pointers, class references or dynamic-array slices: copying such a value can copy references to shared storage. Independence depends on the representation of the whole object, not just the assignment syntax.


| Point in the exercise | image total | saved total |
| --- | --- | --- |
| After originalImage | 1530 | Not yet created |
| After editing row copies | 1530 | Not yet created |
| After Image saved = image | 1530 | 1530 |
| After removeRed(image) | 1020 | 1530 |


## Read the effect annotations without overclaiming them

The small helper functions declare @safe, pure, nothrow and @nogc. The intent is to have the D compiler enforce their permitted operations: memory-safe language operations, restricted external effects, no normal exception propagation and no garbage-collector allocation. These annotations do not mean the entire executable has no runtime or uses no memory. main imports std.stdio for console output, and stack values still occupy storage. The example is an ordinary D program, not a BetterC build. The current source must be compiled with the selected toolchain before treating those annotations as verified evidence.


## Use unit tests and normal-path checks together

The unittest block compares the original image with its saved value after copy editing, checks total 1020 after reference editing, and confirms that saved still contains the original red channel. The main function also checks the three totals before printing. These checks explain the intended behavior at both levels. They are small, deterministic examples, not a performance benchmark. Keep assertions and bounds checks enabled while learning; disabling a check does not correct an invalid index or an ownership mistake.


## Compile and inspect the expected output

Use the D compiler installation from the setup lesson. Open PowerShell in the laboratory directory. The -unittest option includes unit tests, and -checkaction=context requests useful context when supported checks fail. Run compilation first and stop if it fails. Do not execute a previous file left behind by an earlier successful build.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
dmd -unittest -checkaction=context -of=static_pixel_arrays.exe static_pixel_arrays.d
& .\static_pixel_arrays.exe
$LASTEXITCODE
~~~


## Check each line against the ownership drawing

Expect the three lines below and exit code zero. If the first total changes, check whether you accidentally added ref to the outer loop in editRowCopies. If the second total remains 1530, check whether removeRed still references rows and pixels. If saved changes, verify that its declared representation remains Image rather than a dynamic view. If the compiler rejects a construct or attribute, inspect its exact diagnostic and compiler version before changing the example. Source review and C checks in another laboratory do not establish that this D executable has passed.

~~~text
Editing row copies: original total = 1530
Editing referenced rows: image total = 1020
Independent static-array copy: saved total = 1530
~~~


## Apply the lesson at a Framework boundary

The useful lesson for Umicom applications is explicit ownership, not replacing Framework services with a D-specific duplicate. A thin D client can prepare data, but the shared native converter should still own RGB-to-float layout conversion. Before a C call, define the byte span, channel order, row stride, output capacity and how long the memory remains valid. A local array must not escape through a pointer retained by a background job. Compile-time type information can help verify a wrapper’s assumptions, but it does not prove that a downloaded model expects the chosen tensor layout or numerical range. The separate Framework image lesson describes those model-facing choices.


## Practice by changing one layer

Use the following variations to test your understanding. Keep each version separate until you have written its expected totals and reviewed the exact storage it edits.

1. Remove ref from the inner loop of removeRed but keep it on the outer loop. Explain why each pixel then becomes another value copy and the image remains unchanged.
2. Remove only the red component from the white pixel with a direct indexed assignment. Predict total 1275.
3. Change Row to hold three Pixels. Explain why the initialization, size assertion and expected totals need review rather than merely changing one number.
4. Describe the difference between this fully nested static-array copy and a copy of a dynamic-array slice.
5. Explain why a compiler can check a static shape but cannot infer that a model uses RGB instead of BGR.


## Language references and the shared native exercise


- [D static arrays and array declarations](https://dlang.org/spec/arrays.html)
- [D foreach value and reference variables](https://dlang.org/spec/statement.html#foreach-statement)
- [Read pixels as an explicit Framework tensor](../../05-ai/generative-ai-foundations/20-read-pixels-as-an-explicit-tensor.md)


[Previous: Reuse typed declarations with template mixins](37-reuse-typed-declarations-with-template-mixins.md)

[Next: Separate text bytes, code points and display](39-separate-text-bytes-code-points-and-display.md)
