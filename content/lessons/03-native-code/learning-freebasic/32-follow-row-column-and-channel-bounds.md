<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/32-follow-row-column-and-channel-bounds.md

PURPOSE:
Follow row, column and channel bounds

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Follow row, column and channel bounds

[Course contents](index.md)

## Give each index a meaning

A one-dimensional array is like a numbered shelf. A multidimensional array lets you select an element with several coordinates. In this exercise the first coordinate is a row, the second is a column and the third is a color channel. A channel is one component of a pixel; RGB uses red, green and blue. We use a two-row, two-column image so that every value can be checked by hand. Nothing in the array itself knows that it represents an image. Those meanings come from our program’s documented convention.

1. Draw a two-by-two grid on paper. Put red at the top left, green at the top right, blue at the bottom left and white at the bottom right.
2. Label rows zero and one from top to bottom, and columns zero and one from left to right.
3. Label channels zero=red, one=green and two=blue. A pixel therefore needs three stored values.


## Read the declaration one part at a time

Dim introduces the array. Each To range states inclusive lower and upper bounds. The three comma-separated ranges describe three dimensions. As UByte selects unsigned eight-bit elements, which can hold integers zero through 255. The declared counts are two rows, two columns and three channels: twelve elements in total. Twelve is an element count, not the number of pixels. There are four pixels, each with three elements.

~~~basic
Dim pixels(0 To 1, 0 To 1, 0 To 2) As UByte
~~~


## Distinguish a dimension number from an element index

LBound and UBound ask for a particular dimension’s smallest and largest index. Their dimension argument is numbered from one. In this declaration, dimension one is the row dimension even though its first element index is zero. UBound(pixels,0) has a separate purpose: it reports the number of dimensions, which is three here. Do not confuse that query with reading pixel zero. The diagram below is a record of our chosen meanings, not a promise that every library uses this convention.


| Query or coordinate | Meaning in this exercise | Result |
| --- | --- | --- |
| LBound(pixels,1) | First row index | 0 |
| UBound(pixels,1) | Last row index | 1 |
| UBound(pixels,2) | Last column index | 1 |
| UBound(pixels,3) | Last channel index | 2 |
| UBound(pixels,0) | Number of dimensions | 3 |
| pixels(1,0,2) | Blue component of bottom-left pixel | 255 after initialization |


## Trace initialization through three nested loops

A nested loop is a loop inside another loop. For each row, our program visits each column. For each selected pixel, it visits each channel. The innermost assignment sets that element to zero. The innermost loop completes all three channels before the column advances, and both columns complete before the row advances. Writing the initialization explicitly makes the traversal visible. Next channel, Next column and Next row close the matching loops; indentation helps you see which work belongs to each.

~~~basic
For row As Integer = LBound(pixels, 1) To UBound(pixels, 1)
    For column As Integer = LBound(pixels, 2) To UBound(pixels, 2)
        For channel As Integer = LBound(pixels, 3) To UBound(pixels, 3)
            pixels(row, column, channel) = 0
        Next channel
    Next column
Next row
~~~


## Turn zero channels into four visible colors

A zero RGB triple is black in this encoded example. To make the top-left pixel red, the program changes only pixels(0,0,0) to 255. To make the top-right pixel green, it changes pixels(0,1,1). The bottom-left pixel uses pixels(1,0,2) for blue. Finally, the white pixel needs all three components set to 255. We are manipulating already decoded color samples. A PNG or JPEG file has its own encoding and cannot simply be substituted for this array.

1. Find each assignment in pixel_grid.bas and point to the corresponding square in your drawing.
2. For the white pixel’s loop, hold row one and column one fixed while channel moves from zero to two.
3. Write the completed triples: red=(255,0,0), green=(0,255,0), blue=(0,0,255), white=(255,255,255).


## Use a wider accumulator for a sum

A UByte can hold one channel but cannot hold the sum of three maximum channels, which is 765. The program uses a ULong accumulator for pixelTotal and channelTotal. Accumulator means a variable that collects partial results. Each pixel starts with a new pixelTotal of zero; its three channels are then added. If pixelTotal were not reset inside the column loop, later pixels would incorrectly include earlier pixels. This example’s maximum total is small and known. A general image reader must also bound dimensions and total arithmetic before processing untrusted input.


