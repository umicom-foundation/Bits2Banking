# 3. Why a treasury department needs a system

*Bits to Banking · Treasury Management, TMS and Calypso From Zero · Umicom Foundation*

A spreadsheet can be a good way to begin. The kitchen in our example has one bank account and a handful of payments. Imagine, however, that it grows into a charity with branches in three countries. Each branch keeps a spreadsheet, and nobody knows which version is the latest.

Now the finance team asks: “How much money will we have available next Friday?” The answer arrives after a day of emails, and two people disagree because one has counted a promised donation as received.

A **Treasury Management System**, usually shortened to **TMS**, helps organisations keep a controlled picture of cash, funding, financial contracts, risk and payments. It is not just a fancy spreadsheet; it records where numbers came from, who may change them and what happened afterwards.

## A small problem with a spreadsheet

Imagine three people working on the same payment:

- A clerk enters an instruction to pay £900 for equipment.
- A manager checks and approves the payment.
- A bank later confirms whether the money moved.

If these are simply three rows in different spreadsheets, the organisation may accidentally pay twice, mistake approval for settlement or lose the reason why the instruction changed.

A well-designed system gives each instruction a stable identifier and a **status**. In our teaching example, the instruction might move from *Draft* to *Approved* to *Sent* to *Settled*. Each transition is recorded. If the bank rejects it, the system records *Rejected* and the reason rather than pretending it succeeded.

The idea is the same for financial trades: an agreed contract and a completed bank transfer are not the same event.

## What information belongs in a TMS?

Think of five connected kinds of information:

| Kind | Example | Why it matters |
|---|---|---|
| Reference information | Currencies, bank accounts, business partners | Identifies who and what a record concerns |
| Financial commitments | A loan, deposit or foreign-exchange trade | Explains future obligations |
| Cash movements | Expected receipts and outgoing payments | Builds the cash forecast |
| Controls and decisions | Approval, limit checks, exceptions | Prevents unauthorised or inconsistent actions |
| Evidence and reporting | Bank confirmations, audit history, reconciliations | Shows what actually happened |

Not every TMS includes the same products or modules. A corporate cash-management TMS can have a different focus from a multi-asset bank platform such as Calypso. We will study the differences later.

## The important distinction: planned, approved and completed

Suppose the kitchen plans to pay £900 tomorrow. The planned payment affects its **forecast**. When an authorised manager approves it, the payment is eligible for further processing, but no money has necessarily left the bank yet. Only appropriate confirmation and reconciliation can establish that it completed.

This is why a trustworthy system cannot replace the status *Payment sent* with *Payment settled*. The first describes an instruction. The second describes an observed outcome.

A system is also not a substitute for good business decisions. If a treasurer enters the wrong due date, software can calculate a perfectly accurate forecast of the wrong plan. People need to verify important inputs and review exceptions.

## A practical comparison

On paper, draw two versions of a £900 payment record. In Version A, write only `900`. In Version B, write: `PAY-0042`, `£900`, `Bank account: practice account`, `Due: Friday`, `Approved by: manager`, `Bank status: awaiting confirmation`.

Which record can another person investigate more easily? Why? Add one more field you would want before releasing a payment.

**Check your answer.** Version B records a currency, owner, date, identity and current state. It should also include the payee and authorised payment destination, subject to appropriate access controls. The system needs enough evidence to prevent duplicates, incorrect routing and unsupported claims of settlement.

The next chapter explains why dates, currencies and account balances must be recorded carefully before we start modelling trades.

*Reading connection: **Introduction to Treasury Management Systems Development**, Chapter 1, and **Calypso and TMS Training Manual**, Chapter 9.*
