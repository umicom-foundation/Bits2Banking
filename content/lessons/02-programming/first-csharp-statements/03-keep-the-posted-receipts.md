<!--
Umicom Bits2Banking
File: content/lessons/02-programming/first-csharp-statements/03-keep-the-posted-receipts.md

PURPOSE:
Build a new typed list of the posted amounts and preserve all original entries.

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

# Keep only the posted receipts

[Course contents](index.md) · [Previous lesson · Count posted receipts](02-count-posted-receipts.md) · [Next lesson · Check the posted total](04-check-the-total.md)

Build a new typed list of the posted amounts and preserve all original entries.

## Choose the items to keep

A list is a collection that can grow when you add an item. A filter is a rule for choosing which items to keep. Start with three complete receipts. Keep only the amounts from posted receipts. On paper, draw an empty column. Write 2600 in it, then -850. Leave the pending amount of 500 in the original receipt list only.

## Make a list in C#

A `Receipt` is a small class that groups the status and amount. `new Receipt(...)` makes one receipt. `new List<int>()` creates an empty list that stores whole numbers. `Add` appends an amount. The full example below uses `foreach` because the loop needs each receipt without its position.

```csharp
using System;
using System.Collections.Generic;

class Receipt
{
    public readonly string Status;
    public readonly int Cents;

    public Receipt(string status, int cents)
    {
        Status = status;
        Cents = cents;
    }
}

static class Program
{
    static void Main()
    {
        Receipt[] original = {
            new Receipt("posted", 2600),
            new Receipt("posted", -850),
            new Receipt("pending", 500)
        };
        // Own the filtered amounts separately from the original receipts.
        List<int> posted = new List<int>();
        foreach (Receipt receipt in original)
        {
            if (receipt.Status == "posted")
            {
                posted.Add(receipt.Cents);
            }
        }
        foreach (int cents in posted)
        {
            Console.WriteLine(cents);
        }
        Console.WriteLine("Kept: " + posted.Count);
    }
}
```

Run it in the same practice project. Expect `2600`, then `-850`, then `Kept: 2`, each on its own line. `Count` tells you the number of items that were added to the new list. The `readonly` fields keep their assigned values after the receipt is created.

## Try a second result

Change the first receipt to `pending`. The remaining output should be `-850` and `Kept: 1`. Restore the original before the next lesson. If your program still prints the amount of the last pending receipt, inspect the status test and the braces that enclose the call to `Add`.

## Connect to Umicom

A practice Umicom Bank screen can keep the original receipt list and show a filtered view beside it. Once a filter is easy to explain, compare it with a browser filter or a database query.

- [Accessible Statement Review](../../../courses/accessible-statement-review/index.html)
- [SQL Statement Reconciliation](../../../courses/sql-statement-reconciliation/index.html)
- [C# List type](https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1)

[Open the HTML edition](../../../courses/first-csharp-statements/lessons/03-keep-the-posted-receipts.html)
