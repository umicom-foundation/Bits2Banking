<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/rust-keyword-reference/04-link-types-and-ownership.md

PURPOSE:
  Teach the selected strict words in the Rust 2024 edition.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Connect types and ownership

[Course contents](index.md) · [Previous lesson](03-define-data-and-share-modules.md) · [Next lesson](05-external-and-asynchronous-boundaries.md) · [HTML edition](../../../courses/rust-keyword-reference/lessons/04-link-types-and-ownership.html)

## Give different types a shared way to answer

A practice ticket stores a name and a quantity. Borrow its name long enough to print it. Then put the ticket into a small function value called a closure. The closure asks for the same quantity twice, first through a generic function and then through a trait object.

~~~rust
trait Quantity {
    fn units(&self) -> u32;
}

struct Ticket {
    label: String,
    units: u32,
}

impl Ticket {
    fn new(label: String, units: u32) -> Self {
        Self { label, units }
    }
}

impl Quantity for Ticket {
    fn units(&self) -> u32 {
        self.units
    }
}

fn quantity_of<T>(value: &T) -> u32
where
    T: Quantity,
{
    value.units()
}

fn main() {
    let ticket = Ticket::new(String::from("Day pass"), 3);
    let Ticket { ref label, .. } = ticket;
    println!("Label: {label}");

    // The closure keeps the ticket it will read when called.
    let report = move || {
        let source: &dyn Quantity = &ticket;
        println!("Generic quantity: {}", quantity_of(&ticket));
        println!("Dynamic quantity: {}", source.units());
    };
    report();
}
~~~

## Match each word to its job

| Word | Example | What it tells Rust |
| --- | --- | --- |
| `dyn` | `let source: &dyn Quantity = &ticket;` | Borrow a trait object. The method used for `source.units()` is selected at runtime from the stored implementation for the underlying type. |
| `impl` | `impl Quantity for Ticket { /* methods */ }` | Supply the methods required by `Quantity` for `Ticket`. The separate `impl Ticket` associates `new` directly with the type. |
| `move` | `let report = move \|\| { /* body */ };` | Capture the values used by the closure by value. In this example the closure takes ownership of the ticket. A `move` closure can be called later. |
| `ref` | `let Ticket { ref label, .. } = ticket;` | Bind `label` by shared reference while leaving the original field in the ticket. The `..` pattern skips the other field. |
| `Self` | `fn new(label: String, units: u32) -> Self` | Refer to the implementing type. Here `Self` is a name for `Ticket`. Lowercase `self` in `units` refers to the current ticket value. |
| `trait` | `trait Quantity { fn units(&self) -> u32; }` | Name a contract that several types can implement. Each implementation supplies how a value reports its units. |
| `where` | `where T: Quantity` | Add a condition on a generic type. The generic function accepts a reference to a type that implements `Quantity`. |

`&self` is the method's shared reference to the value receiving the call. `ref` affects a binding inside a pattern. In the example, the pattern reads an owned `Ticket` and makes a shared reference to its label. Rust 2024 requires an explicit pattern when writing `ref`. If you change the expression being matched to `&ticket`, write `let Ticket { label, .. } = &ticket;` so Rust infers the borrowed binding. [Rust Reference, strict keywords](https://doc.rust-lang.org/reference/keywords.html#strict-keywords) · [Rust 2024 Edition Guide, matching references](https://doc.rust-lang.org/edition-guide/rust-2024/match-ergonomics.html)

The generic version uses a type parameter. The trait-object version uses a reference to a value through the `Quantity` interface. In the example both use `Ticket`'s method and produce the same result. [Rust Reference, generic parameters](https://doc.rust-lang.org/reference/items/generics.html) · [Rust Reference, trait objects](https://doc.rust-lang.org/reference/types/trait-object.html) · [Rust Reference, closure expressions](https://doc.rust-lang.org/reference/expressions/closure-expr.html)

## Predict a change and run it

1. Save the program as `ticket.rs`. In PowerShell run `rustc --edition=2024 ticket.rs -o ticket.exe`. Continue only after compilation succeeds.
2. Run `.\ticket.exe`. Expect these three lines.

   ~~~text
   Label: Day pass
   Generic quantity: 3
   Dynamic quantity: 3
   ~~~

3. Change the last argument to `Ticket::new` from `3` to `5`. Compile and run again. Both quantities should now be `5`.
4. To see ownership checking, add `println!("{}", ticket.label);` between the closure definition and `report();` and compile. The compiler should report that the ticket has moved into the closure. Remove that added line and compile again to recover.

## Compare with C and Umicom Framework

In C, a small interface can pair a function pointer with a context pointer. The caller passes the context and the receiver documents who keeps it alive. Umicom Framework uses this pattern in C callbacks. Rust's trait object connects the value to its implementation, and Rust checks borrowing and ownership at compile time. Trace those responsibilities when you translate a callback between the languages.
