# Knowing who asked and what they may do

Understand permissions, boundaries and reviewable automation before joining applications to external systems.

Lesson 1 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

**Authentication** establishes an identity. **Authorisation** decides what that identity may do. Logging in successfully does not mean every action is permitted. A person allowed to prepare a payment might not be allowed to approve it.

A **capability** represents an allowed class of actions. The Bank operations contract accepts a trusted actor identity and capability flags. Those flags must be supplied by trusted application or identity code. A web request saying “I have all capabilities” cannot be accepted as proof.

```text
untrusted request → authenticate → authorise → validate → execute
                                          refusal ↘ preserve state
```

A **trust boundary** is a point where data passes between different levels of authority. A browser, plug-in or remote service is not trusted simply because it can send a well-formed message. Even a local web listener needs a clear policy about which clients and requests it accepts.

## Separate two responsibilities

1. Create two fictional identities: maker and checker.
2. Give the maker permission to prepare a transfer.
3. Give the checker permission to approve it.
4. Try approval with the maker identity. Expect refusal when separation of duties is required.
5. Try again with the checker but remove approval permission. Identity difference alone must not be enough.

**Separation of duties** reduces the chance that one mistaken or malicious actor can complete a sensitive action alone. It is one control, not a complete security system. The service must still validate amounts, account states and current revisions.

Do not place passwords, authentication codes or secret keys in exercises, screenshots or logs. Use invented names and identifiers. Useful logs can record operation type, status and correlation identity without recording secret input.

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
2. Find UmiBankCapability and UmiBankActor. Read the warning about the local simulation profile and explain which authentication functions this service does not provide.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

Can disabling an Approve button replace the service permission check?

### Worked answer

No. A different client could call the service directly. The disabled button helps the user understand availability; the authoritative permission check belongs at the service boundary.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/secure-connected-services/lessons/identity-and-authority.html) · [Learning sequence](../../../../start/learning-sequence.md)
