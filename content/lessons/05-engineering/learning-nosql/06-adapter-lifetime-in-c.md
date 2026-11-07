<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-nosql/06-adapter-lifetime-in-c.md

PURPOSE:
Follow a database adapter lifetime in C

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Follow a database adapter lifetime in C

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

## What an adapter does

An adapter translates a common interface into a provider's operations. Framework defines open, execute and close callbacks. A callback is a function supplied for another component to call. The registry copies callback addresses and descriptive metadata. It borrows the driver's context, so that context must remain alive while its callbacks may run.

Open the connector-lifetime lab linked below. Its README contains complete PowerShell and Bash build steps for an installed Framework SDK. The driver is an in-memory teaching fixture; no database server, account or network connection is used.

## Trace the program

1. main creates a registry with capacity for one descriptor.
2. The descriptor advertises the document family and points to three functions in the lab.
3. open allocates a small connection object. Its pointer is returned through out_connection.
4. Framework copies the callbacks into the caller's handle.
5. The registry is destroyed. The handle remains usable because it does not point into the registry.
6. execute reports a bounded row count. It does not return actual documents.
7. close clears handle ownership before invoking the driver to free its connection.

A pointer is an address used to reach an object. free ends the allocated object's lifetime; it does not erase every copy of its address. A dangling pointer still holds an address but no longer refers to the live object it used to identify.

## Observe re-entry

The fixture close callback calls Framework close again on the same handle. This models a notification that triggers a second close request. The inner call sees a closed handle and returns. The expected release count is one. Moving invalidation after the callback would make the inner call observe the old open connection.

This is serial callback re-entry, not two threads running at once. The handle still needs owner-controlled serial access. Closing a handle concurrently with a running query requires a different synchronisation design.

## Check the ownership map

| Object | Owner | Ends when |
| --- | --- | --- |
| registry | main | registry_destroy |
| connection | driver | driver close |
| handle | main | end of its scope |
| driver context | main | after callbacks finish |

Exercise: draw arrows from the handle to the connection, callbacks and driver context. Cross out only the registry after its destruction. Explain why moving the driver context out of scope would still be unsafe.

## Read the source

[Open the example source](../../../../labs/framework/connector-lifetime/main.c).

## Continue learning

[Course contents](../../../courses/learning-nosql/index.html) · [Previous: Indexes, duplicate identities and concurrent edits](05-indexes-and-concurrent-edits.md) · [Next: Plan a real document-database provider](07-connect-a-real-provider.md)
