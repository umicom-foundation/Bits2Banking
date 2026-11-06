# Validate before changing state

[Course contents](index.md) · [Previous: An exact record format](01-an-exact-record-format.md) · [Next: History, replay and recovery](03-history-replay-and-recovery.md)

## A failed request must not partly succeed

Our ledger has one balance of practice units. A request asks to spend some units. Before changing state, check that the amount is permitted and available. A status return tells the caller whether the change happened.

```c
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static bool spend(uint64_t *balance, uint64_t amount)
{
    if (balance == NULL || amount == 0 || amount > *balance)
        return false;
    *balance -= amount;
    return true;
}
```

The stddef.h header defines NULL. A pointer identifies caller-owned memory. The short-circuit OR operator stops checking once a condition is true, so the null check prevents dereferencing a null pointer. Subtract only after all checks pass.

This is an account model, not Bitcoin's unspent-output model. It has no authorisation, concurrency or persistence yet. Stating those limits prevents a small arithmetic example from being mistaken for a financial service.

## Trace success and failure

1. Set balance to 10.
2. Request a spend of 4. Predict true and balance 6.
3. Request a spend of 7. Predict false and balance still 6.
4. Request zero. Under this exercise's rule, predict false.
5. Give two callers the same balance snapshot. Notice that checking each in isolation is not enough to prevent concurrent overspending.

A production service needs an atomic check-and-update or equivalent transaction isolation. Atomic means the operation appears as one indivisible state change to other participants. A hash chain does not supply that property by itself.

## Exercise

For a credit operation, why is balance += amount insufficient for a uint64_t value near its maximum? Write the condition to check first.

## Explained answer

Unsigned addition wraps modulo the type's range. Check amount > UINT64_MAX - balance before adding. Reject without mutation when the sum cannot fit. When extending the lab, add assertions for unchanged output on rejected requests. Expected results in this lesson are reasoning targets, not a claim that a particular compiler has run them.

## Continue learning

[Course contents](index.md) · [Previous: An exact record format](01-an-exact-record-format.md) · [Next: History, replay and recovery](03-history-replay-and-recovery.md)

[Browser edition](../../../courses/building-blockchain-from-scratch/lessons/02-validate-before-changing-state.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/base/sha256.h). This public revision matches the source inspected for this lesson.
