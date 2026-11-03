# Turn an observation into a reviewed change

Understand permissions, boundaries and reviewable automation before joining applications to external systems.

Lesson 2 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

An automated assistant can suggest a fix after seeing an error. The suggestion is not evidence that the fix works. A reliable workflow separates **observation**, **proposal**, **review**, **execution** and **verification**.

Imagine a tool observes “file not found”. It might be a missing input, a wrong working directory or a file removed by security software. Automatically rewriting source code after that message could make the system worse. First collect the command, relevant path, source revision and complete diagnostic.

```text
observation → explanation → candidate change → review
                                               ↓
                                  bounded execution → evidence
```

A **candidate** is a proposed change with an explicit scope. A **precondition** is something that must still be true before applying it: for example, the source file still has the revision reviewed. If another writer changed the file, the old approval should not silently apply to the new content.

## Design a review record

1. Write the observed failure and keep its original text.
2. List two plausible causes instead of assuming one.
3. Choose one small candidate change and state what it is expected to improve.
4. Record the inputs and permissions needed to execute it.
5. Define a check that could prove the candidate wrong.
6. Record the actual result separately from the expected result.

A model confidence score is not a permission grant. Similarly, a passed syntax check does not prove an application workflow works. An automated loop should stop when required evidence is missing, report uncertainty, and preserve previous work.

Framework's approval contract is an existing source anchor for explicit decisions. The larger autonomous regeneration ideas are design topics; this lesson does not claim a complete self-improving production system is implemented.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\ai\approval.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef struct UmiAiApproval {
    char approval_id[UMI_AI_ID_CAPACITY];
    char action[UMI_AI_SMALL_TEXT_CAPACITY];
    int required;
    int approved;
    char approved_by[UMI_AI_ID_CAPACITY];
} UmiAiApproval;

/**
 * Initialise ai approval from caller-provided values so later operations receive a known
 * state.
 */
UmiStatus umi_ai_approval_init(UmiAiApproval *value);
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Inspect the approval header's states and operations. Identify the information available to a reviewer and what callers must still enforce outside the record.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

A tool proposed a patch and its text looks sensible. Which stage is complete?

### Worked answer

Proposal and perhaps human review. Execution and verification remain separate. Only observed results tied to the changed source can support a claim that it repaired the defect.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/secure-connected-services/lessons/reviewable-automation.html) · [Learning sequence](../../../../start/learning-sequence.md)
