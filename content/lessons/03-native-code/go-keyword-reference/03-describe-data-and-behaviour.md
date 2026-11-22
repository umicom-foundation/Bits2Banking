<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/go-keyword-reference/03-describe-data-and-behaviour.md

PURPOSE:
Group named fields, find values by a key and describe what an object can do.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Describe data and behaviour

[Course contents](index.md) · [Previous lesson: Choose and repeat with Go](02-choose-and-repeat.md) · [Next lesson: Pass a result between workers](04-pass-a-result-between-workers.md)

Group named fields, find values by a key and describe what an object can do.

## Group fields and give them names

The letters in `Entry` and `Cents` are names chosen for this example. `struct` is the reserved word. Fields may be read using a dot. A map uses a key such as `posted` to look up a value. Request both lookup results when you need to distinguish a missing item from an item whose value is zero.

## Ask for behaviour

An interface describes what a value can do. `Namer` describes a value that can return a string when asked for its name. `Reconciliation` provides the method. The next program passes a value of that type to a function that expects a `Namer`.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `struct` | `type Entry struct { Cents int }` | Group fields that belong together. |
| `map` | `counts := map[string]int{"posted": 2}` | Build a collection that uses a string key to find an integer value. |
| `interface` | `type Namer interface { Name() string }` | Describe required methods. A type can satisfy it by providing the method set. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
ASK the item for its name
LOOK UP the name in the count table
SHOW the name, the result and whether it was found
```

## Run the complete example

Save the whole program as `practice.go`. Open a terminal in that folder, then enter the command shown for your language.

```go
package main

import "fmt"

type Namer interface {
    Name() string
}

type Reconciliation struct {
    label string
}

func (item Reconciliation) Name() string {
    return item.label
}

func printCount(item Namer, counts map[string]int) {
    label := item.Name()
    count, found := counts[label]
    fmt.Println(label, count, found)
}

func main() {
    counts := map[string]int{"posted": 2}
    printCount(Reconciliation{label: "posted"}, counts)
}
```

```text
go run practice.go
```

Expected line

```text
posted 2 true
```

If the terminal cannot find go, complete the setup for your operating system before running the command. If Go reports a missing package or main function, check that the whole program was copied and saved as practice.go. The paper trace still works without a toolchain.

## Try a change

Change the label supplied to printCount to "pending". Why is the final flag useful even when the count is 0?

**Check your answer**

Expect `pending 0 false`. The false flag distinguishes absence from an explicitly stored count of zero.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Go Statement Tools](../../../courses/go-statement-tools/index.html)
- [The Go language specification, Keywords](https://go.dev/ref/spec#Keywords)
