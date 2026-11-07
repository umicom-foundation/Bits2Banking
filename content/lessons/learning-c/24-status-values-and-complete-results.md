<!--
Umicom Bits2Banking
File: content/lessons/learning-c/24-status-values-and-complete-results.md

PURPOSE:
Explain the lesson: Return a status and publish one complete result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Return a status and publish one complete result

## Separate the answer from the outcome

A function may be unable to produce an answer. A status value tells the caller whether the operation completed. The checksum is a separate output. This is useful when an empty or zero-like answer could otherwise be confused with failure.

## Setup recap

Open the checksum lab in a text editor. The [lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-checksum/README.md) explains compiler setup, the required Framework SDK, configuration, building and tests. You can trace this chapter on paper before installing tools.

## Read the contract first

~~~c
UmiStatus BtbChecksumStream(FILE *stream,
    char output[UMI_SHA256_HEX_CAPACITY]);
~~~

`UmiStatus` is Framework's shared result type. `UMI_STATUS_OK` means success. The caller supplies a writable buffer of 65 characters: 64 hexadecimal digits and one terminating zero.

The array notation in a C parameter does not check the caller's buffer size at runtime. It documents a requirement; the caller still has to allocate enough space. Both `main.c` and the tests use the named capacity rather than guessing.

## Trace the publication point

The adapter calculates into local storage. After reading and finalising succeed, it copies the complete result into the caller's buffer. An earlier return leaves that output untouched.

~~~text
caller output: "unchanged"
invalid input -> return INVALID_ARGUMENT -> output still "unchanged"
valid input   -> calculate locally       -> copy result -> return OK
~~~

This promise applies to the output, not every object involved. The stream may already have advanced. Good contracts say exactly which state is preserved.

## Lab

1. Find each return in `checksum.c`.
2. Mark which returns occur before the output copy.
3. Inspect the test that passes a null stream and a buffer containing `unchanged`.
4. Explain why that test checks both the status and the buffer.
5. Build and run the checks from the lab guide.
6. Add an exercise assertion that the successful string has length 64.

Do not remove status checks merely because the happy path works. An invalid SDK context or file error still needs a meaningful outcome.

## Troubleshooting

A linker error for `umi_status_text` means the declaration was visible but its implementation was not linked correctly. Check the Framework base library and SDK revision. A compiler warning about incompatible pointers is not fixed by an arbitrary cast; compare the declaration with the actual argument.

## Connect to applications

A desktop label, a web response or a command line can display the same model result. The presentation decides how to explain the status. Reusable result semantics belong to Framework; interfaces should not invent different meanings for the same error.

## Exercise and explanation

A file read fails after one chunk. The output buffer still contains its old value. Can the caller retry from the same position without seeking? No. The promise preserves the output buffer, but reading may already have advanced the stream. A retry needs a deliberate stream-position policy and another error check.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-checksum/checksum.h). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](23-chunks-eof-and-read-errors.md) · [Next lesson](25-check-file-digests-independently.md)

