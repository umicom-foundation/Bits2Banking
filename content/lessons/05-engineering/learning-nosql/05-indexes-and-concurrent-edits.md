<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-nosql/05-indexes-and-concurrent-edits.md

PURPOSE:
Indexes, duplicate identities and concurrent edits

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Indexes, duplicate identities and concurrent edits

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

## Why an index exists

An index is an additional structure that helps a database locate data using selected fields. It uses storage and adds work when those fields change. A unique index also enforces a uniqueness rule. Existing duplicate values can prevent creation of a unique index. [Unique index behaviour](https://www.mongodb.com/docs/manual/core/index-unique/).

For a fresh local exercise, use the separate lesson_identity collection:

~~~javascript
db.lesson_identity.createIndex({ catalogue_key: 1 }, { unique: true })
db.lesson_identity.updateOne({ _id: "one" },
  { $set: { catalogue_key: "intro-c", title: "Learning C", revision: 1 } },
  { upsert: true })
db.lesson_identity.updateOne({ _id: "two" },
  { $set: { catalogue_key: "intro-c", title: "Another title", revision: 1 } },
  { upsert: true })
~~~

The final command deliberately attempts a duplicate catalogue key. Expect a duplicate-key error. This is a designed negative exercise, not a reason to disable uniqueness. If the collection already has other data, inspect it first rather than deleting records to make this lab pass.

## Two editors can disagree

Imagine two people read revision 1. One changes the title, while another changes a summary. A blind replacement can erase the first person's change. A revision condition makes the conflict visible:

~~~javascript
db.lesson_identity.updateOne({ _id: "one", revision: 1 },
  { $set: { title: "Introduction to C", revision: 2 } })
~~~

A first matching update changes the record; repeating it should match zero documents because the revision is now 2. Read the returned matchedCount. Do not tell the user their edit was saved when nothing matched. [Conditional update operations](https://www.mongodb.com/docs/manual/reference/method/db.collection.updateOne/).

## Application exercise

Design a conflict message with three facts: the stored record changed, the local draft is preserved, and the user can review both. Umicom editing workflows should keep an unsaved draft while a conflict is resolved. A revision check does not merge text automatically, and a database uniqueness rule does not decide which of two differing drafts is correct.

Write down why an identifier and a revision solve different problems: the identifier chooses the record; the revision chooses the version the editor intended to change.

## Read the source

[Open the example source](https://www.mongodb.com/docs/manual/core/index-unique/).

## Continue learning

[Course contents](../../../courses/learning-nosql/index.html) · [Previous: Validate records and keep identity stable](04-validation-and-stable-identity.md) · [Next: Follow a database adapter lifetime in C](06-adapter-lifetime-in-c.md)
