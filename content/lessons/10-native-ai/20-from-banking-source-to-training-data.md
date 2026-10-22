# Lesson 20 — From a Banking Source File to Training Data

**Level:** beginner • **Estimated time:** 14 minutes • **Language:** C23

## What you will learn

By the end you should be able to distinguish a **source file**, a **byte**, a **token** and a **training example**. You will inspect the real Umicom source-dataset interface and understand why a language model learns to predict symbols rather than directly executing a banking application.

## Begin with a useful engineering problem

Consider a small C23 module that checks a proposed fictional account transfer. The bank must reject requests that exceed the available balance; the code below is an **illustration**, not Umicom's production banking implementation:

```c
#include <stdbool.h>
#include <stdint.h>

bool CanTransfer(uint64_t availablePence, uint64_t transferPence)
{
    return transferPence <= availablePence;
}
```

We want a model eventually to recognise code structures such as a function declaration, parameter types, comparisons and return statements. A language model does **not** learn the bank's ledger semantics merely by reading this file. Initially it receives numerical symbols and tries to predict the next symbol.

## A file is a sequence of bytes

In a UTF-8 file the character `C` is represented by byte value **67**. For the simplest ASCII characters, one character is one byte. Non-ASCII characters can occupy several bytes. Therefore a byte-level model learns **bytes**, not necessarily letters or words.

Umicom's teaching tokeniser reserves four IDs for control symbols and maps ordinary byte `b` to token **`b + 4`**. For example, the ASCII capital `C` becomes token `71`. The lowercase `a` is byte `97`, so it becomes token `101`.

| Original byte | Numeric byte | Token ID |
|---|---:|---:|
| `C` | 67 | 71 |
| `a` | 97 | 101 |
| `(` | 40 | 44 |
| space | 32 | 36 |

This byte vocabulary contains 256 ordinary byte IDs plus four reserved IDs: **260 token IDs**. It is intentionally small and reversible. It cannot directly treat a whole C23 keyword as one token.

## From a sequence to a prediction

Suppose our example begins with `Can`. The model receives the first part of a sequence and predicts which token should follow. It may learn that `Can` is sometimes followed by `T` in names like `CanTransfer`, but it has no guarantee that the continuation is correct or safe.

Training provides an **input window** and its **target window**, shifted by one byte. The matching target for each input position is the next byte in the same source file. The decoder uses causal attention, so a position cannot read a later input position.

## Where it lives in Umicom Framework

The source-of-truth components are:

- `include/umicom/ai/training/byte_tokenizer.h` — reversible byte-to-ID mapping;
- `include/umicom/ai/training/dataset_manifest.h` — approved local source files;
- `src/ai/training/dataset_manifest.c` — bounded file sampling;
- `learning/native-llm/fixtures/` — deliberately tiny teaching sources.

The website explains these files; it does **not** introduce a second tokenizer, parser or training engine.

## Practical exercise: inspect the approved files

Open PowerShell and run the following from the existing local repository. These commands inspect files; they do not train or execute C23 source:

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
Get-Content '.\framework\learning\native-llm\fixtures\manifest.txt'
Get-Content '.\framework\include\umicom\ai\training\byte_tokenizer.h' -TotalCount 70
```

Look for the manifest entries for `train/account.c`, `train/notes.c` and `eval/payment.c`. Explain why the payment file belongs to a different partition. Do not replace these sources with live bank records, credentials or confidential project code.

## Check your understanding

1. Why can a single visible Unicode character occupy more than one byte?
2. What token ID represents ASCII `C` in the approved byte vocabulary?
3. Does training on a C23 transfer example prove that the resulting model can safely author financial software?

<details><summary>Reveal suggested answers</summary><p>UTF-8 uses one or more bytes per code point. ASCII `C` is byte 67 plus the reserved offset 4, giving ID 71. No: next-token training is not evidence of functional correctness, security or business-domain understanding.</p></details>

**Next:** assemble the bytes into carefully shaped input and target windows.
