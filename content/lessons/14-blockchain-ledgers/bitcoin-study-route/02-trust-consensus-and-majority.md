![Umicom](../../../assets/branding/umicom-wordmark.svg)

# 2. Who decides which ledger to trust?

Imagine a club keeps a list of who paid breakfast money. A phone photo of the list is evidence of a copy. The rules still have to say who can write a new entry, when an entry is accepted and what happens after a disagreement.

| Arrangement | Who checks a proposed update? | What the reader relies on |
| --- | --- | --- |
| Centrally administered ledger | The operator and its authorised systems | The operator follows its rules, preserves records and makes corrections through its procedures. |
| Independent readers of a signed log | Each reader checks the signatures and a known starting point | The reader recognises the signing key and has a way to identify the expected log history. |
| Bitcoin | Independent nodes check the candidate blocks and transactions they receive | Participants can check the same rules and compare cumulative work among valid candidate histories. |

A hash is a fingerprint of the bytes it covers. If you already know the expected hash, a mismatch tells you the bytes differ. A digital signature lets a verifier check that a signing key authorised a message under its rules. Neither a matching hash nor a valid signature decides by itself which of two otherwise acceptable payment histories the network settles on. That is a separate consensus question. [Bitcoin white paper, sections 2–5](https://bitcoin.org/en/bitcoin-paper)

## What a majority of work could change

The expression **51% attack** refers to control of a majority of the network's block-producing hash rate. It does not count wallets, computers or IP addresses. Sustained majority hash rate can make competing valid history grow faster on average. It increases the risk of reordering recent history, reversing an attacker's own recent payment through a conflicting spend, or omitting selected transactions. Other participants still apply their transaction and issuance rules. A majority of hash rate cannot create a valid signature for someone else's funds or require an independently validating node to accept an invalid subsidy. [Bitcoin white paper, sections 4 and 11](https://bitcoin.org/en/bitcoin-paper)

Use four cards to test the idea on paper. Write `valid` or `invalid` on two branch cards and a made-up work total on two score cards. Give an invalid branch a larger total than a valid branch. The invalid branch should be refused before comparing scores. Then make both branches valid and compare their scores. The rules require two different checks, even when the scores are very far apart.

### Check your understanding

The club wants a way to tell if an old receipt was altered and already trusts one operator to resolve disputes. Which benefit does a signed, hash-linked log give the club? Which separate governance question would a distributed consensus protocol have to answer?

<details>
<summary>Worked answer</summary>

A signed, hash-linked log can help someone check an old receipt against a trusted earlier commitment. A shared consensus protocol must also define how independent operators select an accepted history when they disagree or receive updates in a different order.

</details>

[Previous lesson: Money creation](01-money-creation.md) · [Course outline](index.md) · [Next lesson: Work, stake and confirmations](03-work-stake-and-confirmations.md) · [Umicom icon](../../../assets/branding/umicom-icon.svg)
