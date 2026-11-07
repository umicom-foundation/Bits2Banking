<!--
Umicom Bits2Banking
File: content/lessons/10-native-ai/llm-from-scratch/understand-byte-token-windows.md

PURPOSE:
Understand input tokens and next-byte targets

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand input tokens and next-byte targets

This practical module starts with ordinary text files. You will learn what a dataset, token, training step and evaluation result mean by following the existing native Framework laboratory.

## Setup recap

A terminal runs commands that you type. A compiler translates C source into a program; CMake describes the build and Ninja performs the necessary steps. On Windows install Git and the MSYS2 UCRT64 C compiler, CMake and Ninja. Keep Umicom Applications at `C:\umicom\Umicom-Applications`. On Linux use your system's C23 compiler, CMake and Ninja and change into your Applications checkout.

This module uses a small standalone directory within Framework. It does not require a GPU, account or model download. Configure once in PowerShell:

~~~powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S framework/learning/native-llm -B build/learning-dataset -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/learning-dataset --target umicom-native-llm-dataset umicom-native-llm-source-train --parallel 2
~~~

In Bash use the same CMake commands from the checkout directory; omit the PowerShell Path line. Stop if a command reports an error. The lessons explain expected results rather than assuming the build has succeeded. The [CMake course](../../../courses/learning-cmake/index.html) expands each build concept.


## Numbers at the model boundary

A model calculates with numbers. A tokenizer converts input into token identifiers. This laboratory uses one token for each byte, with four reserved identifiers before the byte values. An ordinary byte becomes its value plus four.

For ASCII text `cat`, the byte values are 99, 97 and 116. Their token identifiers are 103, 101 and 120. The word is still text; these identifiers are the representation used by the model.

## Shift the target by one position

~~~text
Text bytes:    c   a   t   !
Input tokens: 103 101 120
Target tokens:101 120  37
~~~

The first input position asks the model to predict `a` after `c`. The final target predicts `!` after `t`. A context of three input tokens therefore needs four source bytes.

## Read the real arrays

1. Run the dataset inspector.
2. Find `Training input tokens` and the following `Next-byte targets`.
3. Check that each target except the final one equals the next input token.
4. Subtract four from an ordinary token to obtain its byte value.
5. Repeat for the evaluation window.

UTF-8 uses several bytes for some characters. Therefore a byte token is not always a complete displayed character. Never subtract four from a reserved token or assume every number is printable text.

## Extend the exercise

In a practice document write `cat!` several times, followed by a different sentence. Inspect the dataset and explain which window was sampled. The exact sample depends on the file order, seed and eligible windows, so do not expect the first eight bytes automatically.

If you want to read complete sentences, use the tokenizer's decode contract and its output capacity rules. Numeric token reports are useful for debugging small examples; they are not a user-facing document viewer.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/ai/training/byte_tokenizer.h).

## Continue learning

[Course contents](../../../courses/llm-from-scratch/index.html) · [Previous: Inspect the dataset with a native C program](inspect-dataset-with-native-c.md) · [Next: Reproduce a sample without crossing document boundaries](reproduce-a-training-sample.md)
