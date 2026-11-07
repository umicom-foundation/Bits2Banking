<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/16-distinguish-dispatch-from-delivery.md

PURPOSE:
Explain the lesson: Distinguish dispatch from delivery.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish dispatch from delivery

A server can finish an operation and still fail to deliver its reply. The caller then has an uncertain outcome, not proof that nothing happened.

## Prepare

Read the second Exchange call in exchange.c. It enables fail_write while leaving reading and routing unchanged.

The handler increments calls and prepares ready. The first attempted write then returns IO_ERROR.

## Predict the result

| Observation | Expected value |
| --- | --- |
| Handler calls | 1 |
| dispatched | true |
| response_complete | false |
| bytes sent | 0 |
| Overall result | IO_ERROR |

The two booleans answer different questions. Routing occurred; complete response delivery did not.

## Apply the idea

Imagine a handler that records a payment or adds a media job. Blindly repeating it after a lost reply could duplicate the operation. A production design needs an explicit duplicate-request policy and a way to inspect an operation's outcome.

This lab intentionally uses a counter so no external side effect occurs. It teaches the uncertainty before adding durable state.

## Exercise

Draw a timeline with request completion, handler entry, handler exit, write failure and cleanup. Mark the point after which automatic retry becomes an application policy decision.

## Recovery

Preserve the exchange result along with the status. Logging only IO_ERROR loses the useful distinction between a request that was never dispatched and one whose reply was lost.

For a real connection, the host must close the transport after either outcome. Framework borrows it; ownership remains with the host.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-http-contracts/exchange.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](15-handle-short-transfers.md)

