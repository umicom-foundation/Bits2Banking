<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/rust-keyword-reference/03-define-data-and-share-modules.md

PURPOSE:
  Teach the selected strict words in the Rust 2024 edition.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Define data and share modules

[Course contents](index.md) · [Previous lesson](02-make-a-decision-and-repeat.md) · [Next lesson](04-link-types-and-ownership.md) · [HTML edition](../../../courses/rust-keyword-reference/lessons/03-define-data-and-share-modules.html)

## Give related data and code a home

A practice event has five seats. A group has reserved three. The program records the reservation, checks the remaining capacity and prints the result. A module groups related names. A crate is the compilation unit that contains the module tree. The single source file in this example is enough to build one program crate.

~~~rust
fn seat_limit() -> u32 {
    5
}

mod seating {
    pub type SeatCount = u32;

    pub struct Group {
        pub reserved: SeatCount,
    }

    pub enum Booking {
        SpaceLeft(SeatCount),
        Full,
    }

    pub mod counter {
        use crate::seat_limit;
        use super::{Booking, Group, SeatCount};

        fn remaining(group: &Group) -> SeatCount {
            let limit = seat_limit();
            if group.reserved >= limit {
                0
            } else {
                limit - group.reserved
            }
        }

        pub fn check(group: &Group) -> Booking {
            match self::remaining(group) {
                0 => Booking::Full,
                count => Booking::SpaceLeft(count),
            }
        }
    }
}

use crate::seating::{Booking, Group, counter};

fn main() {
    let group = Group { reserved: 3 };
    match counter::check(&group) {
        Booking::SpaceLeft(count) => println!("{count} seats left"),
        Booking::Full => println!("Full"),
    }
}
~~~

## Match each word to its job

| Word | Example | What it tells Rust |
| --- | --- | --- |
| `crate` | `use crate::seat_limit;` | Start a path at the root of this crate. Here it locates the function above the modules. |
| `enum` | `pub enum Booking { SpaceLeft(SeatCount), Full }` | Define one type with several named possibilities. `Full` stands alone and `SpaceLeft` carries a count. |
| `mod` | `mod seating { /* items */ }` | Put the items inside a module named `seating`. |
| `pub` | `pub fn check(group: &Group) -> Booking` | Make this function available to callers that can reach the enclosing module. Use `pub(crate)` to limit visibility to the current crate. |
| `self` | `self::remaining(group)` | Start the path in the current module. Here `self` refers to `counter`. In a method, the same spelling can refer to the value receiving the call. |
| `struct` | `pub struct Group { pub reserved: SeatCount }` | Define a type with a named field. This field stores the number of reserved seats. |
| `super` | `use super::{Booking, Group, SeatCount};` | Start a path one module up. From `counter` that means `seating`. |
| `type` | `pub type SeatCount = u32;` | Give the existing type `u32` another name for this purpose. |
| `use` | `use crate::seating::{Booking, Group, counter};` | Bring these names into the current scope so they can be written without the full path. |

The `::` separator connects the pieces of a path. The braces in a `use` line let several names share the same starting path. Passing `&group` gives `check` a shared reference to the group. The ownership chapter explains the reference in more detail. [Rust Reference, strict keywords](https://doc.rust-lang.org/reference/keywords.html#strict-keywords) · [Rust Reference, paths](https://doc.rust-lang.org/reference/paths.html) · [Rust Reference, modules](https://doc.rust-lang.org/reference/items/modules.html)

## Predict a change and run it

1. Save the program as `seating.rs` in a practice folder. Check `rustc --version` in PowerShell and use a compiler that supports Rust 2024.
2. Compile with `rustc --edition=2024 seating.rs -o seating.exe`. After compilation succeeds, run `.\seating.exe` and expect `2 seats left`.
3. Set `reserved` to `5`, compile and run again. Expect `Full`. If a path fails to resolve, start at its first piece and trace it from the crate root, current module or parent module.

## Compare with C and Umicom Framework

C groups data in a `struct` and uses `typedef` to give a type another name. Umicom Framework exposes named status values with the C enum `UmiStatus` in `umicom/base/status.h`. The seat example's Rust enum also keeps a count inside its `SpaceLeft` case. To represent that shape in C, a record can hold a status field and a count field, with a documented rule for when callers should read the count.
