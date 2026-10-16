# Episode 148 — Why a saved trade is not a settled trade

*Treasury From Zero · Spoken lesson following a fictional FX forward · Approximately 11–13 minutes*

## Opening: the green tick that doesn't tell the whole story

**On screen:** A training screen shows “Trade saved”. Then a separate panel shows one currency movement as pending.

**Narration:**

“Suppose a colleague tells you that a foreign-exchange trade is finished because the computer displayed a green tick. Before you agree, you need to ask: what did that tick mean? Did the trade get recorded? Was it approved? Were the payment instructions sent? Did the money actually arrive?

“These are different questions. In this video, we will follow one fictional trade through the work that happens after someone clicks Save.”

## First understand the agreement

**On screen:** Display two clearly labelled currencies, both with the company’s point of view:

- Receive USD 125,000.
- Pay GBP 100,000.

**Narration:**

“The company has agreed to buy one hundred and twenty-five thousand US dollars and sell one hundred thousand pounds on a future date. This is a foreign-exchange forward. It is a contract with a counterparty. Each side has a payment obligation.

“Before entering this in a system, we need the currencies, amounts, rate, date, the book that owns the trade and the identity of the other party. A ‘product’ tells us the type of contract. A ‘trade’ is this particular agreement.”

## Walk through the teams

**On screen:** Draw connected boxes: Front office → Controls → Transfers → Messages → Settlement. Place Accounting beneath, connected to the relevant business events.

**Narration:**

“The front office records the trade. A control process may verify the terms and permissions. Back-office processing prepares the cash obligations. Messaging creates instructions or confirmations. Settlement establishes whether the money moved correctly. Accounting records the financial effects under the agreed rules.

“These activities can overlap and sometimes happen in a different order. What matters is that one stage does not magically prove all the others.”

**On screen:** Mark four labels: Saved, Confirmed, Sent, Settled.

**Narration:**

“Saved means a trade version was recorded. Confirmed means an appropriate business confirmation process has completed. Sent means an instruction or message was transmitted. Settled means the required movement completed according to the evidence used by the organisation. Don't treat those words as interchangeable.”

## Where Calypso fits

**On screen:** A simplified architecture with authorised data access, event distribution and processing engines.

**Narration:**

“Calypso is an example of a platform designed to handle many stages of financial processing. In classic architectures, the Data Server provides access to authoritative business objects through supported services. Event services distribute notifications, and processing engines carry out work such as transfer generation or messaging.

“The precise services, screens and engine configuration depend on the Calypso release. You don't need that detail yet. You need to understand why the platform separates the agreement from the work required to fulfil it.”

## The missing-dollar investigation

**On screen:** Show the fictional evidence table: Trade confirmed; GBP transfer settled; USD transfer pending; USD message generated; no final receipt acknowledgement.

**Narration:**

“Our colleague says, ‘The trade is confirmed and the pounds have left, so I'll mark it complete.’ That would be unsafe. The company expects dollars, and we cannot yet prove they arrived.

“Instead, we follow the USD transfer reference, look at the settlement instruction, inspect the message and any acknowledgement, and compare with the relevant bank information. We record what we know and what we don't. We do not send a second payment simply because we cannot see the first one. A duplicate payment could be a much bigger problem.”

## Short viewer exercise

**On screen:** Ask: “Which statement is strongest evidence that the USD obligation is settled?”

A. The trade was saved.  
B. The payment instruction was generated.  
C. The appropriate bank/settlement acknowledgement has been received and reconciled.

**Narration:**

“The best answer is **C**, provided it covers the correct currency, amount, account and settlement reference. Even then, we still need to check any other outstanding business obligations. A strong conclusion has a clearly defined scope.”

## Closing

**Narration:**

“You now know why a financial platform needs trades, workflows, transfers, messages, settlement records and accounting—not just a single status field.

“The next time you see a green status indicator, ask one simple question: **what exactly has been proven?** That habit will help you whether you become a treasury user, a Calypso developer or a production support engineer.”

**Related reading:** [Follow one trade from booking to settlement](../../lessons/09-treasury-tms-calypso/18-follow-one-trade-from-booking-to-settlement.md).
