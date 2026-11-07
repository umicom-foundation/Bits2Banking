<!--
Umicom Bits2Banking
File: content/lessons/14-blockchain-ledgers/building-blockchain-from-scratch/05-define-the-bytes-before-hashing.md

PURPOSE:
  Present "Define the bytes before hashing a record" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Define the bytes before hashing a record

Two programs can describe the same record yet hash different bytes. This lab continues the Framework hash exercise by designing a small unambiguous record representation before using the existing SHA-256 service.

Source to open: `Umicom-Applications/framework/include/umicom/base/sha256.h`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath '..\Umicom-Applications\framework\include\umicom\base\sha256.h'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' '../Umicom-Applications/framework/include/umicom/base/sha256.h'
```

## Understand the idea

Serialization means turning values into a sequence of bytes. A hash consumes that byte sequence; it does not understand fields, currencies or JSON objects. Concatenating text without boundaries can be ambiguous: fields ab and c produce the same combined text as a and bc. A record format must define boundaries, encoding, field order and version. In this exercise we specify byte lengths and UTF-8 text. The specification is a practice format, not a Bitcoin wire format or a new production ledger protocol.

```text
Ambiguous:
  (ab,c) -> abc
  (a,bc) -> abc

Length-delimited practice format, hexadecimal bytes:
  (ab,c): 01 00 00 00 02 61 62 00 00 00 01 63
  (a,bc): 01 00 00 00 01 61 00 00 00 02 62 63
```

## Work through the lab

1. Open sha256.h and find Update's data and length parameters. Explain why the function cannot infer where one application field ends and another begins. Review the previous lesson's incremental-hash example.
2. Write the two ambiguous field pairs below and concatenate them. Observe that the resulting bytes match even though the fields differ. This is a serialization ambiguity, not a broken hash function.
3. Design a version-1 practice record on paper: a version byte, a four-byte unsigned big-endian length, then that many UTF-8 bytes, repeated for the next field. Big-endian means the most significant byte comes first. Define maximum accepted lengths before allocating memory.
4. Encode the short ASCII examples by hand and show the different length bytes. Plan rejection cases for a truncated length, a length larger than the remaining input and an unsupported version. A decoder must reject those before presenting an accepted record.

## Expected result

The two length-delimited byte sequences are different. Identical records should produce identical bytes under one specified format; different field boundaries should not accidentally collapse into the same bytes. A matching digest still does not identify a trusted author or establish network agreement.

## If the result differs

If identical text produces different bytes, inspect encoding, newlines, field order and numeric formatting. Do not remove meaningful differences merely to make hashes match. Keep a format version so a future change can be interpreted deliberately.

## Explain it yourself

Why should a length represent encoded bytes rather than a text editor's visible character count?

<details>
<summary>Worked explanation</summary>

UTF-8 characters can occupy different numbers of bytes, and a visible symbol may contain multiple code points. The decoder needs a precise byte boundary. Count the encoded bytes and validate that those bytes fit inside the remaining input.

</details>

## Use the idea in Umicom

Keep hashing in the existing Framework base service. A production canonical record codec should also be a shared reviewed service; applications should provide domain fields, not invent incompatible byte layouts independently.

[HTML edition](../../../courses/building-blockchain-from-scratch/lessons/05-define-the-bytes-before-hashing.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](04-link-records-with-framework-hashes.md) · [Course contents](index.md)

[Next: Turn record fields into defined bytes](06-turn-record-fields-into-defined-bytes.md)
