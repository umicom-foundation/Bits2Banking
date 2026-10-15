# Major Update 43 — Technical overview

**Title:** Secure Remote Administration, Network Services and Native C23 Remote-Access Review  
**Author / organisation:** Sammy Hegab · Umicom Foundation  
**Date:** 15 October 2026  
**Engineering policy:** C23 / Assembly first; reusable functionality in Umicom Framework after approved architecture review; PowerShell only for interactive instructions.

## Scope and structure

The System Administration course advances from Chapter 72 to **84** through twelve distinct lessons on remote administration, TCP listeners, SSH identities, public/private keys, service principals, firewalls, DNS/routing, TLS, safe SFTP, configuration, incident evidence and an integrated capstone. Five video scripts, seven editable SVG diagrams, glossary, workbook, instructor guide and command reference support the chapters.

Engineering Chapters **304–307** explain the actual C23 adapter and its security limitations. The `labs/native/remote-access-review` module links the previous `btb-deployment-review-lib`, inheriting the earlier maintenance, readiness and evidence contracts. There is no second implementation of those contracts, no authentication stack, and no new scripting-language implementation.

## C23 API and ownership

Header: `remote_access_review.h`; implementation: `remote_access_review.c`.

- `BtbRemoteInit` checks the bounded plan, verifies source-revision equality, and copies a valid upstream `BtbDeploymentReview` snapshot.
- `BtbRemoteAttach` validates and copies one fictional observation. It rejects repeated evidence attachment and source-revision mismatch without changing existing state.
- `BtbRemoteEvaluate` calls the existing `BtbDeploymentEvaluate` and returns one immutable `BtbRemoteDecision`. A malformed plan, observation or upstream review refuses output mutation.
- `REVIEWABLE` indicates only that all *supplied fictional evidence flags* are set and the upstream teaching deployment is qualified. It is **not a production permission, identity proof, host-key validation or remote login approval**.
- `BLOCKED`, `PENDING`, `RESTORED_ONLY` and missing-evidence bits distinguish failures, incomplete reviews and recovery without false promotion.

All records are passed as caller-owned values. There is no heap ownership transfer, background thread, real file I/O, socket, SSH login, credential access, OS service start/stop, remote deployment, firewall control or Git change. The lab's time values and identity labels are external claims; it performs neither clock validation nor independent verification of their provenance.

## What belongs in Umicom Framework later

Real identity/authentication, capability-based authorisation, secure configuration, platform trust stores, TLS/SSH adapters, audit storage, network process supervision and remote service operations must use already existing Framework services or an approved extension in C23/Assembly. Bits2Banking owns only the instructional model and its reproducible tests. Umicom Kernel and Umicom OS are not modified in this batch.

## Validation boundary

In the reference Linux environment, the complete composed GCC suite produced **101/101 passing tests** and the Clang ASan/UBSan suite also produced **101/101 passing tests**, including 22 new tests/demo and 79 inherited cases. GCC static analysis of the new policy translation unit reported no diagnostics. SVGs were generated in an editable vector format and XML-parsed. The offline 84-chapter HTML was generated from the previous 72-chapter HTML plus new content, preserving the 72 previous articles exactly.

**Not verified:** Windows UCRT64 acceptance, end-to-end MkDocs site publishing, real SSH/TLS/fingerprint checks, real user authorisation, production service readiness and any production deployment. These must never be inferred from the C23 classroom suite.
