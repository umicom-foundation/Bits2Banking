<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-nosql/03-query-and-limit-results.md

PURPOSE:
Ask precise questions and limit the result

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Ask precise questions and limit the result

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

## A filter is a question

A filter is a document describing which records match. Prepare two records for this lesson, even if you skipped the previous one:

~~~javascript
db.lesson_query.updateOne({ _id: "c" },
  { $set: { title: "Learning C", language: "C", minutes: 20 } }, { upsert: true })
db.lesson_query.updateOne({ _id: "hdl" },
  { $set: { title: "A CPU simulation", language: "VHDL", minutes: 30 } }, { upsert: true })
db.lesson_query.find({ language: "C" }, { _id: 1, title: 1 }).limit(5)
~~~

The query selects the C record. The second document requests only identity and title. limit(5) bounds the number returned. A find operation returns a cursor, which manages reading the result rather than promising an entire in-memory array. [Query and cursor guide](https://www.mongodb.com/docs/manual/tutorial/query-documents/).

## Work through the result

1. Read both fixture titles to understand the data you inserted.
2. Run the filtered query. Expect the Learning C title.
3. Replace C with VHDL. Expect A CPU simulation.
4. Replace it with an unused value. An empty result is valid; it is different from a failed connection.
5. Remove the filter by using {} and observe both records, subject to the limit.

A small limit does not guarantee an inexpensive query: the database may still examine many records to find matching ones. Index choice and measurement become important when the dataset grows.

## Bring the idea into Framework

UmiDataConnectorQueryRequest carries query_text, read_only and row_limit. UmiDataConnectorQuerySummary reports row_count and has_more. These fields express an application request and result. The driver must enforce the limit and read-only policy. Merely setting a Boolean is not an access-control boundary against a driver or server that ignores it.

An application should handle three distinct results: matching records, no matching records and an error. In a lesson browser, show a helpful empty state for no matches, and a retryable connection message for an unavailable server. Do not display an error as an empty list of lessons.

## Exercise

Write down the fields needed for a search-results row. Keep lesson bodies and private learner data out of that row unless required. Explain how returning less data can reduce memory use, disclosure and screen clutter while leaving the full lesson available through a separate authorised request.

## Read the source

[Open the example source](https://www.mongodb.com/docs/manual/tutorial/query-documents/).

## Continue learning

[Course contents](../../../courses/learning-nosql/index.html) · [Previous: Create and read a training document](02-create-and-read-a-document.md) · [Next: Validate records and keep identity stable](04-validation-and-stable-identity.md)
