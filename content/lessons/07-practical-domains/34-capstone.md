# 34. Your next project: one application, several skills

You now have the pieces needed to plan a substantial application. Instead of writing unrelated demonstrations, you can extend the same task board into a small project-management system and use the accounting and trading exercises to learn how different domains add new rules.

The most important habit is to build **one working feature at a time**. A feature is ready when you can demonstrate its result, explain its code, and show that its tests still pass.

## Stage 1 — define the application

Our project is a task board for people contributing to Umicom. It needs tasks, statuses, a simple search, and safe storage. Write an acceptance criterion for each feature before editing code.

| Feature | Example acceptance criterion |
| --- | --- |
| Add a task | Entering a valid title adds one item with a unique identifier |
| Reject blank input | Whitespace-only titles are not saved |
| Complete a task | Status changes to Done without changing its identifier |
| Restart | Previously saved tasks reappear correctly |
| Search | A query returns matching titles without editing them |
| Handle failures | Failed storage is reported; no false success message appears |

## Stage 2 — build the small versions

Start with the [Python notes program](../02-programming/07-python.md). It already handles saving, reading and rejecting blank input. Extend it so a note record contains `id`, `title` and `status`, then write a unit test for the new rule.

Next, open the [HTML task board](../04-web/12-html.md), add the [CSS](../04-web/13-css.md), and make its tasks interactive with [JavaScript](../04-web/14-javascript.md). Check that the interface works using the keyboard as well as a mouse.

When you need shared storage, move persistence behind a service contract and implement an appropriate backend with the [database concepts](../05-engineering/19-databases.md). Do not allow the graphical interface to become the only authority for task data.

## Stage 3 — connect to the Umicom ecosystem

Build the real Framework Notes example from [Chapter 25](../06-umicom/25-use-the-framework.md). Identify which service already handles documents and persistence. If a task-board feature can reuse a Framework service, call that service instead of copying the implementation.

Keep product-specific rules in the task-board module. The task-board window should be a frontend, not a place where database writes and global application policies are mixed together.

## Stage 4 — put the project under version control

Create a repository in your practice area, commit one working feature and keep your changes reviewable. Use the [Git chapter](../05-engineering/16-git.md) and the [pull-request walkthrough](../05-engineering/17-first-pull-request.md) when you are ready to propose a contribution to an Umicom repository.

A good review explains what changed, why it changed and which checks were run. Keep your existing source and tests available when making improvements; if implementation needs replacing, make the reason and migration path clear.

## Stage 5 — try a new domain

After the task board works, choose a related practice application:

- **Accounting:** create balanced fictional journals and reject unbalanced ones.
- **Banking:** model two fictional customer accounts and an authorised internal transfer.
- **Treasury:** record an FX forward and generate expected cashflows.
- **Trading:** process a simulated limit order through validation and fills.

All four benefit from shared concepts: identifiers, validation, persistent state, audit events, permission checks and tests. Those shared concepts are where Umicom Framework provides value.

## When is the project ready?

You should be able to demonstrate a clean build, run the application, save and restore its data, handle one expected failure, inspect the Git diff and explain which module owns each important rule. That is a stronger result than having a large program whose correctness you cannot explain.

You can continue with the advanced *Bits to Banking* volumes for market risk, financial messaging, operating-system engineering, database architecture and specialised Umicom applications. The foundations remain the same: clear contracts, explicit ownership, small changes and observable results.
