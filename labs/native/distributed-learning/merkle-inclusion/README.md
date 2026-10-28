# Three-record Merkle inclusion lab

This C23 laboratory consumes the existing Umicom Framework Merkle and canonical SHA-256 sources from an independently checked-out Framework repository. It does **not** provide a second digest implementation, an application-local ledger engine or executable script.

Three **synthetic 32-byte digests** stand in for previously validated record-chain entries. The student proves inclusion of the second digest, holds the expected root separately, then flips one byte and confirms the altered leaf fails verification. The third leaf demonstrates the library's duplicate-last rule for odd layer widths; the final root commits to the exact leaf count.

A root is meaningful only if it comes from an independently trusted anchor. It does not provide author signatures, transaction validity, irreversible distributed finality, proof of model quality or permission to disclose confidential data. For full blockchain understanding, also study the consensus and governance lessons in the Blockchain Technology and Distributed Ledgers course.

Licence: MIT · Author: Sammy Hegab, Umicom Foundation.
