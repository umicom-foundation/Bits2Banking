# Process events without losing work

## Delivery and completion are different

An event tells an engine that something occurred. Receiving it does not mean your custom work has completed. The supplied classic guide describes custom engines derived from com.calypso.engine.Engine, an EngineContext initialization hook, processing of PSEvent and the RemoteTrade eventProcessed acknowledgement boundary.

Those names are useful evidence, but constructors, registration and deployment remain release-specific. Persistent and non-persistent subscriptions must not be confused.

## Design the state machine first

Consider an original outbound-report engine. It records a stable event key, creates an export and only then acknowledges the source event. Its durable states might be received, export-recorded and acknowledged. These are your integration states, not invented Calypso status values.

A crash after the export but before acknowledgement can cause replay. The destination must recognize the same stable event key and return the original outcome, rather than creating a duplicate report. Acknowledging before durable work instead risks permanent loss.

## Worked failure table

- Crash before export: replay must attempt the work.
- Crash after export, before acknowledgement: replay must find the prior export.
- Acknowledgement exception: retain the completed export and retry acknowledgement under a controlled policy.
- Export rejection: record refusal and follow the agreed operational policy; do not silently acknowledge success.

A single database transaction cannot automatically cover an external file server or remote API. Use a durable outbox or another explicitly reviewed coordination design where appropriate.

## Exercise and answer

The process method returns true after placing work in an in-memory queue. Power fails before the worker runs. What was lost? Answer: the source may regard processing as complete while the queued work never became durable. Successful queue insertion is not the same as completed business processing.

## Before writing the engine

Inspect the matching Engine and PSEvent declarations, persistent subscription configuration and eventProcessed signature. Use the guide to explain the lifecycle, then compile a release-specific implementation. No persistent-engine deployment or replay test has been run for this course.

[Course contents](index.md)
