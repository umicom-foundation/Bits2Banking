<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/rust-keyword-reference/07-words-reserved-for-later.md

PURPOSE:
  Teach the selected reserved words in the Rust 2024 edition.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Recognise reserved words

[Course contents](index.md) · [Previous lesson](06-words-that-depend-on-context.md) · [HTML edition](../../../courses/rust-keyword-reference/lessons/07-words-reserved-for-later.html)

## Why the compiler rejects some names

Rust keeps certain words available for possible changes to the language. In the 2024 edition they cannot appear as plain variable names, even if you have never seen one used in a program. The compiler can tell you this before any statements run.

Use a descriptive name when writing new code. If you must keep an existing identifier for compatibility, a raw identifier starts with `r#`. The prefix changes how Rust reads the spelling. It is part of the source notation and is excluded from the identifier name. [Rust Reference, reserved keywords](https://doc.rust-lang.org/reference/keywords.html#reserved-keywords) · [Rust Reference, raw identifiers](https://doc.rust-lang.org/reference/identifiers.html#raw-identifiers)

## Find a plain name or keep the existing spelling

Each left-hand fragment is expected to be refused in the body of a Rust 2024 function. The middle column offers a clearer name for new code. The last column preserves an existing name.

| Reserved word example | New name example | Compatibility example |
| --- | --- | --- |
| `let abstract = 1;` | `let summary = 1;` | `let r#abstract = 1;` |
| `let become = 1;` | `let next_state = 1;` | `let r#become = 1;` |
| `let box = 1;` | `let package_label = 1;` | `let r#box = 1;` |
| `let do = 1;` | `let action = 1;` | `let r#do = 1;` |
| `let final = 1;` | `let last_total = 1;` | `let r#final = 1;` |
| `let gen = 1;` | `let generation = 1;` | `let r#gen = 1;` |
| `let macro = 1;` | `let template_name = 1;` | `let r#macro = 1;` |
| `let override = 1;` | `let replacement = 1;` | `let r#override = 1;` |
| `let priv = 1;` | `let private_note = 1;` | `let r#priv = 1;` |
| `let try = 1;` | `let attempt = 1;` | `let r#try = 1;` |
| `let typeof = 1;` | `let type_label = 1;` | `let r#typeof = 1;` |
| `let unsized = 1;` | `let variable_width = 1;` | `let r#unsized = 1;` |
| `let virtual = 1;` | `let model_name = 1;` | `let r#virtual = 1;` |
| `let yield = 1;` | `let harvest = 1;` | `let r#yield = 1;` |

## Check a name when you update an edition

The 2024 edition added `gen` to the reserved list. The following definition and its use both retain the old identifier. [Rust 2024 Edition Guide](https://doc.rust-lang.org/edition-guide/rust-2024/gen-keyword.html)

~~~rust
fn main() {
    let r#gen = 4;
    println!("{}", r#gen + 8);
}
~~~

1. Save as `names.rs`. Run `rustc --edition=2024 names.rs -o names.exe`. Once compilation succeeds, run `.\names.exe` and expect `12`.
2. Remove both `r#` prefixes and repeat the compile. Read the diagnostic about the identifier. Restore both prefixes or rename both occurrences to `generation` to recover.
3. If you already have a project using the prior edition, review all renamed declarations and calls together so the same name is used at both ends.

## Compare with a C entry

The spelling `gen` is usable as a local name in this Umicom C example. A translator needs the target language's keyword rules before it chooses how to write a name.

~~~c
int main(void) {
    int gen = 4;
    return gen + 8;
}
~~~

Save as `names.c` and run `umicom-c interpret names.c`. Expect `Result: 12`.
