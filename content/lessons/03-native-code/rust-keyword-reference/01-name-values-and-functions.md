<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/rust-keyword-reference/01-name-values-and-functions.md

PURPOSE:
  Teach the selected strict words in the Rust 2024 edition.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Name values and functions

[Course contents](index.md) · [Next lesson](02-make-a-decision-and-repeat.md) · [HTML edition](../../../courses/rust-keyword-reference/lessons/01-name-values-and-functions.html)

## Read an example before memorising the words

You are adding up the items on a practice shelf. Start with five, add twelve, then add seven more. The program prints 24. Each name has a type so the compiler can tell what can be stored in it.

~~~rust
const BASE: u32 = 12;
static EXTRA: u32 = 7;

fn shelf_total(seed: u8) -> u32 {
    let mut total = seed as u32;
    total += BASE;
    let _ = "Practice shelf";
    return total + EXTRA;
}

fn main() {
    println!("{}", shelf_total(5));
}
~~~

## Match each word to its job

| Word | Example | What it tells Rust |
| --- | --- | --- |
| `_` | `let _ = "Practice shelf";` | The value has no name in this pattern. The expression on the right is still evaluated. |
| `as` | `seed as u32` | Convert the value to the named type. Here the range of `u32` can hold every `u8` value. |
| `const` | `const BASE: u32 = 12;` | Give a name to a value the compiler can determine without running this function. |
| `fn` | `fn shelf_total(seed: u8) -> u32` | Define a function, its input, and its result type. |
| `let` | `let count = 5;` | Bind a name to a value in the current scope. |
| `mut` | `let mut total = seed as u32;` | Permit the binding to receive a new value, such as after `total += BASE`. |
| `return` | `return total + EXTRA;` | End this function and give its result to the caller. |
| `static` | `static EXTRA: u32 = 7;` | Give one named object storage for the program's lifetime. This object is immutable. |

The name `main` selects the starting function in this program. `u8` and `u32` name unsigned integer types with 8 and 32 bits. The Rust keyword list separately classifies these eight spellings as strict. [Rust Reference, strict keywords](https://doc.rust-lang.org/reference/keywords.html#strict-keywords)

## Try the program

1. Save it as `shelf.rs` in a practice folder. Use `rustc --version` to check that your compiler is available and supports the 2024 edition.
2. In PowerShell run `rustc --edition=2024 shelf.rs -o shelf.exe`. If the compiler reports a problem, read the file and line before starting the program.
3. Run `.\shelf.exe`. Expect `24`. Remove `mut` and compile again. The assignment should now be refused. Put `mut` back to recover.

## Do the same calculation in C

This small Umicom C comparison uses the same numbers in its signed integer profile. The return value is shown by the interpreter. The two languages use different rules for a binding that may change.

~~~c
constexpr int BASE = 12;
constexpr int EXTRA = 7;

int main(void) {
    int total = 5;
    total += BASE;
    return total + EXTRA;
}
~~~

Save as `shelf.c` and run `umicom-c interpret shelf.c`. Expect `Result: 24`. In C, the local is writable with this declaration. Adding `const` makes the assignment invalid in this profile. Try the C practice first if you have Umicom C available already.
