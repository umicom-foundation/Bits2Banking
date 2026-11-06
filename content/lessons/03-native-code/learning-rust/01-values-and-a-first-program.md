# Values and a first program

[Course contents](index.md) · [Next: Borrow a title](02-borrow-a-title.md)

## Begin with a small calculation

A compiler translates source and checks language rules. Rust uses explicit types and checks many ownership rules before a program runs. This does not mean every Rust program is correct: business rules and external interfaces still need tests.

Install the Rust toolchain using the official Rust Book's first-steps instructions for your operating system. Open a new terminal and run `rustc --version`. If the command is missing, resolve the installation or terminal path before continuing. Save this complete program as `progress.rs` in a practice folder:

```rust
fn main() {
    let completed: u32 = 3;
    let target: u32 = 5;
    let remaining = target - completed;
    println!("Remaining exercises: {}", remaining);
}
```

`fn` introduces a function. `main` is the starting function. `let` introduces a binding. `u32` is an unsigned 32-bit integer type. The compiler infers the type of remaining from its expression. `println!` is a macro invocation that prints a formatted line; `{}` marks where the value is placed.

Compile with `rustc progress.rs`. On PowerShell run `./progress.exe`; on Linux run `./progress`. Expect `Remaining exercises: 2`. Stop if compilation fails, because an older executable is not evidence that the new source worked.

## Exercise

Change completed to 5 and predict the printed line before compiling again. Then consider completed=6 on paper. Can an unsigned value represent the intended remaining count?

## Explained answer

With completed=5, expect `Remaining exercises: 0`. With completed=6, the mathematical result would be minus one, which `u32` cannot represent. This is called underflow. A domain check must establish completed <= target before calculating the difference. A later lesson will express that possible failure with `Result`; fitting each input into a type alone does not make every calculation valid.

## Compare with Umicom

Read the maximum-count promise in the activity header. Rust syntax can express a similar exercise, but duplicating a production rule in every language client would create inconsistent sources of truth. The Framework remains the shared engine. This course teaches Rust and future integration concepts; it does not claim a Rust binding to every Umicom module exists.

[Review the prerequisite course](../../../courses/learning-c/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/Bits2Banking/blob/bb0da4654632ab847ce7e729ced64f14cf230933/labs/native/framework-activity/activity.h). Path: `labs/native/framework-activity/activity.h`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://doc.rust-lang.org/book/). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-rust/lessons/01-values-and-a-first-program.html).

[Course contents](index.md) · [Next: Borrow a title](02-borrow-a-title.md)

Sammy Hegab · Umicom Foundation · Original learning material.
