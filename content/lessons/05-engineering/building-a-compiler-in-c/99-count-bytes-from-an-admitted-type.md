<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/99-count-bytes-from-an-admitted-type.md

PURPOSE:
Practise converting a count of fixed-width C fields to a checked byte count.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Count bytes from an admitted type

[Course contents](index.md) · [Previous lesson](98-name-values-before-the-entry.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/99-count-bytes-from-an-admitted-type.html)

A record can carry several fields, such as the number of books borrowed, returned and still on loan. If you encode three signed 32-bit fields consecutively, each one uses four bytes. Find that width from the compiler profile before calculating the size of the record.

~~~c
constexpr int BYTES_PER_FIELD = sizeof(const int);
enum { FIELDS = 3, RECORD_BYTES = FIELDS * BYTES_PER_FIELD };
static_assert(RECORD_BYTES == 12, "Expect three four-byte fields");

int main(void) {
    return RECORD_BYTES;
}
~~~

`sizeof` tells the compiler to measure the admitted type. Adding `const` keeps the same representation and limits how an object can be changed. The operator accepts a parenthesized integer type in this profile. Other C compilers can choose a different width for `int`. [WG14 C23 working draft, section 6.5.3.4](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf)

## Run and check the units

1. Save the program as `record-size.c`. Run `umicom-c interpret record-size.c` and look for `Result: 12`.
2. Change `FIELDS` to 5. Run `umicom-c interpret record-size.c --check-only` and read the assertion message. The field count is now five, so the byte count is 20. Update the assertion to check 20 and describe five fields, then expect `Result: 20` when you run the program.
3. Replace `sizeof(const int)` with `sizeof(void)` and repeat the check. This profile expects an integer type after the opening parenthesis. Restore the original type to recover.

A native structure can include alignment padding and a real binary format also defines byte order. This exercise counts consecutive fixed-width fields. It is the first arithmetic check you can make before designing a file or message format.

## Measure a type before its value is ready

Consider an integer whose first value should be the size of its own type. In the practice file `labs/native/compiler-source-boundaries/own_declarator.c`, `const int byte_count = sizeof byte_count;` already establishes the name and its integer type before the initializer is checked. Measuring the type requires no stored value from `byte_count`. The compiler can place the result into that new variable once the measurement succeeds.

Run `umicom-c interpret labs/native/compiler-source-boundaries/own_declarator.c` from the Bits2Banking checkout. The final comparison returns `Result: 1` when the stored count matches `sizeof(int)`. In a copy, add parentheses to make `sizeof(byte_count)` and expect the same result. Changing the initializer to the name `byte_count` on its own requests an actual value from a variable still being initialized. Check that copy with `--check-only` and expect refusal.

When reading compiler code, follow the name and its value separately. The declared type can be known while its storage is waiting for initialization. The interpreter uses the same distinction when it prepares source steps. Its source check does not need to reach into uninitialized storage.

~~~c
int main(void)
{
    /* The operand names its type while byte_count is being initialized. */
    const int byte_count = sizeof byte_count;
    /* A normalized comparison gives the same answer at different int widths. */
    return byte_count == sizeof(int);
}
~~~

[Next lesson on aligning a field](100-align-record-fields.md)
