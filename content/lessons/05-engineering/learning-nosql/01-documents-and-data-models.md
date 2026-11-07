<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-nosql/01-documents-and-data-models.md

PURPOSE:
Documents, collections and the questions an application asks

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Documents, collections and the questions an application asks

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

## Begin with a useful question

Suppose a learning browser must show a lesson title, the languages it uses and whether a learner has bookmarked it. Write the question first: "Show bookmarked C lessons." A data model describes which facts are stored and how they relate. It is a design choice, not a picture of a screen.

A relational model organises rows and columns. A document model can group related values and lists. A key-value model looks up a value using one key. A graph describes connected entities and relationships. The word NoSQL covers several approaches; it does not choose the correct model for an application.

Consider this invented document. Read it without executing it yet:

~~~json
{
  "_id": "lesson-c-hello",
  "title": "Printing a message",
  "languages": ["C"],
  "bookmarked": true
}
~~~

Braces enclose the document. A name before a colon identifies a field. Text is quoted, a Boolean is true or false, and square brackets hold a list. The identifier is stable even if the title changes. In MongoDB, the _id field identifies a document uniquely within its collection. [Document creation and identity](https://www.mongodb.com/docs/manual/tutorial/insert-documents/).

## Design on paper

1. Draw a box for a lesson and write its identifier and title inside.
2. Add a list of languages.
3. Draw a separate learner box. A bookmark belongs to a learner, so placing it directly on a shared lesson would give every learner the same bookmark.
4. Move the bookmark to a learner-lesson relationship in your design.
5. Decide which question each collection answers before writing queries.

The four-field document is suitable for a single-user exercise. The relationship design is more suitable for a shared service. Neither arrangement alone provides login, permission checks or progress synchronisation.

## Follow Umicom's boundary

Framework's UmiDataConnectorFamily distinguishes relational, document, key-value, graph, column and time-series adapters. An application requests a connector rather than implementing every database protocol in its screen. The descriptor advertises capabilities, but a capability must be implemented and tested by its driver before a product can rely on it.

## Check your understanding

Why should a title not be the only identifier? Two lessons may share a title, and titles can be edited. What is missing for shared bookmarks? A learner identity and an access-controlled relationship. These answers explain why selecting a database is only part of application design.

## Read the source

[Open the example source](https://www.mongodb.com/docs/manual/tutorial/insert-documents/).

## Continue learning

[Course contents](../../../courses/learning-nosql/index.html) · [Next: Create and read a training document](02-create-and-read-a-document.md)
