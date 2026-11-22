<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/go-keyword-reference/01-write-a-first-go-program.md

PURPOSE:
Find the package, the entry function and two ways to give a value a name.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Write a first Go program

[Course contents](index.md) · [Next lesson: Choose and repeat with Go](02-choose-and-repeat.md)

Find the package, the entry function and two ways to give a value a name.

## Find the entry point

A package groups Go source files. A command program declares package `main` and has a zero-argument `main` function. An import lets a file use names from another package. `fmt.Println` is a library function, and `fmt` is its package name.

## Read names and values aloud

A variable is a named place for a value that can change. A constant names a value that keeps its meaning. In Go, write the type after the name in a declaration. C normally writes it before the name. In `total := ...`, the colon-equals form introduces a local variable and infers its type. The `:=` characters are a symbol, not a keyword.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `package` | `package main` | Name the package. A complete executable example uses package main. |
| `import` | `import "fmt"` | Make the fmt standard library package available to this file. |
| `func` | `func cents() int { return 425 }` | Define a callable function with an int result. |
| `return` | `return 425` | Give the result to the caller and leave the function. |
| `var` | `var opening int = 425` | Introduce a variable that may change. An explicit type here makes the example easy to read. |
| `const` | `const adjustment = -25` | Give a constant a name. The literal is an untyped constant in this declaration. |
| `type` | `type WholeCents int` | Define a new type whose underlying type is int. This differs from a C typedef alias. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
START with 425 cents
ADD the adjustment to the opening amount
SHOW the result
```

## Run the complete example

Save the whole program as `practice.go`. Open a terminal in that folder, then enter the command shown for your language.

```go
package main

import "fmt"

type WholeCents int

func posted() WholeCents {
    return 425
}

func main() {
    const adjustment = -25
    var opening WholeCents = posted()
    fmt.Println(opening + adjustment)
}
```

```text
go run practice.go
```

Expected line

```text
400
```

If the terminal cannot find go, complete the setup for your operating system before running the command. If Go reports a missing package or main function, check that the whole program was copied and saved as practice.go. The paper trace still works without a toolchain.

## Try a change

Change adjustment to 75 and predict the output. Try the paper version even if you have not installed Go.

**Check your answer**

Go adds 425 and 75. Expect `500`.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Go Statement Tools](../../../courses/go-statement-tools/index.html)
- [The Go language specification, Keywords](https://go.dev/ref/spec#Keywords)
