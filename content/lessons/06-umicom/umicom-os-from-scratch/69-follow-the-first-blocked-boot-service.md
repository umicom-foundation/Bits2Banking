<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/69-follow-the-first-blocked-boot-service.md

PURPOSE:
Follow the first blocked boot service

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Follow the first blocked boot service

An Umicom OS boot plan lists the services the operating system would start. A
service is a program with one job. One service can name another as a
prerequisite, which means the prerequisite must finish successfully before
the service can start. In this lesson you will read a plan on paper and
follow its dependency lines.

## 1. Read a service declaration

A declaration has a service ID, executable path, prerequisite and timeout,
separated by vertical bars. The ID is the name other declarations use. A
single dash in the prerequisite field means the service has no prerequisite.
Read each arrow in this lesson as “requires”.

```text
service=report|/usr/libexec/umicom-report|ledger|1000
report → ledger
```

This line says that `report` requires `ledger`. The timeout is 1,000
milliseconds. The parser checks the prerequisite name separately.
The Umicom OS plan inspector shares the startup parser, so the same
dependency rule applies when you review the plan.

## 2. Follow the first blocked declaration

Read the sample below as plain text. The header is line 1 and the comment
counts as line 3.

```text
UMICOM_OS_BOOT 1
hostname=classroom
# Services for a sample accounting report
service=report|/usr/libexec/umicom-report|ledger|1000
service=ledger|/usr/libexec/umicom-ledger|rates|1000
service=rates|/usr/libexec/umicom-rates|ledger|1000
service=clock|/usr/libexec/umicom-clock|-|1000
```

1. Find the service with a dash. The parser can place `clock` in the draft
   order because it has no prerequisite.
2. Check the remaining services. `ledger` needs `rates`, and `rates` needs
   `ledger`. Neither can go first. This repeated chain is a dependency cycle.
3. Note the first declaration that remains blocked. The diagnostic points
   to line 4, where `report` waits for `ledger`. The cycle itself is the
   pair on lines 5 and 6. Follow the names from line 4 until one repeats.

This plan is refused as a whole. The inspector cannot publish an accepted
order for the plan, even though it could choose one independent service while
checking the dependencies.

## 3. Practise reading the indicated line

For each situation, decide which declaration needs attention before reading
the answer column.

| Situation | Where the diagnostic points |
| --- | --- |
| A declaration on line 3 names a prerequisite that never appears. | Line 3, which contains the reference to check. |
| A second declaration uses the same ID on line 6, following a comment and blank line. | Line 6, where the repeated ID was found. |
| A service uses its own ID as its prerequisite on line 3. | Line 3, which contains the self-reference. |
| The sample above leaves `report` waiting on a cycle. | Line 4, the first blocked declaration. |

Now suppose the requirements say that `rates` can start independently.
Change its prerequisite to a dash on paper. The shared parser selects the
first ready declaration each time, in source order. Work out the order.

The answer is `rates`, `ledger`, `report`, then `clock`. Once `rates`
is selected, `ledger` becomes ready. Once `ledger` is selected, `report`
becomes ready. Each appears before `clock` in the source.

## 4. Keep the reason and the location together

Record both the diagnostic and the original line when reviewing a refused
plan. Count physical lines, including comments and blank lines. Check the
prerequisite names against the intended service design before changing an
edge in the plan. When reviewing a real configuration, compare it with the
Umicom OS guide at `docs/foundation/boot-plan-inspection.md`.

In `boot/foundation/config.c`, the C parser records the source line for
each admitted service declaration while building a temporary plan.
`UmiOsBootConfigParseDetailed` retains the graph error category on refusal
and returns the corresponding line. The caller's previously accepted
configuration remains intact. The lesson illustrates the expected
diagnostics from the source. Actual service execution and boot qualification
require separate evidence.

## 5. Identify an empty declaration

Read the plan below on paper. Count the header, comments and blank line before choosing the first line to correct.

```text
UMICOM_OS_BOOT 1
# A practice plan for the reporting service

hostname=
# Add the reporting service below
service=
```

1. The first diagnostic identifies the empty hostname on line 4. Supply `hostname=classroom` on paper and read the plan again.
2. The next diagnostic identifies the empty service on line 6. Try replacing it with `service=report|/usr/libexec/umicom-report|-|1000` on paper.
3. Now imagine replacing line 6 with `owner=classroom`. The parser treats `owner` as an unknown field. Compare this with the earlier known field named `service` that was missing its value.

Each rejected plan leaves the previous accepted configuration intact. Record the field and the physical line number together when you review a saved plan.

[Course contents](index.md) · [Previous lesson · Count the slots both GPT tables need](68-count-the-slots-both-gpt-tables-need.md) · [Plan startup before executing it](03-service-dependencies.md) · [Keep rejected state separate from recovery](04-failure-and-recovery.md) · [HTML edition](../../../courses/umicom-os-from-scratch/lessons/69-follow-the-first-blocked-boot-service.html)

[Next lesson · Keep the first boot failure when a report cannot be saved](70-keep-the-first-boot-failure.md)
