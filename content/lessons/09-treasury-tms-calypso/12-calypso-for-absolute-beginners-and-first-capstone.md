# 12. Your first guided tour of Calypso—and a complete practice trade

*Bits to Banking · Treasury Management, TMS and Calypso From Zero · Umicom Foundation*

We have travelled from a small kitchen's cash balance to a bank's financial contracts. You now understand why an organisation needs treasury, what a TMS records and why a completed trade has more than one status.

**Calypso** is a commercial platform used for front-to-back processing across capital-markets and treasury activities. It brings together financial products, trade processing, data services, risk, workflow, operational engines, settlement, accounting and reporting. It is not necessary to install Calypso to understand this architecture.

## Think of the platform as a connected workplace

Imagine several teams sharing reliable information. A person in the front office records a trade. A middle-office control checks risk and approvals. A back-office process derives settlement obligations. Finance records accounting effects. Users see different views of the same underlying business activity.

A large financial platform needs separate components because the activities have different requirements. One service must protect authoritative trade data; another can distribute notifications; others can process payments or calculate risk.

In the classic architecture described by the supplied Calypso materials, three names are particularly important:

**Data Server:** the authorised service gateway for persistent trade and reference information, working with caching, validation and object versioning. Applications should use supported services rather than changing core database tables directly.

**Event Server:** distributes notifications about relevant changes to subscribing components. For example, a processing engine may need to learn that a trade reached a workflow state.

**Engine Server:** hosts engines that carry out business processing. A transfer engine can prepare settlement obligations; messaging and accounting engines have other responsibilities.

The actual deployment and APIs can vary by Calypso release and client estate. Here we are learning the responsibilities, not memorising server commands.

## Trace one fictional deal from beginning to end

Our practice company will buy **USD 125,000** and sell **GBP 100,000** under a forward agreement. We will follow what different people and systems need to know.

| Stage | What happens | What proves it? |
|---|---|---|
| 1. Agreement | Parties agree terms and future exchange date | Trade identity and agreed terms |
| 2. Capture | User records the trade against a book and counterparty | Saved trade version |
| 3. Control | Authorised people and rules verify it | Approval and workflow history |
| 4. Processing | Transfer obligations are prepared | Transfer records and their states |
| 5. Communication | Confirmation or payment messages are produced | Message identity and delivery status |
| 6. Settlement | Cash movements complete | Bank or settlement confirmation, reconciled |
| 7. Accounting | Financial effects are recorded | Balanced authorised postings and ledger reconciliation |

The stages may overlap and involve parallel processes. There may also be exceptions, amendments and reversals. The table is a **conceptual classroom journey**, not a guaranteed execution order for every product or Calypso release.

## The most important lesson: never confuse technical success with business success

Suppose the engine process is running and its log contains “message generated”. Can we say the FX forward has settled? **No.** We still need the appropriate evidence that both currency obligations were completed and reconciled. A healthy-looking program may have unfinished business work.

Similarly, if a transfer fails, restarting every server may not help. We first need to identify whether the problem is an account instruction, a missing event, an external rejection, an invalid date or a processing exception.

## Capstone: solve a trade-processing problem

Complete this exercise using paper or a text editor. You do not need a programming language or Calypso installation.

**Scenario:** A company agrees to receive USD 125,000 and pay GBP 100,000 three months from today. The trade is verified and confirmed. On settlement day, the outgoing GBP leg is confirmed, but the incoming USD leg has not appeared in the expected account.

Write a short investigation with these sections:

1. **Known facts.** What is the trade, who are the parties, and which movement is missing?
2. **Checks.** Which trade version, transfer, settlement instruction, message and bank evidence would you inspect?
3. **Action.** Why should staff avoid blindly sending a second instruction or marking everything settled?
4. **Conclusion.** Which evidence would allow the case to be closed?

**Suggested answer:** The trade's economic terms and verification history should be checked first. The team then traces the USD transfer, routing instructions, message acknowledgements and receiving bank records, preserving all identifiers and timestamps. The outgoing GBP payment alone does not prove both obligations completed. Closure requires the appropriate settlement evidence and reconciliation, or an authorised exception and recovery process.

## Where your learning goes next

You have completed the introductory stage. The next stage will explain cash ladders in greater depth, loan and deposit lifecycles, FX swaps, funding, book positions, and practical simulations with exact amounts and dates. Programming will be introduced gradually; it is not a prerequisite for these first lessons.

The supplied books provide the professional depth that we will work towards. The *Calypso Training Presentation*, **page 20**, shows the classic multi-tier architecture; **pages 22–24** explain data and event responsibilities. The *Calypso and TMS Training Manual* introduces later V18-oriented concepts. Differences between versions will be identified explicitly rather than treating one historical interface as universal.

*Reading connection: **Calypso Training Presentation**, pages 20–24; **Volume 11: Calypso Production Engineering**, Chapter 1; **Calypso and TMS Training Manual**, Parts III–IV.*