| Pixel | Addition | Expected sum |
| --- | --- | --- |
| Red | 255+0+0 | 255 |
| Green | 0+255+0 | 255 |
| Blue | 0+0+255 | 255 |
| White | 255+255+255 | 765 |
| All four | 255+255+255+765 | 1530 |


## Check values instead of trusting a printed label

The expected array stores one known channel sum for each row and column. Before printing a pixel, the program compares its calculated sum with that expected entry. A mismatch ends with code one. At the end it checks three dimensions, four visited pixels and total 1530; a mismatch ends with code two. A zero exit code means those bounded exercise checks passed. It is not evidence of image quality, correct decoding, a trained model or a production graphics pipeline. The use of OrElse in the final check combines independent refusal conditions; each condition describes a different assumption.


## Build and run the complete source

Use a working FreeBASIC installation from the earlier setup lesson. Open PowerShell in the example directory. The compiler translates the source into an executable; the second command runs it. The -lang fb option selects the modern FreeBASIC dialect. The -w all and -exx options request useful warnings and additional runtime checks during learning. Run the commands separately and stop if compilation fails; a previous executable may still be present.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
fbc -lang fb -w all -exx pixel_grid.bas -x pixel_grid.exe
& .\pixel_grid.exe
$LASTEXITCODE
~~~


## Read the result by coordinates

Expect four pixel lines in this order: row zero/column zero, row zero/column one, row one/column zero and row one/column one. Their sums are 255, 255, 255 and 765. The final line reports total 1530 and the process should return zero. Printed spacing around integers may differ. Compare the numerical values and coordinates, not the number of blank spaces. If fbc is not recognized, return to the installation lesson and check the compiler location. Do not interpret a shell command-not-found error as a language error in the example.

1. Compare each printed row and column with your drawing.
2. If a sum is wrong, inspect that pixel’s three channel assignments before changing the expected array.
3. If the final total is wrong but individual sums are right, inspect where channelTotal is initialized and updated.
4. If a bounds check fails, identify the dimension and its declared interval rather than disabling runtime checks.


## Keep the language array separate from a native storage contract

This program teaches indexed access; it does not promise that a pointer to a multidimensional BASIC array is a portable C image format. A Framework API needs explicit channel order, row stride, byte count, ownership and lifetime. Row stride is the byte distance between consecutive row starts; it may include padding. A tensor also needs a selected dimension order and numerical range. The separate Framework image-tensor laboratory uses a defined RGB8 byte span and a shared C converter. Reuse that public operation at a reviewed language boundary instead of assuming that similar-looking array declarations are interchangeable.


## Practice one deliberate change

Change only one assumption at a time and predict the new result before compiling. This is how a small fixture becomes a useful reasoning tool rather than a program that merely prints numbers.

1. Change the white pixel to black by setting its three channels to zero. Predict a total of 765 and update the expected white-pixel sum deliberately.
2. Change one channel from 255 to 128. Calculate the new affected pixel sum and overall total on paper.
3. Explain why a dimension with bounds 0 To 2 has three elements, while an upper bound of two alone is not an element count.
4. Add a second expected check for a particular channel so that two wrong channel values cannot accidentally cancel in a sum.
5. Describe what must change if the image gains an alpha channel; increasing a dimension alone does not define alpha compositing.


## Reference and next connection


- [FreeBASIC LBound reference](https://www.freebasic.net/wiki/KeyPgLbound)
- [FreeBASIC UBound reference](https://www.freebasic.net/wiki/KeyPgUbound)
- [Read pixels as an explicit Framework tensor](../../05-ai/generative-ai-foundations/20-read-pixels-as-an-explicit-tensor.md)


[Previous: Edit record fields with an explicit candidate](31-edit-records-with-an-explicit-candidate.md)

[Next: Format fixed ASCII fields without losing data](33-format-fixed-ascii-fields-without-losing-data.md)
