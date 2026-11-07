<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-nosql/07-connect-a-real-provider.md

PURPOSE:
Plan a real document-database provider

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Plan a real document-database provider

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

## Separate the two interfaces

The preceding lab demonstrates Framework's callback contract. A real provider must additionally speak the database protocol and handle errors, credentials, timeouts and rows. MongoDB's C driver provides libmongoc and uses libbson for BSON documents. BSON is a binary document representation. [C driver setup](https://www.mongodb.com/docs/languages/c/c-driver/current/get-started/).

Do not substitute query text into a raw JSON string using unchecked concatenation. Construct structured values with the driver's supported document API. Validate which operations an application is allowed to request before sending them.

## Design the adapter before implementing it

1. Name one initial use case: read lesson titles by a stable language filter.
2. Record the exact driver version, compiler and architecture used for the build. All linked libraries need compatible binaries.
3. Give open a credential reference rather than a password in a saved profile.
4. Resolve that reference through the approved credential service and configure the provider connection.
5. Give execute a bounded query operation and convert provider errors into Framework status plus a useful, redacted diagnostic.
6. Iterate rows with explicit limits and copy only data whose ownership the caller understands.
7. Close the cursor, collection, client and other owned resources on every successful or failed path, following the driver contract.
8. Test with a disposable database and explicit sample records before connecting production data.

Framework's current summary interface reports counts. A full lesson browser needs a suitable row/result contract as well. Advertising streaming or transactions without that implementation would mislead clients. Document these missing pieces on the integration task rather than simulating success.

## Failure table

| Event | User-facing result | Engineering evidence |
| --- | --- | --- |
| server unavailable | Connection could not be opened | endpoint class, timeout, redacted code |
| access denied | Account lacks access | operation type and permission failure |
| no match | No lessons found | successful query with zero rows |
| malformed document | Record cannot be displayed | field name and validation rule |

Never place passwords, access tokens or full private documents into an error log. The adapter should preserve enough evidence to diagnose the failure while keeping secret values outside application profiles.

Exercise: identify which responsibilities belong to Framework's shared adapter and which belong to a Studio lesson screen. The screen chooses and displays a workflow; it should not contain another implementation of the database protocol.

## Read the source

[Open the example source](https://www.mongodb.com/docs/languages/c/c-driver/current/get-started/).

## Continue learning

[Course contents](../../../courses/learning-nosql/index.html) · [Previous: Follow a database adapter lifetime in C](06-adapter-lifetime-in-c.md) · [Next: Review and extend an Umicom data feature](08-review-and-extend-a-data-feature.md)
