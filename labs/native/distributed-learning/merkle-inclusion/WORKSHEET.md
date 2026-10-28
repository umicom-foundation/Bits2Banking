# Workbook — audit a batch of three synthetic receipts

**Bits to Banking · Sammy Hegab · Umicom Foundation · MIT**

This is an exercise for learners working with the Framework's shared native Merkle API, not maintainer instructions or a new language runtime.

## Experiment A: membership

Represent three *previously hashed* records with 32 bytes each. Construct the native Merkle root and a proof for zero-based leaf index 1. Explain which sibling comes first and why the final root binds the exact leaf count. Predict the result before executing the C23 lab.

## Experiment B: mutation and false anchors

Change one byte of the second digest. Verify against the ORIGINAL independently known root; observe rejection. Now imagine an attacker replaces both the digest list and the claimed root. Explain why the forged copy can be self-consistent and why an independent trusted anchor is essential.

## Experiment C: application semantics

Invent three synthetic decisions: ACCEPT, REJECT, CANCEL. All decisions may be present in an honest audit, but only independently valid accepted updates can enter a federated aggregate. Draw a table separating four predicates: inclusion, authenticated identity, active authorisation and held-out model usefulness. State the result of each predicate or write “not checked”.

## Expected reasoning

A valid inclusion proof establishes membership of a byte commitment in a specified snapshot. It does not reveal or validate the training data, establish blockchain consensus, authorise a banking transaction or certify model quality. Under the duplicate-last scheme, proofs for odd counts must follow the published canonical encoding and final root must bind the original count.
