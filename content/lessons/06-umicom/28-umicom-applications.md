# 28. Umicom Applications: reuse one foundation in many products

Umicom Framework becomes easier to understand when you see what it enables. Umicom Applications combines a pinned Framework revision with independently maintained application modules. Some products focus on development tools, others on trading, financial operations or desktop workflows.

## Start with Umicom Studio IDE

**Umicom Studio IDE** is the development environment in which a programmer can inspect source files, build targets, tests and diagnostics. It is also an important consumer of Framework components. A shared document model can support an editor inside Studio and a note-taking application without duplicating all file-handling behaviour.

The normal path through a development task is:

```text
Open project → Edit source → Build → Read diagnostics
                    ↓
                 Run tests → Review result
```

A test result is useful only if it corresponds to the source and build configuration actually used. If a binary was compiled yesterday but a source file changed today, rerun the relevant build before trusting an old test report.

## Umicom Desk and the application shell

**Umicom Desk** is the desktop shell and launcher for the suite. It coordinates application selection, task switching and shared presentation behaviour. The Framework owns common launch and layout contracts; an application contributes its identity, initial layout and product-specific capabilities.

A **window layout** describes where panels appear. A **launch operation** starts or activates an application process. These are not the same action even though they may be exposed in the same desktop interface.

## Financial applications

**Umicom Trader** explores market data, trading workstations and simulated or controlled execution flows. **Umicom Open TMS** models treasury and trade lifecycles from capture through risk and settlement. **Umicom Bank** applies customer, account, payment and ledger services. These products share some financial concepts but are not identical.

| Product | First concept to explore | Possible safe exercise |
| --- | --- | --- |
| Studio IDE | Project, document, build target, test result | Trace a Save command to its Framework service |
| Desk | Application, window, layout and session | Explain how a window is launched and restored |
| Trader | Instrument, order, fill and position | Follow a simulated order through its statuses |
| Open TMS | Trade, cashflow, confirmation, settlement | Follow a fictional FX trade to an accounting event |
| Bank | Customer, account, transfer and ledger | Validate a mock internal account transfer |
| OS Control Centre | System state and configuration | Explain which calls are user-space operations |

These learning tasks use sample data rather than genuine customer details or a live brokerage account.

## Follow one feature through the source

Choose a simple feature such as saving a note or showing a diagnostic message. Locate its application entry point, follow the service or controller it calls, then find the Framework header that defines the relevant contract. Finally, locate the focused test.

This is more effective than trying to read every source file in the repository from top to bottom. A large codebase becomes understandable one complete operation at a time.

## How to decide where a change belongs

If you discover that multiple applications need the same functionality, ask whether Framework already provides it. If it does, consume that contract. If not, consider whether a new shared module is justified. Keep specialised application behaviour in its owning product; avoid copying a shared subsystem into every application folder.

All work should preserve existing behaviour unless a reviewed change explicitly modifies it. A smaller implementation is not automatically a better implementation if it removes error handling, comments, tests or user-visible features.

**Next:** [Plan a project using Kanban](../07-practical-domains/29-kanban.md).
