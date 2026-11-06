# A service boundary before an API call

[Course contents](index.md) · [Next: A Java port and a fake repository](02-a-java-port-and-a-fake-repository.md)

## What an API lets a program ask

An application programming interface is a documented way for one program component to request something from another. In a treasury system, a request might ask for a trade or submit a permitted workflow action. An API is not permission to bypass the system's business rules.

First complete the introductory treasury lessons: trade, book, currency, value date and status. For practical Java examples, complete classes, methods and exceptions in Learning Java. This opening lesson needs only a diagram and a notebook.

Umicom treasury training separates business services from the repository interface they use. The data server owns treasury persistence. The key learning point is ownership: integrations should use supported services rather than directly changing tables behind the application's workflow.

```text
Umicom application -> Framework integration contract
                               |
                               v
                    version-specific Java adapter
                               |
                               v
                    supported treasury service
```

## Prepare an environment inventory

1. Record the licensed system version and patch level.
2. Record the approved Java runtime and the SDK documentation location.
3. Identify a non-production environment and a read-only practice user.
4. Find the supported service for the operation and its permission requirements.
5. Identify logs and a contact for environment recovery before any later write exercise.

The examples here are original teaching interfaces informed by the provided training material. They are not vendor SDK signatures. Names seen in an older manual must be checked against the installed licensed version before use. We do not assume that one version's method name, classpath or deployment procedure works everywhere.

## Exercise

A query is slow. A developer proposes updating the database directly to change trade status. Why is that unrelated to fixing the query and potentially inconsistent?

## Explained answer

A status change can require validation, permission checks, events, transfers and audit records. Direct table changes can omit those consequences. First narrow and measure the read query; use a supported workflow service for any authorised state change. The same principle keeps Framework as the owner of shared Umicom behaviour.

## Continue learning

[Course contents](index.md) · [Next: A Java port and a fake repository](02-a-java-port-and-a-fake-repository.md)

[Browser edition](../../../courses/introduction-to-calypso-api-development/lessons/01-a-service-boundary-before-an-api-call.html)

## Read the related Umicom source

[Source and context](../sources-and-licensing.md). Follow the source and licensing notes before using vendor APIs.
