# Borrow a title

[Course contents](index.md) · [Previous: Values and a first program](01-values-and-a-first-program.md)

## Reading does not always require taking ownership

An owner is responsible for a value's lifetime. A borrow allows access while ownership remains elsewhere. Begin with this complete program in `title.rs`:

```rust
fn show_title(title: &str) {
    println!("Lesson: {}", title);
}

fn main() {
    let title = String::from("Learning Umicom Framework");
    show_title(&title);
    println!("Still available: {}", title);
}
```

Compile using `rustc title.rs` and run the resulting executable as in the first lesson. Expect two lines containing the title. `String` owns text storage. `&title` borrows it, and the function's `&str` parameter is a borrowed view of text. The function reads the text without acquiring responsibility for freeing its storage.

## Compare with a move

In a separate practice copy, change the parameter to `String` and the call to `show_title(title)`. Keep the final print. Now the call transfers the String into the function, and the later use should be rejected by the compiler. Read the diagnostic before changing anything else. Restore the borrowed version to make the intended read-only use clear.

```text
Borrow: main owns title -> function reads -> main can still use title
Move:   main transfers title -> function owns it -> old binding unavailable
```

## Exercise and answer

Call the borrowed version twice before the final print. Both calls can read the same title. This does not create two owners of the allocation. The compiler tracks the permitted references; there is no manual `free` call in this example.

## Connect to Framework ownership

Read `activity.h` again. Its output pointer refers to caller-owned storage. C requires the contract and implementation to establish valid access; a C pointer does not automatically carry Rust's checking guarantees. A future foreign-function interface must document nullability, lifetime, ownership and error representation on both sides. Merely changing a caller's language cannot repair an invalid pointer passed by a native library. Later lessons build on this distinction with mutable borrows and fallible operations.

[Review the prerequisite course](../../../courses/learning-c/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/Bits2Banking/blob/bb0da4654632ab847ce7e729ced64f14cf230933/labs/native/framework-activity/activity.h). Path: `labs/native/framework-activity/activity.h`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://doc.rust-lang.org/book/). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-rust/lessons/02-borrow-a-title.html).

[Course contents](index.md) · [Previous: Values and a first program](01-values-and-a-first-program.md)

Sammy Hegab · Umicom Foundation · Original learning material.

[Next lesson: Represent success and refusal](03-represent-success-and-refusal.md)
