<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/47-publish-a-complete-record-size.md

PURPOSE:
Publish a complete record size

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Publish a complete record size

A summary record has a body and a header. A correct body length can still produce an invalid total when the header is added. Treat both results as a single plan that other code can safely read.

## Separate the two operations

Eight entries of 16 bytes have a 128-byte body. Adding a 64-byte header produces a total of 192. First check the multiplication. Then check the addition using that candidate body size.

## Exercise a late failure

`SIZE_MAX / 16` gives an admissible body count. `SIZE_MAX % 16` is the leftover space. Add a header with one byte more than the leftover and only the second calculation will fail. Verify both fields of the prior output. This check would catch a premature write of the body.

## Connect to Framework and WebServer

Framework can return complete sizing information to a WebServer caller that prepares a response. Each refusal keeps the previous answer available. File writes, network delivery and storage limits still belong to their own operations.

## Trace the logic

~~~text
MULTIPLY item count BY item size INTO candidate body
IF BODY DOES NOT FIT, REFUSE
ADD header size TO candidate body INTO candidate total
IF TOTAL DOES NOT FIT, REFUSE
COPY BOTH CHECKED FIELDS TO the caller
~~~

~~~c
typedef struct RecordSize {
    size_t body;
    size_t total;
} RecordSize;

static bool plan_record(size_t items, size_t header, RecordSize *sizes)
{
    /* Either stage may fail. Copy the complete plan after both succeed. */
    RecordSize candidate;
    if (ckd_mul(&candidate.body, items, (size_t)16)) return false;
    if (ckd_add(&candidate.total, candidate.body, header)) return false;
    *sizes = candidate;
    return true;
}
~~~

## Build and run one practice case

1. Open a PowerShell terminal with GCC, CMake and Ninja on the search path. To use Clang, select `clang` in the configure command and choose a separate build directory in all three commands. Check that the selected C compiler and its headers provide `<stdckdint.h>`. If that header is missing, the final lesson demonstrates `size_t` guards using only older headers.
2. Open `labs/native/checked-integers/record.c`. Read the successful case and at least one refusal case.
3. Run the commands one at a time. Stop on the first error so an earlier executable cannot be mistaken for the latest build.

~~~powershell
Set-Location "C:/umicom/Umicom-Bits2Banking"
cmake -S labs/native/checked-integers -B build/checked-integers -G Ninja -DCMAKE_C_COMPILER=gcc
cmake --build build/checked-integers --target checked-integers-record
ctest --test-dir build/checked-integers -R "^lesson[.]checked-integers[.]record$" -V --no-tests=error
~~~

Expect one passing test and this line of program output.

~~~text
Body: 128 bytes. Total: 192 bytes. Both refusals kept the original plan.
~~~

## Try a change

Try a 32-byte header. Update only the expected complete total. Leave one case that fails during multiplication and one that fails during addition.

## If a result differs

If only the body changes after an overflow, step through the stores. Keep `candidate.body` and `candidate.total` temporary until both checks have succeeded.

## Read the C language reference

[WG14 N3220, section 7.20.1 on checked integer operations](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf#page=326)

[Course contents](index.md) · [Previous: Check block counts before using bytes](46-check-block-counts-before-using-bytes.md) · [Next: Use unsigned guards without the library](48-use-unsigned-guards-without-the-library.md)
