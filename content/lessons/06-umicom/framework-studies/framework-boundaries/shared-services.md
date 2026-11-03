# One service, several applications

Follow a request from a window to a shared service, and learn how C interfaces connect native components.

Lesson 1 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

A program is a set of instructions a computer follows. An application adds a purpose, such as editing a document or showing an account. A **framework** supplies reusable parts so each application does not have to solve the same problems again. A **service** is a named capability with a defined interface: for example, asking for a document snapshot.

Consider a balance shown in a Bank window and a Treasury report. If each window calculates its own balance, a correction might reach one and miss the other. Instead, both ask the same financial service. The windows choose how to display the answer; the service owns the rule and the authoritative data.

## Follow a request

```text
Bank button → command → shared service → result
Treasury screen → query ────────┘           ↓
                                 each screen updates its view
```

A **command** requests a change. A **query** asks a question. An **event** reports something that happened. Pressing a button proves only that a request was made; success must come from the result. A refused request should explain the problem and preserve the previous state.

In Framework's service registry, an identifier names a service. A version describes the interface expected by a consumer. Ownership says who eventually releases the service. The flags distinguish properties such as a shared instance and thread safety. A registry can organise dependencies; it cannot make arbitrary service code safe to use concurrently.

## A small design exercise

1. Draw two boxes labelled Bank and TMS, then one labelled Balances.
2. Draw read requests from both applications to Balances.
3. Add a transfer command. Route it through the service, not directly into a label or database table.
4. Add a failure result named “insufficient available funds”. Keep the original displayed balance until a fresh result arrives.

This sketch is an architecture exercise. It is not a claim that every product screen already follows this route. To assess a real screen, trace its callback to the service and inspect the returned status.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\runtime\service_registry.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef enum UmiServiceFlags {
    UMI_SERVICE_NONE = 0U,
    UMI_SERVICE_SINGLETON = 1U << 0,
    UMI_SERVICE_OWNED = 1U << 1,
    UMI_SERVICE_THREAD_SAFE = 1U << 2,
    UMI_SERVICE_REPLACEABLE = 1U << 3
} UmiServiceFlags;

typedef void (*UmiServiceDestroyFn)(void *service, void *user_data);

/**
 * Represent the service descriptor data shared with callers of this public contract.
 */
typedef struct UmiServiceDescriptor {
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Find UmiServiceFlags and UmiServiceDestroyFn. Identify the ownership flag and the callback used when owned service storage is released. Explain why a borrowed pointer must not outlive its owner.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

Why should changing the colour of the balance display not change how the balance is calculated?

### Worked answer

Colour belongs to presentation. Calculation belongs to the shared financial service. Keeping those responsibilities separate lets several applications display the same result and lets a non-graphical check exercise the same rules.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/framework-boundaries/lessons/shared-services.html) · [Learning sequence](../../../../start/learning-sequence.md)
