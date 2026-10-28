# Blockchain Technology and Distributed Ledgers — Lesson 028: Distinguish signatures from authenticated channels

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English  
**Study route:** Blockchain Technology and Distributed Ledgers · **Method:** reason → compute → test → qualify

## Learning objective

TLS can protect a connection; digital signatures can provide portable statement attribution under key governance; HMAC requires shared-secret trust. None establish economic consensus by themselves.

By the end of the lesson, a learner should be able to distinguish what the method mathematically establishes from what its security or distributed-systems context still requires. The objective is to explain the mechanism, reproduce the worked argument and recognise an invalid inference.

## Mechanism and architecture

TLS can protect a connection; digital signatures can provide portable statement attribution under key governance; HMAC requires shared-secret trust. None establish economic consensus by themselves. Consider the boundaries of **data identity**, **computation**, **trust** and **governance** independently. When several computers contribute to a model or ledger, the system must identify the exact input revision, define the legal operation, check the output against an independently fixed reference and record which entity has authority to accept the transition.

A hash or signature secures a *statement about bytes and keys*; a numerical test constrains a *calculation*; a protocol governs *who may decide*; and an independent benchmark measures *whether the model is useful*. These statements are complementary, not interchangeable. A transparent experiment separates claims from measured outcomes.

## Worked case

A worker sends a message over TLS to a server, but a later independent auditor needs proof of who approved the publication decision.

**Interpretation.** The worked result is a defined calculation or carefully bounded scenario. It does not assert an observed speedup, network finality, legal authorisation or a trained production model. When interpreting a number, state its denominator, units, assumptions and the exact predicate being checked.

## Practical native engineering exercise

Study Framework identity/authorisation and signature records without claiming deployed PKI.

A safe experiment uses **synthetic or explicitly authorised inputs**, checks every buffer bound, preserves independent reference results and records both expected-success and deliberate-rejection cases. Implement reusable operations in Umicom Framework C23/Assembly first; an application or course laboratory consumes the published API rather than maintaining a second implementation of its mathematics or hashing.

## Independent exercise

**Question:** Which artefact is more portable for independent audit?

<details><summary>Reveal a worked answer</summary>

A separately verified signed statement plus trusted signer registry and timestamp/sequence evidence.

</details>

## Security, scientific and governance limits

Signature verification cannot prove computation honesty or transaction validity.

The small experiments in this course do not establish a deployed blockchain, secure multiparty computation, real Internet-scale learning, a signed identity infrastructure or superior model quality unless a separate qualification specifically measures that property. **Honest negative results are valuable evidence.**

## Primary research and technical reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)
- [Hyperledger Fabric transaction flow](https://hyperledger-fabric.readthedocs.io/en/latest/txflow.html)
- [Ethereum Proof of Stake](https://ethereum.org/developers/docs/consensus-mechanisms/pos/)

## Continue learning

- [Previous lesson](027-understand-selective-disclosure-and-private-metadata.md)
- [Next lesson](029-explain-leader-changes-in-crash-tolerant-replication.md)
- [Browser lesson](../../courses/blockchain-ledgers/lessons/028-distinguish-signatures-from-authenticated-channels.html)
- [Complete study route](../../courses/blockchain-ledgers/state-consensus-and-audit-anchors.html)

*Service to Many Leads to Greatness.*
