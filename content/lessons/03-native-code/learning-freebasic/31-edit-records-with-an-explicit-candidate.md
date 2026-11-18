<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/31-edit-records-with-an-explicit-candidate.md

PURPOSE:
Edit record fields with an explicit candidate

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Edit record fields with an explicit candidate

[Course contents](index.md)

## Give a record a concrete purpose

A record groups related named values. FreeBASIC declares a record with Type and End Type. Our PixelSize record contains a width and a height. A FramePlan contains two PixelSize records: inputSize describes an input image and outputSize describes a requested result. This is only a plan made of numbers. It does not allocate pixels, open an image or perform resizing. Keeping the exercise numerical lets us inspect state changes without a graphics library.

~~~freebasic
Type PixelSize
    width As ULong
    height As ULong
End Type

Type FramePlan
    inputSize As PixelSize
    outputSize As PixelSize
End Type
~~~


## Read dotted names from left to right

Dim plan As FramePlan creates one variable of the declared record type. plan.inputSize.width means: begin with plan, select its inputSize field, then select that field’s width. A period separates each step. A type describes what fields exist; a variable stores actual field values. We can create many FramePlan variables from one declaration. In this example ULong is an unsigned 32-bit integer, suitable for nonnegative dimensions within its range. It cannot represent negative values, but that alone does not prevent an excessive image request.

1. Write the complete name plan.inputSize.width and assign 640.
2. Assign 360 to plan.inputSize.height.
3. Assign 320 and 180 to the output fields. Check that the input and output describe different sizes.


## Use With as field-access shorthand

With plan begins a block in which .inputSize.width refers to that plan. End With closes it. A nested With .outputSize makes the leading period refer to the nested output record until its own End With. After closing the inner block, the outer plan is the implicit receiver again. The leading period is therefore meaningful: it identifies a field of the active record. With changes how names are written. It does not create an independent snapshot, validate dimensions or automatically undo assignments.

~~~freebasic
Dim plan As FramePlan
With plan
    .inputSize.width = 640
    .inputSize.height = 360
    With .outputSize
        .width = 320
        .height = 180
    End With
End With
~~~


## Trace the receiver before each assignment

A receiver is the record whose field an operation addresses. Expand every shorthand line into its full dotted name to check your understanding. The two output assignments become plan.outputSize.width = 320 and plan.outputSize.height = 180. The inner and outer End With statements close different blocks. Indentation helps humans see that structure, while the keywords tell the compiler where each block ends. Start the block normally; jumping into its middle with Goto would bypass the setup used for field access. Use this exercise’s fb dialect and stable local records rather than mixing dialect-specific scope rules or temporary object behavior.


| Inside which block? | Short spelling | Complete receiver path |
| --- | --- | --- |
| Outer With plan | .inputSize.width | plan.inputSize.width |
| Inner With .outputSize | .width | plan.outputSize.width |
| Inner With .outputSize | .height | plan.outputSize.height |
| After inner End With | .inputSize.height | plan.inputSize.height |


## Decide what makes a request acceptable

A valid output must have two nonzero dimensions and contain at most 1,048,576 pixels. A pixel is one picture position; this limit counts positions, not bytes. A color format may use several bytes per position. MAX_PIXELS is a named constant, so one declaration states the policy. The function receives the plan ByRef, meaning it can change the caller’s record, and receives dimensions ByVal, meaning its parameter values are separate copies. Boolean reports acceptance or refusal. Refusal must keep the previous accepted plan.

1. Reject a zero width or zero height before division.
2. Convert the dimensions to ULongInt, an unsigned 64-bit integer type, for the admission calculation. CULngInt is the conversion function.
3. Compare width with MAX_PIXELS divided by height using integer division. This checks width times height against the budget without first calculating a possibly overflowing product.
4. Only construct and publish an accepted change after those checks.


## Make the candidate and publication visible

