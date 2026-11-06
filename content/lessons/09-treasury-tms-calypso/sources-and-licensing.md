# Sources and how this course uses them

The *Introduction to Treasury Management Systems* course is an independent beginner-friendly explanation based on Umicom Foundation training sources prepared or supplied by Sammy Hegab. The course is not official Nasdaq Calypso documentation.

The core learning references are:

- **Introduction to Treasury Management Systems Development: A Developer's Guide to Calypso Development** — treasury purpose, account management, software benefits and the introductory TMS curriculum.
- **Bits to Banking: Calypso and Treasury Management Systems Training Manual, Edition 1** — front/middle/back office, product coverage, lifecycle, risk and the progression from computing to treasury and Calypso.
- **Calypso Training Presentation by Sammy Hegab** — especially the product/trade/book/entity diagrams on pages 9–15, back-office transfer/message/posting diagrams on pages 16–18 and classic service architecture around pages 20–24.
- **Calypso Development and Treasury Management Systems — Practical Refresher Manual** — business economics, lifecycle, settlement, risk and operational responsibilities.
- **Bits to Banking, Volume 11: Calypso Production Engineering** — traceable business outcomes and operational evidence.
- **Bits to Banking, Volume 12: Java, Calypso Development and Native Integration** — financial values, dates, classic API boundaries and integration principles.

The financial examples are original classroom scenarios and are not intended as financial advice, live rates or executable payment instructions. Named Calypso objects and examples are discussed conceptually; actual modules, signatures and deployment steps depend on the licensed product release and client environment.

The original books, presentation and their authorship remain intact. This reader edition explains their ideas through an ordered set of introductory lessons and original worked examples. It does not overwrite or relicense the original source documents. Commercial names remain the property of their respective owners.

## How the foundational manuscript connects to the lessons

Start with Sammy Hegab's *Introduction to Treasury Management Systems Development*. Its introduction explains why treasury systems exist before discussing software development. The learning route follows that order:

| Manuscript theme | Existing lessons to study | What to practise |
| --- | --- | --- |
| Cash management and account information | Lessons 1–4, then 13 | Work out a dated cash forecast |
| Liquidity: having funds available when needed | Lessons 2, 13 and 15 | Identify a shortfall before a payment is due |
| Managing financial agreements and risk | Lessons 6–10, then 16–17 | Separate agreed cashflows from a changing valuation |
| Controls and operational processing | Lessons 5, 9, 11 and 18 | Trace an agreement through approval and settlement evidence |
| Introducing a TMS and later development | Lessons 3 and 12 | Explain the business workflow before reading an API |

The [main course contents](index.md) gives the exact reading order and links. Later programming modules build on these financial ideas. They must identify the licensed API version before presenting executable vendor-specific calls; a conceptual object name is not a promise that a particular installed API has that signature.
