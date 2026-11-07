<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-nosql/04-validation-and-stable-identity.md

PURPOSE:
Validate records and keep identity stable

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Validate records and keep identity stable

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

## Flexible storage still needs rules

An application depends on meanings: a duration must be a number, an identifier must be stable, and a lesson title must be text. Flexible document storage does not establish these rules automatically. MongoDB supports validation rules for fields, types and values; behaviour for invalid writes depends on the configured validation level and action. [Schema validation](https://www.mongodb.com/docs/manual/core/schema-validation/).

Before designing a rule, write examples:

| Field | Accept | Refuse or review |
| --- | --- | --- |
| lesson identifier | c-hello | missing or changed identity |
| title | Printing a message | empty title |
| estimated minutes | 15 | negative number or text |
| language | C | an unrecognised spelling requiring review |

## Work through an application boundary

1. A form collects values as text.
2. The application parses a duration into a number and reports an actionable error for invalid input.
3. Framework validates the domain record before changing persistent state.
4. The driver serialises the record using its structured data API.
5. Server-side validation rejects malformed writes from other clients too.
6. The application reports success only after receiving the expected write acknowledgement.

Each step has a different job. A disabled Save button does not prevent a second client writing invalid data. Server validation cannot explain every local editing error as clearly as the form can.

## Learn from a real C boundary

Framework connector descriptors use fixed arrays for connector_id and display_name. Registration now checks that each nonempty field contains its terminating zero byte inside the array. Otherwise later string comparisons could read beyond the intended field. This is a memory boundary, distinct from the meaning of a database record.

Study valid_descriptor in the Framework connector source. The memchr call searches a bounded number of bytes. The short-circuit && operators stop evaluation when a required earlier condition fails. A non-null pointer still has to refer to a valid descriptor object; this function cannot make an arbitrary pointer readable.

## Plan a migration

A migration changes stored data or rules. If old documents use duration_text, do not abruptly require minutes without examining them. Plan a reviewed conversion, preserve a backup and test old readers. Record rejected documents for correction rather than silently inventing values.

Exercise: describe one valid record, one malformed record and one older record requiring migration. State what the UI, Framework and database should each do.

## Read the source

[Open the example source](https://www.mongodb.com/docs/manual/core/schema-validation/).

## Continue learning

[Course contents](../../../courses/learning-nosql/index.html) · [Previous: Ask precise questions and limit the result](03-query-and-limit-results.md) · [Next: Indexes, duplicate identities and concurrent edits](05-indexes-and-concurrent-edits.md)
