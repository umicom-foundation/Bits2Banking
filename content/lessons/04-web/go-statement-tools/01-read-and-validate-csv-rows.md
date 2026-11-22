<!--
Umicom Bits2Banking
File: content/lessons/04-web/go-statement-tools/01-read-and-validate-csv-rows.md

PURPOSE:
Teach Read and validate CSV rows through original worked exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Read and validate CSV rows

[Course contents](index.md) · [Next: Print deterministic posted totals](02-print-deterministic-posted-totals.md)

## What you will learn

Parse a fixed CSV statement, convert amounts to whole cents and report the first invalid record.

## Use a reader for the training input

CSV is a delimited text format. A CSV reader handles fields and returns one record at a time. This activity uses an in-memory example and the standard library. A Go struct keeps the parsed fields together. A nil error means the function succeeded.

## Parse the full fixture

Save the program as statement.go. Check your Go command with go version, then run go run statement.go in the practice directory.

```go
package main

import (
	"encoding/csv"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

type movement struct {
	account string
	cents   int64
	state   string
}

const statement = `reference,account,cents,state
101,reserve,2600,posted
102,reserve,-850,posted
103,reserve,500,pending
104,operating,1200,posted
105,operating,-300,posted
106,operating,-150,pending
`

func parseStatement(input io.Reader) ([]movement, error) {
	rows := csv.NewReader(input)
	rows.FieldsPerRecord = 4
	header, err := rows.Read()
	if err != nil || strings.Join(header, ",") != "reference,account,cents,state" {
		return nil, fmt.Errorf("unexpected statement header")
	}

	var result []movement
	previousReference := int64(0)
	for record := 2; ; record++ {
		fields, err := rows.Read()
		if err == io.EOF {
			return result, nil
		}
		if err != nil {
			return nil, fmt.Errorf("record %d: %w", record, err)
		}
		reference, refErr := strconv.ParseInt(fields[0], 10, 64)
		cents, centsErr := strconv.ParseInt(fields[2], 10, 64)
		account, state := fields[1], fields[3]
		if refErr != nil || reference <= previousReference || centsErr != nil ||
			(account != "reserve" && account != "operating" && account != "clearing") ||
			(state != "posted" && state != "pending") {
			return nil, fmt.Errorf("invalid training values at record %d", record)
		}
		previousReference = reference
		result = append(result, movement{account, cents, state})
	}
}

func main() {
	movements, err := parseStatement(strings.NewReader(statement))
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
	fmt.Printf("accepted %d movements\n", len(movements))
}
```

Expect accepted 6 movements. The parser starts data at record 2 because the header is record 1. A successful read and a valid amount alone are not enough. The example also checks the reference order and a small list of known account and state values.

## Practice and check your answer

Replace -850 with unknown. Predict the error record, then run the program. Restore the original value afterwards.

**Worked answer**

The parser reports invalid training values at record 3. No accepted count prints, because the function returns nil and an error instead of exposing the partially accepted slice.

## If Go is unavailable

Run the paper trace from the header through the second data row. Mark each reference, account, amount and state check true or false. Keep the original fixture in a practice folder for a later run with the Go toolchain.

[Read this lesson as HTML](../../../courses/go-statement-tools/lessons/01-read-and-validate-csv-rows.html)

## Continue learning

- [SQL Statement Reconciliation](../../../courses/sql-statement-reconciliation/index.html)
- [Introduction to Programming](../../../courses/introduction-to-programming/index.html)

## Further reading

- [Tech Sustainify course catalogue](https://techsustainify.com/)
- [W3Schools Go tutorial](https://www.w3schools.com/go/index.php)
- [Go encoding/csv package](https://pkg.go.dev/encoding/csv)


[Course contents](index.md) · [Next: Print deterministic posted totals](02-print-deterministic-posted-totals.md)
