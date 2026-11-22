<!--
Umicom Bits2Banking
File: content/lessons/02-programming/first-csharp-statements/01-name-values-in-a-receipt.md

PURPOSE:
Read one C# declaration and use a small console program to display three parts of a fictional receipt.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom Foundation" width="220">
</picture>

# Name values in a receipt

[Course contents](index.md) · [Next lesson · Count posted receipts](02-count-posted-receipts.md)

Read one C# declaration and use a small console program to display three parts of a fictional receipt.

## Read before typing

A receipt records something that happened. In this practice example, the ID is 1, the amount is 2600 cents and the status is posted. Posted means the entry is counted in this workshop. The data belongs to a fictional account.

A variable gives a value a name. A type describes which kind of value can be stored there. Here `int` holds a whole number and `string` holds text. In C# and Java, `int` is a signed 32-bit type. C spells some declarations the same way, and the width of its `int` can vary.

## Make your first small program

You can trace the example with a pencil. If a .NET SDK is already installed, open a new practice folder in a terminal and enter the command below. It creates a `ReceiptLab` subfolder. Keep any earlier project in its own folder.

```text
dotnet new console --name ReceiptLab --output ReceiptLab
```

Open `ReceiptLab/Program.cs` in your editor. In this private practice copy, replace its starter text with the program below. The program starts at `Main` and uses `Console.WriteLine` to display one line.

```csharp
using System;

static class Program
{
    static void Main()
    {
        // Use whole cents so the amount keeps a clear unit.
        int receiptId = 1;
        int cents = 2600;
        string status = "posted";
        Console.WriteLine(receiptId + " " + status + " " + cents);
    }
}
```

Read `int cents = 2600;` as a declaration of a whole-number value called cents. The `=` gives it an initial value. The semicolon ends that instruction. The text values in quotes include single spaces so the output has three parts.

```text
dotnet run --project ReceiptLab
```

Expect `1 posted 2600`. Change only the starting value of `cents` to `3000` and predict the output. Run again or check on paper for `1 posted 3000`.

## If the output differs

If the terminal cannot find `dotnet`, use the paper trace or check whether the SDK is installed. If the message says it cannot find the project, check that the terminal is in the practice folder that contains `ReceiptLab`. If the compiler points near a line ending, compare the semicolons and matching braces with the example.

## Connect to Umicom

You can open the example in Studio as a text file and read the names and expected output side by side. Use the C# tools above when you want to execute it. Umicom product code in this learning path uses C for the shared calculation. This C# example teaches the equivalent idea.

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [C# integral types](https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/builtin-types/integral-numeric-types)
- [.NET project creation](https://learn.microsoft.com/en-us/dotnet/core/tools/dotnet-new)
- [.NET project execution](https://learn.microsoft.com/en-us/dotnet/core/tools/dotnet-run)

[Open the HTML edition](../../../courses/first-csharp-statements/lessons/01-name-values-in-a-receipt.html)
