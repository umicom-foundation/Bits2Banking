<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/rust-keyword-reference/05-external-and-asynchronous-boundaries.md

PURPOSE:
  Teach the selected strict words in the Rust 2024 edition.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read external and asynchronous boundaries

[Course contents](index.md) · [Previous lesson](04-link-types-and-ownership.md) · [Next lesson](06-words-that-depend-on-context.md) · [HTML edition](../../../courses/rust-keyword-reference/lessons/05-external-and-asynchronous-boundaries.html)

## Prepare a future

A future is a value that represents work that can make progress when asked. In this example, the main function prepares a future, prints one line, and drops the future. Read the code and predict which message appears.

~~~rust
async fn count_reviewed() -> u32 {
    println!("Counting the reviewed entries");
    7
}

fn main() {
    let pending = async {
        let total = count_reviewed().await;
        println!("Reviewed {total}");
    };

    println!("Future prepared");
    drop(pending);
}
~~~

The output is `Future prepared`. Creating the `async` block produces the future. Its body does not start because nothing polls the future to make it progress. If an executor drove this future, `.await` would let it wait for the result of `count_reviewed()`. A future that is already ready can supply its result without suspending. An async block does not start a background thread on its own. [Rust Reference, async blocks](https://doc.rust-lang.org/reference/expressions/block-expr.html#async-blocks) · [Rust Reference, await expressions](https://doc.rust-lang.org/reference/expressions/await-expr.html)

## Read a value across a language boundary

Imagine a practice file format with version number 7. The C function owns that number. Rust imports the function using the C application binary interface, or ABI. The ABI is the agreement on how the caller and the compiled function pass arguments and return a result.

Save this function as `schema-version.c`.

~~~c
#include <stdint.h>

/* Report the version of this practice format without accessing external state. */
uint32_t practice_schema_version(void) {
    return UINT32_C(7);
}
~~~

Save this Rust caller as `version-boundary.rs`.

~~~rust
unsafe extern "C" {
    fn practice_schema_version() -> u32;
}

fn schema_version() -> u32 {
    // SAFETY: the linked C function takes no arguments, returns uint32_t
    // and has no caller preconditions. The return type matches Rust u32.
    unsafe { practice_schema_version() }
}

fn main() {
    println!("Schema version {}", schema_version());
}
~~~

The outer `unsafe extern` block places responsibility for the declared signature on its author. Rust cannot check the C definition merely by reading this block. The imported function defaults to unsafe to call. The small wrapper contains the call and explains why it satisfies the contract for the linked C implementation. A regular call to `schema_version()` then has no extra work for the caller. [Rust Reference, external blocks](https://doc.rust-lang.org/reference/items/external-blocks.html) · [Rust 2024 Edition Guide, unsafe extern blocks](https://doc.rust-lang.org/edition-guide/rust-2024/unsafe-extern.html) · [Rust Reference, unsafe](https://doc.rust-lang.org/reference/unsafe-keyword.html)

## Match each word to its job

| Word | Example | What it tells Rust |
| --- | --- | --- |
| `async` | `async fn count_reviewed() -> u32` | Calling this function creates a future whose result, when ready, is a `u32`. |
| `await` | `count_reviewed().await` | Obtain the ready value or suspend the enclosing future until it can proceed. Use this inside an async context. |
| `extern` | `unsafe extern "C" { fn practice_schema_version() -> u32; }` | Declare a function supplied outside this Rust crate, using the C ABI. The linker must find its implementation. |
| `unsafe` | `unsafe { practice_schema_version() }` | Permit this call in a small block where the author has checked the requirements Rust cannot verify. In `unsafe extern` the word assigns responsibility for the external declarations. |

All four spellings are strict keywords in Rust 2024. [Rust Reference, strict keywords](https://doc.rust-lang.org/reference/keywords.html#strict-keywords)

## Try the two programs

1. Save the first program as `prepare-future.rs`. In PowerShell run `rustc --edition=2024 prepare-future.rs -o prepare-future.exe`. After compilation succeeds, run `.\prepare-future.exe` and expect the single line `Future prepared`.
2. For the C and Rust practice, check `rustc -vV` and `gcc -dumpmachine`. The commands below use a Windows GNU Rust toolchain and a C compiler for the same architecture and ABI. Work in the folder containing the two saved files.

~~~powershell
gcc -std=c23 -c schema-version.c -o schema-version.o
rustc --edition=2024 version-boundary.rs -C link-arg=schema-version.o -o version-boundary.exe
.\version-boundary.exe
~~~

3. Run each line only after the preceding one succeeds. Expect `Schema version 7`. If the linker cannot find `practice_schema_version`, rebuild the C object and check the file name and target compatibility. The `link-arg` option passes that object along to the linker. [The rustc book, link arguments](https://doc.rust-lang.org/rustc/codegen-options/index.html#link-arg)
4. Remove just the `unsafe { ... }` wrapper around the call and try compiling. The compiler should refuse the unmarked call. Restore the block and its safety comment. Keep both signatures fixed while experimenting with the returned version number.

## Compare with a C caller

A C caller can declare `uint32_t practice_schema_version(void);` in a header, include it, and call the function in the ordinary way. Both callers need declarations that match the linked definition. Rust adds the external ABI marker and makes the responsibility for an unchecked foreign call visible. A small version function makes that agreement easy to review. A real Umicom component can use the same lesson when it documents which numeric version fields callers may read across an interface.
