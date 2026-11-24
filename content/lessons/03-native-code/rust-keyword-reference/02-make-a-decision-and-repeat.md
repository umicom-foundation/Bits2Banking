<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/rust-keyword-reference/02-make-a-decision-and-repeat.md

PURPOSE:
  Teach the selected strict words in the Rust 2024 edition.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Make a decision and repeat

[Course contents](index.md) · [Previous lesson](01-name-values-and-functions.md) · [Next lesson](03-define-data-and-share-modules.md) · [HTML edition](../../../courses/rust-keyword-reference/lessons/02-make-a-decision-and-repeat.html)

## Count only the rows that belong

A practice list contains counts 2, 0, 3 and 9. Skip an empty row and stop at the first value greater than 5. The counted total is 5. Then advance a separate check value to 7 and turn that last number into a yes-or-no result.

~~~rust
fn main() {
    let mut total = 0;
    for count in [2, 0, 3, 9] {
        if count == 0 {
            continue;
        } else if count > 5 {
            break;
        }
        total += count;
    }

    let mut check = total;
    while check < 7 {
        check += 1;
    }
    let accepted = loop {
        break match check {
            7 => true,
            _ => false,
        };
    };
    println!("{total} {check} {accepted}");
}
~~~

| Word | Example | What it tells Rust |
| --- | --- | --- |
| `break` | `if count > 5 { break; }` | Leave the current loop. In a `loop` expression, a value after `break` can become its result. |
| `continue` | `if count == 0 { continue; }` | Skip the rest of this turn of the loop and move to the next one. |
| `else` | `if count == 0 { continue; } else { total += count; }` | Choose the second block when the first condition is false. |
| `false` | `let accepted = false;` | Store the Boolean value for a condition that is false. |
| `for` | `for count in [2, 3] { total += count; }` | Repeat once for each value the collection supplies. |
| `if` | `if total == 5 { println!("Five"); }` | Run the block when its condition is true. |
| `in` | `count in [2, 3]` | Connect the name assigned on each turn to the values supplied by the following expression. Use it as part of a `for` loop. |
| `loop` | `let result = loop { break 7; };` | Enter a loop with no fixed stopping test. Here `break 7` ends it and supplies its value. |
| `match` | `match check { 7 => true, _ => false }` | Choose the first pattern that fits. The wildcard arm handles every other number. |
| `true` | `let accepted = true;` | Store the Boolean value for a condition that is true. |
| `while` | `while check < 7 { check += 1; }` | Check the condition before each turn, including the first one. |

[Rust Reference, control-flow expressions](https://doc.rust-lang.org/reference/expressions.html) · [Rust Reference, strict keywords](https://doc.rust-lang.org/reference/keywords.html#strict-keywords)

## Predict a change and run it

1. Save as `practice-counts.rs`. In PowerShell run `rustc --edition=2024 practice-counts.rs -o practice-counts.exe`. Start `.\practice-counts.exe` only after compilation succeeds. Expect `5 7 true`.
2. Replace `9` with `4` and compile and run it again. The total is now 9. The `while` condition is initially false, so the result should be `9 9 false`.
3. If the `match` expression is rejected after you remove the wildcard arm, restore it. The compiler needs a route for every possible value of `check`.

## Compare the decision in Umicom C

The C exercise below starts with the total already counted. It uses the same decision with a numeric result, where 1 stands for true and 0 stands for false. It leaves the Rust list iteration to the Rust example.

~~~c
int main(void) {
    int check = 5;
    for (int i = 0; i < 2; ++i) {
        if (check < 7) { check += 1; }
    }
    int accepted = 0;
    if (check == 7) { accepted = 1; }
    return accepted;
}
~~~

Save as `practice-counts.c`. Run `umicom-c interpret practice-counts.c` and expect `Result: 1`. Change the initial `check` to 9 and expect `Result: 0`.
