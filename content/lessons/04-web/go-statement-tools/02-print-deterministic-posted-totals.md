<!--
Umicom Bits2Banking
File: content/lessons/04-web/go-statement-tools/02-print-deterministic-posted-totals.md

PURPOSE:
Teach Print deterministic posted totals through original worked exercises.

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

# Print deterministic posted totals

[Course contents](index.md) · [Previous: Read and validate CSV rows](01-read-and-validate-csv-rows.md)

## What you will learn

Group posted movements by account, retain zero entries and print account names in a stable order.

## Use keys for the account groups

Continue with statement.go from the previous lesson. A map stores one value per key. Start with all three training accounts present, including clearing. Skip pending rows before changing the map. The resulting order comes from sorting keys explicitly.

## Extend the existing program

Add math and sort to the existing import block. Insert postedTotals before main, then replace main with the version shown below.

```go
func postedTotals(movements []movement) (map[string]int64, error) {
	totals := map[string]int64{"clearing": 0, "operating": 0, "reserve": 0}
	for _, item := range movements {
		if item.state != "posted" {
			continue
		}
		prior := totals[item.account]
		// Check both signed boundaries before adding the next movement.
		if (item.cents > 0 && prior > math.MaxInt64-item.cents) ||
			(item.cents < 0 && prior < math.MinInt64-item.cents) {
			return nil, fmt.Errorf("posted total outside range for %s", item.account)
		}
		totals[item.account] = prior + item.cents
	}
	return totals, nil
}

func main() {
	movements, err := parseStatement(strings.NewReader(statement))
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
	totals, err := postedTotals(movements)
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}

	accounts := make([]string, 0, len(totals))
	for account := range totals {
		accounts = append(accounts, account)
	}
	sort.Strings(accounts)
	for _, account := range accounts {
		fmt.Printf("%s %d\n", account, totals[account])
	}
}
```

```text
go run statement.go
```

```text
clearing 0
operating 900
reserve 1750
```

## Practice and check your answer

Change entry 103 to posted. Which group changes, and what should its new value be? Compare it with the change in the Umicom C lesson.

**Worked answer**

Reserve becomes 2250 because it now includes the 500-cent entry. Clearing and operating stay at 0 and 900. The equivalent Umicom C exercise reaches the same result from the same inclusion rule.

## If your output differs

Check the state on all six rows and make sure sort.Strings runs before printing. If the compiler says math or sort is undefined, check both new imports. A size error means the example refused to report any partial totals.

[Native Statement Calculations](../../../courses/native-statement-calculations/index.html)

[Read this lesson as HTML](../../../courses/go-statement-tools/lessons/02-print-deterministic-posted-totals.html)

## Continue learning

- [SQL Statement Reconciliation](../../../courses/sql-statement-reconciliation/index.html)
- [Introduction to Programming](../../../courses/introduction-to-programming/index.html)

## Further reading

- [Tech Sustainify course catalogue](https://techsustainify.com/)
- [W3Schools Go tutorial](https://www.w3schools.com/go/index.php)
- [Go encoding/csv package](https://pkg.go.dev/encoding/csv)


[Course contents](index.md) · [Previous: Read and validate CSV rows](01-read-and-validate-csv-rows.md)
