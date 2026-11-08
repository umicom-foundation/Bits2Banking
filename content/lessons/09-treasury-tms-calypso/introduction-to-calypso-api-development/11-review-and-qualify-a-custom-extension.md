# Review and qualify a custom extension

## Assemble an evidence package

A useful extension review identifies what was built and what was actually exercised. A source listing without its SDK identity is difficult to reproduce. A green unit test without a server environment says little about integration.

For this module, collect the Java source revision, Calypso release and patch, JDK identity, approved JAR hashes, compiler output and an environment label. Keep credentials, client names and trade details outside public teaching material.

## Read-only capstone

1. Select three approved sandbox trade IDs.
2. Confirm the adapter's input checks before any remote calls.
3. Read identities using a host-owned DSConnection.
4. Compare each identity with an authorized application view.
5. Exercise one missing-record case and one controlled service failure.
6. Verify that the host connection remains usable afterward.
7. Record which checks executed, failed, skipped or remain unexecuted.

Never replace an unavailable-server result with a successful fake-repository result. The latter belongs in a separate unit-test report.

## Deployment reasoning

The supplied classic guide discusses older application-server packaging. Current Calypso education describes newer architecture variants, so do not apply a classic WAR instruction to an unidentified modern installation. Use the release's approved deployment procedure, a rollback package and controlled configuration changes. This course does not install an extension or authorize live trade writes.

## Exercise and answer

A package compiles and loads, but its query is rejected by permissions. Is deployment complete? Answer: the binary and loading steps have evidence, while the requested workflow remains unqualified. Record the rejection and resolve the authorized role or design; do not bypass permissions.

## Source perspective

[Nasdaq Calypso core architecture training](https://calypsoeducation.nasdaq.com/courses/102-calypso-core-architecture-1) describes release-specific platform architecture. It does not supply the exact licensed API signatures used by this adapter. The supplied developer guide and your matching SDK remain the technical sources for those calls.

Continue by implementing one verified business-field mapping, with explicit units and failure cases. Event engines, task scheduling and writing workflows need their own qualification; they are not completed by this read-only capstone.

[Course contents](index.md)
