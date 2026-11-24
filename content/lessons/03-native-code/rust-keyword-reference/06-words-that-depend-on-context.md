<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/rust-keyword-reference/06-words-that-depend-on-context.md

PURPOSE:
  Teach the selected weak words in the Rust 2024 edition.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read words that depend on context

[Course contents](index.md) · [Previous lesson](05-external-and-asynchronous-boundaries.md) · [Next lesson](07-words-reserved-for-later.md) · [HTML edition](../../../courses/rust-keyword-reference/lessons/06-words-that-depend-on-context.html)

## Read the surrounding symbols

Rust gives some words a special job only in particular positions. The Rust Reference calls these weak keywords. In the practice below, `union` introduces a type, and `let union` names an ordinary local value. The quote in `'static` matters. It marks a built-in lifetime, while `static` on its own is a strict keyword used for items with static storage. [Rust Reference, weak keywords](https://doc.rust-lang.org/reference/keywords.html#weak-keywords)

## Print a label, compare an address, and read two bytes

~~~rust
macro_rules! twice {
    ($count:expr) => { 2 * $count };
}

#[repr(C)]
union WordBytes {
    word: u16,
    bytes: [u8; 2],
}

fn main() {
    let label: &'static str = "Review queue";
    println!("{label} count {}", twice!(3));

    let values = [3_u16, 5];
    let raw = &raw const values[0];
    println!("Same first address {}", raw == values.as_ptr());

    let union = WordBytes { word: 0x0102 };
    // SAFETY: word initialized both bytes. The C layout starts both
    // fields at the same offset, and every byte is valid in [u8; 2].
    let bytes = unsafe { union.bytes };
    println!("Native bytes match {}", bytes == 0x0102_u16.to_ne_bytes());
}
~~~

The macro accepts an expression and inserts it once into a multiplication. The raw borrow obtains the address of the first element. The program compares addresses without reading through the pointer. The union fields share storage, so reading the byte field examines the two bytes stored by the number. The comparison uses the machine's native byte order, making the result independent of whether the machine stores the high or low byte first. [Rust Reference, macros by example](https://doc.rust-lang.org/reference/macros-by-example.html) · [Rust Reference, raw borrow operators](https://doc.rust-lang.org/reference/expressions/operator-expr.html#raw-borrow-operators) · [Rust Reference, unions](https://doc.rust-lang.org/reference/items/unions.html)

## Match each word to its job

| Word | Example | What it tells Rust |
| --- | --- | --- |
| `'static` | `let label: &'static str = "Review queue";` | The string literal can be referred to for the lifetime of the program. The local binding still goes out of scope at the end of `main`. |
| `macro_rules` | `macro_rules! twice { ($count:expr) => { 2 * $count }; }` | Define a pattern to match an invocation and the Rust code to expand at that site. Here `$count:expr` matches one expression. |
| `raw` | `let raw = &raw const values[0];` | Produce a raw read-only pointer. The second `raw` is part of `&raw const`, while the first is an ordinary variable name. |
| `safe` | `safe fn practice_schema_version() -> u32;` | In an external block, promise that a Rust caller may call this function without meeting additional safety requirements. The author still checks the foreign definition. |
| `union` | `union WordBytes { word: u16, bytes: [u8; 2] }` | Give fields shared storage. Reading a union field needs an explicit safety check. |

An owned value such as a `String` may satisfy a generic `T: 'static` bound and still be dropped when its owner goes out of scope. A bound constrains the references that a type can contain. A reference declaration such as `&'static str` instead describes how long its referenced data is available. [Rust By Example, static lifetime](https://doc.rust-lang.org/rust-by-example/scope/lifetime/static_lifetime.html)

## Put `safe` where the caller has no extra requirement

Use the same C function and object file from the previous chapter. This substitute Rust caller records the reviewed contract on the external declaration itself.

~~~rust
unsafe extern "C" {
    // The linked function takes no inputs and returns a plain uint32_t.
    safe fn practice_schema_version() -> u32;
}

fn main() {
    println!("Schema version {}", practice_schema_version());
}
~~~

The declaration is in an `unsafe extern` block because the author must ensure that the ABI and implementation match. The `safe` marker changes how Rust callers may use this particular function. Review that promise before applying it to any different foreign function. [Rust Reference, external functions](https://doc.rust-lang.org/reference/items/external-blocks.html#functions)

## Try and compare the results

1. Save the first program as `context-words.rs`. Run `rustc --edition=2024 context-words.rs -o context-words.exe` in PowerShell. Run `.\context-words.exe` after it compiles. Expect `Review queue count 6`, `Same first address true`, and `Native bytes match true` on separate lines.
2. Change `twice!(3)` to `twice!(4 + 1)`. The count should become 10. The macro takes the whole expression and multiplies its result by two.
3. Save the second Rust program as `version-safe.rs` beside `schema-version.o`. Use the same compatible GNU toolchain from the previous chapter. Run `rustc --edition=2024 version-safe.rs -C link-arg=schema-version.o -o version-safe.exe`. Then run `.\version-safe.exe` and expect `Schema version 7`.
4. Remove `safe` and compile the second example again. The unmarked call should now be refused because an external declaration defaults to unsafe. Restore `safe` after checking that you are linking the same C implementation.

C's `&values[0]` also produces an address, and a C union also gives its members shared storage. When Umicom C and Rust components exchange file or message bytes, agree on a fixed wire byte order and encode it explicitly. Rust's `to_le_bytes()`, for example, produces little-endian bytes regardless of the machine's byte order. The union example here only inspects native memory.