A candidate is a proposed new value that has not yet replaced the accepted one. The function copies the current FramePlan into a local variable, updates the candidate’s output fields, then assigns the completed candidate back to plan. This particular record contains only nested numeric value fields: there are no pointers or dynamic arrays sharing hidden storage. Do not generalize that independence to records that contain addresses of other objects. A shallow copy of a pointer still points at the same storage. The explicit candidate pattern is useful in native settings, media plans and form validation, but it is not a database transaction or protection against concurrent writers.

~~~freebasic
Function TryOutput(ByRef plan As FramePlan, ByVal width As ULong, ByVal height As ULong) As Boolean
    If width = 0 OrElse height = 0 Then Return False
    If CULngInt(width) > MAX_PIXELS \ CULngInt(height) Then Return False
    Dim candidate As FramePlan = plan
    With candidate.outputSize
        .width = width
        .height = height
    End With
    plan = candidate
    Return True
End Function
~~~


## Predict acceptance before running

An 800 by 600 output contains 480,000 pixels and fits the limit. A 2,000 by 1,000 output contains 2,000,000 and must be refused. An 800 by zero output is also refused. After both refusals, the accepted output remains 800 by 600 and the input remains 640 by 360. Preserving the input fields matters: editing one aspect of a plan should not accidentally replace unrelated choices. The program contains explicit checks and nonzero exit codes if these expectations fail.


| Requested output | Expected result | Stored output afterward |
| --- | --- | --- |
| 800 × 600 | Accept | 800 × 600 |
| 2000 × 1000 | Refuse: over pixel limit | 800 × 600 |
| 800 × 0 | Refuse: empty dimension | 800 × 600 |


## Compile the complete source and observe

Use FreeBASIC’s fbc compiler in a PowerShell terminal. A compiler translates source text into a native executable. The -lang fb option selects the language dialect used here, and -exx enables runtime error checking supported by the compiler. Checks help diagnose mistakes but do not replace the function’s explicit admission branches. The following commands assume a Bits2Banking checkout under C:\umicom. Run each command separately and stop after an error; a previously created executable can remain after a later compilation fails.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
fbc -lang fb -exx record_drafts.bas -x record-drafts-basic.exe
.\record-drafts-basic.exe
~~~


## Check output and solve common mistakes

The expected text appears below. If fbc is not recognized, review the course’s compiler setup lesson and ensure the compiler directory is available in this terminal. If the compiler reports a missing field, expand the dotted name and inspect the Type declaration. If it reports an unmatched block, count each With and End With pair. Do not change a failed assertion until you have traced the requested dimensions and the last accepted record. This example is a FreeBASIC source exercise; a successful Framework C build does not validate its language semantics.

~~~text
input stays 640 by 360; output is 800 by 600
oversized and empty requests refused; accepted record preserved
~~~


## Apply the idea without duplicating the Framework

In a BASIC client for Umicom, a record can collect a user’s proposed settings before calling a documented C API. The Framework service should remain the owner of reusable validation, resource lifetime and publication rules. This self-contained exercise teaches the mechanics without claiming FramePlan has a published Framework ABI. ABI means the binary calling and layout agreement between separately compiled code. Before sharing a record across languages, specify field widths, padding, ownership and calling convention. In production, use the existing Framework service instead of creating a second implementation of its rule.

1. Rewrite the nested With block using only full dotted names. Predict that the resulting values remain identical.
2. Add an explicit successful 1,024 by 1,024 request. Calculate its pixel count and explain why equality with the limit is accepted.
3. Test 1,025 by 1,024 and explain why the candidate must not become the accepted plan.
4. Explain what would change if PixelSize contained a pointer to a pixel buffer: a record assignment would not automatically clone the pointed-to pixels.


## Language reference


- [FreeBASIC With statement](https://www.freebasic.net/wiki/KeyPgWith)


[Previous: Read fixed data records and reset the cursor](30-read-fixed-data-records-and-reset-the-cursor.md)

[Next: Follow row, column and channel bounds](32-follow-row-column-and-channel-bounds.md)
