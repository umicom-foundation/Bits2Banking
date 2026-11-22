![Umicom](../../../assets/branding/umicom-wordmark.svg)

# 1. Where new money comes from

Think of a ledger as a notebook with a rule for writing down every amount. The same £100 can be a deposit you can spend, a loan you must repay or part of a settlement between banks. The name tells you what the entry represents and who owes it.

## Follow a £100 bank loan

Suppose a bank lends you £100 and credits your account at that bank. The bank gains a £100 loan asset, because you owe it £100. You gain a £100 bank deposit, which is a liability of the bank because it owes you that balance. In this example the new deposit is created at the same time as the loan. The entries below show changes from the starting point, before interest and fees. [Bank of England explanation of money creation](https://www.bankofengland.co.uk/explainers/how-is-money-created)

| Event | Change in the bank's loan asset | Change in the bank's deposit liability |
| --- | ---: | ---: |
| Loan is made | +£100 | +£100 |
| £25 of principal is repaid using a deposit at this bank | −£25 | −£25 |
| Net change after both events | +£75 | +£75 |

If you pay someone at another bank, your bank reduces your deposit and the recipient's bank credits theirs. The banks settle with one another using central bank reserves. Reserves are balances held at a central bank by eligible institutions. A customer's bank deposit is a separate balance. Bank lending is constrained by regulation, funding, the ability to settle payments and the risk that borrowers may fail to repay. [Bank of England on deposits and reserves](https://www.bankofengland.co.uk/explainers/how-is-money-created)

Now suppose a central bank buys a £100 bond directly from a commercial bank and pays by crediting that bank's reserve account. The central bank records a £100 bond asset and a £100 reserve liability. The commercial bank exchanges a bond asset for a reserve asset. No household deposit changes in this two-party example. The reserve credit represents central bank money creation, with a different issuer and a different ledger from the customer's bank deposit. [Bank of England Quarterly Bulletin on money creation](https://www.bankofengland.co.uk/-/media/boe/files/quarterly-bulletin/2014/money-creation-in-the-modern-economy.pdf)

## Follow a Bitcoin block reward

A valid block can contain a special first transaction called a coinbase transaction. Under Bitcoin's rules it can claim the allowed subsidy and the fees from transactions included in that block. The subsidy permits new bitcoin to be issued. The fees are amounts that already existed and are reassigned to the block producer. Nodes check the producer's claim against the protocol rules. [Bitcoin white paper, section 6](https://bitcoin.org/en/bitcoin-paper)

Imagine a classroom rule permits a subsidy of four units plus fees of two units. If the producer claims six, four are new units and two came from earlier balances. A claim of seven breaks the rule. Keep these classroom numbers separate from Bitcoin's actual parameters and denominations.

### Check your understanding

1. In the example, what remains after the borrower repays another £5 of principal from the same bank deposit?
2. Under the classroom rules, can the block producer make a seven-unit claim valid by doing more proof of work?

<details>
<summary>Worked answers</summary>

1. The new loan asset and deposit liability are each £70 above their original amounts. The extra principal repayment reduced each by £5.
2. No. The maximum claim is six units under the stated rules. Work measures effort on a block candidate. The validator still checks the subsidy and fees.

</details>

[Course outline](index.md) · [Next lesson: Trust and control](02-trust-consensus-and-majority.md) · [Umicom icon](../../../assets/branding/umicom-icon.svg)
