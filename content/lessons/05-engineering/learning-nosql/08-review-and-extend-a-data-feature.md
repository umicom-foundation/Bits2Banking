<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-nosql/08-review-and-extend-a-data-feature.md

PURPOSE:
Review and extend an Umicom data feature

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Review and extend an Umicom data feature

Learn how applications store documents, find records and manage database connections. Start with an invented lesson catalogue, then inspect the real Umicom Framework connector boundary. Each lesson includes its own setup summary and a small exercise.

## Before you begin

A database keeps organised information. A document is a group of named values, such as a lesson identifier, title and list of topics. A collection groups documents. A query asks the database to find information. A terminal is a window where typed commands start programs. This course explains the commands before asking you to use them.

For the database exercises, install MongoDB Community Server using its [official platform instructions](https://www.mongodb.com/docs/manual/installation/) and install the [mongosh command-line client](https://www.mongodb.com/docs/mongodb-shell/install/). Choose a local training installation. Keep it reachable only from your own computer while learning. Use invented course records, never customer accounts or credentials. A shared or remote server needs authentication, transport security and explicit access control before use.

1. Open PowerShell on Windows, or a terminal running Bash on Linux.
2. Type `mongosh --version`. A version means the client can be found. If it is not recognised, finish the client installation and reopen the terminal.
3. Start your local server using the instructions for its installed service. The client and server are separate programs.
4. Connect with `mongosh "mongodb://127.0.0.1:27017"`. Here `127.0.0.1` means this computer, and `27017` is the default local port. Use your configured port if different.
5. At the mongosh prompt type `use bits2banking_learning`. All database examples below belong to this disposable training database. Do not select a production database.

A connection refusal means there is no reachable server at that address; check the service and port. Do not fix it by exposing the server to the public network. Type `exit` to leave mongosh. Each practical lesson creates its own named record, so you may start there without running an earlier lesson.

The native C lab later in the course uses the existing Umicom Framework data SDK. It does not connect to MongoDB; its purpose is to make adapter ownership visible before a real driver is introduced.

## Put the pieces together

A feature is more than a query. Consider a saved-project list in Studio: a user opens a project, the list records its identity and location, a later session reads the list, and selecting an entry attempts to open it. A missing file, inaccessible directory or malformed record needs a clear outcome.

The same review method applies to Media assets and a learning catalogue. Financial applications need their own stronger transaction and reconciliation rules. A document database example is not an accounting ledger implementation.

## Walk through one feature

1. Write one sentence describing what the user accomplishes.
2. List its data fields and explain why each is needed.
3. Name the owner of each allocation and callback context.
4. Identify the shared Framework service the application calls.
5. Draw the success path and at least three failure paths.
6. Define what remains unchanged if validation fails.
7. Add tests for empty results, maximum sizes, invalid types, duplicate identity and repeat close.
8. Add an integration test using an explicitly selected disposable provider.
9. Keep provider integration results separate from an in-memory fixture test.
10. Document the actual supported behaviour in the user guide.

## A small test matrix

| Input or event | Expected observation |
| --- | --- |
| valid short identity | accepted without truncation |
| identifier fills its array with no terminator | registration refused |
| registry destroyed after open | copied handle callbacks remain usable |
| nested close notification | one provider release |
| query after close | invalid operation reported |
| database unavailable | failure, not an empty successful result |

The connector-lifetime lab and Framework connector regression cover the ownership rows. They do not prove the network rows. A test name or a written test is not execution evidence: record the source revision, environment, command, result and any skipped coverage when qualifying an implementation.

## Independent exercise

Design a read-only project catalogue using a fake provider first. Return at most three entries. Add a deliberately malformed fourth record and describe whether the service rejects the whole result or reports a per-record error. Explain that choice in a short public engineering note.

Then plan the real provider's tests without changing credentials or network settings. The objective is a reviewable path from user action to shared service, provider response and visible result, with no hidden duplication inside the application's screen.

## Read the source

[Open the example source](../../../../labs/framework/connector-lifetime/README.md).

## Continue learning

[Course contents](../../../courses/learning-nosql/index.html) · [Previous: Plan a real document-database provider](07-connect-a-real-provider.md)
