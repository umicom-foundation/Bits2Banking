<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/08-spans-terminators-and-text-policy.md

PURPOSE:
Explain the lesson: Separate a byte span from a terminated string.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate a byte span from a terminated string

## Prepare
Read `Validate` and `CopyPair` in the fault-injection lab. A byte span is an address plus a count of readable bytes. A C string ends at a zero byte, written `'\0'`. These are different contracts.

The lab accepts an explicit span, checks its contents, then makes an owned terminated copy.

## Walk through a short title
For the title `Plan`, titleBytes is 4. CopyPair requests 5 bytes. Four bytes hold P, l, a and n; the final byte holds the terminator.

```text
Index:     0   1   2   3    4
Stored:    P   l   a   n   \0
Span size: 4
Allocation size: 5
```

The input itself need not contain a terminator within its readable span. The caller must still provide at least the stated number of readable bytes.

## Explain the checks
The lab refuses a null pointer, even for an empty body. It refuses an empty title, allows a zero-length body with a valid pointer, and limits either span to 80 bytes. It uses `memchr` to reject an embedded zero byte because the saved representation promises ordinary C strings.

The bound of 80 makes adding one representable. A general-purpose routine accepting arbitrary size_t values would need an overflow check before adding terminator space.

## Exercise
Predict the result for:
1. title `"A"`, length 1;
2. title `"A"`, length 0;
3. body `""`, length 0;
4. title bytes A, zero, B with length 3;
5. a valid readable span with length 81.

Expected statuses are OK, INVALID, OK, INVALID and LIMIT, assuming all other arguments are valid. For rejected input, allocation attempts should not increase.

## Diagnose safely
Never claim a small array has a longer readable span merely to test a boundary that is accepted. For the rejected length 81, the implementation checks the limit before reading; the test relies on that specified ordering. Use valid live pointers and inspect the contract before constructing cases. Bytes and displayed characters also differ for UTF-8; this lab has a byte limit, not a complete Unicode editing policy.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/fault-injection/note.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-allocator-context-and-test-doubles.md) · [Next lesson](09-revisions-and-stale-writers.md)

