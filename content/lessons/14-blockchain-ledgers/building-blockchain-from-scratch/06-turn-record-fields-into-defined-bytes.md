<!--
Umicom Bits2Banking
File: content/lessons/14-blockchain-ledgers/building-blockchain-from-scratch/06-turn-record-fields-into-defined-bytes.md

PURPOSE:
Explain the lesson: Turn record fields into defined bytes.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Turn record fields into defined bytes

## Prepare

Open `labs/native/framework-hash/main.c` and its README. A hash is a fixed-size summary of exact bytes. This lab calls the existing Umicom Framework hashing service; it does not create a cryptocurrency network. Use the `chain` scenario as the source for these paper exercises.

## Understand the idea

A chain must have one agreed representation of each record. C structures can contain padding and machine-dependent layouts, so their raw memory is unsuitable as an implicit format.

## Work through the example

1. Find `HashLink`.
2. Identify the record's sequence and amount fields.
3. Draw eight byte boxes.
4. Put sequence 1 and amount 25 into the specified little-endian fields.

## Check your reasoning

The first four bytes are 01 00 00 00 and the next four are 19 00 00 00 in hexadecimal. Hexadecimal writes each byte using two base-16 digits.

## If something differs

Do not hash the address of a struct and assume it represents the same record on every target. Keep the byte-writing rule explicit and test it separately.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-hash/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](07-connect-a-record-to-the-previous-digest.md)


[Previous: Define the bytes before hashing a record](05-define-the-bytes-before-hashing.md)
