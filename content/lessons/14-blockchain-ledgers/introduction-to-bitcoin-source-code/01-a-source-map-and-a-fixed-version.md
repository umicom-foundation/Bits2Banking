# A source map and a fixed version

[Course contents](index.md) · [Next: Inputs, outputs and data types](02-inputs-outputs-and-data-types.md)

## Reading a large project without getting lost

Complete Introduction to Bitcoin first. Read C structures, functions and return values before trying the C++ source. Bitcoin Core is largely C++; a future C teaching implementation is a separate project, not a claim that Core is written in C.

This course uses the historical v28.0 tag as a stable reading reference. It is not a recommendation to install an old release or a claim that v28.0 is current. Fixing a reference version lets two readers discuss the same files. The lessons below do not require compiling or connecting a node.

```text
primitives/transaction.h   -> transaction data structures
consensus/tx_check.cpp    -> context-free transaction checks
validation.cpp           -> wider validation and chain context
```

Open the tagged repository page. Confirm the version selector says v28.0. Use the filename search to open the three files above. A header usually declares data and interfaces. A .cpp file contains C++ implementation. Neither filename size nor number of lines tells you whether a component is safe or complete.

## Make your own reading record

1. Record the tag and file path.
2. Find one symbol, such as CheckTransaction.
3. Write its input types and return type in plain language.
4. Identify one rejected condition and where the explanation is recorded.
5. Write what the function does not know. A function without a coins view cannot establish that an input is currently unspent.

Avoid starting with every line of a very large file. Follow a single responsibility and its callers. A useful notebook entry is a question and evidence path, not a copied wall of source.

## Exercise

Which file would you open first to understand the shape of a transaction? Which would you open to examine basic transaction rejection rules?

## Explained answer

Start with primitives/transaction.h for the data model and consensus/tx_check.cpp for the checks. Later inspect callers in validation.cpp. The same method applies to Umicom: start with a public header, then its implementation, then callers and tests. A source-reading exercise is not runtime verification.

## Continue learning

[Course contents](index.md) · [Next: Inputs, outputs and data types](02-inputs-outputs-and-data-types.md)

[Browser edition](../../../courses/introduction-to-bitcoin-source-code/lessons/01-a-source-map-and-a-fixed-version.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/base/sha256.h). This public revision matches the source inspected for this lesson.

[Primary reference](https://github.com/bitcoin/bitcoin/tree/v28.0).
