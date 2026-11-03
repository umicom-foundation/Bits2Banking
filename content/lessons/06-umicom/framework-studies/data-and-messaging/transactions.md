# Keep related changes together

Connect storage, message identity, retries and recovery without confusing a request with completion.

Lesson 1 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

A **database** is an organised store of information. A table contains records called rows. A key identifies a row. A **transaction** groups changes so they are accepted together or rejected together. These words matter when one action changes several related records.

Suppose a practice transfer moves 500 minor units from account A to account B. A starts at 2,000 and B at 700. The intended result is A = 1,500 and B = 1,200. The total remains 2,700. If a program writes A first and crashes before writing B, 500 appears to have vanished.

```text
begin transaction
  verify both accounts and permissions
  check available funds
  debit A and credit B
  record the transfer and audit event
commit transaction
```

This is pseudocode: a description of the steps, not a copyable Framework function. A real implementation must also define what happens after a crash, when storage is full, and when another writer changes the same account.

The Bank operations header describes an opaque service that owns its Data Server and state. It requires serial access to a handle. **Serial** means one operation at a time. Separate persistent handles can detect an outdated revision and return BUSY instead of silently replacing newer data.

## Simulate an interruption

1. Write A = 2,000 and B = 700.
2. Calculate the intended transfer result.
3. Stop after the debit. Record the incorrect total.
4. Repeat with both changes treated as a single unit. Before commit, observers should still see the old committed state.
5. Add a unique transfer identifier so a later retry can refer to the same request.

A transaction is not a promise that every external system participates in the same atomic operation. A bank network and a local database may have different commit points. That boundary needs a durable record of intent and later reconciliation.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\bank_operations\operations.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef struct UmiBankOperations UmiBankOperations;

/** Capabilities are checked before command execution and before idempotent
 * receipts are disclosed. Maker/checker identity separation is also enforced. */
typedef enum UmiBankCapability {
    UMI_BANK_CAP_CUSTOMERS = 1U,
    UMI_BANK_CAP_PAYMENTS = 2U,
    UMI_BANK_CAP_APPROVE = 4U,
    UMI_BANK_CAP_OPERATE = 8U,
    UMI_BANK_CAP_TEST_FUNDING = 16U,
    UMI_BANK_CAP_ALL = 31U
} UmiBankCapability;

typedef struct UmiBankActor {
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Read the service ownership and concurrency comments. Locate the transfer states and distinguish pending, approved and executed.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

If the UI stops waiting, does that prove a transfer was cancelled?

### Worked answer

No. The service may already have committed it. Query the recorded outcome using the original identifier before deciding whether to retry. A timeout describes missing knowledge, not a financial reversal.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/data-and-messaging/lessons/transactions.html) · [Learning sequence](../../../../start/learning-sequence.md)
