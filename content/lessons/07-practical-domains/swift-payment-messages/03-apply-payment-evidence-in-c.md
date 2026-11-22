<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/swift-payment-messages/03-apply-payment-evidence-in-c.md

PURPOSE:
Write a native status gate that keeps repeats and mismatches from posting a second result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom Foundation" width="220">
</picture>

# Apply Payment Evidence in C23

[Course contents](index.md) · [Previous lesson · Normalize Message Evidence for Review](02-normalize-message-evidence.md)

Write a native status gate that keeps repeats and mismatches from posting a second result.

## Choose the narrow state machine

A state machine names each permitted condition and the events that can move a record to another condition. This exercise starts with an instruction awaiting status. A modeled accepted status moves it to accepted. A matched independent statement can then mark it reconciled. This program has no ledger postings.

~~~c
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

enum State { AWAITING, ACCEPTED, REJECTED, RECONCILED };
enum Event { ACCEPT_STATUS, REJECT_STATUS, MATCHED_STATEMENT };
enum Outcome { CHANGED, REPEAT, REVIEW };
struct Payment { unsigned reference; int64_t cents; unsigned currency; enum State state; };

static enum Outcome apply(struct Payment *row, struct Payment linked, enum Event event)
{
    // All incoming values have passed version mapping in this paper model.
    if (row->reference != linked.reference || row->cents != linked.cents ||
        row->currency != linked.currency || linked.cents <= 0) {
        return REVIEW;
    }
    switch (event) {
    case ACCEPT_STATUS:
        if (row->state == ACCEPTED || row->state == RECONCILED) return REPEAT;
        if (row->state != AWAITING) return REVIEW;
        row->state = ACCEPTED;
        return CHANGED;
    case REJECT_STATUS:
        if (row->state == REJECTED) return REPEAT;
        if (row->state != AWAITING) return REVIEW;
        row->state = REJECTED;
        return CHANGED;
    case MATCHED_STATEMENT:
        if (row->state == RECONCILED) return REPEAT;
        if (row->state != ACCEPTED) return REVIEW;
        row->state = RECONCILED;
        return CHANGED;
    }
    return REVIEW;
}

int main(void)
{
    struct Payment row = {201, 12500, 840, AWAITING};
    const struct Payment linked = row;
    const struct Payment wrong_amount = {201, 12499, 840, AWAITING};
    assert(apply(&row, linked, MATCHED_STATEMENT) == REVIEW);
    assert(apply(&row, linked, ACCEPT_STATUS) == CHANGED);
    assert(apply(&row, linked, ACCEPT_STATUS) == REPEAT);
    assert(apply(&row, wrong_amount, MATCHED_STATEMENT) == REVIEW);
    assert(row.state == ACCEPTED);
    assert(apply(&row, linked, MATCHED_STATEMENT) == CHANGED);
    assert(apply(&row, linked, MATCHED_STATEMENT) == REPEAT);
    puts("P-201 reconciled once");
    return 0;
}
~~~

Here 840 is the local numeric identifier for the USD classroom row. Use an agreed currency-code table at the adapter. A live service should retain each source message identity separately before applying its own transaction and replay rules.

1. Copy into payment_evidence.c and keep assert checks enabled.
2. Build with the supplied C23 command. On Windows use a configured GCC toolchain, name the output payment-evidence.exe and run .\payment-evidence.exe in PowerShell.
3. Try a matching reference P-201 with a different currency number. The gate should keep the existing state and return REVIEW.

~~~text
cc -std=c23 -Wall -Wextra -pedantic payment_evidence.c -o payment-evidence
./payment-evidence
Expected: P-201 reconciled once
~~~

## Read an x86-64 Assembly comparison

On a System V AMD64 target, the first two integer parameters arrive in RDI and RSI. The comparison writes zero or one to EAX. This illustration compares the count of minor units only. The C gate still owns the reference, currency and business-state checks.

~~~asm
# Intel syntax, System V AMD64
same_minor_units:
    xor eax, eax
    cmp rdi, rsi
    sete al
    ret
~~~

Follow the 12,500 and 12,499 paper values through CMP and SETE. The unequal comparison leaves the return value at zero. An object built for another calling convention requires that convention's argument registers.

[Browser edition](../../../courses/swift-payment-messages/lessons/03-apply-payment-evidence-in-c.html)

