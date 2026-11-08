<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-wt/14-plan-bounded-work-and-session-lifetime.md

PURPOSE:
Plan bounded work across a session lifetime

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Plan bounded work across a session lifetime

## Before starting

Trace the current synchronous name-check lambda. It performs a small bounded C operation and updates widgets immediately. No background job is implemented in this lab. This lesson prepares an extension design without pretending that cancellation or asynchronous completion already exists.

## Describe a future operation

Suppose the form later asks Framework to inspect a large project. Define an operation identifier, a bounded input snapshot, status, progress and cancellation request. The service should own the operation data; the session should own presentation state. A worker must not borrow an input widget as its long-lived data source.

## Write the lifetime transitions

An operation may complete after the page closes or after a newer request replaces it. Before a result updates the view, the presentation layer must establish that the session still exists and that the result belongs to the current operation. Cancellation is a request, not proof that every resource has already been released.

~~~text
idle -> submitted -> running -> completed
                         |
                         +-> cancellation requested -> terminal result
view closed -> detach presentation; service still owns cleanup
~~~

## Choose explicit limits

Set a maximum input size, work budget or deadline and a limit on pending operations. Describe what the user sees when a limit is reached. A disabled button can reduce accidental duplicates, but the service still needs its own admission checks. Keep reusable scheduling and cancellation in Framework instead of reproducing them in each web callback.

## Review a proposed callback

A callback captures resultWidget and writes to it whenever work finishes. Identify the missing conditions: widget lifetime, operation identity and the toolkit-required session/event context. Do not approve the callback merely because it worked in a single quick run. Consult the selected Wt version before implementing a cross-thread handoff.

## Exercise and worked answer

The user starts inspection A, then inspection B. A finishes last and overwrites B. What identity check is missing? The completion handler must compare A's operation identifier with the currently displayed operation and refuse a stale presentation update. The service still records A's terminal outcome. This is a design exercise; it adds no asynchronous execution to the supplied lab.

## Read the source

[labs/framework/wt-profile/profile_application.cpp](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/profile_application.cpp). Use the matching local revision when working offline.

## Continue learning

[Course contents](../../../courses/learning-wt/index.html) · [Previous: Diagnose transport, resource and event failures](13-diagnose-http-and-event-failures.md) · [Next: Review deployment and shutdown as separate work](15-review-a-deployment-and-shutdown-plan.md)
