<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/100-align-record-fields.md

PURPOSE:
  Practise finding a valid starting byte for an aligned integer in a small record.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Align the fields in a record

[Course contents](index.md) · [Previous lesson](99-count-bytes-from-an-admitted-type.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/100-align-record-fields.html)

A record has a five-byte label followed by a four-byte signed count. The label takes bytes 0 through 4. If the count starts at a multiple of four, the first suitable starting byte is 8. Bytes 5, 6 and 7 are padding, which is space set aside between fields.

## Find the first suitable byte

For small nonnegative lengths, add one less than the alignment, use integer division by the alignment, then multiply back. Integer division discards the remainder. Starting at 5, add 3 to get 8, divide by 4 to get 2, then multiply by 4 to get 8 again.

~~~c
constexpr int ALIGNMENT = alignof(const int);
enum { LABEL_BYTES = 5 };
enum { COUNT_OFFSET = ((LABEL_BYTES + ALIGNMENT - 1) / ALIGNMENT) * ALIGNMENT };
static_assert(COUNT_OFFSET == 8, "Expect the count to start at byte eight");

int main(void) {
    return COUNT_OFFSET + sizeof(int);
}
~~~

1. Save as `alignment.c`. Run `umicom-c interpret alignment.c` and look for `Result: 12`, the byte just after the last byte used.
2. Change `LABEL_BYTES` to 8. The result stays at 12 and the label ends exactly where the count starts.
3. Change the length to 9 and run `umicom-c interpret alignment.c --check-only`. Read the assertion message. Update the assertion to check 12 and describe the new start. Run again and expect `Result: 16`.

## Write the calculation in pseudocode

~~~text
BEGIN
    LET alignment = 4;
    LET label_bytes = 5;
    LET count_offset = ((label_bytes + alignment - 1) / alignment) * alignment;
    RETURN count_offset + 4;
END
~~~

Save as `alignment.ump` and run `umicom-c pseudocode alignment.ump`. Expect `Result: 12`. Pseudocode supplies both fours explicitly. The C example gets alignment and size from separate operators, and other types can give different values.

A real file format also specifies padding values and byte order. Before using the formula with larger inputs, check that alignment is positive and the addition fits. [WG14 C23 working draft](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf)

## Find the next admitted offset

The `%` operator gives the remainder after division. Offset one leaves remainder one when divided by four, so three more bytes reach the next multiple. Offset four leaves remainder zero and stays at four.

~~~text
GET the chosen type alignment
FIND the remainder of the current offset divided by the alignment
IF that remainder is nonzero
    ADVANCE by alignment minus remainder
RETURN the resulting offset
~~~

~~~c
int main(void)
{
    /* Leave one byte for a practice kind field before the first int. */
    int alignment = alignof(int);
    int offset = 1;
    int remainder = offset % alignment;
    /* Move only when the present offset violates the type's requirement. */
    if (remainder != 0) {
        offset = offset + alignment - remainder;
    }
    return offset;
}
~~~

## Run the C practice program

1. Open `labs/native/compiler-source-boundaries/align_field.c` in your Bits2Banking checkout. Read the declared alignment and predict the offset before running it.
2. In that checkout’s terminal, use the `umicom-c` executable from your checked compiler build. Run `umicom-c interpret labs/native/compiler-source-boundaries/align_field.c`.
3. With the checked integer profile used here, expect `Result: 4` from the starting offset of one. A hosted compiler may choose a different integer alignment. You can build the same source with its C23 mode to check the result on that target.
4. Try starting offsets four and five. Predict which one stays put. Run each copy separately and write down the starting and returned offsets.

The expression keeps all values small. In a reusable loader, verify the field width, check the addition against the destination capacity and keep any existing output when an invalid field is refused. An integer alignment is positive. A receiver should separately validate any alignment number read from another source.

## When a type spelling is refused

Keep the admitted type inside `alignof(int)`. In C23, `alignof` measures a type name. The local-name exercise in the previous lesson uses `sizeof`, which can measure an admitted expression’s type. A normal `sizeof` on an already admitted fixed-width integer does not read its current value.

[C23 working draft, size and alignment operators](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf#page=95)

[Next: Read adjacent assertion messages](101-read-adjacent-assertion-messages.md)
