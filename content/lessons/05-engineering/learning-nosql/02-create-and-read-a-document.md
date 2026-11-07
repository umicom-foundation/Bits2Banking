<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-nosql/02-create-and-read-a-document.md

PURPOSE:
Create and read a training document

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Create and read a training document

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

## What this lab changes

This lab writes one invented record to the lesson_create collection in the training database. The method updateOne receives a filter, a change and an option. The filter locates the identifier; $set supplies values; upsert permits creation when no document matches. [UpdateOne reference](https://www.mongodb.com/docs/manual/reference/method/db.collection.updateOne/).

At the mongosh prompt run:

~~~javascript
db.lesson_create.updateOne(
  { _id: "c-hello" },
  { $set: { title: "Printing a message", language: "C", minutes: 15 } },
  { upsert: true }
)
db.lesson_create.findOne({ _id: "c-hello" })
~~~

1. Confirm the prompt uses bits2banking_learning.
2. Paste the complete update command, including matching braces and parentheses.
3. Read the acknowledgement. The first run can report an inserted identifier; another run can report a match with no changed values.
4. Read the returned document and identify each field.
5. Run the update again. The same _id selects the same document. This is intentional repeatability for a small exercise.

An acknowledgement is the server's report for this operation. It does not prove that a whole application workflow, backup or second service completed.

## Make one controlled change

Change minutes from 15 to 20 and repeat the update. Read the record again. The expected document has the same identity and new duration. A duration is stored as a number; writing "20" creates text instead, which can behave differently in comparisons.

## Explain the punctuation

A dot selects a collection or method. Parentheses pass arguments to a method. Commas separate fields and arguments. The outer command is mongosh's JavaScript interface; the document itself contains data. It is not C source and should not be pasted into a C compiler.

## Recovery and extension

If a quote is left open, cancel the unfinished input and paste the complete command again. If a command targets an unexpected database, stop and check its name before writing. For an exercise, add a summary field with a short explanation in your own words. Read it back and check that title and identity still exist.

A real Umicom lesson catalogue would validate incoming records and decide which user may change them. This exercise teaches storage operations, not a complete catalogue or authentication service.

## Read the source

[Open the example source](https://www.mongodb.com/docs/manual/reference/method/db.collection.updateOne/).

## Continue learning

[Course contents](../../../courses/learning-nosql/index.html) · [Previous: Documents, collections and the questions an application asks](01-documents-and-data-models.md) · [Next: Ask precise questions and limit the result](03-query-and-limit-results.md)
