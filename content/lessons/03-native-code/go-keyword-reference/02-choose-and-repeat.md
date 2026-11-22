<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/go-keyword-reference/02-choose-and-repeat.md

PURPOSE:
Carry a loop through a short list, then choose one way to respond to its total.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Choose and repeat with Go

[Course contents](index.md) · [Previous lesson: Write a first Go program](01-write-a-first-go-program.md) · [Next lesson: Describe data and behaviour](03-describe-data-and-behaviour.md)

Carry a loop through a short list, then choose one way to respond to its total.

## Follow one position at a time

The three-part `for` in Go covers the same basic pattern as the C loop. `range` makes it easier to walk a slice, which is a sequence of values in this example. `_, cents` uses the blank identifier to ignore the position. Unlike a C switch, an ordinary Go switch does not fall through by default.

## Keep the filter readable

The next program uses a toy rule to ignore negative values. That rule is only for demonstrating control flow. A real statement would often retain a negative transaction and use a separate posted flag.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `if` | `if total > 0 { report() }` | Run the block when the condition is true. Go requires braces for this body. |
| `else` | `if total > 0 { report() } else { reset() }` | Take the other branch when the condition is false. Write else on the same line as the closing brace of the first block. |
| `for` | `for i := 0; i < 3; i++ { total += i }` | Use setup, a condition and an update. Go does not surround them with parentheses. |
| `range` | `for i, cents := range amounts { use(i, cents) }` | Walk a slice and receive the index and value. The meaning of the variables depends on the thing ranged over. |
| `break` | `if total > 100 { break }` | Leave the closest surrounding for, switch or select, unless a label selects another permitted target. |
| `continue` | `if cents < 0 { continue }` | Skip to the next iteration of the surrounding loop. |
| `switch` | `switch code { case 1: report(); default: reset() }` | Choose a matching clause. The chosen clause normally ends without executing the next one. |
| `case` | `case 1: report()` | Mark one matching clause of a switch, or a communication clause of a select. |
| `default` | `default: reset()` | Use a fallback in a switch. A default in select instead lets the statement proceed when no communication can proceed. |
| `fallthrough` | `case 1: report(); fallthrough` | In an expression switch, explicitly enter the next clause. This belongs at the end of a non-final clause. |
| `goto` | `if bad { goto done }; report(); done: return` | Jump to a permitted label in the same function. Use normal branches for straightforward decisions. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
START total at 0
FOR each amount
    IF amount is negative, skip this turn
    ADD amount to total
IF the total equals the practice result, label it as practice
OTHERWISE label it as unexpected
```

## Run the complete example

Save the whole program as `practice.go`. Open a terminal in that folder, then enter the command shown for your language.

```go
package main

import "fmt"

func main() {
    amounts := []int{425, -25, 100}
    total := 0
    for _, cents := range amounts {
        if cents < 0 {
            continue
        }
        total += cents
    }
    switch total {
    case 525:
        fmt.Println("practice total", total)
    default:
        fmt.Println("unexpected", total)
    }
}
```

```text
go run practice.go
```

Expected line

```text
practice total 525
```

If the terminal cannot find go, complete the setup for your operating system before running the command. If Go reports a missing package or main function, check that the whole program was copied and saved as practice.go. The paper trace still works without a toolchain.

## Try a change

Delete the check that skips negative values and predict which switch clause runs.

**Check your answer**

The new total is 500. Expect `unexpected 500` from the default clause.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Go Statement Tools](../../../courses/go-statement-tools/index.html)
- [The Go language specification, Keywords](https://go.dev/ref/spec#Keywords)
