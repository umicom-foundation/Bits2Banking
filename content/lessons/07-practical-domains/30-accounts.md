# 30. Understanding accounts: software, banking and finance

The word **account** is used in several fields, and it does not always mean the same thing. A user account controls access to a computer. A bank account represents an agreement and records money-related rights and obligations. An accounting ledger account is a category for recording transactions. A trading account has its own permissions and financial arrangements.

Understanding the context prevents confusion when building a banking or treasury application.

## Software user accounts

A **user account** identifies a person or workload so a system can apply authentication and permissions. A **service account** is an identity used by software running a defined task. Neither type is automatically a bank account.

Authentication asks **who are you?** Authorisation asks **what are you allowed to do?** A user might be allowed to view a task but not approve an outgoing payment. The same principles apply to Umicom Studio workspaces and the administrative services in Umicom OS.

## Bank customer accounts

Bank products vary by jurisdiction and provider, but several broad account types recur:

| Account type | Typical purpose | Important distinction |
| --- | --- | --- |
| Current or checking account | Everyday payments, receipts and transfers | Usually designed for frequent transactions |
| Savings account | Holding funds and potentially earning interest | Withdrawal and rate terms depend on the product |
| Term deposit | Keeping funds for an agreed period | Maturity date and early-withdrawal conditions matter |
| Business account | Payments and cash management for an organisation | May support mandates and multiple authorised users |
| Foreign-currency account | Holding balances in a specified currency | Currency risk and conversion costs must be considered |
| Joint account | Shared contractual access | Ownership, authority and survivorship rules vary |

A **bank balance** can have several definitions. A **ledger balance** reflects recorded postings. An **available balance** may subtract reservations, unsettled holds or other restrictions. A user interface should show which balance it is presenting, particularly before allowing a payment.

## Brokerage and trading accounts

A **cash brokerage account** generally requires trades to be financed from eligible cash and settled funds under its applicable rules. A **margin account** can permit borrowing or leveraged positions subject to permissions, margin requirements and risk controls. A **custody account** records holdings under a custody arrangement. Account types and investor protections vary, so software must not assume a universal set of rules.

A trading system distinguishes the **customer**, **legal entity**, **account**, **portfolio**, **book**, **order** and **position**. These are related records but they answer different questions.

## Correspondent banking: nostro and vostro

Banks may maintain accounts with one another to support payments and settlements. **Nostro** means “our account with you” from one bank's perspective; **vostro** means “your account with us” from the other bank's perspective. They can describe the same underlying banking relationship from opposite viewpoints.

## Accounting ledger accounts

In double-entry accounting, a **ledger account** is a category such as cash, loans payable, income or expenses. It is not necessarily an actual bank account. One company may have several real bank accounts while its general ledger uses a structured chart of accounts to summarise and control them.

The five fundamental accounting categories are **assets**, **liabilities**, **equity**, **income** and **expenses**. The next chapter shows why debits and credits have different effects depending on the account category.

## Model an account in software

A small banking simulator might define a record such as:

```text
Account ID: A-1001
Customer ID: C-204
Currency: GBP
Account type: Current
Ledger balance: 12500 pence
Reserved amount: 1500 pence
Available balance: 11000 pence
```

The values are fictional. The available balance here follows a deliberately simplified rule: ledger balance minus reserved amount. Real banking availability calculations can include overdraft limits, pending credits, settlement rules and other restrictions.

An account identifier must not be treated as permission to operate the account. Before allowing a transfer, a system must also check identity, authority, limits and applicable product rules.

## Check your understanding

Is a service account the same as a current account? What is the difference between a bank account and a general-ledger account? Why might the available balance differ from the ledger balance? Which records would an authorised internal transfer need?

**Next:** [Learn double-entry accounting](31-accounting.md).
