<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/59-interpret-a-retained-chain-head.md

PURPOSE:
Explain the lesson: Interpret a retained chain head.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Interpret a retained chain head

## Prepare

Open labs/native/framework-hash/main.c and its README. The lab links an installed Umicom Framework SDK through Umicom::base; use the documented CMake prefix for your SDK. Read base/sha256.h alongside the consumer before compiling.

## Understand the idea

Chain compares a recomputed head with a retained expected head. Altering an earlier record changes the demonstrated result. This illustrates integrity relative to a trusted reference, not authentication or network consensus.

## Work through the example

Trace the two-record chain, change amount twenty-five to twenty-six, then recompute. Ask what happens if an attacker can replace both records and the retained reference.

## Check your reasoning

The demonstration detects the changed history only against the unchanged reference. Replacing the reference removes that comparison's trust anchor.

## If something differs

If building a ledger, separately design authorization, durable storage, replay rules and consensus where needed. A chain of hashes alone supplies none of those policies.


## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-hash/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](58-separate-hash-domains.md)


[Next: Introduce byte token identities](60-introduce-byte-token-identities.md)
