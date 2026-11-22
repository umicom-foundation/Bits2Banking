<!--
Umicom Bits2Banking
File: content/lessons/02-programming/first-csharp-statements/02-count-posted-receipts.md

PURPOSE:
Trace a counting loop and read the matching structure in C and Java.

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

# Count posted receipts

[Course contents](index.md) · [Previous lesson · Name values in a receipt](01-name-values-in-a-receipt.md) · [Next lesson · Keep only the posted receipts](03-keep-the-posted-receipts.md)

Trace a counting loop and read the matching structure in C and Java.

## Check each item in order

The practice account has three receipts with the states `posted`, `posted` and `pending`. An array keeps items in order. An index is the position used to select one item. C#, C and Java number the first position zero. Here a loop repeats a test for each of the three positions.

```text
count starts at zero
for each position from zero up to the end of the list
    if the state at that position is posted
        add one to count
show count
```

The lines above are pseudocode. They describe the work without choosing one programming language. Trace the count as 0, then 1, then 2. The last receipt leaves the count at 2.

## Run the C# counting loop

Use the practice project from the previous lesson. Replace `Program.cs` in your practice copy, then run `dotnet run --project ReceiptLab` from its parent folder. The C# `for` line has a starting value, a condition and a step.

```csharp
using System;

static class Program
{
    static void Main()
    {
        string[] states = { "posted", "posted", "pending" };
        int count = 0;
        // Use the list length as the exclusive end of the loop.
        for (int index = 0; index < states.Length; index++)
        {
            if (states[index] == "posted")
            {
                count++;
            }
        }
        Console.WriteLine(count);
    }
}
```

C# uses `states.Length` to get three. The last valid position is two. `index++` adds one to the index after each loop body. The `==` test compares the text values in this C# example. The assignment sign `=` gives a variable a value.

## Read C and Java equivalents

C and Java share the three-part `for` shape. Java reads the array length with lowercase `length`. For ordinary strings, Java uses `equals` to compare content. With C strings, `strcmp` declared in `<string.h>` returns zero when two strings match. Here are the loop bodies with the conditions already selected for each language.

```c
/* states holds three C strings. The array size supplies state_count. */
for (size_t index = 0; index < state_count; index++) {
    if (strcmp(states[index], "posted") == 0) {
        count++;
    }
}
```

```java
// states is a Java array of strings.
for (int index = 0; index < states.length; index++) {
    if ("posted".equals(states[index])) {
        count++;
    }
}
```

Change the last item in your C# array to `posted`. The count should rise to 3. When an index error occurs, check the end of the loop. Starting at zero and checking `<` keeps the index below the length.

## Connect to Umicom

The number of posted rows gives you a quick cross-check when designing a practice statement report. Write the expected count before you run the program. Then read all five language forms in the comparison lesson.

- [Repeat the same loop in several languages](../../../courses/programming-across-languages/lessons/04-repeat-the-same-for-loop.html)
- [Learning C](../../../courses/learning-c/index.html)
- [Learning Java](../../../courses/learning-java/index.html)
- [C# iteration statements](https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/statements/iteration-statements)
- [C# equality](https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/operators/equality-operators)

[Open the HTML edition](../../../courses/first-csharp-statements/lessons/02-count-posted-receipts.html)
