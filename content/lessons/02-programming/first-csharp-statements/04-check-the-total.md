<!--
Umicom Bits2Banking
File: content/lessons/02-programming/first-csharp-statements/04-check-the-total.md

PURPOSE:
Run small checks for normal input, a pending receipt, an unknown status and an amount outside the supported total.

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

# Check the posted total

[Course contents](index.md) · [Previous lesson · Keep only the posted receipts](03-keep-the-posted-receipts.md) · [Next course · Native Statement Calculations](../../../courses/native-statement-calculations/index.html)

Run small checks for normal input, a pending receipt, an unknown status and an amount outside the supported total.

## Write an expected result

A check compares what a program did with what you expected. Use both an ordinary example and an example that should be refused. With these fictional rows, the normal result is `2600 - 850 = 1750` cents. A list containing only a pending row should succeed with zero posted cents. A status of `waiting` should be refused.

The example saves the total only after all the rows pass. The method returns true or false as its main answer. An `out` parameter also lets it return the calculated number. The program sets that number to zero before any refusal.

## Run a program that checks itself

```csharp
using System;

static class Program
{
    static bool TryPostedTotal(string[] states, int[] amounts, out int total)
    {
        total = 0;
        if (states.Length != amounts.Length)
        {
            return false;
        }

        int subtotal = 0;
        try
        {
            for (int index = 0; index < states.Length; index++)
            {
                if (states[index] == "posted")
                {
                    // Refuse a result that cannot fit in the chosen whole-number type.
                    subtotal = checked(subtotal + amounts[index]);
                }
                else if (states[index] != "pending")
                {
                    return false;
                }
            }
        }
        catch (OverflowException)
        {
            return false;
        }
        total = subtotal;
        return true;
    }

    static void Check(string name, bool expectedSuccess, int expectedTotal,
                      string[] states, int[] amounts)
    {
        int total;
        bool success = TryPostedTotal(states, amounts, out total);
        if (success != expectedSuccess || total != expectedTotal)
        {
            throw new InvalidOperationException("Check failed: " + name);
        }
        Console.WriteLine("Pass: " + name);
    }

    static void Main()
    {
        // Check ordinary input, absence of posted rows and two refusal paths.
        Check("ordinary total", true, 1750,
              new[] { "posted", "posted", "pending" }, new[] { 2600, -850, 500 });
        Check("pending only", true, 0, new[] { "pending" }, new[] { 500 });
        Check("unknown status", false, 0, new[] { "waiting" }, new[] { 500 });
        Check("too large", false, 0,
              new[] { "posted", "posted" }, new[] { int.MaxValue, 1 });
    }
}
```

The word `checked` tells C# to signal overflow if adding an amount would go beyond the range of `int`. The `catch` block turns that signal into refusal. `true` and `false` are the two values of a Boolean. `||` means either comparison can show that the check failed.

```text
Pass: ordinary total
Pass: pending only
Pass: unknown status
Pass: too large
```

If a check reports a failure, read its name and compare its input and expected value. To see one failure safely, temporarily change the `pending only` expected total to `500`. Restore it to zero when you finish.

## Connect to Umicom

Use the same habit when you edit a practice project in Studio. Save a copy, write down the expected result, run the check, and compare the output. The linked native workshop uses the same synthetic posted amounts with Umicom C.

- [Native Statement Calculations](../../../courses/native-statement-calculations/index.html)
- [Umicom WebServer practice form](../../../labs/statement-cvm-web/index.html)
- [C# out parameters](https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/keywords/out-parameter-modifier)

[Open the HTML edition](../../../courses/first-csharp-statements/lessons/04-check-the-total.html)
