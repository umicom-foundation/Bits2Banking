# Chapter 308 — Security evidence is not authorisation

**Bits to Banking · Native C23 engineering · Umicom Foundation**  
**Prerequisites:** Chapters 292–307; System Administration Chapters 85–96.  
**Implementation:** ISO C23; no Python or PowerShell implementation scripts.

## Real software engineering question

An Umicom Studio service is running, and a background observer reports that its configuration hash has not changed. Should a program then automatically approve a privileged configuration update? **No.** A working service, a matching digest, authorisation and a human approval are distinct facts. A correct system must not turn technical observations into permissions that were never granted.

Update 39 introduced owned, bounded support observations. Update 40 added dependency readiness; Update 41 modelled maintenance and restoration; Update 42 modelled private deployment staging; Update 43 added remote-review prerequisites. Those capabilities remain intact. Update 44 is an **additional teaching layer**, not a replacement implementation.

## The three different kinds of statement

1. **Observation:** A trusted collector saw a relevant state at a recorded time, or could not obtain a result.
2. **Policy:** The system requires accounts, permissions, configuration, recovery and incident evidence before review.
3. **Authorisation:** The responsible person or existing governed service permits a particular action on a specific target.

A set of fictional Boolean fields may model the second type for education, but it cannot establish the first or the third in a real environment. That is why the lab status is named `BTB_SECURITY_REVIEWABLE`, **not** `APPROVED_FOR_EXECUTION`.

![Separation of observation, review, and human approval](../../assets/diagrams/sysadmin-security-review-lifecycle-update44.svg)

## Start from the public contract

Open `labs/native/security-operations-review/security_operations_review.h`. The public interface uses caller-owned records and a stable set of enum values. Input strings have explicit maximum storage capacities. The review *copies* its upstream `BtbRemoteReview`, rather than retaining an unsafe pointer to a temporary object. The `BtbSecurityDecision` carries a reason mask so the caller can report every unsatisfied gate.

Important boundary:

```c
BtbSecurityResult BtbSecurityInit(BtbSecurityReview *review,
                                  const BtbSecurityPlan *plan,
                                  const BtbRemoteReview *remote);
BtbSecurityResult BtbSecurityAttach(BtbSecurityReview *review,
                                    const BtbSecurityEvidence *evidence);
BtbSecurityResult BtbSecurityEvaluate(const BtbSecurityReview *review,
                                      BtbSecurityDecision *outDecision);
```

The calls do **not** connect to a server, read a password, inspect real OS accounts, change a firewall or execute Git. That limitation is a feature of the teaching model, and must appear in its tests and documentation.

## A common implementation error

Suppose a service called `StartDeployment()` whenever `BtbSecurityEvaluate()` returned `BTB_SECURITY_OK`. That would be wrong: the return value means only **the function evaluated valid inputs**. The decision might say `BLOCKED`, `PENDING` or `RESTORED_ONLY`. Even `REVIEWABLE` does not grant operational authority. The application must use the existing Framework policy and identity services to perform any real privileged action.

## Practical review

Inspect the header and label which structures are caller-owned and which fields are copied. Find the exact code path setting `BTB_SECURITY_MISSING_RESTORE_TEST` when restore evidence is absent. Put a breakpoint there, change the fictional flag and observe that the output becomes `BLOCKED` without changing the host.

**Question:** Why should a status type separate success of evaluation from readiness? **Answer:** Function execution and domain-state decisions are different outcomes and must not be confused.

**Question:** Why keep every missing reason? **Answer:** It lets an operator address several gaps independently rather than repeatedly discovering one hidden failure at a time.

**Umicom architecture:** The Framework Master Controller coordinates lifecycle; domain Slave Controllers and security services enforce their own contracts. Bits2Banking owns only educational composition, not production authority.

**Next:** Chapter 309 — composing previous C23 libraries without copying their implementations.
