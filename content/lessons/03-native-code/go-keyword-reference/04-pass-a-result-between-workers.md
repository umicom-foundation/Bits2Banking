<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/go-keyword-reference/04-pass-a-result-between-workers.md

PURPOSE:
Send one value through a channel, know when cleanup runs and avoid depending on timing.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Pass a result between workers

[Course contents](index.md) · [Previous lesson: Describe data and behaviour](03-describe-data-and-behaviour.md) · [Continue to Go Statement Tools](../../../courses/go-statement-tools/index.html)

Send one value through a channel, know when cleanup runs and avoid depending on timing.

## Sketch the hand-off

A goroutine is a separate flow of execution inside a Go program. Think of the channel as a hand-off point. The worker brings one result, and the main function receives it. A one-case select waits for that hand-off. Neither side needs a guessed delay.

## Distinguish a keyword from a built-in name

`chan` is reserved, while `make`, `close`, `nil`, `true` and type names such as `int` are predeclared identifiers. The token `<-` marks a send or receive direction depending on location. `defer` registers cleanup for the surrounding function rather than creating a worker.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `go` | `go send(out)` | Start a function call in a goroutine. The caller can continue independently. |
| `chan` | `out := make(chan int)` | Create a channel that carries int messages. The word make is a predeclared built-in. |
| `select` | `select { case cents := <-out: fmt.Println(cents) }` | Wait for a channel operation from the supplied cases. If several can proceed, do not rely on which one is chosen. |
| `defer` | `defer close(out)` | Schedule cleanup for when the surrounding function returns. close is a built-in. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
MAKE a channel for an integer result
START the worker
WORKER: send one result, then close the channel
MAIN: wait for the result and show it
```

## Run the complete example

Save the whole program as `practice.go`. Open a terminal in that folder, then enter the command shown for your language.

```go
package main

import "fmt"

func send(out chan<- int) {
    defer close(out)
    out <- 425
}

func main() {
    out := make(chan int)
    go send(out)
    select {
    case received := <-out:
        fmt.Println("received", received)
    }
}
```

```text
go run practice.go
```

Expected line

```text
received 425
```

If the terminal cannot find go, complete the setup for your operating system before running the command. If Go reports a missing package or main function, check that the whole program was copied and saved as practice.go. The paper trace still works without a toolchain.

## Try a change

Name the exact line where the worker hands over the number. What stays the same if either side happens to reach its channel operation first?

**Check your answer**

The send is `out <- 425`. The receiver and sender still meet on the channel and transfer 425.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Go Statement Tools](../../../courses/go-statement-tools/index.html)
- [The Go language specification, Keywords](https://go.dev/ref/spec#Keywords)
